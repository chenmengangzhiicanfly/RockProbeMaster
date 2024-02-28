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
#include<QTreeWidget>
#include<QTreeWidgetItem>
#include<QCheckBox>
#include "databaseconnector.h"
#include "excelexporter.h"
#include "excelimporter.h"
#include "loginwidget.h"
#include <atomic>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),workspaceFileManager(new WorkspaceFileManager(this)),detectorManager(DetectorManagerSingleton::getInstance())
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("RockProbeMaster");
    qDebug()<<"主窗口的线程地址是："<<QThread::currentThread();
    DatabaseConnector::connectDatabase(db);

    connect(this, &MainWindow::detectionComplete, this, &MainWindow::handleDetectionCompleted);
    connect(this, &MainWindow::setTotalVideoCount, this, &MainWindow::handleSetTotalVideoCount);
    connect(this,&MainWindow::detectionAllComplete,this,&MainWindow::handleDetectionAllCompleted);

    //        QtConcurrent::run([&]() {
    //        detectorManager.Init(2);
    //        });


    //    LoginWidget *loginWidget = new LoginWidget(this);
    //    loginWidget->show();
    //加上this 不显示的问题  setWindowFlags(Qt::Window)
    //    setWindowFlags(this->windowFlags() | Qt::FramelessWindowHint | Qt::WindowCloseButtonHint);
    // 无法解决
    //    LoginWidget *loginWidget = new LoginWidget();
    //    loginWidget->show();

    initStatus();
    //    connect(loginWidget,&LoginWidget::successLogin,this,[=](){
    //        this->show();
    //    });
    //    menuBar()->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    //        setupConnections();

}

MainWindow::~MainWindow()
{
    delete ui;
    qDebug("调用主窗口析构函数！");
}

