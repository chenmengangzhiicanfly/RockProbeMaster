#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QMenu>
#include <QThread>
#include<QMenuBar>
#include<QStatusBar>
#include<QLabel>
#include<QAction>
#include<QDebug>
#include<QFileDialog>
#include<QAxObject>
#include<QTimer>
#include "excelexporter.h"
#include "excelimporter.h"
#include "loginwidget.h"
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),workspaceFileManager(new WorkspaceFileManager(this))
    , ui(new Ui::MainWindow)
{

    ui->setupUi(this);
    setWindowTitle("RockProbeMaster");
    qDebug()<<"主窗口的线程地址是："<<QThread::currentThread();
//    QtConcurrent::run([&]() {
//    detectorManager=new DetectorManager;
//    detectorManager->Init(1);
//    });

//        detectorManager=new DetectorManager;
//        detectorManager->Init(1);

    float p1 = 0, p2 = 0, p3 = 0, p4 = 0;
//    LoginWidget *loginWidget = new LoginWidget(this);
//    loginWidget->show();
    //加上this 不显示的问题  setWindowFlags(Qt::Window)
//    setWindowFlags(this->windowFlags() | Qt::FramelessWindowHint | Qt::WindowCloseButtonHint);
    // 无法解决
//    LoginWidget *loginWidget = new LoginWidget();
//    loginWidget->show();
//    initStatus();
//    connect(loginWidget,&LoginWidget::successLogin,this,[=](){
//        this->show();
//    });
//    menuBar()->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    workspaceFileManager->insertVideoData("F:/test",ui->testWidget);
    for(auto temp : workspaceFileManager->videoList){
        qDebug()<<temp.stationNumber<<temp.workDate<<temp.worker<<temp.workspaceInfo.workspaceStationNumber<<temp.workspaceInfo.workspaceVideoPath
                 <<temp.workspaceInfo.workspaceLeader<<temp.workspaceInfo.workspaceName;
    }

}

MainWindow::~MainWindow()
{
    delete ui;
    qDebug("调用主窗口析构函数！");
}

void MainWindow::updateQTableWidget(QTableWidget *&qTableWidget)
{
    QSqlQuery query,query2;
    QString sqlstr=("select id,"
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
                     "status from rockprobemaster");
    query.prepare(sqlstr);
    query2.exec("select * from rockprobemaster");
    int rowCnt = 0 , column = 0;
    column=qTableWidget->columnCount();
    rowCnt=query2.size();

    if(rowCnt > 0){
        query.exec();
        ui->progressBar->setMaximum(rowCnt-1);
        ui->progressBar->setValue(0);
        ui->processDetails->setText(QString("数据加载中..."));

        for(int i=0;i<rowCnt;i++){
            ui->progressBar->setValue(i);
            query.next();
            for(int j=0;j<column;j++){
                qTableWidget->setRowCount(i+1);
                qTableWidget->setItem(i,j,new QTableWidgetItem(query.value(j).toString()));
                qTableWidget->item(i,j)->setTextAlignment(Qt::AlignVCenter|Qt::AlignHCenter);
            }
        }
    }

    qTableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    qTableWidget->verticalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    qTableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
}

void MainWindow::markQTableWidget(QTableWidget *&qTableWidget)
{
    int row=qTableWidget->rowCount();
    int errorCount = 0;
    QString status;
    for(int i=0;i<row;i++){
        status=qTableWidget->item(i,11)->text();
        if(status==QString("未检测"))
            {
            qTableWidget->item(i,11)->setBackground(QBrush(QColor(255,0,0)));
        }
        else if(status==QString("已完成"))
            {
            qTableWidget->item(i,11)->setBackground(QBrush(QColor(0,255,0)));
        }
        else errorCount++;
    }
    if(errorCount >0){
        QMessageBox::warning(this,"警告",QString("存在%1条不合规的数据").arg(errorCount));
    }
}

bool MainWindow::databaseIsEmpty(QTableWidget *qTableWidget,int row)
{
    for(int i=0;i<qTableWidget->columnCount();i++){
        if(qTableWidget->item(row,i)->text()=="")
            return false;
    }
    return true;
}


void MainWindow::exportQtable()
{
    ExcelExporter *excelExporter=new ExcelExporter;
    excelExporter->qTableWidget2Excel(ui->detailsWidget);
}

void MainWindow::importQtable()
{
    ExcelImporter *excelImporter = nullptr;
    excelImporter->Excel2qTableWidget(ui->detailsWidget);
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    int result = QMessageBox::information(this,tr("提示"),tr("是否关闭界面!"),tr("是"), tr("否"),0,1);
    if(result == 0)
    {
        //输入关闭的指令
        event->accept();
    }
    else
    {
        //输入不关闭的指令
        event->ignore();
    }
}

