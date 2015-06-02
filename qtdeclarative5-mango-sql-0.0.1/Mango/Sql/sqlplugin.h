/*
 * Copyright (C) 2014 Joseph Mills.
 *
 */
#ifndef SQLPLUGIN_H
#define SqlPLUGIN_H

#include <QQmlExtensionPlugin>
#include <QQmlContext>
#include <QQmlComponent>
#include <QQuickItem>

class SqlPlugin : public QQmlExtensionPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "org.qt-project.Qt.QQmlExtensionInterface")

public:
    void registerTypes(const char *uri);

};

#endif // SqlPLUGIN_H

