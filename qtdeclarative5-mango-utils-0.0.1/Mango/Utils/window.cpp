
#include "window.h"
#include <QDebug>


Window::Window(QObject *parent)
    : QObject(parent),
      m_window(static_cast<QQuickWindow*>(parent))
{
}

int Window::surfaceRole() const
{
    return m_window->property("surfaceRole").toInt();
}

void Window::setSurfaceRole(int surfaceRole)
{
    qDebug() << "setSurfaceRole" << surfaceRole;
    m_window->setProperty("SurfaceRole", surfaceRole);
}
