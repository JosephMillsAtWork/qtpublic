#include "hostinfo.h"


/*!
  \qmltype HostInfo
  \inqmlmodule Mango.Networking 0.1
  \ingroup Mango.Networking
  \inherits Item
  \since 5.3
  This Qml plugin is used to look up ip address of local machines and also non-local machine,
  it then returns the ipaddress of the machine.
  \code
  HostInfo{
      id: looker
      hostName: "mangoES"
      dotName:  ".local"
      Componet.onCompleted:{
           lookupedup()
           var ipadd = getIpAdresss()
           console.log("this is the ip address for " +  machine  +"\n" + ipadd )
          }
  }
  \endcode
 */

HostInfo::HostInfo(QObject *parent) :
    QObject(parent),
    m_localMachine(true)
{
}

/*!
 * \qmlproperty string HostInfo::hostName
 * set the host name of the mdns that you would like to look up.
 */
QString HostInfo::hostName()
{
    return m_hostName;
}

void HostInfo::setHostName(const QString &hostName)
{
    m_hostName = hostName;
}
/*!
 * \qmlproperty string HostInfo::dotName
 * for systems that are sitting on the .local domain .local should be used I guess esp if it is a linux OS that is using avahi.
 * This can be left blank if one is looking to look up a ipaddress buy a FQDN see QHostInfo Docs for that,
 */
QString HostInfo::dotName()
{
    return m_dotName;
}

void HostInfo::setDotName(const QString &dotName)
{
    m_dotName = dotName;
}

/*!
 \qmlproperty bool HostInfo::localMachine
  Used to look up a ipaddress of a machine that is not on the local network, When using this there is no need to set the dotName
  Default this is set to true.

 EXAMPLE:

 \code
  HostInfo{
      id: looker
      localMachine: false
      hostName: "www.kde.org"
      Componet.onCompleted:{
           lookupedup()
           var ipadd = getIpAdresss()
           console.log("this is the ip address for " +  hostName  +"\n" + ipadd )
          }
   }

 \endcode
 */

bool HostInfo::localMachine()
{
    return m_localMachine;
}

void HostInfo::setLocalMachine(const bool &localMachine)
{
    m_localMachine = localMachine;
}


void HostInfo::lookedUp(const QHostInfo &host)
{
    if (host.error() != QHostInfo::NoError) {       
        qDebug() << "Lookup failed for " << host.hostName() << "Are you sure that it is live ? Here is the error string " << host.errorString();
        emit error(host.errorString());
        return;
    }

    foreach (const QHostAddress &address, host.addresses()){
//        qDebug() << "Found address:" << address.toString();
        m_ipAddress.append(address.toString());
        emit gotIp();
    }
}

/*!
 * \qmlsignal HostInfo::lookup()
 * this is a signal that is passed that loops up the host name.  To retrive the host's ip getIpAddress
 */
void HostInfo::lookup(){
    if(m_localMachine == true)
    {
        QString hs = m_hostName;
        QString addDot = m_dotName;
        hs.append(addDot);
        if( hs == QHostInfo::localHostName() ){
            qDebug() << "can not find the machine " << m_hostName << " with the local dot name of " << m_dotName;
            emit isAPi(true);
        }
        emit isAPi(false);
        QHostInfo::lookupHost(hs,this,SLOT(lookedUp(QHostInfo)));
    }
    else
    {
        QString hs = m_hostName;
        if( hs == QHostInfo::localHostName() ){
            qDebug() << "can not find the machine " << m_hostName;
            emit isAPi(true);
        }
        emit isAPi(false);
        QHostInfo::lookupHost(hs,this,SLOT(lookedUp(QHostInfo)));
    }
}
/*!
 * \qmlmethod string HostInfo::getIpAddress()
  return the ipaddress of devices looked up ,

  see also lookup()
 */
QString HostInfo::getIpAddress(){
    return m_ipAddress;
}