void MainWindow::TimeUpdate()
{
    QDateTime currentTime = QDateTime::currentDateTime();
    QString strTime = currentTime.toString(" yyyy年MM月dd日 hh:mm::ss ");
    showTimeLabel->setText(strTime);
    statusBar->addPermanentWidget(showTimeLabel);
    statusBar->setSizeGripEnabled(true);
}


void MainWindow::initStatus(){
        statusBar = new QStatusBar(this);
        setStatusBar(statusBar);

        // 在状态栏上添加版本
        QLabel *lbVersion = new QLabel;
        lbVersion->setText("V1.00");
        statusBar->addWidget(lbVersion);

        // 在状态栏上添加永久标签
//        statusBar->addPermanentWidget(new QLabel("永久标签", this));

        QTimer *timer = new QTimer(this);
        timer->start(1000);

        showTimeLabel = new QLabel(this);
        connect(timer,&QTimer::timeout,this,&MainWindow::TimeUpdate);

        // 设置状态栏显示信息
        statusBar->showMessage("欢迎使用Qt 6状态栏", 5000);  // 显示5秒后自动清除

        // 添加其他的状态栏组件和信号槽连接等
}



void MainWindow::on_loadButton_clicked()
{
    ui->detailsWidget->clearContents();
    updateQTableWidget(ui->detailsWidget);
    markQTableWidget(ui->detailsWidget);
    ui->detailsWidget->setAlternatingRowColors(true);

    QMessageBox::information(this,"提示","数据已经完全加载完毕");

    ui->progressBar->setValue(0);
    ui->processDetails->setText(QString("无"));

}


void MainWindow::on_addButton_clicked()
{
    databaseInsertPage=new DatabaseInsertPage;
    databaseInsertPage->show();
}


void MainWindow::on_deleteButton_clicked()
{
    switch(QMessageBox::warning(this,tr("删除提示"),tr("确认删除当前条目？"),QMessageBox::Yes
 | QMessageBox::No,QMessageBox::No)){
    case QMessageBox::Yes:
    {
        qDebug()<<"删除行！";
        int curRow=-1;
        curRow=ui->detailsWidget->currentRow();
        if(curRow!=-1){
            QString deleteSql=QString("delete from rockprobemaster where id='%1'").arg
                                (ui->detailsWidget->item(curRow,0)->text());
            QSqlQuery query;
            query.exec(deleteSql);
            QMessageBox::information(this,"提示","删除成功");
        }
        else {
            QMessageBox::warning(this,tr("提示"),"删除失败，当前记录为空，请先加载数据");
            return ;
        }
        updateQTableWidget(ui->detailsWidget);
        markQTableWidget(ui->detailsWidget);
    }
        break;
    case QMessageBox::No:
    {
        qDebug()<<"放弃删除";
        break;
    }
    default:
        break;
  }
}


void MainWindow::on_saveButton_clicked()
{
//  int curRow=0;
//  curRow=ui->detailsWidget->currentRow();
//  qDebug()<<"curRow";
//  if(curRow!=-1){
//        if()
//  }
}


void MainWindow::on_saveAllButton_clicked()
{
  int row=0;
  row=ui->detailsWidget->rowCount();
  QString curId="";
  QString nowTable="";
  QSqlQuery query;
  for(int i=0;i<row;i++){
        curId=ui->detailsWidget->item(i,0)->text();
        qDebug()<<curId;
        nowTable=QString("update rockprobemaster set pilenumber = '%1', "
                           "responsible_person = '%2', "
                           "date = '%3',"
                           "charge_count = '%4', "
                           "rod_count = '%5',"
                           "detonator_count = '%6',"
                           "well_depth = '%7',"
                           "charge_count_detected = '%8',"
                           "rod_count_detected = '%9',"
                           "manual_inspection = '%10',"
                           "status = '%11' where id='%12'")
                       .arg(ui->detailsWidget->item(i,1)->text())
                       .arg(ui->detailsWidget->item(i,2)->text())
                       .arg(ui->detailsWidget->item(i,3)->text())
                       .arg(ui->detailsWidget->item(i,4)->text())
                       .arg(ui->detailsWidget->item(i,5)->text())
                       .arg(ui->detailsWidget->item(i,6)->text())
                       .arg(ui->detailsWidget->item(i,7)->text())
                       .arg(ui->detailsWidget->item(i,8)->text())
                       .arg(ui->detailsWidget->item(i,9)->text())
                       .arg(ui->detailsWidget->item(i,10)->text())
                       .arg(ui->detailsWidget->item(i,11)->text())
                       .arg(curId);
        qDebug()<<nowTable;
        query.exec(nowTable);
        if (query.exec(nowTable)) {
            qDebug() << "Query executed successfully!";
        } else {
            qDebug() << "Error executing query:" << query.lastError().text();
        }
  }
  QMessageBox::information(this,"提示","全部保存成功");
}


void MainWindow::on_actionWatch_triggered()
{
  ui->stackedWidget->setCurrentWidget(ui->page);
}


