/*
 * Copyright (C) 2014 Joseph Mills.
 *
 */
#ifndef FILEMOVE_H
#define FILEMOVE_H
#include <QDir>
#include <QDebug>
#include <QFile>
#include <QTextStream>
#include <QObject>

class FileMove : public QObject
{
    Q_OBJECT
public:
    explicit FileMove(QObject *parent = 0);
    Q_PROPERTY(QString oldFile READ oldFile WRITE setOldFile NOTIFY oldFileChanged)
    Q_PROPERTY(QString newFile READ newFile WRITE setNewFile NOTIFY newFileChanged)
    Q_INVOKABLE void moveFile();


    QString oldFile()const ;
    void setOldFile(const QString &oldfile);

    QString newFile()const ;
    void setNewFile(const QString &newfile);


    signals:
    void newFileChanged();
    void oldFileChanged();
private:
   QString m_OldFile;
   QString m_NewFile;

};

#endif // FILEMOVE_H
