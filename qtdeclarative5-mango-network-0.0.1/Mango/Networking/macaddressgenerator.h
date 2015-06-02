#ifndef MACADDRESSGENERATOR_H
#define MACADDRESSGENERATOR_H

#include <QObject>
#include <QString>
#include <QDebug>
#include <QTime>

class MacAddressGenerator : public QObject
{
    Q_OBJECT
public:
    explicit MacAddressGenerator(QObject *parent = 0);

    Q_PROPERTY(QString macAddress READ macAddress)
    Q_INVOKABLE QString generateMacAddress();

    QString macAddress();
    void setMacAddress(const QString &mac);

signals:

public slots:
private:
    QString m_mac;
};

#endif // MACADDRESSGENERATOR_H
