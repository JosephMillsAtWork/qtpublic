/*
 * Copyright (C) 2014 Joseph Mills.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; version 3.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#include <QAbstractListModel>
#include <QStringList>

class Menu
{
public:
    Menu(const QString &name, const QString &desc,  const QString &price,const QString &extra, const QString &image,const QString &chef);
    QString name() const;
    QString desc() const;
    QString price() const;
    QString extra() const;
    QString image() const;
    QString chef() const;



private:
    QString m_name;
    QString m_desc;
    QString m_price;
    QString m_extra;
    QString m_image;
    QString m_chef;
};

class MenuModel : public QAbstractListModel
{
    Q_OBJECT
public:
    enum MenuRoles {
        NameRole = Qt::UserRole + 1,
        DescRole,
        PriceRole,
        ExtraRole,
        ImageRole,
        ChefRole
    };

    MenuModel(QObject *parent = 0);

    void addMenu(const Menu &menu);

    int rowCount(const QModelIndex & parent = QModelIndex()) const;

    QVariant data(const QModelIndex & index, int role = Qt::DisplayRole) const;

    QHash<int,QByteArray> roleNames() const;

private:
    QList<Menu> m_menus;
};


