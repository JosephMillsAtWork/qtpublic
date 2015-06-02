/*
 * Joseph Mills
 */
#ifndef MangoSAVEFILE_H
#define MangoSAVEFILE_H

#include <QSaveFile>
#include "mangofile.h"

class MangoSaveFile : public QSaveFile
{
    Q_OBJECT
    Q_PROPERTY(QString fileName READ fileName WRITE setFileName NOTIFY fileNameChanged)
    Q_ENUMS( OpenModeFlag OpenMode Permissions FileError FileHandleFlag MemoryMapFlags )

public:
    explicit MangoSaveFile(QObject *parent = 0);

    Q_INVOKABLE bool open() { return QSaveFile::open(QIODevice::WriteOnly); }

    /* --- QSaveFile specific functions --- */

    Q_INVOKABLE bool commit() {
        return QSaveFile::commit();
    }

    Q_INVOKABLE void cancelWriting() {
        QSaveFile::cancelWriting();
    }

    Q_INVOKABLE void setDirectWriteFallback(bool enabled) {
        QSaveFile::setDirectWriteFallback(enabled);
    }

    Q_INVOKABLE bool directWriteFallback() const {
        return QSaveFile::directWriteFallback();
    }

    /* Other methods */


    Q_INVOKABLE void setTextModeEnabled(bool enabled) { return QSaveFile::setTextModeEnabled(enabled); }
    Q_INVOKABLE bool isTextModeEnabled() const { return QSaveFile::isTextModeEnabled(); }

    Q_INVOKABLE bool isOpen() const { return QSaveFile::isOpen(); }
    Q_INVOKABLE bool isReadable() const { return QSaveFile::isReadable(); }
    Q_INVOKABLE bool isWritable() const { return QSaveFile::isWritable(); }
    Q_INVOKABLE virtual bool isSequential() const { return QSaveFile::isSequential(); }

    Q_INVOKABLE qint64 pos() const { return QSaveFile::pos(); }
    Q_INVOKABLE bool seek(qint64 offset) { return QSaveFile::seek(offset); }
    Q_INVOKABLE bool atEnd() const { return QSaveFile::atEnd(); }
    Q_INVOKABLE bool flush() { return QSaveFile::flush(); }
    Q_INVOKABLE virtual bool reset() { return QSaveFile::reset(); }

    Q_INVOKABLE uchar *map(qint64 offset, qint64 size, MemoryMapFlags flags = NoOptions) {
        return QSaveFile::map(offset,size, flags);
    }

    Q_INVOKABLE bool unmap(uchar *address) {
        return QSaveFile::unmap(address);
    }

    Q_INVOKABLE virtual qint64 bytesAvailable() const { return QSaveFile::bytesAvailable(); }
    Q_INVOKABLE virtual qint64 bytesToWrite() const { return QSaveFile::bytesToWrite(); }

    Q_INVOKABLE qint64 read(char *data, qint64 maxlen) { return QSaveFile::read(data,maxlen); }
    Q_INVOKABLE QByteArray read(qint64 maxlen) { return QSaveFile::read(maxlen); }
    Q_INVOKABLE QByteArray readAll() { return QSaveFile::readAll(); }
    Q_INVOKABLE qint64 readLine(char *data, qint64 maxlen) { return QSaveFile::readLine(data, maxlen); }
    Q_INVOKABLE QByteArray readLine(qint64 maxlen = 0) { return QSaveFile::readLine(maxlen); }
    Q_INVOKABLE virtual bool canReadLine() const { return QSaveFile::canReadLine(); }

    Q_INVOKABLE qint64 write(const char *data, qint64 len) { return QSaveFile::write(data, len); }
    Q_INVOKABLE qint64 write(const char *data) { return QSaveFile::write(data); }
    Q_INVOKABLE inline qint64 write(const QByteArray &data)
    { return write(data.constData(), data.size()); }

    Q_INVOKABLE qint64 peek(char *data, qint64 maxlen) { return QSaveFile::peek(data,maxlen); }
    Q_INVOKABLE QByteArray peek(qint64 maxlen) { return QSaveFile::peek(maxlen); }

    Q_INVOKABLE virtual bool waitForReadyRead(int msecs) { return QSaveFile::waitForReadyRead(msecs); }
    Q_INVOKABLE virtual bool waitForBytesWritten(int msecs) { return QSaveFile::waitForBytesWritten(msecs); }

    Q_INVOKABLE void ungetChar(char c) { return QSaveFile::ungetChar(c); }
    Q_INVOKABLE bool putChar(char c) { return QSaveFile::putChar(c); }
    Q_INVOKABLE bool getChar(char *c) { return QSaveFile::getChar(c); }

    Q_INVOKABLE QString errorString() const { return QSaveFile::errorString(); }

    Q_INVOKABLE QString fileName() const { return QSaveFile::fileName(); }
    Q_INVOKABLE void setFileName(const QString &name) {
        QSaveFile::setFileName(name);
        emit fileNameChanged();
    }

    Q_INVOKABLE qint64 size() const { return QSaveFile::size(); }
    Q_INVOKABLE bool resize(qint64 sz) { return QSaveFile::resize(sz); }
    Q_INVOKABLE Permissions permissions() const { return QSaveFile::permissions(); }
    Q_INVOKABLE bool setPermissions(Permissions permissionSpec) { return QSaveFile::setPermissions(permissionSpec); }

signals:
    void fileNameChanged();

};

#endif // MANGOSAVEFILE_H
