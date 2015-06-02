/*
 * Copyright (C) 2014 Joseph Mills.
 *
 */
#ifndef MANGO_PLUGIN_H
#define MANGO_PLUGIN_H

#include <QQmlExtensionPlugin>
#include <QQmlContext>
#include <QQmlEngine>
#include <QQmlComponent>
#include <QQuickItem>

class MangoPlugin : public QQmlExtensionPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "org.qt-project.Qt.QQmlExtensionInterface")

public:
    void registerTypes(const char *uri);
    virtual void initializeEngine(QQmlEngine* engine, const char* uri);

};

#endif // MANGO_PLUGIN_H

