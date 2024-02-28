#include "mainwindow.h"
#include "./ui_mainwindow.h"


void MainWindow::on_selectAllCheckBox_stateChanged(int state)
{
    Qt::CheckState checkState = (state==Qt::Checked) ?Qt::Checked:Qt::Unchecked;
    for(int row=0;row<ui->videoInfoTableWidget->rowCount();row++){
        QTableWidgetItem *checkBoxItem = ui->videoInfoTableWidget->item(row,0);
        if(checkBoxItem){
            checkBoxItem->setCheckState(checkState);
        }
    }
}
void MainWindow::on_stationnumberpushButton_clicked()
{
    if(currentWorkspace.workspaceName.isEmpty()){
        QMessageBox::critical(this,"错误","未打开工区");
    }
    else qDebug()<<currentWorkspace.workspaceName;
    QString newStationNumber = ui->stationnumberlineSearch->text();
    QString sql=("select stationNumber,"
                   "videoName,"
                   "designDrillingDepth,"
                   "designInitiationDepth,"
                   "singleWellExplosiveAmount,"
                   "quantityOfDetonatorsPerWell,"
                   "numberOfWells,"
                   "depthOfCharging,"
                   "difference,"
                   "wellSupervisor,"
                   "inspector,"
                   "chargingDate,"
                   "inspectionDate,"
                   "drillingEvaluation,"
                   "remarks,"
                   "videoPath FROM " +currentWorkspace.workspaceName+" WHERE stationNumber = "+newStationNumber);

  this->loadTableToWidget(currentWorkspace.workspaceName,sql,ui->videoInfoTableWidget);
}
void MainWindow::on_stationnumberlineSearch_textChanged(const QString &arg1)
{
  QString sql=("select stationNumber,"
                 "videoName,"
                 "designDrillingDepth,"
                 "designInitiationDepth,"
                 "singleWellExplosiveAmount,"
                 "quantityOfDetonatorsPerWell,"
                 "numberOfWells,"
                 "depthOfCharging,"
                 "difference,"
                 "wellSupervisor,"
                 "inspector,"
                 "chargingDate,"
                 "inspectionDate,"
                 "drillingEvaluation,"
                 "remarks,"
                 "videoPath from "+currentWorkspace.workspaceName);
  this->loadTableToWidget(currentWorkspace.workspaceName,sql,ui->videoInfoTableWidget);
}
