#include "iconprovider.h"

#include <QIcon>
#include <QDebug>
 /*!
  \qmltype IconProvider
  \inqmlmodule Mango.System 0.1
  \ingroup Mango.System
  \inherits Item
  \since 5.3
  This is a internal class that is used on linux machines to get the path of icons in themes. Or to set a Icons Theme .
  \b{ this plugin is under heavy development. }
 */
IconProvider::IconProvider():
  QQuickImageProvider(QQuickImageProvider::Pixmap)
{
    QString theme = QIcon::themeName();
    qDebug() << "current extra theme is " << theme;
//    QIcon::setThemeSearchPaths("/usr/share/icons/");
    QIcon::setThemeName("Faenza");
}
/*!

 */
QPixmap IconProvider::requestPixmap(const QString &id, QSize *realSize, const QSize &requestedSize)
{
    QIcon icon;
    Q_FOREACH (const QString &name, id.split(",", QString::SkipEmptyParts)) {
        icon = QIcon::fromTheme(name);
        if (!icon.isNull()) {
            if (requestedSize.isValid()) {
                *realSize =requestedSize;
                return icon.pixmap(requestedSize);
            } else {
                QList<QSize> sizes = icon.availableSizes();
                if (sizes.count() > 0 && sizes.last().isValid()) {
                    *realSize = sizes.last();
                } else {
                    *realSize = QSize(32,32);
                }
                return icon.pixmap(*realSize);
            }
            break;
        }
    }
    return  QPixmap();
}
