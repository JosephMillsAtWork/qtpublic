#ifndef MANGOMIME_H
#define MANGOMIME_H

#include <QObject>
#include "mangomimetype.h"

class MangoMime : public QObject
{
    Q_OBJECT

public:
    Q_INVOKABLE static MangoMimeType* get_mime_type(QString fileName);
    static QObject *singletontype_provider(QQmlEngine *engine, QJSEngine *scriptEngine);
    static MangoMime* instance(QQmlEngine *engine);

protected:
    explicit MangoMime(QObject *parent = 0);
    static MangoMime* m_pInstance;
};

#endif // MANGOMIME_H
