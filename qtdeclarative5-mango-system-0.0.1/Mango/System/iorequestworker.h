/*
 * Copyright (C) 2014 Joseph Mills.
 *
 */
#ifndef IOREQUESTWORKER_H
#define IOREQUESTWORKER_H

#include <QObject>
#include <QThread>
#include <QMutex>
#include <QWaitCondition>

#include "iorequest.h"

class IORequestWorker : public QThread
{
    Q_OBJECT
public:
    explicit IORequestWorker();

    void addRequest(IORequest *request);

    void run();

    void exit();

private:
    QMutex mMutex;
    QWaitCondition mWaitCondition;
    QList<IORequest *> mRequests;
    bool mTimeToQuit;
};

#endif // IOREQUESTWORKER_H
