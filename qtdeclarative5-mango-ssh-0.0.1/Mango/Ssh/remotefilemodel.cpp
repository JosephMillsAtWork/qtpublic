#include "remotefilemodel.h"

RemoteFileModel::RemoteFileModel(QSsh::SftpFileSystemModel *parent) :
    QSsh::SftpFileSystemModel(parent)
{
}
