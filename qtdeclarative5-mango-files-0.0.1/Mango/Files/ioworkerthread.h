/*
 * Copyright (C) 2014 Joseph Mills.
 *
 */
#ifndef IOWORKERTHREAD_H
#define IOWORKERTHREAD_H

#include <QObject>
#include <QThread>

#include "iorequestworker.h"

class IOWorkerThread : public QObject
{
    Q_OBJECT
public:
    explicit IOWorkerThread(QObject *parent = 0);
    virtual ~IOWorkerThread();
    bool addRequest(IORequest *request);

private:
    IORequestWorker mWorker;
};

#endif // IOWORKERTHREAD_H
