#include "databaseconnector.h"
#include <QMessageBox>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QThread>
DatabaseConnector::DatabaseConnector()
{
  qDebug()<<"数据库的线程地址是："<<QThread::currentThread();
}

DatabaseConnector::~DatabaseConnector()
{
    qDebug("数据库退出连接！");
}

void DatabaseConnector::connectDatabase(QSqlDatabase &db)
{
  db = QSqlDatabase::addDatabase("QMYSQL");
  db.setHostName("localhost");
  db.setPort(3306);
  db.setUserName("root");
  db.setPassword("123456");
  db.setDatabaseName("rock2");
  if (!db.open()) {
    QMessageBox::critical(nullptr, "错误", db.lastError().text());
    }
  else qDebug("数据库连接成功！");
}
