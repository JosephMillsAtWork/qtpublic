/*
 * Joseph Mills
 */

#ifndef MANGOFILESYSTEMWATCHER_H
#define MANGOFILESYSTEMWATCHER_H

#include <QtCore>
#include <QFileSystemWatcher>

class MangoFileSystemWatcher : public QObject
{
    Q_OBJECT

public:
    explicit MangoFileSystemWatcher(QObject *parent = 0);

    Q_INVOKABLE bool addPath(const QString &file) {
        return m_fileSystemWatcher.addPath(file);
    }

    Q_INVOKABLE QStringList addPaths(const QStringList &files) {
        return m_fileSystemWatcher.addPaths(files);
    }

    Q_INVOKABLE bool removePath(const QString &file) {
        return m_fileSystemWatcher.removePath(file);
    }

    Q_INVOKABLE  QStringList removePaths(const QStringList &files) {
        return m_fileSystemWatcher.removePaths(files);
    }

    Q_INVOKABLE QStringList files() const { return m_fileSystemWatcher.files(); }
    Q_INVOKABLE QStringList directories() const { return m_fileSystemWatcher.directories(); }

signals:
    void fileChanged(const QString &path);
    void directoryChanged(const QString &path);

protected:
    QFileSystemWatcher m_fileSystemWatcher;
};

#endif // MANGOFILESYSTEMWATCHER_H
