#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QCheckBox>
void MainWindow::addVideofileRow(const QString &fileName,const QString &filePath)
{
    int row = ui->videoWidget_2->rowCount();
    ui->videoWidget_2->insertRow(row);

    QCheckBox *checkBox = new QCheckBox(this);
    checkBox->setChecked(false);
    QTableWidgetItem *item = new QTableWidgetItem(fileName);
    item->setToolTip(filePath);
    ui->videoWidget_2->setCellWidget(row,0,checkBox);
    ui->videoWidget_2->setItem(row,1,item);
}
