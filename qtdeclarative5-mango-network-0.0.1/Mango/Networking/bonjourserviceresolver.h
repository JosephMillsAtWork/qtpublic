/*
 * Copyright (C) 2012-2013 Joseph Mills.
 *
 */


#ifndef BONJOURSERVICERESOLVER_H
#define BONJOURSERVICERESOLVER_H

#include <QtCore/QObject>


#include <dns_sd.h>

class QSocketNotifier;
class QHostInfo;
class BonjourRecord;

class BonjourServiceResolver : public QObject
{
    Q_OBJECT
public:
    BonjourServiceResolver(QObject *parent);
    ~BonjourServiceResolver();

    void resolveBonjourRecord(const BonjourRecord &record);
//    int bonjourPort;

signals:
    void bonjourRecordResolved(const QHostInfo &hostInfo, int port);
    void error(DNSServiceErrorType error);

private slots:
    void bonjourSocketReadyRead();
    void cleanupResolve();
    void finishConnect(const QHostInfo &hostInfo);

private:
    static void DNSSD_API bonjourResolveReply(DNSServiceRef sdRef, DNSServiceFlags flags,
                                    quint32 interfaceIndex, DNSServiceErrorType errorCode,
                                    const char *fullName, const char *hosttarget, quint16 port,
                                    quint16 txtLen, const char *txtRecord, void *context);
    DNSServiceRef dnssref;
    QSocketNotifier *bonjourSocket;
    int bonjourPort;
};

#endif // BONJOURSERVICERESOLVER_H
