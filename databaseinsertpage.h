#ifndef DATABASEINSERTPAGE_H
#define DATABASEINSERTPAGE_H

#include <QDialog>
#include <QString>
#include <QSqlQuery>
#include <QSqlError>

namespace Ui {
class DatabaseInsertPage;
}

class DatabaseInsertPage : public QDialog
{
    Q_OBJECT

public:
    explicit DatabaseInsertPage(QWidget *parent = nullptr);
    ~DatabaseInsertPage();

private slots:


    void on_verifyButton_clicked();

    void on_cancelButton_clicked();

private:
    Ui::DatabaseInsertPage *ui;
    QString id;
    QString pilenumber;
    QString responsible_person;
    QString date;
    QString charge_count;
    QString rod_count;
    QString detonator_count;
    QString well_depth;
    QString charge_count_detected;
    QString rod_count_detected;
    QString manual_inspection;
    QString status;
    QSqlQuery sql;
};

#endif // DATABASEINSERTPAGE_H
