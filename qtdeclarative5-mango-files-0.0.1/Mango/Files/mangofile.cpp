#include "mangofile.h"
/*!
 \qmltype MangoFile
 \inqmlmodule Mango.Files 0.1
 \ingroup Mango.Files
 \inherits Item
 \since 5.3
The QFile class provides an interface for reading from and writing to files.

QFile is an I/O device for reading and writing text and binary files and resources. A QFile may be used by itself or, more conveniently, with a QTextStream or QDataStream.

The file name is usually passed in the constructor, but it can be set at any time using setFileName(). QFile expects the file separator to be '/' regardless of operating system. The use of other separators (e.g., '\') is not supported.

You can check for a file's existence using exists(), and remove a file using remove(). (More advanced file system related operations are provided by QFileInfo and QDir.)

The file is opened with open(), closed with close(), and flushed with flush(). Data is usually read and written using QDataStream or QTextStream, but you can also call the QIODevice-inherited functions read(), readLine(), readAll(), write(). QFile also inherits getChar(), putChar(), and ungetChar(), which work one character at a time.

The size of the file is returned by size(). You can get the current file position using pos(), or move to a new file position using seek(). If you've reached the end of the file, atEnd() returns true.
*/
MangoFile::MangoFile(QObject *parent) :
    QFile()
{
    Q_UNUSED(parent);
}


/*!
      \qmlproperty string MangoFile::fileName
      the default filename to set
    */

/*!
    \qmlmethod static MangoFile::readLink(string &fileName)
    Use symLinkTarget() instead.
    */


/*!
    \qmlmethod inline static QString MangoFile::symLinkTarget(string &fileName)
This is an overloaded function.

Returns the absolute path of the file or directory a symlink (or shortcut on Windows) points to, or a an empty string if the object isn't a symbolic link.

This name may not represent an existing file; it is only a string. QFile::exists() returns true if the symlink points to an existing file.

This function was introduced in Qt 4.2.

See also fileName() and setFileName().

    */


/*!
    \qmlmethod MangoFile::exists(string fileName)
Returns true if the file specified by fileName exists; otherwise returns false.

Note: If fileName is a symlink that points to a non-existing file, false is returned.

    */



/*!
    \qmlmethod static bool MangoFile::link(string &oldname, string &newName)
Creates a link named linkName that points to the file currently specified by fileName(). What a link is depends on the underlying filesystem (be it a shortcut on Windows or a symbolic link on Unix). Returns true if successful; otherwise returns false.

This function will not overwrite an already existing entity in the file system; in this case, link() will return false and set error() to return RenameError.

Note: To create a valid link on Windows, linkName must have a .lnk file extension.

See also setFileName().

    */

/*!
    \qmlmethod static bool MangoFile::copy(string &fileName, string &newName)
Copies the file currently specified by fileName() to a file called newName. Returns true if successful; otherwise returns false.

Note that if a file with the name newName already exists, copy() returns false (i.e. QFile will not overwrite it).

The source file is closed before it is copied.

See also setFileName().

    */

/*!
    \qmlmethod static bool MangoFile::rename(string &oldName,string &newName)
Renames the file currently specified by fileName() to newName. Returns true if successful; otherwise returns false.

If a file with the name newName already exists, rename() returns false (i.e., QFile will not overwrite it).

The file is closed before it is renamed.

If the rename operation fails, Qt will attempt to copy this file's contents to newName, and then remove this file, keeping only newName. If that copy operation fails or this file can't be removed, the destination file newName is removed to restore the old state.

See also setFileName().

    */

/*!
    \qmlmethod static bool MangoFile::remove(string &fileName)
Removes the file specified by fileName(). Returns true if successful; otherwise returns false.

The file is closed before it is removed.

See also setFileName().

    */

/*!
    \qmlmethod static bool MangoFile::resize(string &filename, qint64 sz)
This is an overloaded function.

Sets fileName to size (in bytes) sz. Returns true if the file if the resize succeeds; false otherwise. If sz is larger than fileName currently is the new bytes will be set to 0, if sz is smaller the file is simply truncated.

See also resize().

    */

