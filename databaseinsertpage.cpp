#include "databaseinsertpage.h"
#include "ui_databaseinsertpage.h"

DatabaseInsertPage::DatabaseInsertPage(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DatabaseInsertPage)
{
    ui->setupUi(this);
}

DatabaseInsertPage::~DatabaseInsertPage()
{
    delete ui;
    qDebug()<<"清除内容";
}



void DatabaseInsertPage::on_verifyButton_clicked()
{
    QString insertSql=QString("insert into rockprobemaster(id,"
                                "pilenumber,"
                                "responsible_person,"
                                "date,"
                                "charge_count,"
                                "rod_count,"
                                "detonator_count,"
                                "well_depth,"
                                "charge_count_detected,"
                                "rod_count_detected,"
                                "manual_inspection,"
                                "status)"
                                "values('%1',"
                                "%2,"
                                "%3,"
                                "%4,"
                                "%5,"
                                "%6,"
                                "%7,"
                                "%8,"
                                "%9,"
                                "%10,"
                                "%11,"
                                "%12)")
                            .arg(ui->id_2->text())
                            .arg(ui->pilenumber_2->text())
                            .arg(ui->responsible_person_2->text())
                            .arg(ui->date_2->text())
                            .arg(ui->charge_count_2->text())
                            .arg(ui->rod_count_2->text())
                            .arg(ui->detonator_count_2->text())
                            .arg(ui->well_depth_2->text())
                            .arg(ui->charge_count_detected_2->text())
                            .arg(ui->rod_count_detected_2->text())
                            .arg(ui->manual_inspection_2->text())
                            .arg(ui->status_2->text());
    QSqlQuery query;

    if (query.exec(insertSql)) {
        qDebug() << "Query executed successfully!";
    } else {
        qDebug() << "Error executing query:" << query.lastError().text();
    }


}


void DatabaseInsertPage::on_cancelButton_clicked()
{
    this->close();
}

