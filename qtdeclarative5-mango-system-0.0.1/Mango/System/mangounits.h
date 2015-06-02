/*****************************************************************************
** This file is part of the Cute App Launcher.
**
** Cute App Launcher is free software: you can redistribute it and/or modify
** it under the terms of the GNU Lesser General Public License as published by
** the Free Software Foundation, version 3 of the License.
**
** Cute App Launcher is distributed in the hope that it will be useful,
** but WITHOUT ANY WARRANTY; without even the implied warranty of
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
** GNU Lesser General Public License for more details.
**
** You should have received a copy of the GNU Lesser General Public License
** along with this program.  If not, see <http://www.gnu.org/licenses/>.
******************************************************************************
** Author: Juhapekka Piiroinen <jp+cuteapplauncher@1337.fi>
**
** Copyright (C) 2014 1337 Software Oy.
******************************************************************************/

#ifndef MangoUnits_H
#define MangoUnits_H

#include <QObject>
#include <QtQml>
#include "mangodevice.h"

class MangoUnits : public QObject
{
    Q_OBJECT

    Q_PROPERTY( int desktopWidth READ desktopWidth NOTIFY gridUnitChanged )
    Q_PROPERTY( int desktopHeight READ desktopHeight NOTIFY gridUnitChanged )
    Q_PROPERTY( int designWidth READ designWidth NOTIFY gridUnitChanged )
    Q_PROPERTY( int designHeight READ designHeight NOTIFY gridUnitChanged )
    Q_PROPERTY( double displaySize READ displaySize NOTIFY gridUnitChanged )
    Q_PROPERTY( double devicePixelRatio READ devicePixelRatio NOTIFY gridUnitChanged )
    Q_PROPERTY( double gridUnit READ gridUnit NOTIFY gridUnitChanged )

    Q_ENUMS( CuteFont )

public:
    enum CuteFont {
        FONT_NOTSET = 0,
        FONT_XXLARGE,
        FONT_XLARGE,
        FONT_LARGE,
        FONT_MEDIUM,
        FONT_NORMAL,
        FONT_SMALL,
        FONT_TINY
    };

    static QObject *singletontype_provider(QQmlEngine *engine, QJSEngine *scriptEngine);
    static MangoUnits* instance(QQmlEngine *engine);

    Q_INVOKABLE double guToPx(double units);
    Q_INVOKABLE double pxToGu(double px);

    Q_INVOKABLE void setDesignResolution(int width, int height);

    Q_INVOKABLE double font(CuteFont cutefont) { return m_fonts[cutefont]; }

signals:
    void gridUnitChanged();

protected slots:
    void updateFonts();
    void updateGridUnit();

protected:
    void initialize();
    bool isInitialized() { return m_bInitialized; }

    void setGridUnit(double unit);
    double gridUnit() { return m_gridUnit; }

    int desktopWidth() { return m_desktopGeometry.width(); }
    int desktopHeight() { return m_desktopGeometry.height(); }

    int designWidth() { return m_designResolution.width(); }
    int designHeight() { return m_designResolution.height(); }
    double displaySize() { return m_displayDiagonalSize; }
    double devicePixelRatio() { return m_devicePixelRatio; }

    bool m_bInitialized;

    double m_gridUnit;
    double m_defaultGrid;
    double m_devicePixelRatio;
    double m_dpiX;
    double m_dpiY;
    double m_displayDiagonalSize;

    QRect m_desktopGeometry;
    QRect m_designResolution;

    QMap<CuteFont, double> m_fonts;

    explicit MangoUnits(QObject *parent = 0);
    static MangoUnits* m_pInstance;
};

#endif // MANGOUNITS_H
