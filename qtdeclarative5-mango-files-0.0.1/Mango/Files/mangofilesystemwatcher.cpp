#include "mangofilesystemwatcher.h"

MangoFileSystemWatcher::MangoFileSystemWatcher(QObject *parent) :
    QObject(parent)
{
    connect(&m_fileSystemWatcher,SIGNAL(directoryChanged(QString)),this,SIGNAL(directoryChanged(QString)));
    connect(&m_fileSystemWatcher,SIGNAL(fileChanged(QString)),this,SIGNAL(fileChanged(QString)));
}
