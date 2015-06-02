#include "systemplugin.h"
#include <qqml.h>
#include "applicationlauncher.h"
#include "iorequest.h"
#include "iorequestworker.h"
#include "menumodels.h"
#include "mangomimetype.h"
#include "mangomime.h"
#include "mangounits.h"
#include "mangodevice.h"
#include "mangoclipboard.h"
#include "mangosharedmemory.h"
#include "mdesktopentry.h"
#include "placesmodel.h"

void MangoPlugin::registerTypes(const char *uri)
{
    // @uri Mango.System
    qmlRegisterType<MangoMimeType>();
    qmlRegisterType<MangoClipboard>(uri, 0, 1, "MangoClipboard");
    //Linux stuff
    qmlRegisterType<MenuModel>(uri, 0, 1, "Menu");
    qmlRegisterType<PlacesModel>(uri, 0, 1, "PlacesModel");
    qmlRegisterType<Application>(uri, 0, 1, "Application");
    // mem mapping
    qmlRegisterType<MangoSharedMemory>(uri, 0, 1, "MangoSharedMemory");

}

// singleton instance tyes
void MangoPlugin::initializeEngine(QQmlEngine* engine, const char* uri)
{
    QQmlExtensionPlugin::initializeEngine(engine, uri);
    qmlRegisterSingletonType<MangoMime>(uri, 0, 1, "MangoMime", MangoMime::singletontype_provider);
    qmlRegisterSingletonType<MangoUnits>(uri, 0, 1, "MangoUnits", MangoUnits::singletontype_provider);
    qmlRegisterSingletonType<MangoDevice>(uri, 0, 1, "MangoDevice", MangoDevice::singletontype_provider);
}
