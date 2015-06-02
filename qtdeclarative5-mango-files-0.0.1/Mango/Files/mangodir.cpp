/*
 * Joseph Mills
 */
#include "mangodir.h"
MangoDir::MangoDir(QObject *parent) :
    QDir()
{
    Q_UNUSED(parent);
}
/*!
 \qmltype MangoDir
 \inqmlmodule Mango.Files 0.1
 \ingroup Mango.Files
 \inherits Item
 \since 5.3
  The MangoDir Qml Plugin provides access to directory structures and their contents.

A MangoDir is used to manipulate path names, access information regarding paths and files, and manipulate the underlying file system. It can also be used to access Qt's resource system.

Qt uses "/" as a universal directory separator in the same way that "/" is used as a path separator in URLs. If you always use "/" as a directory separator, Qt will translate your paths to conform to the underlying operating system.

A MangoDir can point to a file using either a relative or an absolute path. Absolute paths begin with the directory separator (optionally preceded by a drive specification under Windows). Relative file names begin with a directory name or a file name and specify a path relative to the current directory.
 */

/*!
      \qmlproperty string MangoDir::path
    */

/*!
      \qmlproperty QStringList MangoDir::entryList
    */

/*!
      \qmlproperty enum MangoDir::SortFlag



*/


/*!
    \qmlmethod QString  MangoDir::absolutePath()
    Returns the absolute path (a path that starts with "/" or with a drive specification), which may contain symbolic links, but never contains redundant ".", ".." or multiple separators.
    */


/*!
    \qmlmethod QString MangoDir::canonicalPath() const
Returns the canonical path, i.e. a path without symbolic links or redundant "." or ".." elements.

On systems that do not have symbolic links this function will always return the same string that absolutePath() returns. If the canonical path does not exist (normally due to dangling symbolic links) canonicalPath() returns an empty string.
    */



/*!
      \qmlmethod static void MangoDir::addResourceSearchPath(string &path)
      Adds path to the search paths searched in to find resources that are not specified with an absolute path. The default search path is to search only in the root (:/).
    */


/*!
  \qmlmethod void MangoDir::setSearchPaths(string &prefix, const QStringList &searchPaths)

Sets or replaces Qt's search paths for file names with the prefix prefix to searchPaths.

To specify a prefix for a file name, prepend the prefix followed by a single colon (e.g., "images:undo.png", "xmldocs:books.xml"). prefix can only contain letters or numbers (e.g., it cannot contain a colon, nor a slash).

Qt uses this search path to locate files with a known prefix. The search path entries are tested in order, starting with the first entry.

See also searchPaths().
*/


/*!
    \qmlmethod void MangoDir::addSearchPath(string &prefix,string &path)
    Adds path to the search path for prefix.

This function was introduced in Qt 4.3.

See also setSearchPaths().
*/

/*!
    \qmlmethod static QStringList MangoDir::searchPaths(string &prefix)
Returns the search paths for prefix.

See also setSearchPaths() and addSearchPath().

    */

/*!
      \qmlsignal MangoDir::dirName()
Returns the name of the directory; this is not the same as the path, e.g. a directory with the name "mail", might have the path "/var/spool/mail". If the directory has no name (e.g. it is the root directory) an empty string is returned.

No check is made to ensure that a directory with this name actually exists; but see exists().

See also path(), filePath(), absolutePath(), and absoluteFilePath().
    */

/*!
      \qmlsignal MangoDir::filePath()
Returns the path name of a file in the directory. Does not check if the file actually exists in the directory; but see exists(). If the QDir is relative the returned path name will also be relative. Redundant multiple separators or "." and ".." directories in fileName are not removed (see cleanPath()).

See also dirName(), absoluteFilePath(), isRelative(), and canonicalPath().
    */


/*!
      \qmlmethod MangoDir::absoluteFilePath(string &fileName)
Returns the absolute path name of a file in the directory. Does not check if the file actually exists in the directory; but see exists(). Redundant multiple separators or "." and ".." directories in fileName are not removed (see cleanPath()).

See also relativeFilePath(), filePath(), and canonicalPath().
      */