/*!
    \qmlmethod MangoFile::permissions(string &filename)
This is an overloaded function.

Returns the complete OR-ed together combination of QFile::Permission for fileName.
    */

/*!
    \qmlmethod static bool MangoFile::setPermissions(string &filename, Permissions permissionSpec)
This is an overloaded function.

Sets the permissions for fileName file to permissions.

    */


/*!
    \qmlmethod bool MangoFile::remove(string &fileName)
Removes the file specified by fileName(). Returns true if successful; otherwise returns false.

The file is closed before it is removed.

See also setFileName().

    */



/*!
    \qmlmethod bool MangoFile::rename(string &newName)
Renames the file currently specified by fileName() to newName. Returns true if successful; otherwise returns false.

If a file with the name newName already exists, rename() returns false (i.e., QFile will not overwrite it).

The file is closed before it is renamed.

If the rename operation fails, Qt will attempt to copy this file's contents to newName, and then remove this file, keeping only newName. If that copy operation fails or this file can't be removed, the destination file newName is removed to restore the old state.

See also setFileName().
    */

/*!
    \qmlmethod bool MangoFile::link(string &newName)
Creates a link named linkName that points to the file currently specified by fileName(). What a link is depends on the underlying filesystem (be it a shortcut on Windows or a symbolic link on Unix). Returns true if successful; otherwise returns false.

This function will not overwrite an already existing entity in the file system; in this case, link() will return false and set error() to return RenameError.

Note: To create a valid link on Windows, linkName must have a .lnk file extension.

See also setFileName().
    */

/*!
    \qmlmethod MangoFile::copy(string &newName)
Copies the file currently specified by fileName() to a file called newName. Returns true if successful; otherwise returns false.

Note that if a file with the name newName already exists, copy() returns false (i.e. QFile will not overwrite it).

The source file is closed before it is copied.

See also setFileName().
    */


/*!
    \qmlmethod bool MangoFile::openReadOnly()
    opens a file in read only mode

    */

/*!
    \qmlmethod bool MangoFile::openReadWrite()
    opens a file as readable and also as writable


    */

/*!
    \qmlmethod bool MangoFile::openAppend()
    DOCME

    */

/*!
    \qmlmethod MangoFile::openWriteOnly()
    open a file as write only.
    */



/*!
    \qmlmethod virtul void MangoFile::close()
Reimplemented from QIODevice::close().

Calls QFileDevice::flush() and closes the file. Errors from flush are ignored.

See also QIODevice::close().

    */


/*!
    \qmlmethod void MangoFile::setTextModeEnabled(bool enabled)
If enabled is true, this function sets the Text flag on the device; otherwise the Text flag is removed. This feature is useful for classes that provide custom end-of-line handling on a QIODevice.

The IO device should be opened before calling this function.

See also isTextModeEnabled(), open(), and setOpenMode().
    */

/*!
    \qmlmethod bool MangoFile::isTextModeEnabled()
Returns true if the Text flag is enabled; otherwise returns false.

See also setTextModeEnabled().
    */


/*!
    \qmlmethod bool MangoFile::isOpen()
Returns true if the device is open; otherwise returns false. A device is open if it can be read from and/or written to. By default, this function returns false if openMode() returns NotOpen.

See also openMode() and OpenMode.
    */

/*!
    \qmlmethod MangoFile::isReadable()
Returns true if data can be read from the device; otherwise returns false. Use bytesAvailable() to determine how many bytes can be read.

This is a convenience function which checks if the OpenMode of the device contains the ReadOnly flag.

See also openMode() and OpenMode.

    */

/*!
    \qmlmethod bool MangoFile::isWritable()
Returns true if data can be written to the device; otherwise returns false.

This is a convenience function which checks if the OpenMode of the device contains the WriteOnly flag.

See also openMode() and OpenMode.

    */

/*!
    \qmlmethod virtual bool MangoFile::isSequential()
Reimplemented from QIODevice::isSequential().

Returns true if the file can only be manipulated sequentially; otherwise returns false.

Most files support random-access, but some special files may not.

See also QIODevice::isSequential().
    */


