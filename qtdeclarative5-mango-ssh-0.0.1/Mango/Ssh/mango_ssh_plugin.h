/*
 * Copyright (C) 2014 Joseph Mills.
 *
 */
#ifndef MANGO_SSH_PLUGIN_H
#define MANGO_SSH_PLUGIN_H

#include <QQmlExtensionPlugin>
#include <QQmlContext>
#include <QQmlEngine>
#include <QQmlComponent>
#include <QQuickItem>

class MangoSshPlugin : public QQmlExtensionPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "org.qt-project.Qt.QQmlExtensionInterface")

public:
    void registerTypes(const char *uri);

};
#endif // MANGO_SSH_PLUGIN_H