/*!
    \qmlmethod QString MangoDir::relativeFilePath(string &fileName)
    Returns the path to fileName relative to the directory.

    See also absoluteFilePath(), filePath(), and canonicalPath()
    */


/*!
      \qmlmethod static QString MangoDir::toNativeSeparators(string &pathName)
Returns pathName with the '/' separators converted to separators that are appropriate for the underlying operating system.

On Windows, toNativeSeparators("c:/winnt/system32")

returns

\b{"c: \ winnt \ system32"}

The returned string may be the same as the argument on some operating systems, for example on Unix.

See also fromNativeSeparators() and separator()
    */


/*!
    \qmlmethod static QString MangoDir::fromNativeSeparators(string &pathName)
Returns pathName using '/' as file separator. On Windows, for instance, fromNativeSeparators("c:\\winnt\\system32") returns "c:/winnt/system32".

The returned string may be the same as the argument on some operating systems, for example on Unix.

See also toNativeSeparators() and separator().
    */

/*!
  \qmlmethod bool MangoDir::cd(string &dirName)
Changes the QDir's directory to dirName.

Returns true if the new directory exists; otherwise returns false. Note that the logical cd() operation is not performed if the new directory does not exist.

Calling cd("..") is equivalent to calling cdUp().

See also cdUp(), isReadable(), exists(), and path().
*/

/*!
\qmlmethod bool MangoDir::cdUp()
Changes directory by moving one directory up from the QDir's current directory.

Returns true if the new directory exists; otherwise returns false. Note that the logical cdUp() operation is not performed if the new directory does not exist.

See also cd(), isReadable(), exists(), and path().

*/


/*!
      \qmlmethod QStringList MangoDir::nameFilters()
Returns the string list set by setNameFilters()

See also setNameFilters().
    */


/*!
      \qmlmethod void MangoDir::setNameFilters(string &nameFilters)
Sets the name filters used by entryList() and entryInfoList() to the list of filters specified by nameFilters.

Each name filter is a wildcard (globbing) filter that understands * and ? wildcards. (See QRegExp wildcard matching.)
    */


/*!
      \qmlsignal MangoDir::filter()
Returns the value set by setFilter()

See also setFilter().
    */

/*!
\qmlmethod void MangoDir::setFilter(Filters filter)
Sets the filter used by entryList() and entryInfoList() to filters. The filter is used to specify the kind of files that should be returned by entryList() and entryInfoList(). See QDir::Filter.

See also filter() and setNameFilters().
*/

/*!
      \qmlmethod MangoDir::sorting()
Returns the value set by setSorting()

See also setSorting() and SortFlag.
    */

/*!
    \qmlmethod void MangoDir::setSorting(SortFlags sort)
Sets the sort order used by entryList() and entryInfoList().

The sort is specified by OR-ing values from the enum QDir::SortFlag.

See also sorting() and SortFlag.
    */

/*!
      \qmlmethod  uint MangoDir::count() const
Returns the total number of directories and files in the directory.

Equivalent to entryList().count().

See also operator[]() and entryList().
    */

/*!
    \qmlmethod static QStringList MangoDir::nameFiltersFromString(string &nameFilter)
    DOCME
    */

/*!
    \qmlmethod QStringList MangoDir::entryList(Filters filters, SortFlags sort)
Returns a list of the names of all the files and directories in the directory, ordered according to the name and attribute filters previously set with setNameFilters() and setFilter(), and sorted according to the flags set with setSorting().

The name filter, file attribute filter, and sorting specification can be overridden using the nameFilters, filters, and sort arguments.

Returns an empty list if the directory is unreadable, does not exist, or if nothing matches the specification.

See also entryInfoList()
    */

/*!
    \qmlmethod QStringList MangoDir::entryInfoList(const QStringList &nameFilters, Filters filters, SortFlags sort)
    WHY 2 not sure,
    */