void MainWindow::on_action_Excel_triggered()
{

    excelReaderAndDisplayer =new ExcelReaderAndDisplayer;
    excelReaderAndDisplayer->show();

}


void MainWindow::on_saveFileButton_clicked()
{
    qDebug()<<ui->detailsWidget->rowCount();
    if(ui->detailsWidget->rowCount() < 1){
        QMessageBox::critical(this,"警告","当前数据为空，无法导出");
    }
    else{
    this->exportQtable();
    }
}


void MainWindow::on_pushButton_2_clicked()
{
    this->importQtable();
}


void MainWindow::on_actionExit_triggered()
{
    QMessageBox::StandardButton result = QMessageBox::information(this,"退出系统","确定退出系统？",QMessageBox::Yes|QMessageBox::No,
                                                            QMessageBox::No);
    if(result==QMessageBox::Yes){
        this->close();
   }
}


void MainWindow::on_openFileButton_clicked()
{
   QString folderPath = QFileDialog::getExistingDirectory(this, "Open Folder", QDir::homePath());

   if (!folderPath.isEmpty())
   {
        QStringList nameFilters;
        nameFilters << "*.mp4";

        QStringList files = QDir(folderPath).entryList(nameFilters, QDir::Files);

        ui->videoWidget_2->setRowCount(files.size());

        for (int i = 0; i < files.size(); ++i)
        {
            QString filePath = QDir(folderPath).filePath(files.at(i));
            qDebug()<<filePath<<files.at(i);

            QTableWidgetItem *item = new QTableWidgetItem(files.at(i));
            item->setToolTip(folderPath);  // Set parent folder path as toolTip
            ui->videoWidget_2->setItem(i, 0, item);
        }
   }

}


void MainWindow::on_startDetectionButton_clicked()
{
   int row = ui->videoWidget_2->currentRow();
   int column = ui->videoWidget_2->currentColumn();
   QString fileName = ui->videoWidget_2->item(row,column)->text();
   QString folderPath = ui->videoWidget_2->item(row,column)->toolTip();
   QString filePath = QDir(folderPath).filePath(fileName);

    float p1=0,p2=0;

        qDebug()<<"检测的线程地址是："<<QThread::currentThread();
            std::string str = filePath.toStdString();
//        detectorManager->DetectAsync(str,p2, [](DetectLog detectlog) {
//            qDebug() <<QString::fromStdString(detectlog.ToString());
////                this->ui->resultText->setText("为u");
//        });


}


void MainWindow::on_action_D_triggered()
{
  ui->stackedWidget->setCurrentWidget(ui->page_2);
}


void MainWindow::on_startDetectionButton_2_clicked()
{
  int row = ui->videoWidget_2->currentRow();
  int column = ui->videoWidget_2->currentColumn();
  QString fileName = ui->videoWidget_2->item(row, column)->text();
  QString folderPath = ui->videoWidget_2->item(row, column)->toolTip();  // Get parent folder path from toolTip
  QString filePath = QDir(folderPath).filePath(fileName);

  mediaPlayer->setSource(QUrl::fromLocalFile(filePath));
  mediaPlayer->play();
}


void MainWindow::on_action_create_triggered()
{
  if(workspaceFileManager->exec()==QDialog::Accepted){
        QString tableName = workspaceFileManager->tableNameEdit->text();
        QString stationNumber = workspaceFileManager->stationNumber->text();
        QString leader = workspaceFileManager->leader->text();
        QString videoPath=workspaceFileManager->videoPath->text();
        QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
        db.setHostName("localhost");
        db.setPort(3306);
        db.setUserName("root");
        db.setPassword("123456");
        db.setDatabaseName("mydata");

        if(db.open()){
            QSqlQuery query;
            query.exec("CREATE TABLE "+tableName+"(id INT PRIMARY KEY)");
            QMessageBox::information(this, "Table Created", "New table created successfully!");
            WorkspaceInfo workspaceInfo(tableName,stationNumber,leader,videoPath);
            workspaceFileManager->saveWorkspaceInfoTOJson(workspaceInfo);
            db.close();
        } else {
            QMessageBox::warning(this, "Database Error", "Failed to open the database!");
        }
        workspaceFileManager->tableNameEdit->clear();
        workspaceFileManager->stationNumber->clear();
  }
}



void MainWindow::on_action_open_workspace_triggered()
{
  workspaceOpener = new WorkspaceOpener(this);
  if(workspaceOpener->loadWorkspacesFromJson())
        workspaceOpener->show();
  else QMessageBox::critical(this,"错误","文件没有打开");
  connect(workspaceOpener,&WorkspaceOpener::onTableItemDoubleClickedtoMain,this,&MainWindow::openWorkspaceTable);
}

void MainWindow::openWorkspaceTable(WorkspaceInfo workspace)
{
  QMessageBox::warning(this,"提示","打开成功");
  qDebug()<<workspace.workspaceName<<workspace.workspaceStationNumber;
}

