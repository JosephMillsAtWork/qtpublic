#include "sqlplugin.h"
#include <qqml.h>
#include "sqlquery.h"
#include "sqlquerymodel.h"

void SqlPlugin::registerTypes(const char *uri)
{
    // @uri Mango.Sql
    qmlRegisterType<SqlQuery>(uri, 0, 1, "SqlQuery");
    qmlRegisterType<SqlQueryModel>(uri, 0, 1, "SqlQueryModel");
}