/*!
    \qmlmethod QFileInfoList MangoDir::entryInfoList(Filters filters, SortFlags sort)
Returns a list of QFileInfo objects for all the files and directories in the directory, ordered according to the name and attribute filters previously set with setNameFilters() and setFilter(), and sorted according to the flags set with setSorting().

The name filter, file attribute filter, and sorting specification can be overridden using the nameFilters, filters, and sort arguments.

Returns an empty list if the directory is unreadable, does not exist, or if nothing matches the specification.

See also entryList(), setNameFilters(), setSorting(), setFilter(), isReadable(), and exists().
    */




/*!
    \qmlmethod bool MangoDir::mkdir(string &dirName)
Creates a sub-directory called dirName.

Returns true on success; otherwise returns false.

If the directory already exists when this function is called, it will return false.

See also rmdir().
    */


/*!
      \qmlmethod bool MangoDir::rmdir(string &dirName)
Removes the directory specified by dirName.

The directory must be empty for rmdir() to succeed.

Returns true if successful; otherwise returns false.

See also mkdir().
    */


/*!
    \qmlmethod bool MangoDir::mkpath(string &dirPath)
Removes the directory specified by dirName.

The directory must be empty for rmdir() to succeed.

Returns true if successful; otherwise returns false.

See also mkdir().
    */


/*!
    \qmlmethod bool MangoDir::rmpath(string &dirPath)
Removes the directory path dirPath.

The function will remove all parent directories in dirPath, provided that they are empty. This is the opposite of mkpath(dirPath).

Returns true if successful; otherwise returns false.

See also mkpath().
    */


/*!
    \qmlmethod bool MangoDir::removeRecursively()
Removes the directory, including all its contents.

Returns true if successful, otherwise false.

If a file or directory cannot be removed, removeRecursively() keeps going and attempts to delete as many files and sub-directories as possible, then returns false.

If the directory was already removed, the method returns true (expected result already reached).

Note: this function is meant for removing a small application-internal directory (such as a temporary directory), but not user-visible directories. For user-visible operations, it is rather recommended to report errors more precisely to the user, to offer solutions in case of errors, to show progress during the deletion since it could take several minutes, etc.
    */

/*!
      \qmlmethod bool MangoDir::isReadable()
Returns true if the directory is readable and we can open files by name; otherwise returns false.

Warning: A false value from this function is not a guarantee that files in the directory are not accessible.

See also QFileInfo::isReadable().
    */


/*!
    \qmlmethod bool MangoDir::exists()
Returns true if the file called name exists; otherwise returns false.

Unless name contains an absolute file path, the file name is assumed to be relative to the directory itself, so this function is typically used to check for the presence of files within a directory.

See also QFileInfo::exists() and QFile::exists().
    */


/*!
    \qmlmethod bool MangoDir::isRoot()
Returns true if the directory is the root directory; otherwise returns false.

Note: If the directory is a symbolic link to the root directory this function returns false. If you want to test for this use canonicalPath(), e.g.

FIX ME ADD CODE EXAMPLE

See also root() and rootPath().
    */

/*!
    \qmlmethod static bool MangoDir::isRelativePath(string &path)
Returns true if path is relative; returns false if it is absolute.

See also isRelative(), isAbsolutePath(), and makeAbsolute().
    */

/*!
    \qmlmethod inlne static bool MangoDir::isAbsolutePath(string &path)
    FIXME AND DOCME
    */

/*!
    \qmlmethod bool MangoDir::isRelative()
Returns true if the directory path is relative; otherwise returns false. (Under Unix a path is relative if it does not start with a "/").

See also makeAbsolute(), isAbsolute(), isAbsolutePath(), and cleanPath()
    */


/*!
    \qmlmethod inline bool MangoDir::isAbsolute()
Returns true if the directory's path is absolute; otherwise returns false. See isAbsolutePath().

See also isRelative(), makeAbsolute(), and cleanPath()
    */

/*!
    \qmlmethod bool MangoDir::makeAbsolute()
Converts the directory path to an absolute path. If it is already absolute nothing happens. Returns true if the conversion succeeded; otherwise returns false.

See also isAbsolute(), isAbsolutePath(), isRelative(), and cleanPath()
    */


