/*
 * Copyright (C) 2014 Joseph Mills.
 *
 */
#ifndef FILESPLUGIN_H
#define FILESPLUGIN_H

#include <QQmlExtensionPlugin>
#include <QQmlContext>
#include <QQmlEngine>
#include <QQmlComponent>
#include <QQuickItem>

class FilesPlugin : public QQmlExtensionPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "org.qt-project.Qt.QQmlExtensionInterface")

public:
    void registerTypes(const char *uri);

};

#endif // FILESPLUGIN_H

