#include "serialportplugin.h"
#include <qqml.h>
#include "mangoserialport.h"
void MangoPlugin::registerTypes(const char *uri)
{
    // @uri Mango.SerialPort
    // mem mapping
    qmlRegisterType<MangoSerialPort>(uri, 0, 1, "MangoSerialPort");

}
