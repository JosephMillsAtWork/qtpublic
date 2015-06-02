/*
 * Joseph Mills
 */
#ifndef MANGOMIMETYPE_H
#define MANGOMIMETYPE_H

#include <QObject>
#include <QtCore>
#include <QtQml>
#include <QMimeType>

class MangoMimeType : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString name READ name NOTIFY dataChanged)
    Q_PROPERTY(QString comment READ comment NOTIFY dataChanged)
    Q_PROPERTY(QString genericIconName READ genericIconName NOTIFY dataChanged)
    Q_PROPERTY(QString iconName READ iconName NOTIFY dataChanged)
    Q_PROPERTY(QStringList globPatterns READ globPatterns NOTIFY dataChanged)
    Q_PROPERTY(QStringList parentMimeTypes READ parentMimeTypes NOTIFY dataChanged)
    Q_PROPERTY(QStringList allAncestors READ allAncestors NOTIFY dataChanged)
    Q_PROPERTY(QStringList aliases READ aliases NOTIFY dataChanged)
    Q_PROPERTY(QStringList suffixes READ suffixes NOTIFY dataChanged)
    Q_PROPERTY(QString preferredSuffix READ preferredSuffix NOTIFY dataChanged)
    Q_PROPERTY(QString filterString READ filterString NOTIFY dataChanged)
    Q_PROPERTY(bool isValid READ isValid NOTIFY dataChanged)
    Q_PROPERTY(bool isDefault READ isDefault NOTIFY dataChanged)

    friend class MangoMime;

public:
    Q_INVOKABLE bool inherits(const QString &mimeTypeName) const {
        return m_mimeType.inherits(mimeTypeName);
    }



signals:
    void dataChanged();

protected:
    MangoMimeType(QObject *parent=0) : QObject(parent) {}

    MangoMimeType(QMimeType mimeType) {
        m_mimeType = mimeType;
    }

    bool isValid() const {
        return m_mimeType.isValid();
    }

    bool isDefault() const {
        return m_mimeType.isDefault();
    }

    QString name() const {
        return m_mimeType.name();
    }

    QString comment() const {
        return m_mimeType.comment();
    }

    QString genericIconName() const {
        return m_mimeType.genericIconName();
    }

    QString iconName() const {
        return m_mimeType.iconName();
    }

    QStringList globPatterns() const {
        return m_mimeType.globPatterns();
    }

    QStringList parentMimeTypes() const {
        return m_mimeType.parentMimeTypes();
    }

    QStringList allAncestors() const {
        return m_mimeType.allAncestors();
    }

    QStringList aliases() const {
        return m_mimeType.aliases();
    }

    QStringList suffixes() const {
        return m_mimeType.suffixes();
    }

    QString preferredSuffix() const {
        return m_mimeType.preferredSuffix();
    }

    QString filterString() const {
        return m_mimeType.filterString();
    }

    QMimeType m_mimeType;
};

#endif // MANGOMIMETYPE_H
