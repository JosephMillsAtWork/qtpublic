
#include "placesmodel.h"
#include <QDebug>
#include <QDir>
#include <QAbstractItemModel>
#include <QCoreApplication>
#include <QStandardPaths>
#include <QDebug>
/*!
 * \qmltype PlacesModel
 * \inqmlmodule Mango.System 0.1
 * \ingroup Mango.System
 * \inherits Item
 * \since 5.3
 * A unix only util that is used to set favourites places in a file system. Example home pictures downloads ect. Then makes a model of them places and then can be used in qml 
 */
PlacesModel::PlacesModel(QAbstractListModel *parent) :
    QAbstractListModel(parent)
{

    QStringList defaultLocations;
    // Set the storage location to a path that works well
    // with app isolation
    QString settingsLocation =
            QStandardPaths::standardLocations(QStandardPaths::ConfigLocation).first()
            + "/" + QCoreApplication::applicationName() + "/" + "places.conf";
    m_settings = new QSettings(settingsLocation, QSettings::IniFormat, this);

    // Prepopulate the model with the user locations
    // for the first time it's used
    defaultLocations.append(locationHome());
    defaultLocations.append(locationDocuments());
    defaultLocations.append(locationDownloads());
    defaultLocations.append(locationMusic());
    defaultLocations.append(locationPictures());
    defaultLocations.append(locationVideos());

    if (!m_settings->contains("storedLocations")) {
        m_locations.append(defaultLocations);
    } else {
        m_locations = m_settings->value("storedLocations").toStringList();
    }

}

PlacesModel::~PlacesModel() {

}

QString PlacesModel::standardLocation(QStandardPaths::StandardLocation location) const
{
    QStringList locations = QStandardPaths::standardLocations(location);
    QString standardLocation = "";

    foreach (const QString &location, locations) {
        // We always return the first location or an empty string
        // The frontend should check out that it exists
        if (QDir(location).exists()) {
            standardLocation = location;
            break;
        }
    }

    return standardLocation;
}

QString PlacesModel::locationHome() const
{
    return standardLocation(QStandardPaths::HomeLocation);
}

QString PlacesModel::locationDocuments() const
{
    return standardLocation(QStandardPaths::DocumentsLocation);
}

QString PlacesModel::locationDownloads() const
{
    return standardLocation(QStandardPaths::DownloadLocation);
}

QString PlacesModel::locationMusic() const
{
    return standardLocation(QStandardPaths::MusicLocation);
}

QString PlacesModel::locationPictures() const
{
    return standardLocation(QStandardPaths::PicturesLocation);
}

QString PlacesModel::locationVideos() const
{
    return standardLocation(QStandardPaths::MoviesLocation);
}

int PlacesModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)

    return m_locations.count();
}

QVariant PlacesModel::data(const QModelIndex &index, int role) const
{
    Q_UNUSED(role)

    return m_locations.at(index.row());
}

QHash<int, QByteArray> PlacesModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles.insert(Qt::UserRole, "path");

    return roles;
}

void PlacesModel::removeItem(int indexToRemove)
{

    // Tell Qt that we're going to be changing the model
    // There's no tree-parent, first new item will be at
    // indexToRemove, and the last one too
    beginRemoveRows(QModelIndex(), indexToRemove, indexToRemove);

    // Remove the actual location
    m_locations.removeAt(indexToRemove);

    // Tell Qt we're done with modifying the model so that
    // it can update the UI and everything else to reflect
    // the new state
    endRemoveRows();

    // Remove the location permanently
    m_settings->setValue("storedLocations", m_locations);
}

void PlacesModel::addLocation(const QString &location)
{
    // Do not allow for duplicates
    if (!m_locations.contains(location)) {
        // Tell Qt that we're going to be changing the model
        // There's no tree-parent, first new item will be at
        // m_locations.count(), and the last one too
        beginInsertRows(QModelIndex(), m_locations.count(), m_locations.count());

        // Append the actual location
        m_locations.append(location);


        // Tell Qt we're done with modifying the model so that
        // it can update the UI and everything else to reflect
        // the new state
        endInsertRows();

        // Store the location permanently
        m_settings->setValue("storedLocations", m_locations);
    }
}
