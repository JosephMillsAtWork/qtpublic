/*
* Joseph Mills
*/

#ifndef MANGOTEMPORARYFILE_H
#define MANGOTEMPORARYFILE_H

#include <QTemporaryFile>
#include "mangofile.h"

class MangoTemporaryFile : public QTemporaryFile
{
    Q_OBJECT
    Q_PROPERTY(QString fileName READ fileName NOTIFY fileChanged)

public:
    explicit MangoTemporaryFile(QObject *parent = 0);

    Q_INVOKABLE bool autoRemove() const { return QTemporaryFile::autoRemove(); }
    Q_INVOKABLE void setAutoRemove(bool b) { return QTemporaryFile::setAutoRemove(b); }

    // ### Hides open(flags)
    Q_INVOKABLE bool open() {
        bool retval = QTemporaryFile::open(QIODevice::ReadWrite);
        emit fileChanged();
        return retval;
    }

    Q_INVOKABLE QString fileName() const { return QTemporaryFile::fileName(); }
    Q_INVOKABLE QString fileTemplate() const { return QTemporaryFile::fileTemplate(); }
    Q_INVOKABLE void setFileTemplate(const QString &name) { QTemporaryFile::setFileTemplate(name); }


    // Generic File functions
    Q_INVOKABLE virtual void close() { return QTemporaryFile::close(); }

    Q_INVOKABLE void setTextModeEnabled(bool enabled) { return QTemporaryFile::setTextModeEnabled(enabled); }
    Q_INVOKABLE bool isTextModeEnabled() const { return QTemporaryFile::isTextModeEnabled(); }

    Q_INVOKABLE bool isOpen() const { return QTemporaryFile::isOpen(); }
    Q_INVOKABLE bool isReadable() const { return QTemporaryFile::isReadable(); }
    Q_INVOKABLE bool isWritable() const { return QTemporaryFile::isWritable(); }
    Q_INVOKABLE virtual bool isSequential() const { return QTemporaryFile::isSequential(); }

    Q_INVOKABLE qint64 pos() const { return QTemporaryFile::pos(); }
    Q_INVOKABLE bool seek(qint64 offset) { return QTemporaryFile::seek(offset); }
    Q_INVOKABLE bool atEnd() const { return QTemporaryFile::atEnd(); }
    Q_INVOKABLE bool flush() { return QTemporaryFile::flush(); }
    Q_INVOKABLE virtual bool reset() { return QTemporaryFile::reset(); }

    Q_INVOKABLE uchar *map(qint64 offset, qint64 size, MemoryMapFlags flags = NoOptions) {
        return QTemporaryFile::map(offset,size, flags);
    }

    Q_INVOKABLE bool unmap(uchar *address) {
        return QTemporaryFile::unmap(address);
    }

    Q_INVOKABLE virtual qint64 bytesAvailable() const { return QTemporaryFile::bytesAvailable(); }
    Q_INVOKABLE virtual qint64 bytesToWrite() const { return QTemporaryFile::bytesToWrite(); }


    Q_INVOKABLE qint64 read(char *data, qint64 maxlen) { return QTemporaryFile::read(data,maxlen); }
    Q_INVOKABLE QByteArray read(qint64 maxlen) { return QTemporaryFile::read(maxlen); }
    Q_INVOKABLE QByteArray readAll() { return QTemporaryFile::readAll(); }
    Q_INVOKABLE qint64 readLine(char *data, qint64 maxlen) { return QTemporaryFile::readLine(data, maxlen); }
    Q_INVOKABLE QByteArray readLine(qint64 maxlen = 0) { return QTemporaryFile::readLine(maxlen); }
    Q_INVOKABLE virtual bool canReadLine() const { return QTemporaryFile::canReadLine(); }

    Q_INVOKABLE qint64 write(const char *data, qint64 len) { return QTemporaryFile::write(data, len); }
    Q_INVOKABLE qint64 write(const char *data) { return QTemporaryFile::write(data); }
    Q_INVOKABLE inline qint64 write(const QByteArray &data)
    { return write(data.constData(), data.size()); }

    Q_INVOKABLE qint64 peek(char *data, qint64 maxlen) { return QTemporaryFile::peek(data,maxlen); }
    Q_INVOKABLE QByteArray peek(qint64 maxlen) { return QTemporaryFile::peek(maxlen); }

    Q_INVOKABLE virtual bool waitForReadyRead(int msecs) { return QTemporaryFile::waitForReadyRead(msecs); }
    Q_INVOKABLE virtual bool waitForBytesWritten(int msecs) { return QTemporaryFile::waitForBytesWritten(msecs); }

    Q_INVOKABLE void ungetChar(char c) { return QTemporaryFile::ungetChar(c); }
    Q_INVOKABLE bool putChar(char c) { return QTemporaryFile::putChar(c); }
    Q_INVOKABLE bool getChar(char *c) { return QTemporaryFile::getChar(c); }

    Q_INVOKABLE QString errorString() const { return QTemporaryFile::errorString(); }

    Q_INVOKABLE bool exists() const { return QTemporaryFile::exists(); }

    Q_INVOKABLE QString readLink() const { return QTemporaryFile::readLink(); }
    Q_INVOKABLE inline QString symLinkTarget() const { return readLink(); }

    Q_INVOKABLE qint64 size() const { return QTemporaryFile::size(); }
    Q_INVOKABLE bool resize(qint64 sz) { return QTemporaryFile::resize(sz); }
    Q_INVOKABLE Permissions permissions() const { return QTemporaryFile::permissions(); }
    Q_INVOKABLE bool setPermissions(Permissions permissionSpec) { return QTemporaryFile::setPermissions(permissionSpec); }

signals:
    void fileChanged();

};

#endif // MANGOTEMPORARYFILE_H
