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
  QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
  db.setHostName("127.0.0.1");
  db.setPort(3306);
  db.setUserName("root");
  db.setPassword("xiao");
  db.setDatabaseName("test");
  if (!db.open()) {
    QMessageBox::critical(nullptr, "错误", db.lastError().text());
    }
  else qDebug("数据库连接成功！");
}

DatabaseConnector::~DatabaseConnector()
{
     qDebug("数据库推出连接！");
}
