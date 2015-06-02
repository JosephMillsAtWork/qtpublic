/*
 * Joseph Mills
 */
#include "mangomime.h"

MangoMime* MangoMime::m_pInstance = NULL;

MangoMime::MangoMime(QObject *parent) :
    QObject(parent)
{
}

QObject* MangoMime::singletontype_provider(QQmlEngine *engine, QJSEngine *scriptEngine)
{
    Q_UNUSED(scriptEngine)
    return MangoMime::instance(engine);
}

MangoMimeType* MangoMime::get_mime_type(QString fileName) {
    QMimeDatabase db;
    return new MangoMimeType(db.mimeTypeForFile(fileName));
}

MangoMime* MangoMime::instance(QQmlEngine *engine) {
    if (!m_pInstance) {
        m_pInstance = new MangoMime(engine);
    }
    return m_pInstance;
}
