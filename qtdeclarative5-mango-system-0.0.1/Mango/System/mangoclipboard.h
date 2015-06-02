/*
 * Joseph Mills
 */
#ifndef MANGOCLIPBOARD_H
#define MANGOCLIPBOARD_H

#include <QApplication>
#include <QClipboard>



class MangoClipboard : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QString text READ text WRITE setText NOTIFY dataChanged)

public:
    MangoClipboard() {
        m_clipboard = QApplication::clipboard();
        connect(m_clipboard,SIGNAL(dataChanged()),this,SIGNAL(dataChanged()));
    }

signals:
    void dataChanged();

protected:
    void setText(QString text) {
        m_clipboard->setText(text);
    }

    QString text() { return m_clipboard->text(); }
    QClipboard* m_clipboard;
};

#endif // MANGOCLIPBOARD_H
