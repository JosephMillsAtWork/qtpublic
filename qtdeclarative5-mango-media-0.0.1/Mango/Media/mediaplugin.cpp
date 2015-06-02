#include "mediaplugin.h"
#include <qqml.h>
#include "soundrecorder.h"



void MangoPlugin::registerTypes(const char *uri)
{
    // @uri Mango.Media
    qmlRegisterType<SoundRecorder>(uri, 0, 1, "SoundRecorder");

}
