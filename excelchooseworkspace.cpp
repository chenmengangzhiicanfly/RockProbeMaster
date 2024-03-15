#include "excelchooseworkspace.h"
#include "ui_excelchooseworkspace.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QCheckBox>
excelChooseWorkspace::excelChooseWorkspace(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::excelChooseWorkspace)
{
    ui->setupUi(this);
    workspaceInit();
}

excelChooseWorkspace::~excelChooseWorkspace()
{
    delete ui;
}

void excelChooseWorkspace::addRow(QString rowtext)
{

}

void excelChooseWorkspace::workspaceInit()
{
    QSqlQuery query;
    if (!query.exec("SELECT workspaceName FROM tablelist")) {
        qDebug() << "Failed to execute query:" << query.lastError().text();
        return;
    }
    int rowCount =0;
    ui->tableWidget->clearContents();
    ui->tableWidget->setRowCount(0);
    ui->tableWidget->setColumnWidth(0, 10); // 第一列的索引是 0
    while(query.next()){
//        qDebug() << query.value(0).toString()<<"\n";
        ui->tableWidget->insertRow(rowCount);
        QTableWidgetItem *checkBoxItem = new QTableWidgetItem();
        checkBoxItem->setCheckState(Qt::Unchecked);

        ui->tableWidget->setItem(rowCount, 0, checkBoxItem);

        QTableWidgetItem *item = new QTableWidgetItem(query.value(0).toString());
        ui->tableWidget->setItem(rowCount,1,item);

        rowCount++;
    }
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    ui->tableWidget->verticalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableWidget->setAlternatingRowColors(true);
    ui->tableWidget->setColumnWidth(0, 10); // 第一列的索引是 0
}

void excelChooseWorkspace::on_pushButton_clicked()
{
    QStringList workspace;
    for (int row = 0; row < ui->tableWidget->rowCount(); ++row) {
        // 处理每一行的数据
         QTableWidgetItem* item = ui->tableWidget->item(row,0);
         if(item->checkState()){
             workspace<<ui->tableWidget->item(row,1)->text();
//             qDebug()<<ui->tableWidget->item(row,1)->text()<<"\n";
         }
    }
    emit workspacelist(workspace);
    this->close();
}

