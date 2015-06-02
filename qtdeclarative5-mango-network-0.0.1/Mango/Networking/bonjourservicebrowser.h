/*
 * Copyright (C) 2012-2013 Joseph Mills.
 *
 *
 */


#ifndef BONJOURSERVICEBROWSER_H
#define BONJOURSERVICEBROWSER_H

#include <QObject>
#include <dns_sd.h>
#include "bonjourrecord.h"

class QSocketNotifier;
class BonjourServiceBrowser : public QObject
{
    Q_OBJECT
public:
    BonjourServiceBrowser(QObject *parent = 0);
    ~BonjourServiceBrowser();
    void browseForServiceType(const QString &serviceType);

    inline QList<BonjourRecord> currentRecords() const { return bonjourRecords; }
    inline QString serviceType() const { return browsingType; }

signals:
    void currentBonjourRecordsChanged(const QList<BonjourRecord> &list);
    void error(DNSServiceErrorType err);

private slots:
    void bonjourSocketReadyRead();

private:
    static void DNSSD_API bonjourBrowseReply(DNSServiceRef , DNSServiceFlags flags, quint32,
                                   DNSServiceErrorType errorCode, const char *serviceName,
                                   const char *regType, const char *replyDomain, void *context);
    DNSServiceRef dnssref;
    QSocketNotifier *bonjourSocket;
    QList<BonjourRecord> bonjourRecords;
    QString browsingType;
};

#endif // BONJOURSERVICEBROWSER_H
