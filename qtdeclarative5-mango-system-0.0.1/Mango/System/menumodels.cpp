/*
 * Copyright (C) 2014 Joseph Mills.
 *
 */
#include "menumodels.h"

/*!
  \qmltype Menu
  \inqmlmodule Mango.System 0.1
  \ingroup Mango.System
  \inherits Item
  \since 5.3
  This qml plugin that is used for making menus into the model view architecture. This was made at first for making models for restaurants.
  \b{WARRNING: this plugin is under heavy development.}
 */

Menu::Menu(const QString &name, const QString &desc, const QString &price, const QString &extra, const QString &image, const QString &chef)
    : m_name(name),
      m_desc(desc),
      m_price(price),
      m_extra(extra),
      m_image(image),
      m_chef(chef)
{
}
/*!
 \qmlproperty string Menu::name
   set the name of the menu item
*/
QString Menu::name() const
{
    return m_name;
}
QString Menu::desc() const
{
    return m_desc;
}
QString Menu::price() const
{
    return m_price;
}
QString Menu::extra() const
{
    return m_extra;
}
QString Menu::image() const
{
    return m_image;
}
QString Menu::chef() const
{
    return m_chef;
}

MenuModel::MenuModel(QObject *parent)
    : QAbstractListModel(parent)
{
}

void MenuModel::addMenu(const Menu &menu)
{
    beginInsertRows(QModelIndex(), rowCount(), rowCount());
    m_menus << menu;
    endInsertRows();
}

int MenuModel::rowCount(const QModelIndex &) const {
    return m_menus.count();
}

QVariant MenuModel::data(const QModelIndex & index, int role) const {
    if (index.row() < 0 || index.row() > m_menus.count())
        return QVariant();
    const Menu &menu = m_menus[index.row()];
    if (role == NameRole)
        return menu.name();
    else if (role == DescRole)
        return menu.desc();
    else if (role == PriceRole)
        return menu.price();
    else if (role == ExtraRole)
        return menu.extra();
    else if (role == ImageRole)
        return menu.image();
    else if (role == ChefRole)
        return menu.chef();
    return QVariant();
}

QHash<int, QByteArray> MenuModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[NameRole] = "name";
    roles[DescRole] = "desc";
    roles[PriceRole] = "price";
    roles[ExtraRole] = "extra";
    roles[ImageRole] = "image";
    roles[ChefRole] = "chef";
    return roles;
}
