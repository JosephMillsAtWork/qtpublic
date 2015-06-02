/*
 * Copyright (C) 2012-2013 Joseph Mills.
 *
 */

#ifndef BONJOURBACKEND_h
#define BONJOURBACKEND_h
#include <QString>
#include <QTcpSocket>
#include "bonjourrecord.h"
#include "bonjourrecord.h"

class BonjourServiceBrowser;
class BonjourServiceResolver;
class QHostInfo;

class BonjourBackend : public QObject
{
    Q_OBJECT
    Q_PROPERTY( QString serviceName READ serviceName  WRITE setServiceName NOTIFY serviceNameChanged )
    Q_PROPERTY(QString registeredType READ registeredType)
    Q_PROPERTY(QString replyDomain READ replyDomain )

public:
    explicit BonjourBackend(QObject *parent = 0);

    QString registeredType()const;
    void setRegisteredType(const QString &registeredType);

    QString serviceName()const;
    void setServiceName(const QString &serviceName);

    QString replyDomain()const;
    void setReplyDomain(const QString &replyDomain);

    Q_INVOKABLE void runBackend();
//    Q_INVOKABLE QString getReplyDomain()const;

signals:
    void serviceNameChanged();
    void replyDomainChanged();
    void registeredTypeChanged();

public slots:
   void updateString(const QList<BonjourRecord> &list);

private:
    quint16 blockSize;
    BonjourServiceBrowser *bonjourBrowser;
    BonjourServiceResolver *bonjourResolver;
    QString m_replyDomain;
    QString m_ServiceName;
    QString m_registeredType;
    QString m_serviceName ;
};
#endif
