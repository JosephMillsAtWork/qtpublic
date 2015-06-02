#include "sqlquerymodel.h"
#include "sqlquery.h"
#include <QSqlRecord>
#include <QSqlField>
#include <QDebug>
#include <QVariant>
#include <QAbstractListModel>

/*!
 * \qmltype SqlQueryModel
 * \inqmlmodule Mango.Sql 0.1
 * \ingroup Mango.Sql
 * \inherits Item
 * \since 5.3
 *  A Qml plugin that is used to make models from a sqlquery
 */
SqlQueryModel::SqlQueryModel(QObject *parent) :
    QSqlQueryModel(parent)
{
}
/*!
 * \qmlproperty string SqlQueryModel::setQuery
 * used to set the query and also the database
 */
void SqlQueryModel::setQuery(const QString &query, const QSqlDatabase &db)
{
    QSqlQueryModel::setQuery(query,db);
    roleNames();
}
// set the query 
void SqlQueryModel::setQuery(const QSqlQuery &query)
{
QSqlQueryModel::setQuery(query);
   roleNames();
}

//helper for rolenames 
QHash<int, QByteArray>SqlQueryModel::roleNames() const
    {
        QHash<int,QByteArray> hash;
        for( int i = 0; i < record().count(); i++) {
            hash.insert(Qt::UserRole + i + 1, QByteArray(record().fieldName(i).toLatin1()));
        }
        return hash;
    }
// set up the model 
 QVariant SqlQueryModel::data(const QModelIndex &index, int role)const
 {
     QVariant value = QSqlQueryModel::data(index, role);
     if(role < Qt::UserRole)
     {
         value = QSqlQueryModel::data(index, role);
     }
     else
     {
         int columnIdx = role - Qt::UserRole - 1;
         QModelIndex modelIndex = this->index(index.row(), columnIdx);
         value = QSqlQueryModel::data(modelIndex, Qt::DisplayRole);
     }
     return value;
 }