/*!
    \qmlmethod qint64 MangoFile::pos()
For random-access devices, this function returns the position that data is written to or read from. For sequential devices or closed devices, where there is no concept of a "current position", 0 is returned.

The current read/write position of the device is maintained internally by QIODevice, so reimplementing this function is not necessary. When subclassing QIODevice, use QIODevice::seek() to notify QIODevice about changes in the device position.

See also isSequential() and seek().
    */

/*!
    \qmlmethod bool MangoFile::seek(qint64 &offset)
For random-access devices, this function sets the current position to pos, returning true on success, or false if an error occurred. For sequential devices, the default behavior is to produce a warning and return false.

When subclassing QIODevice, you must call QIODevice::seek() at the start of your function to ensure integrity with QIODevice's built-in buffer.

See also pos() and isSequential().

    */

/*!
    \qmlmethod bool MangoFile::atEnd()
Reimplemented from QIODevice::atEnd().

Returns true if the end of the file has been reached; otherwise returns false.

For regular empty files on Unix (e.g. those in /proc), this function returns true, since the file system reports that the size of such a file is 0. Therefore, you should not depend on atEnd() when reading data from such a file, but rather call read() until no more data can be read.
    */

/*!
    \qmlmethod bool MangoFile::flush()
Flushes any buffered data to the file. Returns true if successful; otherwise returns false.
    */

/*!
    \qmlmethod virtual bool MangoFile::reset()
Seeks to the start of input for random-access devices. Returns true on success; otherwise returns false (for example, if the device is not open).

Note that when using a QTextStream on a QFile, calling reset() on the QFile will not have the expected result because QTextStream buffers the file. Use the QTextStream::seek() function instead.

See also seek().

    */


/*!
    \qmlmethod uchar MangoFile::map(qint64 offset, qint64 size, MemoryMapFlags flags)
Maps size bytes of the file into memory starting at offset. A file should be open for a map to succeed but the file does not need to stay open after the memory has been mapped. When the QFile is destroyed or a new file is opened with this object, any maps that have not been unmapped will automatically be unmapped.

Any mapping options can be passed through flags.

Returns a pointer to the memory or 0 if there is an error.

Note: On Windows CE 5.0 the file will be closed before mapping occurs.

See also unmap()

    */


/*!
    \qmlmethod bool MangoFile::unmap(uchar *address)
Unmaps the memory address.

Returns true if the unmap succeeds; false otherwise.

See also map().
    */



/*!
    \qmlmethod virtual qint64 MangoFile::bytesAvailable()
Returns the number of bytes that are available for reading. This function is commonly used with sequential devices to determine the number of bytes to allocate in a buffer before reading.

Subclasses that reimplement this function must call the base implementation in order to include the size of QIODevices' buffer.

See also bytesToWrite(), readyRead(), and isSequential().
    */

/*!
    \qmlmethod virtual qint64 MangoFile::bytesToWrite()
For buffered devices, this function returns the number of bytes waiting to be written. For devices with no buffer, this function returns 0.

See also bytesAvailable(), bytesWritten(), and isSequential().
    */



/*!
    \qmlmethod QByteArray MangoFile::read(char *data, qint64 maxlen)
Reads at most maxSize bytes from the device into data, and returns the number of bytes read. If an error occurs, such as when attempting to read from a device opened in WriteOnly mode, this function returns -1.

0 is returned when no more data is available for reading. However, reading past the end of the stream is considered an error, so this function returns -1 in those cases (that is, reading on a closed socket or after a process has died).

See also readData(), readLine(), and write().
   */

/*!
    \qmlmethod QByteArray MangoFile::read(qint64 maxlen)
This is an overloaded function.

Reads at most maxSize bytes from the device, and returns the data read as a QByteArray.

This function has no way of reporting errors; returning an empty QByteArray can mean either that no data was currently available for reading, or that an error occurred.
    */

/*!
    \qmlmethod QByteArray MangoFile::readAll()
This is an overloaded function.

Reads all available data from the device, and returns it as a byte array.

This function has no way of reporting errors; returning an empty QByteArray can mean either that no data was currently available for reading, or that an error occurred.
    */

