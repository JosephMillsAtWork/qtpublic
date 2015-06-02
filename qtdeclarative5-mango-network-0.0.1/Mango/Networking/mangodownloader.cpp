/*
 * Copyright (C) 2014 Joseph Mills.
 *
 */
#include <QFileInfo>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QString>
#include <QStringList>
#include <QTimer>
#include <stdio.h>
#include "mangodownloader.h"

/*!
 * \qmltype MangoDownloader
 * \inqmlmodule Mango.Networking 0.1
 * \ingroup Mango.Networking
 * \inherits Item
 * \since 5.3
 *  A Qml plugin that is used to download files from the internet.
 */
MangoDownloader::MangoDownloader(QObject *parent)
    : QObject(parent)

{
}

void MangoDownloader::append(const QStringList &urlList)
{
    foreach (QString url, urlList)
        append(QUrl::fromEncoded(url.toLocal8Bit()));

    if (downloadQueue.isEmpty())
        QTimer::singleShot(0, this, SIGNAL(finished()));
}

void MangoDownloader::append(const QUrl &url)
{
    if (downloadQueue.isEmpty())
        QTimer::singleShot(0, this, SLOT(startNextDownload()));

    downloadQueue.enqueue(url);
    ++totalCount;
}

/*!
 * \qmlsignal MangoDownloader::doDownload()
 * start the download
 */
void MangoDownloader::doDownload()
{
    QString fileToDownload = mFile ;
    append(fileToDownload);
    emit started(true);
}

/*!
 * \qmlproperty string MangoDownloader::file
 * 
 * sets the file name that one wants to use to download from the web
 */
QString MangoDownloader::file()
{
    return mFile;
}

void MangoDownloader::setFile(const QString &file)
{
    mFile = file ;
}
/*!
 * \qmlproperty string MangoDownloader::savePath
 * 
 * sets the path where one wants to save the file on the local machine
 */
QString MangoDownloader::savePath()
{
    return mPath;
}

void MangoDownloader::setSavePath(const QString &savePath)
{
    mPath = savePath;
}


QString MangoDownloader::saveFileName(const QString &downloadFile)
{
    QString path = downloadFile;
    QString basename = QFileInfo(path).fileName();

    if (basename.isEmpty())
        basename = "Mango.zip";

    if (QFile::exists(basename)) {
        // already exists, don't overwrite
        int i = 0;
        basename += '.';
        while (QFile::exists(basename + QString::number(i)+".zip"))
            ++i;

        basename += QString::number(i);
    }

    return  basename;
}
/*!
 * \qmlsignal MangoDownloader::bytesReceived()
 * 
 * Returns the bytes that the download is getting from the internet speed
 */
quint64 MangoDownloader::bytesReceived()
{
    return m_bytesReceived;
}

void MangoDownloader::setBytesRecived(const quint64 &bytesReceived)
{

    m_bytesReceived = bytesReceived;
    emit  bytesReceivedChanged();
}
/*!
 * \qmlsignal MangoDownloader::bytesTotal()
 * 
 * the total ammount of bytes that it will take to download the file from the web
 */
quint64 MangoDownloader::bytesTotal()
{
    return m_bytesTotal;
}

void MangoDownloader::setBytesTotal(const quint64 &bytesTotal)
{
    m_bytesTotal = bytesTotal;
    emit bytesTotalChanged();
}

/*!
 * \qmlsignal MangoDownloader::errorString()
 *
 * returns errors if there are any in the download.
 */

QString MangoDownloader::errorString()
{
    return m_error;
}

void MangoDownloader::setErrorString(const QString &errorString)
{
    m_error == errorString;
}
/*!
 * \qmlproperty string  MangoDownloader::units
 * 
 * set the units of the download of the file from the web
 */
QString MangoDownloader::units()
{
    return m_units;
}

void MangoDownloader::setUnits(const QString &units)
{
    if (m_units == units)
        return;
    m_units = units;
    emit unitsChanged();
}
/*!
 * \qmlsignal MangoDownloader::incommingSpeed()
 * 
 * used to get back the in-coming speed of the file that is getting downloaded
 */
double MangoDownloader::incommingSpeed()
{
    return m_speed;
}

void MangoDownloader::setincommingSpeed(const double &incommingSpeed)
{
    if(m_speed == incommingSpeed)
        return;
    m_speed = incommingSpeed;
    emit incommingSpeedChanged();
}

/*!
 * \qmlsignal MangoDownloader::startNextDownload()
 * Used if you want to download multiple files
 */
void MangoDownloader::startNextDownload()
{
    if (downloadQueue.isEmpty()) {
        qDebug() << downloadedCount << " " << totalCount << "files downloaded successfully\n";
        emit started(false);
        emit finished();
        return;
    }

    QUrl url = downloadQueue.dequeue();

    QString filename = saveFileName(mPath);
    output.setFileName(mPath + filename);
    if (!output.open(QIODevice::WriteOnly)) {
        qDebug() <<  "Problem opening save file for download";
        startNextDownload();
        return;
    }

    QNetworkRequest request(url);
    currentDownload = manager.get(request);
    connect(currentDownload, SIGNAL(downloadProgress(qint64,qint64)),
            SLOT(downloadProgress(qint64,qint64)));
    connect(currentDownload, SIGNAL(finished()),
            SLOT(downloadFinished()));
    connect(currentDownload, SIGNAL(readyRead()),
            SLOT(downloadReadyRead()));

    // prepare the output
    qDebug () << "Downloading " <<  url.toEncoded().constData() << "........";
    downloadTime.start();
}
/*!
 * \qmlsignal MangoDownloader::downloadProgress()
 * returns to total download progress in MB kb or bytes
 */
void MangoDownloader::downloadProgress(qint64 bytesReceived, qint64 bytesTotal)
{
    double speed = bytesReceived * 1000.0 / downloadTime.elapsed();
    QString unit;
    if (speed < 1024) {
        unit = "bytes/sec";
    } else if (speed < 1024*1024) {
        speed /= 1024;
        unit = "kB/s";
    } else {
        speed /= 1024*1024;
        unit = "MB/s";
    }


    setBytesRecived(bytesReceived);
    setincommingSpeed(speed);
    setUnits(unit);
    setBytesTotal(bytesTotal);

}
/*!
 * \qmlsignal MangoDownloader::downloadFinished()
 * signal that is sent when the download is finished
 */
void MangoDownloader::downloadFinished()
{
    output.close();

    if (currentDownload->error()) {
        // download failed
        setErrorString("Failed " + currentDownload->errorString());
    } else {
        qDebug() << "Succeeded. Downloading " << mPath;
    }

    currentDownload->deleteLater();
}

void MangoDownloader::downloadReadyRead()
{
    output.write(currentDownload->readAll());
}
