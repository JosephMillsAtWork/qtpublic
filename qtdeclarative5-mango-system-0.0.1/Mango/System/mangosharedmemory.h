/*
* Joseph Mills
*/
#ifndef MANGOSHAREDMEMORY_H
#define MANGOSHAREDMEMORY_H

#include <QtCore>
#include <QSharedMemory>

class MangoSharedMemory : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QString key READ key WRITE setKey NOTIFY keyChanged)

public:

    Q_INVOKABLE bool write(QVariant data);
    Q_INVOKABLE QVariant read();

signals:
    void keyChanged();

protected:
    void setKey(const QString& key) { m_sharedMemory.setKey(key); emit keyChanged(); }
    QString key() { return m_sharedMemory.key(); }

    QSharedMemory m_sharedMemory;
};

#endif // MANGOSHAREDMEMORY_H
