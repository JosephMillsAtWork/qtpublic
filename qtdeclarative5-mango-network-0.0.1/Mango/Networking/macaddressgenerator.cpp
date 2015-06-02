#include "macaddressgenerator.h"

MacAddressGenerator::MacAddressGenerator(QObject *parent) :
    QObject(parent)
{
}
/*!
  \qmlsignal MacAddressGenerator::generateMacAddress()
  This is used to intailize the random mac addres
 */

QString MacAddressGenerator::generateMacAddress()
{

    QString possibleCharacters = "ABCDEF0123456789";
    int randomStringLength = 12;

    const int step = 2;
    const char mychar = ':';

    qsrand(QTime::currentTime().msec());
    QString rString;
    for(int i=0; i<randomStringLength; ++i)
    {

        int index = qrand() % possibleCharacters.length();
        QChar nextChar = possibleCharacters.at(index);
        rString.append(nextChar);
    }


    QString myNewMac = rString;
    for (int i = step; i <= myNewMac.size(); i+=step+1)
        myNewMac.insert(i, mychar);
    QString nm = myNewMac;

    nm.chop(1);
    qDebug() << "MACADDRESS The New Mac adress will be " << nm;
    setMacAddress(nm);
    return 0;
}

QString MacAddressGenerator::macAddress()
{
    return m_mac;
}

void MacAddressGenerator::setMacAddress(const QString &mac)
{
    m_mac = mac;
}
