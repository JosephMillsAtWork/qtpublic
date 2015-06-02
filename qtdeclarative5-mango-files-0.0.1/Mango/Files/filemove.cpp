/*
 * Copyright (C) 2014 Joseph Mills.
 *
 */
#include "filemove.h"
/*!
 * \qmltype FileMove
 * \inqmlmodule Mango.Files 0.1
 * \ingroup Mango.Files
 * \inherits Item
 * \since 5.3
 * A Qml plugin that is used to move files that are on the local machine.
 * EXAMPLE:
 * \code
 * ,,
 * ,,,,
 *
 * FileMove{
 *     id filemover
 *     oldFile:"/home/john/foo.txt"
 *     newFile: "/home/john/fooBar.txt"
 * }
 *
 * Button{
 *     text:"move file"
 *     onClicked: fileMover.moveFile()
 * }
 * \endcode
 */
FileMove::FileMove(QObject *parent) :
    QObject(parent)
{
}

/*!
 * \qmlproperty string FileMove::oldFile
 * 
 * used in qml to select a old file that one would like to alter
 */
QString FileMove::oldFile()const{
    return m_OldFile;
}


void FileMove::setOldFile(const QString &oldfile){
    if (m_OldFile == oldfile)
        return;
    m_OldFile = oldfile;
    emit oldFileChanged();
}

/*!
 * \qmlproperty string FileMove::newFile
 *
 * used in QML to rename a oldFile
 * also see oldfile
 */
QString FileMove::newFile()const{
    return m_NewFile;
}


void FileMove::setNewFile(const QString &newfile){
    if (m_NewFile == newfile)
        return;
    m_NewFile = newfile;
    emit newFileChanged();
}


/*!
 * \qmlsignal FileMove::moveFile()
 * 
 * Used in QML to move/rename a file
 */
void FileMove::moveFile(){
    QString oFile;
    oFile = m_OldFile;
    QString nFile;
    nFile =  m_NewFile;
    QFile mFileToMove;

    if(!mFileToMove.copy(oFile,nFile)){
        qDebug() << "Could not move File to new Place";
    }

    qDebug() << "Copied file " << oFile << "to " << nFile ;

}



