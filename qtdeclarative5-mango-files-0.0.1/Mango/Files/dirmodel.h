/*
 * Copyright (C) 2014 Joseph Mills.
 *
 */
#ifndef DIRMODEL_H
#define DIRMODEL_H

#include <QAbstractListModel>
#include <QFileInfo>
#include <QVector>
#include <QStringList>

#include "iorequest.h"

class DirModel : public QAbstractListModel
{
    Q_OBJECT

    enum Roles {
        FileNameRole = Qt::UserRole,
        CreationDateRole,
        ModifiedDateRole,
        FileSizeRole,
        IconSourceRole,
        FilePathRole,
        IsDirRole,
        IsFileRole,
        IsReadableRole,
        IsWritableRole,
        IsExecutableRole
    };

public:
    DirModel(QObject *parent = 0);

    int rowCount(const QModelIndex &index) const
    {
        if (index.parent() != QModelIndex())
            return 0;

        return mDirectoryContents.count();
    }

    // TODO: this won't be safe if the model can change under the holder of the row
    Q_INVOKABLE QVariant data(int row, const QByteArray &stringRole) const;

    QVariant data(const QModelIndex &index, int role) const;

    Q_INVOKABLE void refresh()
    {
        // just some syntactical sugar really
        setPath(path());
    }

    Q_PROPERTY(QString path READ path WRITE setPath NOTIFY pathChanged)
    inline QString path() const { return mCurrentDir; }

    Q_PROPERTY(QString parentPath READ parentPath NOTIFY pathChanged)
    QString parentPath() const;

    Q_INVOKABLE QString homePath() const;

    Q_PROPERTY(bool awaitingResults READ awaitingResults NOTIFY awaitingResultsChanged)
    bool awaitingResults() const;

    void setPath(const QString &pathName);

    Q_INVOKABLE void rm(const QStringList &paths);

    Q_INVOKABLE bool rename(int row, const QString &newName);

    Q_INVOKABLE void mkdir(const QString &newdir);

    Q_PROPERTY(bool showDirectories READ showDirectories WRITE setShowDirectories NOTIFY showDirectoriesChanged)
    bool showDirectories() const;
    void setShowDirectories(bool showDirectories);

    Q_PROPERTY(QStringList nameFilters READ nameFilters WRITE setNameFilters NOTIFY nameFiltersChanged)
    QStringList nameFilters() const;
    void setNameFilters(const QStringList &nameFilters);

public slots:
    void onItemsAdded(const QVector<QFileInfo> &newFiles);
    void onResultsFetched();
signals:
    void awaitingResultsChanged();
    void nameFiltersChanged();
    void showDirectoriesChanged();
    void pathChanged();
    void error(const QString &errorTitle, const QString &errorMessage);

private:
    QHash<int, QByteArray> buildRoleNames() const;

#if QT_VERSION >= QT_VERSION_CHECK(5, 0, 0)
    // In Qt5, the roleNames() is virtual and will work just fine. On qt4 setRoleNames must be used with buildRoleNames.
    QHash<int, QByteArray> roleNames() const;
#endif

    QStringList mNameFilters;
    bool mAwaitingResults;
    bool mShowDirectories;
    QString mCurrentDir;
    QVector<QFileInfo> mDirectoryContents;
};


#endif // DIRMODEL_H
