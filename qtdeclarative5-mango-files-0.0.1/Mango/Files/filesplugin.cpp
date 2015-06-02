#include "filesplugin.h"
#include "dirmodel.h"
#include "dirreader.h"
#include "filemove.h"
#include "filereader.h"
#include "filewriter.h"
#include "mangofile.h"
#include "mangodir.h"
#include "iorequest.h"
#include "iorequestworker.h"
#include "mangofilesystemwatcher.h"
#include "mangosavefile.h"
#include "mangotemporaryfile.h"
#include "mangofileinfo.h"
#include <qqml.h>


void FilesPlugin::registerTypes(const char *uri)
{
    // @uri Mango.Files
    qmlRegisterType<DirModel>(uri, 0, 1, "DirModel");
    qmlRegisterType<DirReader>(uri, 0, 1, "DirReader");
    qmlRegisterType<FileMove>(uri, 0, 1, "FileMove");
    qmlRegisterType<FileReader>(uri, 0, 1, "FileReader");
    qmlRegisterType<FileWriter>(uri, 0, 1, "FileWriter");
    qmlRegisterType<MangoFile>(uri, 0, 1, "MangoFile");
    qmlRegisterType<MangoDir>(uri, 0, 1, "MangoDir");
    qmlRegisterType<MangoSaveFile>(uri, 0, 1, "MangoSaveFile");
    qmlRegisterType<MangoTemporaryFile>(uri, 0, 1, "MangoTemporaryFile");
    qmlRegisterType<MangoFileInfo>(uri, 0, 1,"MangoFileInfo");
    qmlRegisterType<MangoFileSystemWatcher>(uri, 0, 1, "MangoFileSystemWatcher");
}

