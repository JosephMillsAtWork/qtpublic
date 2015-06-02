#ifndef WINDOW_H
#define WINDOW_H

#include <QtCore/QObject>
#include <QtQuick/QQuickWindow>

class Window : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int surfaceRole READ surfaceRole WRITE setSurfaceRole NOTIFY surfaceRoleChanged)

public:
    explicit Window(QObject *parent = 0);
    int surfaceRole() const;
    void setSurfaceRole(int surfaceRole);

Q_SIGNALS:
    void surfaceRoleChanged(int);

private:
    QQuickWindow* m_window;
};

#endif // WINDOW_H
