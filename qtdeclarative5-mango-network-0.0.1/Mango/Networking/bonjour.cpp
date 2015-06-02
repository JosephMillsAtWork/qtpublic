/*
 * Copyright (C) 2012-2013 Joseph Mills.
 *
 *
 */

#include <QtNetwork>
#include "bonjour.h"
#include "bonjourservicebrowser.h"
#include "bonjourserviceresolver.h"
#include <QDebug>
#include <QHostInfo>

/*!
  \qmltype BonjourBackend
    \inqmlmodule Mango 0.1
    \ingroup Mango.Networking
    \inherits Item
    \since 5.3
 * \b{UPDATE: this is going to be deppriciated  }
 * used by qml to set a tcp file spo that one can look for bonjour/avahi services
 */

BonjourBackend::BonjourBackend(QObject *parent)
    : QObject(parent), bonjourResolver(0)
{
}

/*!
 * \qmlsignal BonjourBackend::runBackend()
 * used to run all of the parameters
 */
void BonjourBackend::runBackend(){
    BonjourServiceBrowser *bonjourBrowser = new BonjourServiceBrowser(this);
    setenv("AVAHI_COMPAT_NOWARN","1",1);
    connect(bonjourBrowser, SIGNAL(currentBonjourRecordsChanged(const QList<BonjourRecord> &)),
            this, SLOT(updateString(const QList<BonjourRecord> &)));
    bonjourBrowser->browseForServiceType(m_ServiceName);
}

/*!
 * \qmlproperty string BonjourBackend::serviceName
 * 
 * used in Qml to set the tcp file of the zeroconf/bonjour/avahi
 * that one wish's to find
 */
QString BonjourBackend::serviceName() const
{
    return m_ServiceName;
}

void BonjourBackend::setServiceName(const QString &serviceName)
{
    if(m_ServiceName == serviceName)
        return;
    m_ServiceName = serviceName;
    emit serviceNameChanged();
}

/*!
 * \qmlproperty string BonjourBackend::registeredType
 * 
 * type of registered service
 */

QString BonjourBackend::registeredType()const
{
    return m_registeredType;
}

void BonjourBackend::setRegisteredType(const QString &registeredType)
{
    if(m_registeredType == registeredType)
        return;
    m_registeredType = registeredType;
    emit registeredTypeChanged();

}

/*!
 * \qmlsignal BonjourBackend::replyDomain()
 * 
 * used in QML to get back the replay domain of the tcp files
 */
QString BonjourBackend::replyDomain()const
{
    return m_replyDomain;
}


void BonjourBackend::setReplyDomain(const QString &replyDomain)
{
    if(m_replyDomain == replyDomain)
    return;
    m_replyDomain = replyDomain;
    emit replyDomainChanged();

}


/*!
 * \qmlsignal BonjourBackend::updateString()
 * 
 * used in Qml to return a sting list of all the registration types there service name and there domain
 */
void BonjourBackend::updateString(const QList<BonjourRecord> &list)
{
 foreach(BonjourRecord record ,list){
                m_registeredType.append(record.registeredType) ;
                m_serviceName.append(record.serviceName) ;
                m_replyDomain.append(record.replyDomain) ;
                }


//    qDebug() << "THIS IS Service Name = " << m_serviceName.replace("]","]\n");
//    qDebug() << "THIS IS Reg  Name = " << regName;
//    qDebug() << "THIS IS DOMAIN Name = " << domain;

}

