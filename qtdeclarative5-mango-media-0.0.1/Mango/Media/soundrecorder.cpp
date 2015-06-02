#include "soundrecorder.h"
#include <QFile>
/*!
  \qmltype SoundRecorder
  \inqmlmodule Mango 0.1
  \ingroup Mango
  \inherits Item
  \since 5.3
  \b{ WARNING this is broken and only works once. Need to add to a loop so that it will not freeze up after stopping and starting a new recording  Will Doc Better After the Bugs are FIXED }
 */

SoundRecorder::SoundRecorder(QObject *parent) :
    QObject(parent),
    m_codec("audio/FLAC"),
    m_quality(0),
    m_volume(100),
    m_state(QMediaRecorder::StoppedState),
    m_error(QMediaRecorder::ResourceError)
{
    audioRecorder = new QAudioRecorder;

    connect(audioRecorder, SIGNAL(durationChanged(qint64)), this,
            SLOT(_q_durationChanged()));
    connect(audioRecorder, SIGNAL(stateChanged(QMediaRecorder::State)), this,
            SLOT(_q_stateChanged()));
    connect(audioRecorder, SIGNAL(error(QMediaRecorder::Error)), this,
            SLOT(_q_error()));
}

void SoundRecorder::_q_error()
{
   m_error = audioRecorder->error();
   m_errorString = audioRecorder->errorString();

   emit errorChanged();
}

SoundRecorder::Error SoundRecorder::error() const
{
    return Error(m_error);
}

QString SoundRecorder::errorString() const
{
    return m_errorString;
}

void SoundRecorder::_q_stateChanged()
{
    const QMediaRecorder::State oldState = m_state;
    const QMediaRecorder::State state = audioRecorder->state();

    m_state = audioRecorder->state();

    if (state != oldState) {
        switch (state) {
            case QMediaRecorder::StoppedState:
                emit stopped();
                break;
            case QMediaRecorder::RecordingState:
                if (oldState == QMediaRecorder::PausedState) {
                    emit resumed();
                    break;
                } else {
                    emit recording();
                    break;
                }
            case QMediaRecorder::PausedState:
                emit paused();
                break;
            }

        emit stateChanged();
    }
}

SoundRecorder::State SoundRecorder::state() const
{
    return State(m_state);
}

QString SoundRecorder::path() const
{
    return m_path;
}

void SoundRecorder::setPath(const QString &path)
{
    if (m_path == path)
        return;
    m_path = path;
    emit pathChanged();
}

QString SoundRecorder::codec() const
{
    return m_codec;
}

void SoundRecorder::setCodec(const QString &codec)
{
    if (m_codec == codec)
        return;

    m_codec = codec;
    emit codecChanged();
}

int SoundRecorder::quality() const
{
    return m_quality;
}

void SoundRecorder::setQuality(const int &quality)
{
    if (m_quality == quality)
        return;

    m_quality = quality;
    emit qualityChanged();
}

qreal SoundRecorder::volume() const
{
    return m_volume;
}

void SoundRecorder::setVolume(const qreal &volume)
{
    if (m_volume == volume)
        return;

    m_volume = volume;
    emit volumeChanged();
}

qint64 SoundRecorder::duration() const
{
    return m_duration;
}

void SoundRecorder::_q_durationChanged()
{
    m_duration = audioRecorder->duration();
    emit durationChanged();
}

SoundRecorder::~SoundRecorder()
{
    delete audioRecorder;
}

void SoundRecorder::start() //TODO: reduce noise settings
{
    if (audioRecorder->state() == QMediaRecorder::StoppedState) {
        QAudioEncoderSettings audioSettings;

        // Set codec
        audioSettings.setCodec(m_codec);

        // Set quality: 0=VeryLow, 1=Low, 2=Normal, 3=High, 4=VeryHigh
        audioSettings.setEncodingMode(QMultimedia::ConstantQualityEncoding);
        audioSettings.setQuality(QMultimedia::EncodingQuality(m_quality));

        if (audioSettings.codec() == "audio/PCM" || "audio/FLAC") {
            audioSettings.setSampleRate(-1);

            if (m_quality == 0)
                {audioSettings.setSampleRate(8000);}

            if (m_quality == 1)
                {audioSettings.setSampleRate(16000);}

            if (m_quality == 2)
                {audioSettings.setSampleRate(22050);}

            if (m_quality == 3)
                {audioSettings.setSampleRate(44100);}

            if (m_quality == 4)
                {audioSettings.setSampleRate(88200);}
            }

        audioRecorder->setEncodingSettings(audioSettings);

        audioRecorder->setContainerFormat(getContainerFromCodec(m_codec));

        // Set volume
        audioRecorder->setVolume(m_volume);

        // Set output location
        cPath = "/home/joseph/.qt-googlevoice/output.flac";//m_path + getExtensionFromCodec(m_codec);
//        QFile f;
//        f = "/home/joseph/.qt-googlevoice/output.flac";
//        if (f.is){
//            f.remove();
//        }


        audioRecorder->setOutputLocation(QUrl(cPath));

        audioRecorder->record();
    }
}

QString SoundRecorder::getFilePath()
{
    return cPath;
}

void SoundRecorder::stop()
{
    if (audioRecorder->state() == QMediaRecorder::RecordingState ||
            audioRecorder->state() == QMediaRecorder::PausedState) {

        audioRecorder->stop();
    }
}

void  SoundRecorder::pause()
{
    if (audioRecorder->state() == QMediaRecorder::RecordingState) {
        audioRecorder->pause();
    }
}

void SoundRecorder::resume()
{
    if (audioRecorder->state() == QMediaRecorder::PausedState) {
        audioRecorder->record();
    }
}

// It parses codec name to get the corrisponding container
QString SoundRecorder::getContainerFromCodec(QString codec)
{
    QString container = "";

    if (codec == "audio/vorbis")
        { container = "ogg";}

    if (codec == "audio/PCM")
        { container = "wav";}

    if (codec == "audio/FLAC")
        { container = "raw";}

    if (codec == "audio/AMR")
        { container = "amr";}

    if (codec == "audio/mpeg")
        { container = "raw";}

    return container;
}

// It parses codec name to get the corrisponding extension
QString SoundRecorder::getExtensionFromCodec(QString codec)
{
    QString extension = "";

    if (codec == "audio/vorbis")
        { extension = ".ogg";}

    if (codec == "audio/PCM")
        { extension = ".wav";}

    if (codec == "audio/FLAC")
        { extension = ".flac";}

    if (codec == "audio/AMR")
        { extension = ".amr";}

    if (codec == "audio/mpeg")
        { extension = ".mp3";}

    return extension;
}

QStringList SoundRecorder::getSupportedCodecs()
{
    QStringList allSupportedCodecs = audioRecorder->supportedAudioCodecs();
    QStringList codecsList;

    foreach (QString codec, allSupportedCodecs) {
        if (codec.contains("audio/mpeg", Qt::CaseInsensitive) == true)
            {codecsList << codec;}
        if (codec.contains("audio/vorbis", Qt::CaseInsensitive) == true)
            {codecsList << codec;}
        if (codec.contains("audio/FLAC", Qt::CaseInsensitive) == true)
            {codecsList << codec;}
        if (codec.contains("audio/PCM", Qt::CaseInsensitive) == true)
            {codecsList << codec;}
        if (codec.contains("audio/AMR", Qt::CaseInsensitive) == true)
            {codecsList << codec;}
    }

    return codecsList;
}