/*!
    \qmlmethod qint64 MangoFile::readLine(char *data, qint64 maxlen)
This function reads a line of ASCII characters from the device, up to a maximum of maxSize - 1 bytes, stores the characters in data, and returns the number of bytes read. If a line could not be read but no error ocurred, this function returns 0. If an error occurs, this function returns the length of what could be read, or -1 if nothing was read.

A terminating '\ 0' byte is always appended to data, so maxSize must be larger than 1.

Data is read until either of the following conditions are met:

The first '\ n' character is read.
maxSize - 1 bytes are read.
The end of the device data is detected.

    */

/*!
    \qmlmethod QByteArray MangoFile::readLine(qint64 maxlen)
This is an overloaded function.

Reads a line from the device, but no more than maxSize characters, and returns the result as a byte array.

This function has no way of reporting errors; returning an empty QByteArray can mean either that no data was currently available for reading, or that an error occurred.

    */

/*!
    \qmlmethod MangoFile::canReadLine()
Returns true if a complete line of data can be read from the device; otherwise returns false.

Note that unbuffered devices, which have no way of determining what can be read, always return false.

This function is often called in conjunction with the readyRead() signal.

Subclasses that reimplement this function must call the base implementation in order to include the contents of the QIODevice's buffer. Example:
\code
MangoFile{
id: file
}
Component onCompleated: console.log(file.canReadLine()) const
\endcode

See also readyRead() and readLine().

    */


/*!
    \qmlmethod quint64 MangoFile::write(const char *data, qint64 len)
Writes at most maxSize bytes of data from data to the device. Returns the number of bytes that were actually written, or -1 if an error occurred.

See also read() and writeData().

    */

/*!
    \qmlmethod MangoFile::write(const char *data)

This is an overloaded function.

Writes data from a zero-terminated string of 8-bit characters to the device. Returns the number of bytes that were actually written, or -1 if an error occurred.

See also read() and writeData().
    */

/*!
    \qmlmethod inline MangoFile::write(const QByteArray &data)
This is an overloaded function.

Writes the content of byteArray to the device. Returns the number of bytes that were actually written, or -1 if an error occurred.

See also read() and writeData().
    */



/*!
    \qmlmethod MangoFile::peek(char *data, qint64 maxlen)
Reads at most maxSize bytes from the device into data, without side effects (i.e., if you call read() after peek(), you will get the same data). Returns the number of bytes read. If an error occurs, such as when attempting to peek a device opened in WriteOnly mode, this function returns -1.

0 is returned when no more data is available for reading.

Example:

\code
bool isExeFile(QFile *file)
{
    char buf[2];
    if (file->peek(buf, sizeof(buf)) == sizeof(buf))
        return (buf[0] == 'M' && buf[1] == 'Z');
    return false;
}
\endcode

See also read().
    */

/*!
    \qmlmethod QByteArray MangoFile::peek(qint64 maxlen)
This is an overloaded function.

Peeks at most maxSize bytes from the device, returning the data peeked as a QByteArray.

Example:

\code
bool isExeFile(QFile *file)
{
    return file->peek(2) == "MZ";
}
This function has no way of reporting errors; returning an empty QByteArray can mean either that no data was currently available for peeking, or that an error occurred.
\endcode

See also read().
    */


/*!
    \qmlmethod virtual bool MangoFile::waitForReadyRead(int msecs)
Blocks until new data is available for reading and the readyRead() signal has been emitted, or until msecs milliseconds have passed. If msecs is -1, this function will not time out.

Returns true if new data is available for reading; otherwise returns false (if the operation timed out or if an error occurred).

This function can operate without an event loop. It is useful when writing non-GUI applications and when performing I/O operations in a non-GUI thread.

If called from within a slot connected to the readyRead() signal, readyRead() will not be reemitted.

Reimplement this function to provide a blocking API for a custom device. The default implementation does nothing, and returns false.

Warning: Calling this function from the main (GUI) thread might cause your user interface to freeze.

See also waitForBytesWritten().

    */

