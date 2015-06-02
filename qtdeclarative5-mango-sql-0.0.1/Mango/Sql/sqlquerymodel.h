/*
 * Copyright (C) 2014 Joseph Mills.
 *
 */
#ifndef SQLQUERYMODEL_H
#define SQLQUERYMODEL_H
#include <QVariant>
#include <QSqlQueryModel>
#include <QSqlDatabase>
class SqlQueryModel : public QSqlQueryModel
{
    Q_OBJECT
public:

    explicit SqlQueryModel(QObject *parent = 0);
    Q_INVOKABLE  void setQuery(const QString &query, const QSqlDatabase &db = QSqlDatabase());
    Q_INVOKABLE  void setQuery(const QSqlQuery &query);
    QVariant  data(const QModelIndex &index, int role)const;
     QHash<int, QByteArray>roleNames() const;
signals:
     void compleated();

public slots:
private:
};
#endif // QSQLQUERYMODEL_H
