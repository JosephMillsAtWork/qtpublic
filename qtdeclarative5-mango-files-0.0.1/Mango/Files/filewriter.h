/*
 * Copyright (C) 2014 Joseph Mills.
 *
 */
#ifndef FILEWRITER_H
#define FILEWRITER_H
#include <QDir>
#include <QDebug>
#include <QFile>
#include <QTextStream>
#include <QObject>

class FileWriter : public QObject
{
    Q_OBJECT
public:
    explicit FileWriter(QObject *parent = 0);

    Q_PROPERTY(QString fileName READ fileName WRITE setFileName NOTIFY fileNameChanged)
    Q_PROPERTY(QString output READ output WRITE setOutput NOTIFY outputChanged)
    Q_PROPERTY(QString makeDir READ makeDir WRITE setMakeDir)
    Q_PROPERTY(QString  removeDir READ removeDir WRITE setRemoveDir)
    Q_PROPERTY(QString errorString READ errorString NOTIFY error)

    Q_INVOKABLE void writeFile();
    Q_INVOKABLE void clearFile(const QString &fileName);

    Q_INVOKABLE void createPath();
    Q_INVOKABLE void removePath();
    Q_INVOKABLE void changePermissions(const QString &filename , const QString &permissions);
    QString fileName() const;
    void setFileName(const QString &fileName);
    QString makeDir();
    void setMakeDir(const QString &dirPath);
    QString removeDir();
    void setRemoveDir(const QString &removeDir);


    QString output() const;
    void setOutput(const QString &output);

    QString errorString();

signals:
      void fileNameChanged();
      void outputChanged();
      bool done();
      void error(QString);
      bool running();
private:
    QString m_FileName;
    QString m_Output;
    QString m_MakeDir;
    QString m_RemoveDir;
    QString m_errorString;

};
#endif // FILEWRITER_H
