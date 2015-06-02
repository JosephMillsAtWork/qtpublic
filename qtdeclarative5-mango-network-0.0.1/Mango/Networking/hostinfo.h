/*
 * Copyright (C) 2014 Joseph Mills.
 *
 */
#ifndef HOSTINFO_H
#define HOSTINFO_H

#include <QObject>
#include <QHostInfo>
#include <QHostAddress>
#include <QString>
class HostInfo : public QObject
{
    Q_OBJECT
public:
    explicit HostInfo(QObject *parent = 0);
    Q_PROPERTY(QString hostName READ hostName WRITE setHostName)
    Q_PROPERTY(QString dotName READ dotName WRITE setDotName)
    Q_PROPERTY(bool localMachine READ localMachine WRITE setLocalMachine)
    Q_PROPERTY(QString getIpAddress READ getIpAddress)
    Q_INVOKABLE void lookup();

    QString hostName();
    void setHostName(const QString &hostName);

    QString dotName();
    void setDotName(const QString &dotName);

    QString getIpAddress();

    bool localMachine();
    void setLocalMachine(const bool &localMachine);

signals:
    void error(QString);
    void gotIp();
    void isAPi(bool);
protected slots:
    void lookedUp(const QHostInfo &host);
private :
    QString m_ipAddress;
    QString m_hostName;
    QString m_dotName;
    bool m_localMachine;
};

#endif // HOSTINFO_H
