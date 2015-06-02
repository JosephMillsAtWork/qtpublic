/*
 *Joseph Mills
 */
#ifndef MANGOFILEINFO_H
#define MANGOFILEINFO_H

#include <QFileInfo>
#include <QDir>
#include <QDateTime>
#include "mangodir.h"

class MangoFileInfo : public QObject, public QFileInfo
{
    Q_OBJECT

    Q_PROPERTY(QString fileName READ fileName WRITE setFile NOTIFY fileChanged)
    Q_PROPERTY(bool exists READ exists NOTIFY fileChanged)
    Q_PROPERTY(QString filePath READ filePath NOTIFY fileChanged)
    Q_PROPERTY(QString absoluteFilePath READ absoluteFilePath NOTIFY fileChanged)
    Q_PROPERTY(QString canonicalFilePath READ canonicalFilePath NOTIFY fileChanged)
    Q_PROPERTY(QString baseName READ baseName NOTIFY fileChanged)
    Q_PROPERTY(QString completeBaseName READ completeBaseName NOTIFY fileChanged)
    Q_PROPERTY(QString suffix READ suffix NOTIFY fileChanged)
    Q_PROPERTY(QString bundleName READ bundleName NOTIFY fileChanged)
    Q_PROPERTY(QString completeSuffix READ completeSuffix NOTIFY fileChanged)

    Q_PROPERTY(QString path READ path NOTIFY fileChanged)
    Q_PROPERTY(QString absolutePath READ absolutePath NOTIFY fileChanged)
    Q_PROPERTY(QString canonicalPath READ canonicalPath NOTIFY fileChanged)

    Q_PROPERTY(bool isReadable READ isReadable NOTIFY fileChanged)
    Q_PROPERTY(bool isWritable READ isWritable NOTIFY fileChanged)
    Q_PROPERTY(bool isExecutable READ isExecutable NOTIFY fileChanged)
    Q_PROPERTY(bool isHidden READ isHidden NOTIFY fileChanged)
    Q_PROPERTY(bool isNativePath READ isNativePath NOTIFY fileChanged)
    Q_PROPERTY(bool isRelative READ isRelative NOTIFY fileChanged)
    Q_PROPERTY(bool isAbsolute READ isAbsolute NOTIFY fileChanged)
    Q_PROPERTY(bool isFile READ isFile NOTIFY fileChanged)
    Q_PROPERTY(bool isDir READ isDir NOTIFY fileChanged)
    Q_PROPERTY(bool isSymLink READ isSymLink NOTIFY fileChanged)
    Q_PROPERTY(bool isRoot READ isRoot NOTIFY fileChanged)
    Q_PROPERTY(bool isBundle READ isBundle NOTIFY fileChanged)

    Q_PROPERTY(QString readLink READ readLink NOTIFY fileChanged)
    Q_PROPERTY(QString symLinkTarget READ symLinkTarget NOTIFY fileChanged)

    Q_PROPERTY(QString owner READ owner NOTIFY fileChanged)
    Q_PROPERTY(uint ownerId READ ownerId NOTIFY fileChanged)
    Q_PROPERTY(QString group READ group NOTIFY fileChanged)
    Q_PROPERTY(uint groupId READ groupId NOTIFY fileChanged)
    Q_PROPERTY(QFile::Permissions permissions READ permissions NOTIFY fileChanged)

    Q_PROPERTY(qint64 size READ size NOTIFY fileChanged)

    Q_PROPERTY(QDateTime created READ created NOTIFY fileChanged)
    Q_PROPERTY(QDateTime lastModified READ lastModified NOTIFY fileChanged)
    Q_PROPERTY(QDateTime lastRead READ lastRead NOTIFY fileChanged)

    Q_PROPERTY(bool caching READ caching WRITE setCaching NOTIFY cachingChanged)

public:
    explicit MangoFileInfo(QObject *parent = 0);

    Q_INVOKABLE void setFile(const QString &file) {
        QFileInfo::setFile(file);
        emit fileChanged();
    }

    Q_INVOKABLE void setFile(const QFile &file) {
        QFileInfo::setFile(file);
        emit fileChanged();
    }

