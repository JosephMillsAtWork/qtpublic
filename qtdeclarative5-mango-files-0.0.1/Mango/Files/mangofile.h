/*****************************************************************************
** This file is part of the Mango App Launcher.
**
** Mango App Launcher is free software: you can redistribute it and/or modify
** it under the terms of the GNU Lesser General Public License as published by
** the Free Software Foundation, version 3 of the License.
**
** Mango App Launcher is distributed in the hope that it will be useful,
** but WITHOUT ANY WARRANTY; without even the implied warranty of
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
** GNU Lesser General Public License for more details.
**
** You should have received a copy of the GNU Lesser General Public License
** along with this program.  If not, see <http://www.gnu.org/licenses/>.
******************************************************************************
** Author: Juhapekka Piiroinen <jp+Mangoapplauncher@1337.fi>
**
** Copyright (C) 2014 1337 Software Oy.
******************************************************************************/

#ifndef MANGOFILE_H
#define MANGOFILE_H

#include <QFile>

class MangoFile : public QFile
{
    Q_OBJECT
    Q_PROPERTY(QString fileName READ fileName WRITE setFileName NOTIFY fileNameChanged)
    Q_ENUMS( OpenModeFlag OpenMode Permissions FileError FileHandleFlag MemoryMapFlags )

public:
    explicit MangoFile(QObject *parent = 0);

    Q_INVOKABLE static QString readLink(const QString &fileName) {
        return QFile::readLink(fileName);
    }
    Q_INVOKABLE inline static QString symLinkTarget(const QString &fileName) { return readLink(fileName); }

    Q_INVOKABLE static bool exists(const QString &fileName) {
        return QFile::exists(fileName);
    }

    Q_INVOKABLE static bool link(const QString &oldname, const QString &newName) { return QFile::link(oldname,newName); }
    Q_INVOKABLE static bool copy(const QString &fileName, const QString &newName) { return QFile::copy(fileName, newName); }
    Q_INVOKABLE static bool rename(const QString &oldName, const QString &newName) { return QFile::rename(oldName, newName); }
    Q_INVOKABLE static bool remove(const QString &fileName) { return QFile::remove(fileName); }
    Q_INVOKABLE static bool resize(const QString &filename, qint64 sz) { return QFile::resize(filename, sz); }
    Q_INVOKABLE static Permissions permissions(const QString &filename) { return QFile::permissions(filename); }
    Q_INVOKABLE static bool setPermissions(const QString &filename, Permissions permissionSpec) { return QFile::setPermissions(filename, permissionSpec); }

    Q_INVOKABLE bool remove() { return QFile::remove(); }
    Q_INVOKABLE bool rename(const QString &newName) { return QFile::rename(newName); }
    Q_INVOKABLE bool link(const QString &newName) { return QFile::link(newName); }
    Q_INVOKABLE bool copy(const QString &newName) { return QFile::copy(newName); }

    Q_INVOKABLE bool openReadOnly() { return QFile::open(QIODevice::ReadOnly); }
    Q_INVOKABLE bool openReadWrite() { return QFile::open(QIODevice::ReadWrite); }
    Q_INVOKABLE bool openAppend() { return QFile::open(QIODevice::Append); }
    Q_INVOKABLE bool openWriteOnly() { return QFile::open(QIODevice::WriteOnly); }

    // file actions

    Q_INVOKABLE virtual void close() { return QFile::close(); }

    Q_INVOKABLE void setTextModeEnabled(bool enabled) { return QFile::setTextModeEnabled(enabled); }
    Q_INVOKABLE bool isTextModeEnabled() const { return QFile::isTextModeEnabled(); }

    Q_INVOKABLE bool isOpen() const { return QFile::isOpen(); }
    Q_INVOKABLE bool isReadable() const { return QFile::isReadable(); }
    Q_INVOKABLE bool isWritable() const { return QFile::isWritable(); }
    Q_INVOKABLE virtual bool isSequential() const { return QFile::isSequential(); }

    Q_INVOKABLE qint64 pos() const { return QFile::pos(); }
    Q_INVOKABLE bool seek(qint64 offset) { return QFile::seek(offset); }
    Q_INVOKABLE bool atEnd() const { return QFile::atEnd(); }
    Q_INVOKABLE bool flush() { return QFile::flush(); }
    Q_INVOKABLE virtual bool reset() { return QFile::reset(); }

    Q_INVOKABLE uchar *map(qint64 offset, qint64 size, MemoryMapFlags flags = NoOptions) {
        return QFile::map(offset,size, flags);
    }

    Q_INVOKABLE bool unmap(uchar *address) {
        return QFile::unmap(address);
    }

    Q_INVOKABLE virtual qint64 bytesAvailable() const { return QFile::bytesAvailable(); }
    Q_INVOKABLE virtual qint64 bytesToWrite() const { return QFile::bytesToWrite(); }


    Q_INVOKABLE qint64 read(char *data, qint64 maxlen) { return QFile::read(data,maxlen); }
    Q_INVOKABLE QByteArray read(qint64 maxlen) { return QFile::read(maxlen); }
    Q_INVOKABLE QByteArray readAll() { return QFile::readAll(); }
    Q_INVOKABLE qint64 readLine(char *data, qint64 maxlen) { return QFile::readLine(data, maxlen); }
    Q_INVOKABLE QByteArray readLine(qint64 maxlen = 0) { return QFile::readLine(maxlen); }
    Q_INVOKABLE virtual bool canReadLine() const { return QFile::canReadLine(); }

    Q_INVOKABLE qint64 write(const char *data, qint64 len) { return QFile::write(data, len); }
    Q_INVOKABLE qint64 write(const char *data) { return QFile::write(data); }
    Q_INVOKABLE inline qint64 write(const QByteArray &data)
    { return write(data.constData(), data.size()); }

    Q_INVOKABLE qint64 peek(char *data, qint64 maxlen) { return QFile::peek(data,maxlen); }
    Q_INVOKABLE QByteArray peek(qint64 maxlen) { return QFile::peek(maxlen); }

    Q_INVOKABLE virtual bool waitForReadyRead(int msecs) { return QFile::waitForReadyRead(msecs); }
    Q_INVOKABLE virtual bool waitForBytesWritten(int msecs) { return QFile::waitForBytesWritten(msecs); }

    Q_INVOKABLE void ungetChar(char c) { return QFile::ungetChar(c); }
    Q_INVOKABLE bool putChar(char c) { return QFile::putChar(c); }
    Q_INVOKABLE bool getChar(char *c) { return QFile::getChar(c); }

    Q_INVOKABLE QString errorString() const { return QFile::errorString(); }


    Q_INVOKABLE QString fileName() const { return QFile::fileName(); }
    Q_INVOKABLE void setFileName(const QString &name) {
        if (QFile::fileName().compare(name)==0) { return; }
        QFile::setFileName(name);
        emit fileNameChanged();
    }

    Q_INVOKABLE bool exists() const { return QFile::exists(); }

    Q_INVOKABLE QString readLink() const { return QFile::readLink(); }
    Q_INVOKABLE inline QString symLinkTarget() const { return readLink(); }

    Q_INVOKABLE qint64 size() const { return QFile::size(); }
    Q_INVOKABLE bool resize(qint64 sz) { return QFile::resize(sz); }
    Q_INVOKABLE Permissions permissions() const { return QFile::permissions(); }
    Q_INVOKABLE bool setPermissions(Permissions permissionSpec) { return QFile::setPermissions(permissionSpec); }

signals:
    void fileNameChanged();


};

#endif // MANGOFILE_H
