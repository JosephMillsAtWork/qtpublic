/*
 * Joseph Mills
*/

#ifndef MANGODEVICE_H
#define MANGODEVICE_H

#include <QObject>
#include <QtQml>
class MangoDevice : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QString deviceModelIdentifier READ deviceModelIdentifier NOTIFY dataChanged)

public:
    static QObject *singletontype_provider(QQmlEngine *engine, QJSEngine *scriptEngine);
    static MangoDevice* instance(QQmlEngine *engine);

    Q_INVOKABLE static QString deviceModelIdentifier() { return m_deviceModelIdentifier; }

signals:
    void dataChanged();

protected:
    explicit MangoDevice(QObject *parent = 0);

    static QString m_deviceModelIdentifier;
    static MangoDevice* m_pInstance;
};

#endif // MANGODEVICE_H
