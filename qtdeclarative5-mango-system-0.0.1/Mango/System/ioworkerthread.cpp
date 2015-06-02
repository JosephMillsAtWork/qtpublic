#include "ioworkerthread.h"


/*!
  Hosts a thread, lives on the main thread.

  Responsible for relaying interaction between the main thread and an IOWorkerThread.
 */
IOWorkerThread::IOWorkerThread(QObject *parent) :
    QObject(parent)
{
    mWorker.start(QThread::IdlePriority);
}

/*!
  Destroys an IOWorkerThread instance.
 */
IOWorkerThread::~IOWorkerThread()
{
    mWorker.exit();
    mWorker.wait();
}

/*!
  Attempts an asynchronous attempt to start a \a request.

  If the request may be run, it is queued, and true is returned, otherwise, false.
 */
bool IOWorkerThread::addRequest(IORequest *request)
{
    mWorker.addRequest(request);
    return true;
}
