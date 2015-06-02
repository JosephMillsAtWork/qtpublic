#include "mango_ssh_plugin.h"
#include <qqml.h>
#include "sftpupload.h"
#include "mangosshremoteprocess.h"
#include "generatekeys.h"
#include "remotefilemodel.h"

void MangoSshPlugin::registerTypes(const char *uri)
{
    // @uri Mango.Ssh
   qmlRegisterType<SftpUpload>(uri,0,1,"SftpUpload");
   qmlRegisterType<MangoSshRemoteProcess>(uri,0,1,"MangoSshRemoteProcess");
   qmlRegisterType<GenerateKeys>(uri,0,1,"GenerateKeys");
   qmlRegisterType<RemoteFileModel>(uri,0,1,"RemoteFileModel");
}

// singleton instance tyes