    Q_INVOKABLE void setFile(const QDir &dir, const QString &file) {
        QFileInfo::setFile(dir, file);
        emit fileChanged();
    }

    Q_INVOKABLE bool exists() const { return QFileInfo::exists(); }
    Q_INVOKABLE static bool exists(const QString &file) { return QFileInfo::exists(file); }
    Q_INVOKABLE void refresh() {
        QFileInfo::refresh();
        emit fileChanged();
    }

    Q_INVOKABLE QString filePath() const { return QFileInfo::filePath(); }
    Q_INVOKABLE QString absoluteFilePath() const { return QFileInfo::absoluteFilePath(); }
    Q_INVOKABLE QString canonicalFilePath() const { return QFileInfo::canonicalFilePath(); }
    Q_INVOKABLE QString fileName() const { return QFileInfo::fileName(); }
    Q_INVOKABLE QString baseName() const { return QFileInfo::baseName(); }
    Q_INVOKABLE QString completeBaseName() const { return QFileInfo::completeBaseName(); }
    Q_INVOKABLE QString suffix() const { return QFileInfo::suffix(); }
    Q_INVOKABLE QString bundleName() const { return QFileInfo::bundleName(); }
    Q_INVOKABLE QString completeSuffix() const { return QFileInfo::completeSuffix(); }

    Q_INVOKABLE QString path() const { return QFileInfo::path(); }
    Q_INVOKABLE QString absolutePath() const { return QFileInfo::absolutePath(); }
    Q_INVOKABLE QString canonicalPath() const { return QFileInfo::canonicalPath(); }

    Q_INVOKABLE bool isReadable() const { return QFileInfo::isReadable(); }
    Q_INVOKABLE bool isWritable() const { return QFileInfo::isWritable(); }
    Q_INVOKABLE bool isExecutable() const { return QFileInfo::isExecutable(); }
    Q_INVOKABLE bool isHidden() const { return QFileInfo::isHidden(); }
    Q_INVOKABLE bool isNativePath() const { return QFileInfo::isNativePath(); }

    Q_INVOKABLE bool isRelative() const { return QFileInfo::isRelative(); }
    Q_INVOKABLE inline bool isAbsolute() const { return !isRelative(); }
    Q_INVOKABLE bool makeAbsolute() { return QFileInfo::makeAbsolute(); }

    Q_INVOKABLE bool isFile() const { return QFileInfo::isFile(); }
    Q_INVOKABLE bool isDir() const { return QFileInfo::isDir(); }
    Q_INVOKABLE bool isSymLink() const { return QFileInfo::isSymLink(); }
    Q_INVOKABLE bool isRoot() const { return QFileInfo::isRoot(); }
    Q_INVOKABLE bool isBundle() const { return QFileInfo::isBundle(); }

    Q_INVOKABLE QString readLink() const { return QFileInfo::readLink(); }
    Q_INVOKABLE inline QString symLinkTarget() const { return QFileInfo::symLinkTarget(); }

    Q_INVOKABLE QString owner() const { return QFileInfo::owner(); }
    Q_INVOKABLE uint ownerId() const { return QFileInfo::ownerId(); }
    Q_INVOKABLE QString group() const { return QFileInfo::group(); }
    Q_INVOKABLE uint groupId() const { return QFileInfo::groupId(); }

    Q_INVOKABLE bool permission(QFile::Permissions permissions) const { return QFileInfo::permission(permissions); }
    Q_INVOKABLE QFile::Permissions permissions() const { return QFileInfo::permissions(); }

    Q_INVOKABLE qint64 size() const { return QFileInfo::size(); }

    Q_INVOKABLE QDateTime created() const { return QFileInfo::created(); }
    Q_INVOKABLE QDateTime lastModified() const { return QFileInfo::lastModified(); }
    Q_INVOKABLE QDateTime lastRead() const { return QFileInfo::lastRead(); }

    Q_INVOKABLE bool caching() const { return QFileInfo::caching(); }
    Q_INVOKABLE void setCaching(bool on) {
        QFileInfo::setCaching(on);
        emit cachingChanged();
    }

signals:
    void fileChanged();
    void cachingChanged();
};

#endif // MANGOFILEINFO_H
