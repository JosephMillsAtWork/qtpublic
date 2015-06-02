/*
 * Copyright (C) 2014 Joseph Mills.
 *
 */
#ifndef DIRREADER_H
#define DIRREADER_H

#include <QObject>
#include <QDir>
#include <QFile>
#include <QDebug>
class DirReader : public QObject
{
    Q_OBJECT
public:
    explicit DirReader(QObject *parent = 0);
    Q_PROPERTY(QString dirPath READ dirPath WRITE setDirPath NOTIFY dirPathChanged)
    Q_PROPERTY(QString files READ files NOTIFY filesChanged)
    QString dirPath()const;
    void setDirPath(const QString &path);
    Q_INVOKABLE void readFiles();
    QString files()const;
    void setFiles(const QStringList &someList);

signals:
    void dirPathChanged();
    void filesChanged();
private:
    QString m_dirPath;
    QStringList list;
    QString mFiles;


};

#endif // DIRREADER_H
