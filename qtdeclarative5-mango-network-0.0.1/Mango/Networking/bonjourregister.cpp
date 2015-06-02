/*
 * Copyright (C) 2012-2013 Joseph Mills.
 *
 */
#include <QSocketNotifier>
#include <QtEndian>
#include <QDebug>
#include <stdlib.h>
#include "bonjourregister.h"

#define LOC QString("Bonjour: ")

BonjourRegister::BonjourRegister(QObject *parent)
  : QObject(parent), m_dnssref(0), m_socket(NULL)
{
    setenv("AVAHI_COMPAT_NOWARN", "1", 1);
}

BonjourRegister::~BonjourRegister()
{
    if (m_socket)
        m_socket->setEnabled(false);

    if (m_dnssref)
    {
     qDebug() << QString("De-registering service '%1' on '%2'").arg(m_type.data()).arg(m_name.data());
        DNSServiceRefDeallocate(m_dnssref);
    }
    m_dnssref = 0;

    m_socket->deleteLater();
    m_socket = NULL;
}

bool BonjourRegister::Register(uint16_t port, const QByteArray &type,
                              const QByteArray &name, const QByteArray &txt)
{
    if (m_dnssref)
    {
        qDebug() << "Service already registered.";
        return true;
    }

    uint16_t qport = qToBigEndian(port);
    DNSServiceErrorType res =
        DNSServiceRegister(&m_dnssref, 0, 0, (const char*)name.data(),
                           (const char*)type.data(),
                           NULL, 0, qport, txt.size(), (void*)txt.data(),
                           BonjourCallback, this);

    if (kDNSServiceErr_NoError != res)
    {
        qDebug() <<  QString("Error: %1").arg(res);
    }
    else
    {
        int fd = DNSServiceRefSockFD(m_dnssref);
        if (fd != -1)
        {
            m_socket = new QSocketNotifier(fd, QSocketNotifier::Read, this);
            m_socket->setEnabled(true);
            connect(m_socket, SIGNAL(activated(int)),
                    this, SLOT(socketReadyRead()));
            return true;
        }
    }

    qDebug() << "Failed to register service.";
    return false;
}


void BonjourRegister::socketReadyRead()
{
    DNSServiceErrorType res = DNSServiceProcessResult(m_dnssref);
    if (kDNSServiceErr_NoError != res)
        qDebug() << QString("Read Error: %1").arg(res);
}


void BonjourRegister::BonjourCallback(DNSServiceRef ref, DNSServiceFlags flags,
                                      DNSServiceErrorType errorcode,
                                      const char *name, const char *type,
                                      const char *domain, void *object)
{
    (void)ref;
    (void)flags;

    BonjourRegister *bonjour = static_cast<BonjourRegister *>(object);
    if (kDNSServiceErr_NoError != errorcode)
    {
      qDebug() << QString("Callback Error: %1").arg(errorcode);
    }
    else if (bonjour)
    {
//        qDebug() <<
//            QString("Service registration complete: name '%1' type '%2' domain: '%3'")
//            .arg(QString::fromUtf8(name)).arg(QString::fromUtf8(type))
//            .arg(QString::fromUtf8(domain));
        bonjour->m_name = name;
        bonjour->m_type = type;
    }
    else
    {
        qDebug() <<
            QString("BonjourCallback for unknown object.");
    }
}
