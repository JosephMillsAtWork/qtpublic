/*
 * Joseph Mills
*/
#include "mangosharedmemory.h"


/*!
 * \qmltype MangoSharedMemory
 * \inqmlmodule Mango.System 0.1
 * \ingroup Mango.System
 * \inherits Item
 * \since 5.3
 *  A Qml plugin for QSharedMemory provides access to a shared memory segment by multiple threads and processes. It also provides a way for a single thread or process to lock the memory for exclusive access.
 * When using this class, be aware of the following platform differences:
 *
 * Windows: QSharedMemory does not "own" the shared memory segment. When all threads or processes that have an instance of QSharedMemory attached to a particular shared memory segment have either destroyed their instance of QSharedMemory or exited, the Windows kernel releases the shared memory segment automatically.
 *
 * Unix: QSharedMemory "owns" the shared memory segment. When the last thread or process that has an instance of QSharedMemory attached to a particular shared memory segment detaches from the segment by destroying its instance of QSharedMemory, the Unix kernel release the shared memory segment. But if that last thread or process crashes without running the QSharedMemory destructor, the shared memory segment survives the crash.
 * HP-UX: Only one attach to a shared memory segment is allowed per process. This means that QSharedMemory should not be used across multiple threads in the same process in HP-UX.
 *
 * Remember to lock the shared memory with lock() before reading from or writing to the shared memory, and remember to release the lock with unlock() after you are done.
 *
 * MangoSharedMemory automatically destroys the shared memory segment when the last instance of QSharedMemory is detached from the segment, and no references to the segment remain.
 *
 * Warning: QSharedMemory changes the key in a Qt-specific way, unless otherwise specified. Interoperation with non-Qt applications is achieved by first creating a default shared memory with QSharedMemory() and then setting a native key with setNativeKey(). When using native keys, shared memory is not protected against multiple accesses on it (e.g. unable to lock()) and a user-defined mechanism should be used to achieve a such protection.
 */

/*!
  \qmlproperty string MangoSharedMemory::key
    Sets the platform independent key for this shared memory object. If key is the same as the current key, the function returns without doing anything.

    You can call key() to retrieve the platform independent key. Internally, QSharedMemory converts this key into a platform specific key. If you instead call nativeKey(), you will get the platform specific, converted key.
  */

/*!
  \qmlsignal MangoSharedMemory::write()
 used to write to a process that is in memory
*/
bool MangoSharedMemory::write(QVariant data) {
    bool retval = false;
    if (m_sharedMemory.isAttached()) m_sharedMemory.detach();

    QBuffer buffer;
    if (buffer.open(QBuffer::ReadWrite)) {
        QDataStream out(&buffer);
        out << data;
        qint64 size = buffer.size();
        if (m_sharedMemory.create(size)) {
            m_sharedMemory.lock();
            char* sharedData = (char*)m_sharedMemory.data();
            const char* bufferData = buffer.data().data();
            memcpy(sharedData,bufferData,qMin(m_sharedMemory.size(),(int)size));
            m_sharedMemory.unlock();
            retval = true;
        }
    }
    return retval;
}

/*!
  \qmlsignal MangoSharedMemory::read()
  read the data that is in the process in memory
*/
QVariant MangoSharedMemory::read() {
    QVariant retval;

    if (m_sharedMemory.attach()) {
        QBuffer buffer;
        QDataStream in(&buffer);
        m_sharedMemory.lock();
        buffer.setData((const char*)m_sharedMemory.constData(),m_sharedMemory.size());
        if (buffer.open(QBuffer::ReadOnly)) {
            in >> retval;
        }
        m_sharedMemory.unlock();
        m_sharedMemory.detach();
    }
    return retval;
}
