/*
 * Copyright (C) 2014 Joseph Mills.
 *
 */
#ifndef DNSLOOKUP_H
#define DNSLOOKUP_H
#include <QDnsLookup>
#include <QObject>

class DnsLookUp : public QObject
{
    Q_OBJECT
public:
    explicit DnsLookUp(QObject *parent = 0);

    Q_INVOKABLE void start();
signals:
   void finished();

protected slots:
      void handleServers();

private:
    QDnsLookup m_dns;
};

#endif // DNSLOOKUP_H
