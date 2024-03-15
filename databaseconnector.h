#ifndef DATABASECONNECTOR_H
#define DATABASECONNECTOR_H
#include <QSqlDatabase>

class DatabaseConnector
{
public:
    DatabaseConnector();
    ~DatabaseConnector();

    static void connectDatabase(QSqlDatabase &db);
};

#endif // DATABASECONNECTOR_H
