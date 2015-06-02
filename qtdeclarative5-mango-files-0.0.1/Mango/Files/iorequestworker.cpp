#include <QMutexLocker>
#include <QDebug>

#include "iorequestworker.h"
#include "iorequest.h"

/*!
  Lives on an IOWorkerThread.

  Responsible for running IORequest jobs on the thread instance, and
  disposing of their resources once they are done.
 */
IORequestWorker::IORequestWorker()
    : QThread()
    , mTimeToQuit(false)
{
}

void IORequestWorker::addRequest(IORequest *request)
{
    request->moveToThread(this);

    // TODO: queue requests so we run the most important one first
    QMutexLocker lock(&mMutex);
    mRequests.append(request);

    // wake run()
    mWaitCondition.wakeOne();
}

void IORequestWorker::run()
{
    forever {
        QMutexLocker lock(&mMutex);

        if (mTimeToQuit)
            return;

        if (mRequests.empty())
            mWaitCondition.wait(&mMutex);

        while (!mRequests.isEmpty()) {
            IORequest *request = mRequests.takeFirst();

            lock.unlock();

            request->run();
            request->deleteLater();

            lock.relock();
        }
    }
}

void IORequestWorker::exit()
{
    qDebug() << Q_FUNC_INFO << "Quitting";
    QMutexLocker lock(&mMutex);
    mTimeToQuit = true;
    mWaitCondition.wakeOne();
}