/*!
    \qmlmethod bool MangoDir::remove(string &fileName)
Removes the file, fileName.

Returns true if the file is removed successfully; otherwise returns false.
    */


/*!
      \qmlmethod bool MangoDir::rename(string &oldName,string &newName)
Renames a file or directory from oldName to newName, and returns true if successful; otherwise returns false.

On most file systems, rename() fails only if oldName does not exist, or if a file with the new name already exists. However, there are also other reasons why rename() can fail. For example, on at least one file system rename() fails if newName points to an open file.

If oldName is a file (not a directory) that can't be renamed right away, Qt will try to copy oldName to newName and remove oldName.

See also QFile::rename().
    */



/*!
    \qmlmethod bool MangoDir::exists(string &name)
Returns true if the file called name exists; otherwise returns false.

Unless name contains an absolute file path, the file name is assumed to be relative to the directory itself, so this function is typically used to check for the presence of files within a directory.

See also QFileInfo::exists() and QFile::exists().
    */


/*!
    \qmlmethod static MangoDir::drives()
Returns a list of the root directories on this system.

On Windows this returns a list of QFileInfo objects containing "C:/", "D:/", etc. On other operating systems, it returns a list containing just one root directory (i.e. "/").

See also root() and rootPath()
    */


/*!
    \qmlmethod static QChar MangoDir::separator()
Returns the native directory separator: "/" under Unix (including Mac OS X) and "\" under Windows.

You do not need to use this function to build file paths. If you always use "/", Qt will translate your paths to conform to the underlying operating system. If you want to display paths to the user using their operating system's separator use toNativeSeparators().
    */

/*!
    \qmlmethod static bool MangoDir::setCurrent(string &path)
Sets the application's current working directory to path. Returns true if the directory was successfully changed; otherwise returns false.

See also current(), currentPath(), home(), root(), and temp()
    */

/*!
    \qmlmethod static inline MangoDir::current()
Returns the absolute path of the application's current directory. The current directory is the last directory set with QDir::setCurrent() or, if that was never called, the directory at which this application was started at by the parent process.

See also current(), setCurrent(), homePath(), rootPath(), tempPath(), and QCoreApplication::applicationDirPath().
    */


/*!
    \qmlmethod static MangoDir::currentPath()
Returns the absolute path of the application's current directory. The current directory is the last directory set with QDir::setCurrent() or, if that was never called, the directory at which this application was started at by the parent process.

See also current(), setCurrent(), homePath(), rootPath(), tempPath(), and QCoreApplication::applicationDirPath().
    */


/*!
      \qmlmethod static inline MangoDir::home()

    */

/*!
    \qmlmethod static MangoDir::homePath()

    */

/*!
    \qmlmethod MangoDir::root()

    */


/*!
    \qmlmethod MangoDir::rootPath()

    */

/*!
    \qmlmethod MangoDir::temp()

    */


/*!
    \qmlmethod MangoDir::tempPath()

    */


/*!
    \qmlmethod static bool MangoDir::match(QStringList filter,string fileName)
This is an overloaded function.

Returns true if the fileName matches any of the wildcard (glob) patterns in the list of filters; otherwise returns false. The matching is case insensitive.

See also QRegExp wildcard matching, QRegExp::exactMatch(), entryList(), and entryInfoList().
    */


/*!
    \qmlmethod static bool MangoDir::match(string filter, string filename )
    */



/*!
      \qmlmethod static QString MangoDir::cleanPath(string &path)
Returns path with directory separators normalized (converted to "/") and redundant ones removed, and "."s and ".."s resolved (as far as possible).

Symbolic links are kept. This function does not return the canonical path, but rather the simplest version of the input. For example, "./local" becomes "local", "local/../bin" becomes "bin" and "/local/usr/../bin" becomes "/local/bin".

See also absolutePath() and canonicalPath().
    */

/*!
    \qmlmethod MangoDir::refresh()
    Refreshes the directory information.
    */