/*!
    \qmlmethod virtual bool MangoFile::waitForBytesWritten(int msecs)
For buffered devices, this function waits until a payload of buffered written data has been written to the device and the bytesWritten() signal has been emitted, or until msecs milliseconds have passed. If msecs is -1, this function will not time out. For unbuffered devices, it returns immediately.

Returns true if a payload of data was written to the device; otherwise returns false (i.e. if the operation timed out, or if an error occurred).

This function can operate without an event loop. It is useful when writing non-GUI applications and when performing I/O operations in a non-GUI thread.

If called from within a slot connected to the bytesWritten() signal, bytesWritten() will not be reemitted.

Reimplement this function to provide a blocking API for a custom device. The default implementation does nothing, and returns false.

\b{Warning:} Calling this function from the main (GUI) thread might cause your user interface to freeze.

See also waitForReadyRead().


    */


/*!
    \qmlmethod void MangoFile::ungetChar(char c)
Puts the character c back into the device, and decrements the current position unless the position is 0. This function is usually called to "undo" a getChar() operation, such as when writing a backtracking parser.

If c was not previously read from the device, the behavior is undefined.
    */

/*!
    \qmlmethod bool MangoFile::putChar(char c)
Reads at most maxSize bytes from the device into data, and returns the number of bytes read. If an error occurs, such as when attempting to read from a device opened in WriteOnly mode, this function returns -1.

0 is returned when no more data is available for reading. However, reading past the end of the stream is considered an error, so this function returns -1 in those cases (that is, reading on a closed socket or after a process has died).

See also readData(), readLine(), and write().
    */

/*!
    \qmlmethod bool MangoFile::getChar(char *c)
Reads one character from the device and stores it in c. If c is 0, the character is discarded. Returns true on success; otherwise returns false.

See also read(), putChar(), and ungetChar().

    */


/*!
    \qmlmethod QString MangoFile::errorString()
Returns a human-readable description of the last device error that occurred.

See also setErrorString().

    */



/*!
    \qmlmethod QString MangoFile::fileName()
Reimplemented from QFileDevice::fileName().

Returns the name set by setFileName() or to the QFile constructors.

See also setFileName() and QFileInfo::fileName().

    */

/*!
    \qmlmethod void MangoFile::setFileName(string &name)
Sets the name of the file. The name can have no path, a relative path, or an absolute path.

Do not call this function if the file has already been opened.

If the file name has no path or a relative path, the path used will be the application's current directory path at the time of the open() call.

Example:

\code
QFile file;
QDir::setCurrent("/tmp");
file.setFileName("readme.txt");
QDir::setCurrent("/home");
file.open(QIODevice::ReadOnly);      // opens "/home/readme.txt" under Unix
\endcode

Note that the directory separator "/" works for all operating systems supported by Qt.

See also fileName(), QFileInfo, and QDir.
    */


/*!
    \qmlmethod bool MangoFile::exists()
This is an overloaded function.

Returns true if the file specified by fileName() exists; otherwise returns false.

See also fileName() and setFileName().

    */


/*!
    \qmlmethod QString MangoFile::readLink()

    DOC ME
    */

/*!
    \qmlmethod inline MangoFile::symLinkTarget()


    */


/*!
    \qmlmethod quint64 MangoFile::size()
For open random-access devices, this function returns the size of the device. For open sequential devices, bytesAvailable() is returned.

If the device is closed, the size returned will not reflect the actual size of the device.

See also isSequential() and pos(

    */

/*!
    \qmlmethod bool MangoFile::resize(qint64 sz)
Reimplemented from QFileDevice::resize().
    */

/*!
    \qmlmethod Permissions MangoFile::permissions()
Reimplemented from QFileDevice::permissions().

See also setPermissions().

    */

/*!
    \qmlmethod bool MangoFile::setPermissions(Permissions permissionSpec)
Reimplemented from QFileDevice::setPermissions().

Sets the permissions for the file to the permissions specified. Returns true if successful, or false if the permissions cannot be modified.

See also permissions() and setFileName().


    */

