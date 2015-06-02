/*
 * Joseph Mills
 */

#ifndef MANGODIR_H
#define MANGODIR_H

#include <QDir>

class MangoDir : public QObject, public QDir
{
    Q_OBJECT
    Q_PROPERTY( QString path READ path WRITE setPath NOTIFY pathChanged )
    Q_PROPERTY( QStringList entryList READ entryList NOTIFY pathChanged )
    Q_ENUMS( SortFlags SortFlag )

public:
    explicit MangoDir(QObject *parent = 0);

    void setPath(const QString &path) {
        QDir::setPath(path);
        emit pathChanged();
    }
    QString path() const { return QDir::path(); }
    Q_INVOKABLE QString absolutePath() const { return QDir::absolutePath(); }
    Q_INVOKABLE QString canonicalPath() const { return QDir::canonicalPath(); }

    Q_INVOKABLE static void addResourceSearchPath(const QString &path) { QDir::addResourceSearchPath(path); }

    Q_INVOKABLE static void setSearchPaths(const QString &prefix, const QStringList &searchPaths) { QDir::setSearchPaths(prefix, searchPaths); }
    Q_INVOKABLE static void addSearchPath(const QString &prefix, const QString &path) { QDir::addSearchPath(prefix, path); }
    Q_INVOKABLE static QStringList searchPaths(const QString &prefix) { return QDir::searchPaths(prefix); }

    Q_INVOKABLE QString dirName() const { return QDir::dirName(); }
    Q_INVOKABLE QString filePath(const QString &fileName) const {
        return QDir::filePath(fileName);
    }

    Q_INVOKABLE QString absoluteFilePath(const QString &fileName) const {
        return QDir::absoluteFilePath(fileName);
    }

    Q_INVOKABLE QString relativeFilePath(const QString &fileName) const {
        return QDir::relativeFilePath(fileName);
    }

    Q_INVOKABLE static QString toNativeSeparators(const QString &pathName) {
        return QDir::toNativeSeparators(pathName);
    }

    Q_INVOKABLE static QString fromNativeSeparators(const QString &pathName) {
        return QDir::fromNativeSeparators(pathName);
    }

    Q_INVOKABLE bool cd(const QString &dirName) {
        return QDir::cd(dirName);
    }

    Q_INVOKABLE bool cdUp() {
        return QDir::cdUp();
    }

    Q_INVOKABLE QStringList nameFilters() const { return QDir::nameFilters(); }
    Q_INVOKABLE void setNameFilters(const QStringList &nameFilters) {
        QDir::setNameFilters(nameFilters);
        emit nameFiltersChanged();
    }

    Q_INVOKABLE Filters filter() const { return QDir::filter(); }
    Q_INVOKABLE void setFilter(Filters filter) { QDir::setFilter(filter); }
    Q_INVOKABLE SortFlags sorting() const { return QDir::sorting(); }
    Q_INVOKABLE void setSorting(SortFlags sort) { QDir::setSorting(sort); }

    Q_INVOKABLE uint count() const { return QDir::count(); }
    Q_INVOKABLE static QStringList nameFiltersFromString(const QString &nameFilter) { return QDir::nameFiltersFromString(nameFilter); }

    Q_INVOKABLE QStringList entryList(Filters filters = NoFilter, SortFlags sort = NoSort) const { return QDir::entryList(filters,sort); }
    Q_INVOKABLE QStringList entryList(const QStringList &nameFilters, Filters filters = NoFilter,
                          SortFlags sort = NoSort) const {
        return QDir::entryList(nameFilters,filters,sort);
    }

    Q_INVOKABLE QFileInfoList entryInfoList(Filters filters = NoFilter, SortFlags sort = NoSort) const {
        return QDir::entryInfoList(filters, sort);
    }
    Q_INVOKABLE QFileInfoList entryInfoList(const QStringList &nameFilters, Filters filters = NoFilter,
                                SortFlags sort = NoSort) const {
        return QDir::entryInfoList(nameFilters, filters, sort);
    }

    Q_INVOKABLE bool mkdir(const QString &dirName) const {
        return QDir::mkdir(dirName);
    }
    Q_INVOKABLE bool rmdir(const QString &dirName) const {
        return QDir::rmdir(dirName);
    }
    Q_INVOKABLE bool mkpath(const QString &dirPath) const {
        return QDir::mkpath(dirPath);
    }
    Q_INVOKABLE bool rmpath(const QString &dirPath) const {
        return QDir::rmpath(dirPath);
    }

    Q_INVOKABLE bool removeRecursively() {
        return QDir::removeRecursively();
    }

    Q_INVOKABLE bool isReadable() const {
        return QDir::isReadable();
    }
    Q_INVOKABLE bool exists() const {
        return QDir::exists();
    }
    Q_INVOKABLE bool isRoot() const { return QDir::isRoot(); }

    Q_INVOKABLE static bool isRelativePath(const QString &path) {
        return QDir::isRelativePath(path);
    }

    Q_INVOKABLE inline static bool isAbsolutePath(const QString &path) { return !isRelativePath(path); }
    Q_INVOKABLE bool isRelative() const {
        return QDir::isRelative();
    }
    Q_INVOKABLE inline bool isAbsolute() const { return !isRelative(); }
    Q_INVOKABLE bool makeAbsolute() {
        return QDir::makeAbsolute();
    }


    Q_INVOKABLE bool remove(const QString &fileName) {
        return QDir::remove(fileName);
    }
    Q_INVOKABLE bool rename(const QString &oldName, const QString &newName) {
        return QDir::rename(oldName,newName);
    }

    Q_INVOKABLE bool exists(const QString &name) const {
        return QDir::exists(name);
    }

    Q_INVOKABLE static QFileInfoList drives() {
        return QDir::drives();
    }

    Q_INVOKABLE static QChar separator() { return QDir::separator(); }

    Q_INVOKABLE static bool setCurrent(const QString &path) {
        return QDir::setCurrent(path);
    }

    Q_INVOKABLE static inline QDir current() { return QDir(currentPath()); }
    Q_INVOKABLE static QString currentPath() { return QDir::currentPath(); }

    Q_INVOKABLE static inline QDir home() { return QDir(homePath()); }
    Q_INVOKABLE static QString homePath() { return QDir::homePath(); }
    Q_INVOKABLE static inline QDir root() { return QDir(rootPath()); }
    Q_INVOKABLE static QString rootPath() { return QDir::rootPath(); }
    Q_INVOKABLE static inline QDir temp() { return QDir(tempPath()); }
    Q_INVOKABLE static QString tempPath() { return QDir::tempPath(); }

#ifndef QT_NO_REGEXP
    Q_INVOKABLE static bool match(const QStringList &filters, const QString &fileName) {
        return QDir::match(filters,fileName);
    }

    Q_INVOKABLE static bool match(const QString &filter, const QString &fileName) {
        return QDir::match(filter, fileName);
    }
#endif

    Q_INVOKABLE static QString cleanPath(const QString &path) {
        return QDir::cleanPath(path);
    }
    Q_INVOKABLE void refresh() const {
        QDir::refresh();
    }

signals:
    void nameFiltersChanged();
    void pathChanged();

public slots:

};

#endif // MANGODIR_H
