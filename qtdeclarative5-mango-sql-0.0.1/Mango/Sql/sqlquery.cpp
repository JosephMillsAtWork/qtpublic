#include "sqlquery.h"

/*!
 * \qmltype SqlQuery
 * \inqmlmodule Mango.Sql 0.1
 * \ingroup Mango.Sql
 * \inherits Item
 * \since 5.3
 *  Qml plugin that is used to connect to 7 different types of databases and return all the info that one wishes. In other words it is a sql manager 
 */
SqlQuery::SqlQuery(QObject *parent) :
    QObject(parent),
    m_databaseType("mysql")
{

}

/*!
 * \qmlproperty string SqlQuery::source
 * used in QML to set the source of the database this can be a FQDN or ipaddress.
 */
QString SqlQuery::source() const
{
    return m_Source;
}
void SqlQuery::setSource(const QString &source)
{
    m_Source = source;
}

/*!
 * \qmlproperty string SqlQuery::databaseName
 * Used in QML to set the name of the database that one wishes to get info from and or change
 */
QString SqlQuery::databaseName() const
{
    return m_DbName;
}
void SqlQuery::setdatabaseName(const QString &databaseName)
{
    m_DbName = databaseName;
}
/*!
 * \qmlproperty string SqlQuery::user
 * Used in QML to set the User that will be lo0ging into the database
 */
QString SqlQuery::user() const
{
    return m_User;
}
void SqlQuery::setUser(const QString &user)
{
    m_User = user;
}
/*!
 * \qmlproperty string SqlQuery::password
 * used in qml to set the password of the database that one is going to use
 */

QString SqlQuery::password() const
{
    return m_Password;
}
void SqlQuery::setPassword(const QString &password)
{
    m_Password = password;
}

/*!
 * \qmlproperty string SqlQuery::databaseType
 * String that is used in qml to set the Type of database that one wants to connect to
 * example:
 * mysql
 *
 */
QString SqlQuery::databaseType() const
{
    return m_databaseType;
}
void SqlQuery::setdatabaseType(const QString &databaseType)
{
    m_databaseType = databaseType;
}

/*!
 * \qmlproperty int SqlQuery::port
 *  used in QML to set the port of the database that one is going to use
 */
int SqlQuery::port() const
{
    return m_Port;
}
void SqlQuery::setPort(int port)
{
    m_Port = port;
}
/*!
 * \qmlproperty bool SqlQuery::connectAuto
 * used in qml to set a auto connection to a database so one does not have to use other methods
 */
bool SqlQuery::connectAuto()const
{
    return m_ConnectAuto;
}

void SqlQuery::setConnectionAuto(bool &connectAuto)
{
    m_ConnectAuto = connectAuto;
}

/*!
 * \qmlproperty string SqlQuery::queryString
 * used in QMl to set the query string that one wishes to perform on a selected database
 */
QString SqlQuery::queryString() const
{
    return m_QueryString;
}
void SqlQuery::setQueryString(const QString &queryString)
{
    m_QueryString = queryString;
}


/*!
 * \qmlproperty string SqlQuery::connectionName
 * used in QML for setting a connection name of a data base. See QSqlDatabase::connectionNames()
 */
QString SqlQuery::connectionName() const
{
    return m_ConnectionName;
}

void SqlQuery::setConnectionName(const QString &connectionName)
{
    if(m_ConnectionName == connectionName)
        return ;
    m_ConnectionName = connectionName;
    emit connectionNameChanged();

}

/*!
 * \qmlsignal SqlQuery::currentConnection()
 * returns the current connection name of a selected database
 */
QString SqlQuery::currentConnection() const
{
 return db.connectionName();
}

/*!
 * \qmlsignal SqlQuery::close()
 * This needs a property added to it.
 * example
 * \code
 * SqlQuery{
 * id: query
 * .....
 * ........
 * ............
 * }
 * SqlQuery{
 * id:foo
 * ..........
 * ..............
 * ..................
 * }
 * Button{
 * onclicked:{
 *  query.close(foo)
 *  }
 *
 * }
 * \endcode
 * used in qmnl to disconnect for the selected database
 */
void SqlQuery::close(const QString &name)
{
    if(name == ""){
        qDebug() << "failed to close the database with the connection Name of " << name << "Here are the Databases that are open  "  << db.connectionNames();

    }
            db.removeDatabase(name);
}

/*!
 * \qmlsignal SqlQuery::running()
 * used in qml to see if the connection is still running
 */
bool SqlQuery::running()
{
    if(db.open())
    {
        m_running = true;
        return m_running;
    }
    else
    {
        m_running = false ;
        return m_running;
    }
}


/*!
 \qmlsignal SqlQuery::runQuery()
  This takes in a sqlquery command

  \code
  SqlQuery{
  id: foo
  ...
  ........
  ............

  }
 Button{
    onclicked: foo.runQuery(SELECT * FROM FOO)
    }
  \endcode
  Used to run a insert or select or whatever kinda sql statement one wishes
 */
