/*
 * Copyright (C) 2014 Joseph Mills.
 *
 */
#include "dirreader.h"

/*!
 *  \qmltype DirReader 
 *  \inqmlmodule Mango.Files 0.1
 *  \ingroup Mango
 *  \inherits Item
 *  \since 5.3
 * A Qml plugin that is used for management of direcortys and the ability to alter them. 
 */

DirReader::DirReader(QObject *parent) :
    QObject(parent)
{
}

/*!
 * \qmlproperty string  DirReader::dirPath
 * 
 * sets the path of the directory that on wishes to look at in QML
 */
QString DirReader::dirPath()const{
return m_dirPath;

}


void DirReader::setDirPath(const QString &path){
    if(m_dirPath == path)
        return ;
      m_dirPath = path ;
      emit dirPathChanged();
}

/*!
 * \qmlproperty string DirReader::setFiles
 *
 * used in Qml to return information about some file and or files
 */
void DirReader::setFiles(const QStringList &someList){
    mFiles  = someList.join("");
    mFiles = someList.join(",");
    emit filesChanged();
}


QString DirReader::files()const {
    return mFiles;
}

/*!
 * \qmlproperty string  DirReader::readFiles
 * used in qml to read files that are on a system
 */
void DirReader::readFiles(){
    QDir mDir(m_dirPath);
    foreach (QFileInfo mInfo, mDir.entryList(QDir::AllEntries|QDir::NoDotAndDotDot)){
        list.append(mInfo.fileName());
//        qDebug() << "Files = " << mInfo.fileName();
    }
       setFiles(list);
}
