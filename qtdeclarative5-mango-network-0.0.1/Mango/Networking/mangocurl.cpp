#include "mangocurl.h"
#include <iostream>

#include <QUrl>
#include <QDebug>
#include <QTextCodec>
#include <QStringList>


CURLcode curlGlobalInit() {
    return curl_global_init(CURL_GLOBAL_ALL);
}


int writer(char* data, size_t size, size_t nmemb, std::string* buffer) {
    // What we will return
    int result = 0;

    // Is there anything in the buffer?
    if (buffer != NULL) {
        // Append the data to the buffer
        buffer->append(data, size * nmemb);

        // How much did we write?
        result = size * nmemb;
    }

    return result;
}


#ifdef MANGOCURL_DEBUG
int trace(CURL *handle, curl_infotype type, unsigned char *data, size_t size, void *userp)
{
    std::cerr<< data << std::endl;
    return 1;
}
#endif


MangoCUrl::MangoCUrl(): _textCodec(0) {
    /*
     * It's necessarily to call curl_global_init ones before the first use
     * of curl_easy_init.
     *
     * http://curl.haxx.se/libcurl/c/curl_easy_init.html
     */
    static CURLcode __global = curlGlobalInit();
    Q_UNUSED(__global)

    _curl = curl_easy_init();
    _errorBuffer = new char[CURL_ERROR_SIZE];
}


MangoCUrl::~MangoCUrl() {
    while(_slist.count()) {
        curl_slist_free_all(_slist.first());
        _slist.removeFirst();
    }
    curl_easy_cleanup(_curl);
    delete[] _errorBuffer;
}


void MangoCUrl::setTextCodec(const char* codecName)	{
    _textCodec = QTextCodec::codecForName(codecName);
}


void MangoCUrl::setTextCodec(QTextCodec* codec) {
    _textCodec = codec;
}

QString MangoCUrl::exec(Options& opt) {
    setOptions(opt);
    _lastCode = Code(curl_easy_perform(_curl));
    const char* reply = opt[CURLOPT_WRITEDATA].value<std::string*>()->c_str();

    if (_textCodec) {
        return _textCodec->toUnicode(reply);
    }

    return reply;
}


void MangoCUrl::setOptions(Options& opt) {
    Options defaults;
    defaults[CURLOPT_FAILONERROR] = true;
    defaults[CURLOPT_ERRORBUFFER].setValue(_errorBuffer);
    defaults[CURLOPT_WRITEFUNCTION].setValue(&writer);
    defaults[CURLOPT_WRITEDATA].setValue(&_buffer);

#ifdef MANGOCURL_DEBUG
    curl_easy_setopt(_curl, CURLOPT_VERBOSE, 1);
    curl_easy_setopt(_curl, CURLOPT_DEBUGFUNCTION, trace);
#endif

    OptionsIterator i(defaults);

    while (i.hasNext()) {
        i.next();

        if (! opt.contains(i.key())) {
            opt[i.key()] = i.value();
        }
    }

    i = opt;

    while (i.hasNext()) {
        i.next();
        QVariant value = i.value();

        switch (value.type()) {
            case QVariant::Bool:
            case QVariant::Int: {
                int val = value.toInt();
                curl_easy_setopt(_curl, i.key(), val);
                break;
            }
            case QVariant::ByteArray: {
                QByteArray ba = value.toByteArray();
                curl_easy_setopt(_curl, i.key(), ba.constData());
                break;
            }
            case QVariant::Url: {
                QByteArray ba = value.toUrl().toEncoded();
                curl_easy_setopt(_curl, i.key(), ba.constData());
                break;
            }
            case QVariant::String: {
                std::string str = value.toString().toStdString();
                curl_easy_setopt(_curl, i.key(), str.c_str());
                break;
            }
            case QVariant::ULongLong: {
                qulonglong val = value.toULongLong();
                curl_easy_setopt(_curl, i.key(), (void*) val);
                break;
            }
            case QVariant::StringList: {
                struct curl_slist *slist = NULL;
                foreach (const QString &tmp, value.toStringList()) {
                     slist = curl_slist_append(slist, tmp.toUtf8().data());
                }
                _slist.append(slist);
                curl_easy_setopt(_curl, i.key(), slist);
                break;
            }
            default:
                const QString typeName = value.typeName();

                if (typeName == "MangoCUrl::WriterPtr") {
                    curl_easy_setopt(_curl, i.key(), value.value<WriterPtr>());
                }
                else if (typeName == "std::string*") {
                    curl_easy_setopt(_curl, i.key(), value.value<std::string*>());
                }
                else if (typeName == "char*") {
                    curl_easy_setopt(_curl, i.key(), value.value<char*>());
                }
                else {
                    qDebug() << "[MangoCUrl] Unsupported option type: " << typeName;
                }
        }
    }
}
