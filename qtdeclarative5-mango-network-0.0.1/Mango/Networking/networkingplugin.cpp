#include "networkingplugin.h"
#include <qqml.h>
#include "bonjour.h"
#include "bonjourrecord.h"
#include "bonjourregister.h"
#include "bonjourservicebrowser.h"
#include "bonjourserviceresolver.h"
#include "dnslookup.h"
#include "mangodownloader.h"
#include "oauth2.h"
#include "hostinfo.h"
#include "macaddressgenerator.h"
#include"mangosslsocket.h"


void MangoPlugin::registerTypes(const char *uri)
{
    // @uri Mango.Networking
    qmlRegisterType<MacAddressGenerator>(uri, 0,1,"MacAddressGenerator");

    // networking stuff
    qmlRegisterType<BonjourBackend>(uri, 0, 1, "Bonjour");
    qmlRegisterType<DnsLookUp>(uri, 0, 1, "DNSLookup");
    qmlRegisterType<OAuth2>(uri, 0, 1, "OAuth2");
    qmlRegisterType<MangoDownloader>(uri, 0, 1, "MangoDownloader");
    qmlRegisterType<HostInfo>(uri, 0, 1, "HostInfo");
    qmlRegisterType<MangoSslSocket>(uri, 0, 1, "MangoSslSocket");

}


