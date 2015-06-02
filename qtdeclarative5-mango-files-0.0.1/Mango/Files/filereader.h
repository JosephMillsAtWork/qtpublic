/*
 * Copyright (C) 2014 Joseph Mills.
 *
 */
#ifndef FILEREADER_H
#define FILEREADER_H
#include <QDir>
#include <QDebug>
#include <QFile>
#include <QTextStream>
#include <QStandardPaths>
class FileReader : public QObject
{
public:
    explicit FileReader(QObject *parent = 0);
    Q_OBJECT
    Q_PROPERTY(QString fileName  READ fileName  WRITE setFileName  NOTIFY fileNameChanged)
    Q_PROPERTY(QString output READ output NOTIFY outputChanged)
    Q_INVOKABLE void readFile(const QString &filename);
    Q_INVOKABLE void refresh(const QString &fN);

    QString fileName() const;
    void setFileName(const QString &fileName);



    QString output() const;
    void setOutPut(const QString &output);


signals:
    void fileNameChanged();
    void outputChanged();
private:
    QString m_FileName;
    bool mReading;
    QString mOutput;


};

#endif // FILEREADER_H