void SqlQuery::runQuery(const QString &cmd){
    QString database_Type;
    if (m_databaseType == "mysql"){
        database_Type = "QMYSQL";
    }
    else if (m_databaseType == "postgres"){
        database_Type = "QPSQL";
    }
    else if (m_databaseType == "sqlite"){
        database_Type = "QSQLITE";
    }
    else if (m_databaseType == "sql"){
        database_Type = "QODBC";
    }

    QSqlDatabase db = QSqlDatabase::addDatabase(database_Type);

    db.setHostName(m_Source);
    db.setDatabaseName(m_DbName);
    db.setUserName(m_User);
    db.setPassword(m_Password);
    int qw;
    qw = m_Port;
    db.setPort(qw);

    if (!db.open())
    {
        qDebug() << "Failed to open databse for command " << cmd << "Last Error was " << db.lastError().text() ;
        emit running(false);
    }
    else
        qDebug() << "Database Open" ;
        emit running(true);
        db.exec(cmd);

        db.close();
//    if(db.exec(cmd)){
//         qDebug() << "command \n" << cmd << "\nCompleated Succsully ";
//        db.close();
//        emit running(false);
//        }else {
//            qDebug() << "Running  command " << cmd << "Last Error was " << db.lastError().text() ;
//            db.close();
//            emit running(false);

//        }
}
//this is for models only

/*!
 * \qmlsignal SqlQuery::createConnection()
 * used in qml to create a new connection type
 */
void SqlQuery::createConnection()
{
    QString database_Type;
    if (m_databaseType == "mysql"){
        database_Type = "QMYSQL";
    }
    else if (m_databaseType == "postgres"){
        database_Type = "QPSQL";
    }
    else if (m_databaseType == "sqlite"){
        database_Type = "QSQLITE";
    }
    else if (m_databaseType == "sql"){
        database_Type = "QODBC";
    }

    QSqlDatabase db = QSqlDatabase::addDatabase(database_Type);
    db.close();
    db.setHostName(m_Source);
    db.setDatabaseName(m_DbName);
    db.setUserName(m_User);
    db.setPassword(m_Password);
    int qw;
    qw = m_Port;
    db.setPort(qw);
    db.open();
    if (!db.open())
    {
        qDebug() << "Database Error" << db.lastError().text() ;
//        emit running(false);
    }
    else
        qDebug() << "Database Open" ;

//        emit running(true);

}

/*!
 * \qmlsignal SqlQuery::connect()
 * used in qml for a simple connection
 */
void SqlQuery::connect()
{
    if (m_ConnectAuto == true){
        createConnection();
    }
}
/*!
 \qmlsignal SqlQuery::getText(string cmd,string row)
 This is used to get back some text from a single query. I only use this for mangoSerial number and things like that.

 \b{cmd}

   The sql command that you want to run

 \b{row}

    The Row that you want to get back information from.,

  Example say that we want to this for our cmd
  \code
  ("SELECT * FROM artist");
  \endcode

  And wanted to get the row albums we would pass that in as the row
 */


void SqlQuery::getText(const QString &cmd){
    QString database_Type;
//    QSqlQuery qsql ;
    if (m_databaseType == "mysql"){
        database_Type = "QMYSQL";
    }
    else if (m_databaseType == "postgres"){
        database_Type = "QPSQL";
    }
    else if (m_databaseType == "sqlite"){
        database_Type = "QSQLITE";
    }
    else if (m_databaseType == "sql"){
        database_Type = "QODBC";
    }

    QSqlDatabase db = QSqlDatabase::addDatabase(database_Type , "connection-name");

    db.setHostName(m_Source);
    db.setDatabaseName(m_DbName);
    db.setUserName(m_User);
    db.setPassword(m_Password);
    int qw;
    qw = m_Port;
    db.setPort(qw);

    if (!db.open())
    {
        qDebug() << "Failed to open databse for command " << cmd << "Last Error was " << db.lastError().text() ;
        emit running(false);
    }
    else
        qDebug() << "Database Open" ;

    QSqlDatabase dab = QSqlDatabase::database("connection-name");
    QSqlQuery qsql(dab);

    qsql.prepare(cmd);
    if (!qsql.exec())
    {
        qDebug() << "could not run query of " << cmd << "Reson:     " << qsql.lastError().text();
        db.close();
        emit running(false);
    }
    else
    {
        QSqlRecord rec = qsql.record();
        const int rowCount = rec.count() - 1 ;
        qDebug() << "Number of columns:  " << rowCount;
        while (qsql.next()){
        m_stringResults = qsql.value(rowCount).toString();
    }
         qDebug() << "last string ?   " << m_stringResults;
         lastString();
         db.close();
         emit running(false);
    }
//
}

QString SqlQuery::lastString(){
    return m_stringResults;
}