void MainWindow::setupConnections(){

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

void MainWindow::DetectorSizeSet(int NewSize)
{
            QtConcurrent::run([&]() {
            detectorManager.Init(2);
    });
}

void MainWindow::handleDetectionCompleted()
{
    videoDetectionProcessBar->setValue(videoDetectionProcessBar->value() + 1);
    if(videoDetectionProcessBar->value()==videoDetectionProcessBar->maximum()){
        videoDetectionProcessBar->setVisible(false);
        QMessageBox::information(this,"提示","检测已经全部完成");
        emit detectionAllComplete();
    }

}

void MainWindow::handleSetTotalVideoCount(int videoTotal)
{
    videoDetectionProcessBar->setValue(0);
    videoDetectionProcessBar->setMaximum(videoTotal);
}

void MainWindow::handleDetectionAllCompleted()
{
    ui->startDetectionButton_MainPage->setEnabled(true);
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
        //添加检查进度
        videoDetectionProcessBar = new QProgressBar();
        videoDetectionProcessBar->setMinimum(0);
        videoDetectionProcessBar->setVisible(false);
        statusBar->addWidget(videoDetectionProcessBar);



        QTimer *timer = new QTimer(this);
        timer->start(1000);

        showTimeLabel = new QLabel(this);
        connect(timer,&QTimer::timeout,this,&MainWindow::TimeUpdate);

        // 设置状态栏显示信息
        /*statusBar->showMessage("欢迎使用Qt 6状态栏", 5000); */ // 显示5秒后自动清除

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
   ui->filelineEdit->setText(folderPath);
   if (!folderPath.isEmpty())
   {
        QStringList nameFilters;
        nameFilters << "*.mp4";

        QStringList files = QDir(folderPath).entryList(nameFilters, QDir::Files);
        for (int i = 0; i < files.size(); ++i)
        {
            QString filePath = QDir(folderPath).filePath(files.at(i));
            qDebug()<<filePath<<files.at(i);
            this->addVideofileRow(files.at(i),filePath);
            //            QTableWidgetItem *item = new QTableWidgetItem(files.at(i));
            //            item->setToolTip(folderPath);  // Set parent folder path as toolTip
            //            ui->videoWidget_2->setItem(i, 0, item);
        }
   }
}


void MainWindow::on_startDetectionButton_clicked()
{
   int row_count = ui->videoWidget_2->rowCount();
   int totalTasks = 0;
   int completedTasks = 0;
   QTimer *progressTimer = new QTimer(this);
   progressTimer->setInterval(500);
   // 连接定时器的槽函数
   connect(progressTimer, &QTimer::timeout, this, [this]() {
       // 直接使用 p2 引用更新进度条
       int progressValue = static_cast<int>(p * 100);
       ui->detectProgressBar->setValue(progressValue);

       // 在这里可以进行其他与 p2 相关的操作
       // 例如：this->ui->resultText->setText(QString::fromStdString(currentDetectlog.ToString()));
   });
   connect(progressTimer, &QTimer::timeout, this, [this, &completedTasks, totalTasks]() {
       if (totalTasks > 0) {
           // 计算整体进度
           int overallProgress = static_cast<int>((completedTasks / static_cast<float>(totalTasks)) * 100);
           ui->totaldetectProgressBar->setValue(overallProgress);
       }
   });

   // 在循环外部启动定时器
   progressTimer->start();
   ui->detectProgressBar->setRange(0, 100);  // 设置进度条范围
   ui->detectProgressBar->setValue(0);
   ui->totaldetectProgressBar->setRange(0, 100);  // 设置进度条范围
   ui->totaldetectProgressBar->setValue(0);
   for(int i=0;i<row_count;i++){
        QCheckBox *checkBox = qobject_cast<QCheckBox*>(ui->videoWidget_2->cellWidget(i, 0));
        if(checkBox && checkBox->isChecked()){
            totalTasks++;
            int row = i;
            int column = 1;
            QString fileName = ui->videoWidget_2->item(row,column)->text();
            QString filePath = ui->videoWidget_2->item(row,column)->toolTip();

            p=0;
            qDebug()<<"检测的线程地址是："<<QThread::currentThread();
                    std::string str = filePath.toStdString();
            qDebug() <<filePath;
            detectorManager.DetectAsync(str, p, [this, &completedTasks, totalTasks,filePath](DetectLog detectlog) {
                currentDetectlog = detectlog;
                qDebug() <<QString::fromStdString(currentDetectlog.ToString());

                QMetaObject::invokeMethod(this, [this, &completedTasks, totalTasks,filePath]() {
                    completedTasks++;  // 完成的任务数加一


                    QString temp = QString("视频%1:\n药柱数量为：%2,爆炸杆数量为: %3").arg(filePath).arg(currentDetectlog.GetExplosiveRodCount()).arg(currentDetectlog.GetDepthRodCount());
//                    this->ui->resultText->setText(QString::fromStdString(currentDetectlog.ToString()));
                    this->ui->resultText->append(temp);
                });
            });
        }

   }
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

// 创建工区
void MainWindow::on_action_create_triggered()
{
  if(workspaceFileManager->exec()==QDialog::Accepted){
        QString tableName = workspaceFileManager->tableNameEdit->text();
        QString leader = workspaceFileManager->leader->text();
        QString videoPath=workspaceFileManager->videoPath->text();

        if(db.open()){
            WorkspaceInfo workspaceInfo(tableName,leader,videoPath);
            QTableWidget *videoshow = new QTableWidget();
//            workspaceFileManager->insertVideoData("F:/test",workspaceInfo,videoshow);
            workspaceFileManager->insertVideoData(videoPath,workspaceInfo,videoshow);
            workspaceFileManager->saveWorkspaceInfoTOJson(workspaceInfo);
            workspaceFileManager->createOrInsertMasterTable(workspaceInfo);   //将该表进行登记,汇总在大表中
            workspaceFileManager->createTableInDatabase(tableName);   //建造工区- 建表

           workspaceFileManager->insertDataIntoTable(workspaceFileManager->videoList,workspaceInfo);

            videoshow->setWindowTitle("视频信息");
            videoshow->show();
        } else {
            QMessageBox::warning(this, "Database Error", "Failed to open the database!");
        }
        workspaceFileManager->tableNameEdit->clear();

  }
}


void MainWindow::on_action_open_workspace_triggered()
{
  workspaceOpener = new WorkspaceOpener(this);
  //  if(workspaceOpener->loadWorkspacesFromJson())
  //        workspaceOpener->show();
  //  else QMessageBox::critical(this,"错误","文件没有打开");
  if(workspaceOpener->loadWorkspaceInfoFromDatabase()){
        qDebug()<<"加载数据表";
        workspaceOpener->show();
  }
  else QMessageBox::critical(this,"错误","数据库表没有打开");
  connect(workspaceOpener,&WorkspaceOpener::onTableItemDoubleClickedtoMain,this,&MainWindow::openWorkspaceTable);
}

void MainWindow::openWorkspaceTable(QString table)
{
  QMessageBox::warning(this,"提示","打开成功");
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
                 "videoPath from "+table);
  this->loadTableToWidget(table,sql,ui->videoInfoTableWidget);
  workspaceOpener->close();
  currentWorkspace.workspaceName = table;
  QTreeWidgetItem *workspaceItem = new QTreeWidgetItem(ui->treeWidget);
  workspaceItem->setText(0,table);
}

void MainWindow::loadTableToWidget(QString tableName,QString sqlstr, QTableWidget *qTableWidget)
{
  QSqlQuery query;
  query.prepare(sqlstr);
  if (!query.exec()) {
        qDebug() << "Query failed: " << query.lastError().text();
        return;
  }

  int rowCount =0;
  int columnCount=qTableWidget->columnCount();

  qTableWidget->clearContents();
  qTableWidget->setRowCount(0);

  while (query.next()) {
        int row = rowCount++;
        qTableWidget->insertRow(row);

        //添加复选框到第一列
        QTableWidgetItem *checkBoxItem = new QTableWidgetItem();
        checkBoxItem->setCheckState(Qt::Unchecked);
        qTableWidget->setItem(row, 0, checkBoxItem);

        for (int column = 1; column < columnCount; ++column) {
            QVariant value = query.value(column);
            if(!value.isValid()){
                qDebug()<<column;
            }//无法得到最后一列
            QTableWidgetItem *item = new QTableWidgetItem(query.value(column-1).toString());
            qTableWidget->setItem(row, column, item);
            qTableWidget->item(row,column)->setTextAlignment(Qt::AlignVCenter|Qt::AlignHCenter);
            if(column == 1){
            item->setToolTip(query.value(columnCount-1).toString());
        }
    }
}

  qTableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
  qTableWidget->verticalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
  qTableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
  qTableWidget->setAlternatingRowColors(true);

  //设置单元格文本对齐方式
//  for (int row = 0; row < rowCount; ++row) {
//        for (int column = 0; column < columnCount; ++column) {
//            qTableWidget->item(row, column)->setTextAlignment(Qt::AlignVCenter | Qt::AlignHCenter);
//        }
//  }
}



void MainWindow::on_action_detectors_triggered()
{
  detectorSizeSettings = new DetectorSizeSettings();
  detectorSizeSettings->show();/*
  connect(detectorSizeSettings,&DetectorSizeSettings::detectSizeChanged,this,&MainWindow::DetectorSizeSet);*/
  connect(detectorSizeSettings, &DetectorSizeSettings::detectSizeChanged, this, [this](int newSize) {
      // 启动线程来执行 detectorManager.Init
      QFuture<void> future = QtConcurrent::run([this, newSize]() {
          detectorManager.Init(newSize);

          // 在主线程中更新 UI
          QMetaObject::invokeMethod(this, [this]() {
              // 这里可以在主线程中执行任何 UI 更新操作
          });
      });

      // 等待线程完成
      future.waitForFinished();
  });
}

void MainWindow::updateProgressBar(int progress)
{

}







void MainWindow::on_action_main_triggered()
{
    ui->stackedWidget->setCurrentWidget(ui->mainPage);
}

