/*
 * Copyright (C) 2014 Joseph Mills.
 *
 */
#ifndef IOREQUEST_H
#define IOREQUEST_H

#include <QObject>

class IORequest : public QObject
{
    Q_OBJECT
public:
    explicit IORequest();

public:
    virtual void run() = 0;

private:
    // hide this because IORequest should *NOT* be parented directly
    using QObject::setParent;
};

#endif // IOREQUEST_H
