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
#include<QAbstractItemModel>
#include<QFileSystemModel>
#include<QTreeView>
#include <QStandardItemModel>
#include <QStandardItem>
#include<QCheckBox>
#include "databaseconnector.h"
#include "excelexporter.h"
#include "excelimporter.h"
#include "excelchooseworkspace.h"
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

    initqTableWidgetToDatabaseMap(ui->videoInfoTableWidget);

    filterInit();
//    ui->groupBox_6->setFlat(true);
    model = new QStandardItemModel(this);
    model->setColumnCount(1);//设置为2列
    ui->treeView->setHeaderHidden(false);//设置列头可见
    model->setHorizontalHeaderLabels(QStringList() << QStringLiteral("目录"));
    ui->treeView->setEditTriggers(QTreeView::NoEditTriggers);//设置双击不能编辑
    ui->treeView->setModel(model);
    connect(ui->treeView,&QAbstractItemView::doubleClicked,this,&MainWindow::treeviewDoubleClicked);
    currentWorkspace.workspaceItem=nullptr;
    ui->treeView->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(ui->treeView, &QTreeView::customContextMenuRequested, this, &MainWindow::onCustomContextMenuRequested);







    connect(this, &MainWindow::detectionComplete, this, &MainWindow::handleDetectionCompleted);
    connect(this, &MainWindow::setTotalVideoCount, this, &MainWindow::handleSetTotalVideoCount);
    connect(this,&MainWindow::detectionAllComplete,this,&MainWindow::handleDetectionAllCompleted);
    connect(this, &MainWindow::deleteTimerAndPointer, this, &MainWindow::deleteTimerAndPointerSlot);
    workspacetreelistInit();
    workspacetableInit();
    themeInit();



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
void MainWindow::workspacetreelistInit()
{
    ui->pushButton->hide();
    ui->pushButton_4->hide();
    ui->pushButton_5->hide();
    ui->commitChangeToDatabasePushbutton->hide();
    ui->startDetectionButton_MainPage->hide();


    workspaceBar = new QToolBar(this);
    QVBoxLayout* layout = new QVBoxLayout();
    layout->setSpacing(1);
    layout->setContentsMargins(1,1,1,1);
    layout->addWidget(workspaceBar);
    workspaceBar->layout()->setContentsMargins(1,1,1,1);
    workspaceBar->layout()->setSpacing(1);
    layout->addWidget(ui->treeView);
    QSize iconsize(15,15);
    workspaceBar->setIconSize(iconsize);
    QAction* myAction = new QAction(QIcon(":/videoWidget/images/create.png"), "创建工区", this);

    workspaceBar->addAction(myAction);
    QAction* myAction1 = new QAction(QIcon(":/videoWidget/images/update.png"), "更新日期", this);
    workspaceBar->addAction(myAction1);
    QAction* myAction2 = new QAction(QIcon(":/videoWidget/images/open.png"), "打开工区", this);
    workspaceBar->addAction(myAction2);
    QAction* myAction3 = new QAction(QIcon(":/videoWidget/images/find.png"), "查找", this);
    workspaceBar->addAction(myAction3);
    ui->workspacewidget->setLayout(layout);
    connect(myAction,&QAction::triggered,this,&MainWindow::on_action_create_triggered);
    connect(myAction1,&QAction::triggered,this,&MainWindow::on_pushButton_clicked);
    connect(myAction2,&QAction::triggered,this,&MainWindow::on_action_open_workspace_triggered);
//    connect(myAction3,&QAction::triggered,this,&MainWindow::on_action_open_workspace_triggered);

}

void MainWindow::workspacetableInit()
{
    QSize iconsize(15,15);
    videotableBar = new QToolBar(ui->tablewidget);
    videotableBar->layout()->setContentsMargins(1,1,1,1);
    videotableBar->layout()->setSpacing(10);
    videotableBar->setIconSize(iconsize);
    QVBoxLayout* layout1 = new QVBoxLayout();
    layout1->addWidget(videotableBar);
    layout1->addWidget(ui->videoInfoTableWidget);
//    layout1->addWidget(ui->treeView);
    layout1->setSpacing(1);
    layout1->setContentsMargins(1,1,1,1);
    QAction* myAction0 = new QAction(QIcon(":/videoWidget/images/shaixuan.png"), "筛选", this);
    videotableBar->addAction(myAction0);
    QAction* myAction11 = new QAction(QIcon(":/videoWidget/images/find.png"), "查找桩号", this);
    videotableBar->addAction(myAction11);
    QAction* myAction21 = new QAction(QIcon(":/videoWidget/images/update.png"), "更新列表", this);
    videotableBar->addAction(myAction21);
    QAction* myAction31 = new QAction(QIcon(":/videoWidget/images/start.png"), "开始检测", this);
    videotableBar->addAction(myAction31);
    QAction* myAction41 = new QAction(QIcon(":/videoWidget/images/24gf-stop.png"), "停止检测", this);
    videotableBar->addAction(myAction41);
    QAction* myAction51 = new QAction(QIcon(":/videoWidget/images/push.png"), "上传数据", this);
    videotableBar->addAction(myAction51);
    QAction* myAction61 = new QAction(QIcon(":/videoWidget/images/review.png"), "视频复查", this);
    videotableBar->addAction(myAction61);

    videotableBar->addSeparator();
    videotableBar->addWidget(ui->label_5);
    videotableBar->addWidget(ui->differenceThreshold);
    ui->tablewidget->setLayout(layout1);
    QWidget* spacer = new QWidget();
    spacer->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);

    // 将伸缩的空白小部件添加到工具栏
    videotableBar->addWidget(spacer);

//    QCheckBox *checkbox = new QCheckBox("全选", this);
    videotableBar->addWidget(ui->selectAllCheckBox);
//    connect(myAction0,&QAction::triggered,this,&MainWindow::on_pushButton_clicked);

    ui->widget_2->hide();
//    ui->widget_2->setStyleSheet("background-color: white;");

    connect(myAction21,&QAction::triggered,this,&MainWindow::on_pushButton_clicked);
    connect(myAction31,&QAction::triggered,this,&MainWindow::on_startDetectionButton_MainPage_clicked);
    connect(myAction41,&QAction::triggered,this,&MainWindow::on_pushButton_clicked);
    connect(myAction51,&QAction::triggered,this,&MainWindow::on_commitChangeToDatabasePushbutton_clicked);
    connect(myAction0,&QAction::triggered,this,&MainWindow::filterwidgetshow);
    connect(myAction11,&QAction::triggered,this,&MainWindow::stationnumbersearchshow);


    //    connect(myAction0,&QAction::triggered, [&]{
//        if(!ui->widget->isVisible()){
//            int x=videotableBar->x()+videotableBar->height();
//            int y=videotableBar->y();
//            ui->widget->show();
////            ui->widget->move(x,y);
//        }else{
//            ui->widget->hide();
//        }
//    });
//    connect(myAction11,&QAction::triggered, [&]{
//        if(!ui->widget->isVisible()){
//            int x=videotableBar->x()+videotableBar->height();
//            int y=videotableBar->y();
//            ui->videoWidget_2->show();
//            ui->videoWidget_2->move(x,y);
//        }else{
//            ui->videoWidget_2->hide();
//        }
//    });
//    connect(myAction61,&QAction::triggered,this,&MainWindow::on_pushButton_4_clicked);
//    connect(checkbox,&QCheckBox::stateChanged,this,&MainWindow::on_selectAllCheckBox_stateChanged);
//    connect(myAction0)
}

MainWindow::~MainWindow()
{
    delete ui;
    qDebug("调用主窗口析构函数！");
}

void MainWindow::setupConnections(){

}

void MainWindow::updateCellInfo(QTableWidget *qTable, int row, int column, const QString &newText)
{
    QTableWidgetItem *newItem = new QTableWidgetItem(newText);
    qTable->setItem(row,column,newItem);
}

void MainWindow::updateCurrentDatabase(int row, QString tableName, QTableWidget *qTableWidget)
{

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

void MainWindow::handleDetectionCompleted(int row,double wellDepth)
{
    //表内数据的刷新
    QString wellDepthstr = QString::number(wellDepth,'f',1);
    this->updateCellInfo(ui->videoInfoTableWidget,row,10,wellDepthstr);
    this->calculateDifference(ui->videoInfoTableWidget,row);
    this->updateInspectionDate(ui->videoInfoTableWidget,row);
    this->ui->videoInfoTableWidget->item(row,8)->setText("已处理");

    //更新数据库
    this->updateCurrentDatabase(row,this->currentWorkspace.workspaceName,ui->videoInfoTableWidget);

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

void MainWindow::initqTableWidgetToDatabaseMap(QTableWidget *qTable)
{
        QStringList tableList={
            "stationNumber",
            "videoName",
            "designDrillingDepth",
            "designInitiationDepth",
            "singleWellExplosiveAmount",
            "quantityOfDetonatorsPerWell",
            "numberOfWells",
            "processingStatus",
            "reviewStatus",
            "depthOfCharging",
            "difference",
            "wellSupervisor",
            "inspector",
            "chargingDate",
            "inspectionDate",
            "drillingEvaluation",
            "remarks"
        };
    for(int col=1;col < qTable->columnCount();col++){
        QString columnName = qTable->horizontalHeaderItem(col)->text();
        qTableWidgetToDatabaseMap[columnName] = tableList.at(col-1);
    }

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
        QString tableName = workspaceFileManager->workspace->text();
        QString leader = workspaceFileManager->leader->text();
        QString videoPath = workspaceFileManager->videoPath->text();
        QString excelPath = workspaceFileManager->workspaceExcel->text();
        if(db.open()){
            WorkspaceInfo workspaceInfo(tableName,leader,videoPath,excelPath);
            QTableWidget *videoshow = new QTableWidget();
//            workspaceFileManager->insertVideoData("F:/test",workspaceInfo,videoshow);
            workspaceFileManager->insertVideoData(workspaceInfo,videoshow);
//            workspaceFileManager->saveWorkspaceInfoTOJson(workspaceInfo);
            workspaceFileManager->createOrInsertMasterTable(workspaceInfo);   //将该表进行登记,汇总在大表中
            workspaceFileManager->createTableInDatabase(tableName);   //建造工区- 建表

           workspaceFileManager->insertDataIntoTable(workspaceFileManager->videoList,workspaceInfo);

            videoshow->setWindowTitle("视频信息");
            videoshow->show();
        } else {
            QMessageBox::warning(this, "Database Error", "Failed to open the database!");
        }
        workspaceFileManager->workspace->clear();

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

void MainWindow::openWorkspaceTable(QString table,QString path)
{

    int topLevelItemCount = model->rowCount();
    for (int i = 0; i < topLevelItemCount; ++i) {
        QModelIndex index = model->index(i, 0); // 获取一级节点的索引
        QVariant nodeData = index.data(Qt::DisplayRole); // 获取节点的数据
        if(table==nodeData.toString()){
            treeviewDoubleClicked(index);
            QMessageBox::warning(this,"提示","打开成功");
            workspaceOpener->close();
            return;
        }
        //        qDebug() << "一级节点" << i << ": " << nodeData.toString();
    }

  QMessageBox::warning(this,"提示","打开成功");
  QString sql=("select stationNumber,"
                 "videoName,"
                 "designDrillingDepth,"
                 "designInitiationDepth,"
                 "singleWellExplosiveAmount,"
                 "quantityOfDetonatorsPerWell,"
                 "numberOfWells,"
                 "processingStatus,"
                 "reviewStatus,"
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


  if(currentWorkspace.workspaceItem!=nullptr){
      QBrush brush(Qt::white);
      currentWorkspace.workspaceItem->setData(brush,Qt::BackgroundRole);
  }

    QStandardItem* rootfile = new QStandardItem(table);
    rootfile->setIcon(QIcon(":/videoWidget/images/project.png"));

    QBrush brush(QColor(173, 216, 230));
    rootfile->setData(brush, Qt::BackgroundRole);
//      connect(rootfile,&)
    model->appendRow(rootfile);
    QDir dir(path);
    if (!dir.exists()) {
        qDebug() << "The specified directory does not exist.";
//              return QStringList();
    }

    dir.setFilter(QDir::Dirs | QDir::NoDotAndDotDot); // Only retrieve directories
    QFileInfoList subfolders = dir.entryInfoList();

    QStringList subfolderNames;
    foreach (const QFileInfo& subfolderInfo, subfolders) {
       subfolderNames << subfolderInfo.fileName();
    }
    foreach (const QString& subfileName, subfolderNames) {
        QStandardItem* itemChild = new QStandardItem(subfileName);

        itemChild->setIcon(QIcon(":/videoWidget/images/file.png"));
        itemChild->setCheckable(true); // 设置为可选中
        itemChild->setCheckState(Qt::Checked); // 默认选中状态
        rootfile->appendRow(itemChild);
    }

    currentWorkspace.workspaceName=table;
    currentWorkspace.workspaceVideoPath=path;
    currentWorkspace.workspaceItem=rootfile;

    workspaceFilterInit(currentWorkspace.workspaceName);

//  currentWorkspace.workspaceName = table;
//  QTreeWidgetItem *workspaceItem = new QTreeWidgetItem(ui->treeWidget);
//  workspaceItem->setText(0,table);
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

void MainWindow::loadQTableWidgettoDatabase(QString tableName, QTableWidget *qTableWidget)
{
  // 检查传入的参数是否有效
  if (tableName.isEmpty()  || qTableWidget == nullptr) {
    qDebug() << "Invalid input parameters.";
    return;
  }

  // 连接数据库
  QSqlDatabase db = QSqlDatabase::database(); // 使用默认的数据库连接
  if (!db.isValid()) {
    qDebug() << "Database is not valid.";
    return;
  }

  // 开始事务
  if (!db.transaction()) {
    qDebug() << "Failed to start transaction:" << db.lastError().text();
    return;
  }

  // 准备更新数据的 SQL 语句
  QString updateSql = "UPDATE " + tableName + " SET ";
  int columnCount = qTableWidget->columnCount();

  // 逐行遍历 QTableWidget，并更新数据库中的记录
  for (int row = 0; row < qTableWidget->rowCount(); ++row) {
    QString setValues;
    for (int col = 1; col < columnCount; ++col) {
        QTableWidgetItem *item = qTableWidget->item(row, col);
        if (item) {
            QString columnName = qTableWidget->horizontalHeaderItem(col)->text();
            setValues += qTableWidgetToDatabaseMap[columnName] + "='" + item->text() + "'";
            if (col < columnCount - 1) {
                setValues += ",";
            }
        }
    }

    QString updateQuery = updateSql + setValues + " WHERE stationNumber = "+qTableWidget->item(row,1)->text();
    QSqlQuery query;
    if (!query.exec(updateQuery)) {
        qDebug() << "Failed to update data:" << query.lastError().text();
        db.rollback(); // 回滚事务
        return;
    }
  }

  // 提交事务
  if (!db.commit()) {
    qDebug() << "Failed to commit transaction:" << db.lastError().text();
    return;
  }

  qDebug() << "Data successfully updated in database.";
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
      detectorSizeSettings->close();
      this->isDetectorInitialized=true;
  });
}

void MainWindow::updateProgressBar(int progress)
{

}

void MainWindow::on_action_main_triggered()
{
    ui->stackedWidget->setCurrentWidget(ui->mainPage);
}

void MainWindow::on_pushButton_clicked()
{
//    QString allsql;
    int childrowcount=currentWorkspace.workspaceItem->rowCount();
    QList<QStandardItem*> childItems;
    QString sql=("select stationNumber,"
                 "videoName,"
                 "designDrillingDepth,"
                 "designInitiationDepth,"
                 "singleWellExplosiveAmount,"
                 "quantityOfDetonatorsPerWell,"
                 "numberOfWells,"
                 "processingStatus,"
                 "reviewStatus,"
                 "depthOfCharging,"
                 "difference,"
                 "wellSupervisor,"
                 "inspector,"
                 "chargingDate,"
                 "inspectionDate,"
                 "drillingEvaluation,"
                 "remarks,"
                 "videoPath from "+currentWorkspace.workspaceName)+
            " where chargingDate = '";
    for (int i = 0; i < childrowcount; ++i) {
        QStandardItem* subitem=currentWorkspace.workspaceItem->child(i);
        if(subitem->checkState()==Qt::Checked){
//            qDebug()<<subitem->text()<<"\n";
            sql=sql+subitem->text()+"' OR chargingDate = '";

        }
    }
    sql.chop(20);
//    qDebug()<<sql<<"\n";
    this->loadTableToWidget("",sql,ui->videoInfoTableWidget);


}

void MainWindow::treeviewDoubleClicked(const QModelIndex& index)
{
    QStandardItem *itemToModify = model->itemFromIndex(index);
//    qDebug()<<itemToModify->text()<<" "<<index.row()<<" "<<index.column()<<"\n";
    if(!index.parent().isValid()){
//        qDebug()<<itemToModify->text()<<" "<<index.row()<<" "<<index.column()<<"\n";
//        ui->treeView->collapse(index);
//        ui->treeView->expand(index);

        QBrush brush(Qt::white);
        currentWorkspace.workspaceItem->setData(brush,Qt::BackgroundRole);
        currentWorkspaceChange(itemToModify->text(),itemToModify);
//        ui->treeView->expandAll();
    }
}

void MainWindow::currentWorkspaceChange(QString table,QStandardItem* item)
{
    currentWorkspace.workspaceName=table;
    currentWorkspace.workspaceItem=item;
    QString sql=("select stationNumber,"
                 "videoName,"
                 "designDrillingDepth,"
                 "designInitiationDepth,"
                 "singleWellExplosiveAmount,"
                 "quantityOfDetonatorsPerWell,"
                 "numberOfWells,"
                 "processingStatus,"
                 "reviewStatus,"
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

    int childrowcount=item->rowCount();
    for (int i = 0; i < childrowcount; ++i) {
        QStandardItem* subitem=item->child(i);
        subitem->setCheckable(true);
        subitem->setCheckState(Qt::Checked);
//        if(subitem->checkState()==Qt::Checked){
////            qDebug()<<subitem->text()<<"\n";
////            sql=sql+subitem->text()+" OR chargingDate = ";

//        }
    }
    QBrush brush(QColor(173, 216, 230));
    item->setData(brush, Qt::BackgroundRole);
    workspaceOpener->close();

    workspaceFilterInit(currentWorkspace.workspaceName);
//    currentWorkspace.workspaceVideoPath=path;
}



//void MainWindow::on_action_main_triggered()
//{
//    ui->stackedWidget->setCurrentWidget(ui->mainPage);

//}

void MainWindow::onCustomContextMenuRequested(const QPoint &pos)
{
    QModelIndex index = ui->treeView->indexAt(pos);
    if(!ui->treeView->currentIndex().parent().isValid()){
        QMenu menu;
        QAction* closeAction = new QAction(QStringLiteral("关闭"), this);
        menu.addAction(closeAction);
        connect(closeAction, &QAction::triggered, this, &MainWindow::closeWorkspace);
        menu.exec(QCursor::pos());
//        QAction *expandAction = menu.addAction("Expand");
//        QAction *collapseAction = menu.addAction("Collapse");
    }
}

void MainWindow::closeWorkspace()
{
    QStandardItem *item = model->itemFromIndex(ui->treeView->currentIndex());
    model->removeRow(item->row());
    delete item;
}


void MainWindow::on_pushButton_5_clicked()
{
    excelChooseWorkspace* e=new excelChooseWorkspace();
    e->setWindowTitle("选择工区");
    connect(e,&excelChooseWorkspace::workspacelist,this,&MainWindow::exportWorkSpaceExcel);
    e->show();
}

void MainWindow::exportWorkSpaceExcel(QStringList workspace)
{
    if(workspace.size()==0){
        return;
    }
    QString sql="( ";
    foreach (QString work, workspace) {
        qDebug()<<work<<"\n";
        sql=sql+" select * from "+work+" union all ";
    }
    sql.chop(11);
    sql=sql+") as workspace";
    qDebug()<<sql<<"\n";
    allWorkSpaceVideoExcel(sql);
    inspectorUnqualifiledVideoExcel(sql);
    videoByDateExcel(sql);
}


void MainWindow::unqualifiledVideoExcel(QString workspacelist)
{

}
//不合格
void MainWindow::allWorkSpaceVideoExcel(QString workspacelist)
{
    // 获取当前日期和时间
    QDateTime currentDateTime = QDateTime::currentDateTime();

    // 将日期和时间转换为字符串
    QString currentDateTimeString = currentDateTime.toString(Qt::ISODate);
    currentDateTimeString.replace(":"," ");
    QXlsx::Document xlsx;
    QStringList titleList;
    QString filePathName;
    QString defaultFileName = currentDateTimeString+" "+currentWorkspace.workspaceName+"总视频"+".xlsx";
//    QXlsx::Format title_format; /*设置标题的样式*/


    // 设置保存的默认文件名称
    QFileInfo fileinfo(defaultFileName);
    // 获取保存文件路径
    QFileDialog *fileDlg = new QFileDialog(this);
    fileDlg->setWindowTitle("保存文件");
    fileDlg->setAcceptMode(QFileDialog::AcceptSave);
    fileDlg->selectFile(defaultFileName);
    fileDlg->setNameFilter("Excel Files(*.xls *.xlsx)");
    fileDlg->setDefaultSuffix("xls");

    if (fileDlg->exec() == QDialog::Accepted)//点击保存
    {
        filePathName = fileDlg->selectedFiles().at(0);
    }

    // 保存文件添加后缀名
    fileinfo =  QFileInfo(filePathName);
    if (fileinfo.suffix() != "xls" && fileinfo.suffix() != "xlsx")
    {
        filePathName += ".xlsx";
    }

    QXlsx::Format title_format; /*设置标题的样式*/
    QXlsx::Format format2;/*小标题样式*/
    QXlsx::Format format3;/*数据内容样式*/
    title_format.setFontSize(20);
    title_format.setFontBold(true);
    title_format.setFontColor(QColor(Qt::red));
    title_format.setHorizontalAlignment(QXlsx::Format::AlignHCenter);
    title_format.setVerticalAlignment(QXlsx::Format::AlignVCenter);
//        xlsx.mergeCells("A1:E1",title_format);//合并1~5列写入标题
//        xlsx.write("A1","Student Information");

    xlsx.mergeCells("A1:O1",title_format);//合并1~5列写入标题
    xlsx.write("A1",defaultFileName);

    format2.setFontColor(QColor(Qt::blue));
    format2.setHorizontalAlignment(QXlsx::Format::AlignHCenter);

    xlsx.write(2,1, "序号", format2);/*写入文字，应该刚才设置的样式*/

    xlsx.write(2,2, "桩号", format2);/*写入文字，应该刚才设置的样式*/
    xlsx.write(2,3, "视频名称", format2);
    xlsx.write(2,4, "设计钻井深度", format2);
    xlsx.write(2,5, "设计激发深度", format2);
    xlsx.write(2,6, "单井药量", format2);
    xlsx.write(2,7, "单井雷管数", format2);

    xlsx.write(2,8, "单井井数", format2);
    xlsx.write(2,9, "处理状态", format2);
    xlsx.write(2,10, "是否复查", format2);
    xlsx.write(2,11, "下药深度", format2);
    xlsx.write(2,12, "差值", format2);
    xlsx.write(2,13, "井监", format2);
    xlsx.write(2,14, "检查人", format2);
    xlsx.write(2,15, "下药日期", format2);
    xlsx.write(2,16, "检查日期", format2);
    xlsx.write(2,17, "钻井评价", format2);
    xlsx.write(2,18, "备注", format2);

//    QMessageBox::warning(this,"提示","打开成功");
    QString sql=("select stationNumber,"
                 "videoName,"
                 "designDrillingDepth,"
                 "designInitiationDepth,"
                 "singleWellExplosiveAmount,"
                 "quantityOfDetonatorsPerWell,"
                 "numberOfWells,"
                 "processingStatus,"
                 "reviewStatus,"
                 "depthOfCharging,"
                 "difference,"
                 "wellSupervisor,"
                 "inspector,"
                 "chargingDate,"
                 "inspectionDate,"
                 "drillingEvaluation,"
                 "remarks,"
                 "videoPath from "+workspacelist+
                 " where drillingEvaluation='不合格'");

    QSqlQuery query;
    query.prepare(sql);
    if (!query.exec()) {
          qDebug() << "Query failed: " << query.lastError().text();
          return;
    }

    QString countsql=("");


    int i=3;

    while(query.next())//一行一行遍历
    {
        xlsx.write(i,1,i-2,format3);

        for (int j = 0; j < 18; ++j) {
//            xlsx.write(i,j+1,query.value(j).toString(),format3);
            xlsx.write(i,j+2,query.value(j).toString(),format3);
    //        qDebug()<<query.value(0).toString();
//            xlsx.write(i,2,query.value(1).toInt(),format3);
//            xlsx.write(i,3,query.value(2).toInt(),format3);
//            xlsx.write(i,4,query.value(3).toString(),format3);
//            xlsx.write(i,5,query.value(4).toString(),format3);
        }
        i++;
    }

    xlsx.saveAs(filePathName);

}

void MainWindow::inspectorUnqualifiledVideoExcel(QString workspacelist)
{
    // 获取当前日期和时间
    QDateTime currentDateTime = QDateTime::currentDateTime();

    // 将日期和时间转换为字符串
    QString currentDateTimeString = currentDateTime.toString(Qt::ISODate);
    currentDateTimeString.replace(":"," ");
    QXlsx::Document xlsx;
    QStringList titleList;
    QString filePathName;
    QString defaultFileName = currentDateTimeString+" "+currentWorkspace.workspaceName+"井监视频汇总"+".xlsx";

    // 设置保存的默认文件名称
    QFileInfo fileinfo(defaultFileName);
    // 获取保存文件路径
    QFileDialog *fileDlg = new QFileDialog(this);
    fileDlg->setWindowTitle("保存文件");
    fileDlg->setAcceptMode(QFileDialog::AcceptSave);
    fileDlg->selectFile(defaultFileName);
    fileDlg->setNameFilter("Excel Files(*.xls *.xlsx)");
    fileDlg->setDefaultSuffix("xlsx");

    if (fileDlg->exec() == QDialog::Accepted)//点击保存
    {
        filePathName = fileDlg->selectedFiles().at(0);
    }

    // 保存文件添加后缀名
    fileinfo =  QFileInfo(filePathName);
    if (fileinfo.suffix() != "xls" && fileinfo.suffix() != "xlsx")
    {
        filePathName += ".xlsx";
    }


    QXlsx::Format title_format; /*设置标题的样式*/
    QXlsx::Format format2;/*小标题样式*/
    QXlsx::Format format3;/*数据内容样式*/
    title_format.setFontSize(20);
    title_format.setFontBold(true);
    title_format.setFontColor(QColor(Qt::red));
    title_format.setHorizontalAlignment(QXlsx::Format::AlignHCenter);
    title_format.setVerticalAlignment(QXlsx::Format::AlignVCenter);
//        xlsx.mergeCells("A1:E1",title_format);//合并1~5列写入标题
//        xlsx.write("A1","Student Information");

    xlsx.mergeCells("A1:O1",title_format);//合并1~5列写入标题
    xlsx.write("A1",defaultFileName);

    xlsx.write(2,1, "井监", format2);/*写入文字，应该刚才设置的样式*/
    xlsx.write(2,2, "总下药井数量", format2);/*写入文字，应该刚才设置的样式*/
    xlsx.setColumnWidth(2, 20);
    xlsx.write(2,3, "合格下药井数量", format2);
    xlsx.setColumnWidth(3, 20);
    xlsx.write(2,4, "不合格下药井数量", format2);
    xlsx.setColumnWidth(4, 20);

    QSqlQuery query;
    QString datagroupsql=("SELECT wellSupervisor, SUM(总数量) AS '总数量', SUM(合格数量) AS '合格数量', SUM(不合格数量) AS '不合格数量' "
                          " FROM ( "
                              " SELECT wellSupervisor, COUNT(*) AS 总数量, 0 AS 合格数量, 0 AS 不合格数量 FROM "+ workspacelist +" GROUP BY wellSupervisor "
                              " UNION ALL "
                              " SELECT wellSupervisor, 0 AS 总数量, COUNT(*) AS 合格数量, 0 AS 不合格数量 FROM "+ workspacelist +" WHERE drillingEvaluation = '合格' GROUP BY wellSupervisor "
                              " UNION ALL "
                              " SELECT wellSupervisor, 0 AS 总数量, 0 AS 合格数量, COUNT(*) AS 不合格数量 FROM "+ workspacelist +" WHERE drillingEvaluation = '不合格' GROUP BY wellSupervisor "
                          ") AS T "
                          " GROUP BY wellSupervisor");

//    QString countgroup=("slelect chargingDate , count(*),"
//                      "from "+currentWorkspace.workspaceName+
//                        " group by chargingDate");
    query.prepare(datagroupsql);
    if (!query.exec()) {
          qDebug() << "Query failed: " << query.lastError().text();
          return;
    }

    int i=3;

    while(query.next())//一行一行遍历
    {
//        xlsx.write(i,1,i-2,format3);
        xlsx.write(i,1,query.value(0).toString(),format3);
//        for (int j = 1; j < 16; ++j) {
            xlsx.write(i,2,query.value(1).toString(),format3);
            xlsx.write(i,3,query.value(2).toString(),format3);
            xlsx.write(i,4,query.value(3).toString(),format3);

        i++;
    }


    xlsx.saveAs(filePathName);
}

void MainWindow::videoByDateExcel(QString workspacelist)
{
    // 获取当前日期和时间
    QDateTime currentDateTime = QDateTime::currentDateTime();

    // 将日期和时间转换为字符串
    QString currentDateTimeString = currentDateTime.toString(Qt::ISODate);
    currentDateTimeString.replace(":"," ");
    QXlsx::Document xlsx;
    QStringList titleList;
    QString filePathName;
    QString defaultFileName = currentDateTimeString+" "+currentWorkspace.workspaceName+"视频汇总"+".xlsx";
//    QXlsx::Format title_format; /*设置标题的样式*/


    // 设置保存的默认文件名称
    QFileInfo fileinfo(defaultFileName);
    // 获取保存文件路径
    QFileDialog *fileDlg = new QFileDialog(this);
    fileDlg->setWindowTitle("保存文件");
    fileDlg->setAcceptMode(QFileDialog::AcceptSave);
    fileDlg->selectFile(defaultFileName);
    fileDlg->setNameFilter("Excel Files(*.xls *.xlsx)");
    fileDlg->setDefaultSuffix("xls");

    if (fileDlg->exec() == QDialog::Accepted)//点击保存
    {
        filePathName = fileDlg->selectedFiles().at(0);
    }

    // 保存文件添加后缀名
    fileinfo =  QFileInfo(filePathName);
    if (fileinfo.suffix() != "xls" && fileinfo.suffix() != "xlsx")
    {
        filePathName += ".xlsx";
    }

    QXlsx::Format title_format; /*设置标题的样式*/
    QXlsx::Format format2;/*小标题样式*/
    QXlsx::Format format3;/*数据内容样式*/
    title_format.setFontSize(20);
    title_format.setFontBold(true);
    title_format.setFontColor(QColor(Qt::red));
    title_format.setHorizontalAlignment(QXlsx::Format::AlignHCenter);
    title_format.setVerticalAlignment(QXlsx::Format::AlignVCenter);
//        xlsx.mergeCells("A1:E1",title_format);//合并1~5列写入标题
//        xlsx.write("A1","Student Information");
    xlsx.setRowHeight(1, 30);
    xlsx.mergeCells("A1:O1",title_format);//合并1~5列写入标题
    xlsx.write("A1",defaultFileName);

    format2.setFontColor(QColor(Qt::blue));
    format2.setHorizontalAlignment(QXlsx::Format::AlignHCenter);

    xlsx.write(2,1, "总计", format2);
    xlsx.write(3,1, "合格", format2);
    xlsx.write(4,1, "不合格", format2);
    xlsx.write(2,3, "总计未检测", format2);

    xlsx.write(5,1, "日期", format2);/*写入文字，应该刚才设置的样式*/
    xlsx.write(5,2, "总下药井数量", format2);/*写入文字，应该刚才设置的样式*/
    xlsx.setColumnWidth(2, 20);
    xlsx.write(5,3, "合格下药井数量", format2);
    xlsx.setColumnWidth(3, 20);
    xlsx.write(5,4, "不合格下药井数量", format2);
    xlsx.setColumnWidth(4, 20);
    xlsx.write(5,5, "每日未检测数", format2);
    xlsx.setColumnWidth(5, 20);
//    xlsx.write(2,5, "设计激发深度", format2);
//    xlsx.write(2,6, "单井药量", format2);
//    xlsx.write(2,7, "单井雷管数", format2);
//    xlsx.write(2,8, "单井井数", format2);
//    xlsx.write(2,9, "下药深度", format2);
//    xlsx.write(2,10, "差值", format2);
//    xlsx.write(2,11, "井监", format2);
//    xlsx.write(2,12, "检查人", format2);
//    xlsx.write(2,13, "下药日期", format2);
//    xlsx.write(2,14, "检查日期", format2);
//    xlsx.write(2,15, "钻井结果", format2);
//    xlsx.write(2,16, "备注", format2);

//    QMessageBox::warning(this,"提示","打开成功");

    QString countall=("select count(*) "
                      " from "+workspacelist);

    QSqlQuery query;
    query.prepare(countall);
    if (!query.exec()) {
          qDebug() << "Query failed: 1" << query.lastError().text();
          return;
    }
    query.next();
    xlsx.write(2,2,query.value(0).toString());

    QString countunqualified=("select count(*) "
                      " from "+workspacelist+
                      " where drillingEvaluation='合格' or drillingEvaluation='不合格' group by drillingEvaluation");

    query.prepare(countunqualified);
    if (!query.exec()) {
          qDebug() << "Query failed: 2" << query.lastError().text();
          return;
    }
    query.next();
    xlsx.write(3,2,query.value(0).toString());
    query.next();
    xlsx.write(4,2,query.value(0).toString());


    QString datagroupsql=("SELECT chargingDate, SUM(总数量) AS '总数量', SUM(合格数量) AS '合格数量', SUM(不合格数量) AS '不合格数量' "
                          " FROM ( "
                              " SELECT chargingDate, COUNT(*) AS 总数量, 0 AS 合格数量, 0 AS 不合格数量 FROM "+ workspacelist +" GROUP BY chargingDate "
                              " UNION ALL "
                              " SELECT chargingDate, 0 AS 总数量, COUNT(*) AS 合格数量, 0 AS 不合格数量 FROM "+ workspacelist +" WHERE drillingEvaluation = '合格' GROUP BY chargingDate "
                              " UNION ALL "
                              " SELECT chargingDate, 0 AS 总数量, 0 AS 合格数量, COUNT(*) AS 不合格数量 FROM "+ workspacelist +" WHERE drillingEvaluation = '不合格' GROUP BY chargingDate "
                          " ) AS T "
                          " GROUP BY chargingDate");

//    QString countgroup=("slelect chargingDate , count(*),"
//                      "from "+currentWorkspace.workspaceName+
//                        " group by chargingDate");
    query.prepare(datagroupsql);
    if (!query.exec()) {
          qDebug() << "Query failed: 3" << query.lastError().text();
          return;
    }

    int i=6;
    int processing=0;
    while(query.next())//一行一行遍历
    {
//        xlsx.write(i,1,i-2,format3);
        xlsx.write(i,1,query.value(0).toString(),format3);
//        for (int j = 1; j < 16; ++j) {
            xlsx.write(i,2,query.value(1).toString(),format3);
            xlsx.write(i,3,query.value(2).toString(),format3);
            xlsx.write(i,4,query.value(3).toString(),format3);

            int dateprocessing=query.value(1).toInt()-query.value(2).toInt()-query.value(3).toInt();
            processing=processing+dateprocessing;
            xlsx.write(i,5,dateprocessing,format3);
    //        qDebug()<<query.value(0).toString();
//            xlsx.write(i,2,query.value(1).toInt(),format3);
//            xlsx.write(i,3,query.value(2).toInt(),format3);
//            xlsx.write(i,4,query.value(3).toString(),format3);
//            xlsx.write(i,5,query.value(4).toString(),format3);
//        }
        i++;
    }



    xlsx.saveAs(filePathName);
}

void MainWindow::filterInit()
{
//    ui->treeView_2->setWindowFlags(Qt::WindowStaysOnTopHint);
    ui->treeView_2->setAttribute(Qt::WA_Hover,true);
//    ui->treeView_2->viewport()->installEventFilter(this);
    filtermodel = new QStandardItemModel(this);
    ui->treeView_2->setEditTriggers(QTreeView::NoEditTriggers);//设置双击不能编辑
    ui->treeView_2->setModel(filtermodel);
    ui->treeView_2->setHeaderHidden(true);//设置列头可见
    ui->widget->hide();
//    ui->widget->setStyleSheet("background-color: white;");
//    ui->treeView_2->verticalHeader()->hide();
}

bool MainWindow::eventFilter(QObject *obj, QEvent *event)
{
//    if(obj==ui->treeView_2->viewport()&&event->type()==QEvent::Enter){
////        qDebug()<<"enter\n";
////        ui->groupBox_6->setFixedHeight(250);
//        ui->treeView_2->setFixedSize(170,180);
//    };
//    if (obj == ui->treeView_2->viewport() && event->type() == QEvent::Leave)
//    {

////        qDebug()<<"leave\n";
////        ui->groupBox_6->setFixedHeight(71);
//        ui->treeView_2->setFixedSize(170,30);
//    }
    return QObject::eventFilter(obj, event);
}

void MainWindow::workspaceFilterInit(QString workspaceName)
{
    if(filtermodel->rowCount() != 0){
        for (int row = 0; row <filtermodel->rowCount(); ++row) {
            for (int column = 0; column < filtermodel->columnCount(); ++column) {
                QStandardItem *item = filtermodel->item(row, column);
                delete item; // 删除项并释放内存
            }
        }
        filtermodel->clear(); // 清空模型
    }
//    QStandardItem* root = new QStandardItem("处理状态");
//    filtermodel->appendRow(root);

    filterItemInit("检查结果","drillingEvaluation");
    filterItemInit("井监","wellSupervisor");
//    QStandardItem* root1 = new QStandardItem("处理状态");
//    filtermodel->appendRow(root1);
//    QStandardItem* itemChild = new QStandardItem("已处理");


//    QStandardItem* root2 = new QStandardItem("检查结果");
//    filtermodel->appendRow(root2);

//    QString sqldrillingEvaluation=("select drillingEvaluation from "
//                                   +currentWorkspace.workspaceName +
//                                   " group by drillingEvaluation");
//    QSqlQuery query;
//    query.prepare(sqldrillingEvaluation);
//    if (!query.exec()) {
//          qDebug() << "Query failed: " << query.lastError().text();
//          return;
//    }
//    while(query.next())//一行一行遍历
//    {
//        QStandardItem* itemChild = new QStandardItem(query.value(0).toString());

////        itemChild->setIcon(QIcon(":/videoWidget/images/file.png"));
//        itemChild->setCheckable(true); // 设置为可选中
//        itemChild->setCheckState(Qt::Checked); // 默认选中状态
//        root2->appendRow(itemChild);

//    }


//    QStandardItem* root3 = new QStandardItem("视频评价");
//    filtermodel->appendRow(root3);

//    QStandardItem* root4 = new QStandardItem("井监");
//    filtermodel->appendRow(root4);

//    QString sqlinspector=("select wellSupervisor from "
//                                   +currentWorkspace.workspaceName +
//                                   " group by wellSupervisor");
////    QSqlQuery query;
//    query.prepare(sqlinspector);
//    if (!query.exec()) {
//          qDebug() << "Query failed: " << query.lastError().text();
//          return;
//    }
//    while(query.next())//一行一行遍历
//    {
//        QStandardItem* itemChild = new QStandardItem(query.value(0).toString());

////        itemChild->setIcon(QIcon(":/videoWidget/images/file.png"));
//        itemChild->setCheckable(true); // 设置为可选中
//        itemChild->setCheckState(Qt::Checked); // 默认选中状态
//        root4->appendRow(itemChild);

//    }
}

void MainWindow::filterItemInit(QString filterItem,QString databaseItem)
{
    QStandardItem* root2 = new QStandardItem(filterItem);
    filtermodel->appendRow(root2);
    QString sqldrillingEvaluation=("select "+ databaseItem +" from "
                                   +currentWorkspace.workspaceName +
                                   " group by "+databaseItem);
    QSqlQuery query;
    query.prepare(sqldrillingEvaluation);
    if (!query.exec()) {
          qDebug() << "Query failed: " << query.lastError().text();
          return;
    }
    while(query.next())//一行一行遍历
    {
        if(query.value(0).toString().size()==0){
            continue;
        }
        QStandardItem* itemChild = new QStandardItem(query.value(0).toString());

//        itemChild->setIcon(QIcon(":/videoWidget/images/file.png"));
        itemChild->setCheckable(true); // 设置为可选中
        itemChild->setCheckState(Qt::Checked); // 默认选中状态
        root2->appendRow(itemChild);

    }

}


void MainWindow::on_pushButton_6_clicked()
{
//    int childrowcount=currentWorkspace.workspaceItem->rowCount();
//    QStandardItem* item=filtermodel->findItems("检查结果");

//    for (int i = 0; i < childrowcount; ++i) {
////        QStandardItem* subitem=filtermodel->child(i);
//        if(subitem->checkState()==Qt::Checked){
////            qDebug()<<subitem->text()<<"\n";
////            sql=sql+subitem->text()+" OR chargingDate = ";

//        }
//    }
//    QStringList namesToBeHighlighted = getNames();
    if(currentWorkspace.workspaceItem==nullptr){
        return;
    }
    QString drillingEvaluationresult;
    QString inspector;
    qDebug()<<"shaixuan\n";
    for (int row = 0; row < filtermodel->rowCount(); ++row) {
        QStandardItem *parentItem = filtermodel->item(row);
        qDebug() << "Parent item:" << parentItem->text()<<"\n";
        if(parentItem->text()=="检查结果"){
            for (int column = 0; column < parentItem->rowCount(); ++column) {
                QStandardItem *childItem = parentItem->child(column);
                if(childItem->checkState()==Qt::Checked){
                    drillingEvaluationresult=drillingEvaluationresult+"  drillingEvaluation = '"+childItem->text()+"'";
                    drillingEvaluationresult=drillingEvaluationresult+" or ";
                }

//                qDebug() << "Child item:" << childItem->text()<<"\n";
            }
            if(drillingEvaluationresult.size()!=0){
                drillingEvaluationresult.chop(4);
            }

        }
        if(parentItem->text()=="井监"){
//            inspector=inspector+" or ";
            for (int column = 0; column < parentItem->rowCount(); ++column) {
                QStandardItem *childItem = parentItem->child(column);
                if(childItem->checkState()==Qt::Checked){
                    inspector=inspector+"  wellSupervisor = '"+childItem->text()+"'";
                    inspector=inspector+" or ";
                }
//                qDebug() << "Child item:" << childItem->text()<<"\n";
            }
            if(inspector.size()!=0){
                inspector.chop(4);
            }

        }

    }
    int childrowcount=currentWorkspace.workspaceItem->rowCount();

    QString datesql=" chargingDate = '";
    bool datebool=false;
    for (int i = 0; i < childrowcount; ++i) {
        QStandardItem* subitem=currentWorkspace.workspaceItem->child(i);
        if(subitem->checkState()==Qt::Checked){
//            qDebug()<<subitem->text()<<"\n";
            datebool=true;
            datesql=datesql+subitem->text()+"' OR chargingDate = '";

        }
    }
    if(datebool){
        datesql.chop(20);
    }else{
        datesql="";
    }

    QString sql=("select stationNumber,"
                 "videoName,"
                 "designDrillingDepth,"
                 "designInitiationDepth,"
                 "singleWellExplosiveAmount,"
                 "quantityOfDetonatorsPerWell,"
                 "numberOfWells,"
                 "processingStatus,"
                 "reviewStatus,"
                 "depthOfCharging,"
                 "difference,"
                 "wellSupervisor,"
                 "inspector,"
                 "chargingDate,"
                 "inspectionDate,"
                 "drillingEvaluation,"
                 "remarks,"
                 "videoPath from "+currentWorkspace.workspaceName+
                   " where ");
    if(drillingEvaluationresult.size()!=0){
        sql=sql+"("+drillingEvaluationresult+ ") and ";
    }
    if(inspector.size()!=0){
        sql=sql+"("+inspector+") and ";
    }
    if(datesql.size()!=0){
        sql=sql+"("+datesql+") and ";
    }
    sql.chop(4);
    qDebug()<<sql<<"\n";
    this->loadTableToWidget("",sql,ui->videoInfoTableWidget);
//    workspaceOpener->close();

}



void MainWindow::on_pushButton_4_clicked()
{

}

void MainWindow::filterwidgetshow()
{
    if(!ui->widget->isVisible()){
        int x=ui->tablewidget->x()+1;
        int y=ui->tablewidget->y()+videotableBar->height()+2;
//        qDebug()<<x<<" "<<y<<"\n";
//        videotableBar->pos();
        ui->widget->show();
        ui->widget->move(x,y);
    }else{
        ui->widget->hide();
    }
}

void MainWindow::stationnumbersearchshow()
{
    if(!ui->widget_2->isVisible()){
//        int x=workspaceBar->x()+workspaceBar->height();
//        int y=workspaceBar->y();
        int x=ui->tablewidget->x()+2;
        int y=ui->tablewidget->y()+videotableBar->height()+1;

        ui->widget_2->show();
        ui->widget_2->move(x,y);
    }else{
        ui->widget_2->hide();
    }
}


void MainWindow::on_action_triggered()
{
    this->setStyleSheet("");
}

void MainWindow::themeInit()
{
    QDir dir(":/qsstemplate/QSS");
    if (!dir.exists()) {
        qDebug() << "The specified directory does not exist.";
//              return QStringList();
    }
//    dir.setFilter(QDir::Dirs | QDir::NoDotAndDotDot);
    QStringList fileList = dir.entryList(QDir::Files);
//    QFileInfoList subfolders = dir.entryInfoList();
//    QStringList subfolderNames;
//    foreach (const QFileInfo& subfolderInfo, fileList) {
//        QString a=subfolderInfo.fileName();
//        a.chop(4);
//        qDebug()<<a<<"\n";
//       subfolderNames << a;
//    }
    foreach (const QString& subfileName, fileList) {
        QString the=subfileName;
        the.chop(4);
        qDebug()<<the<<"\n";
        QAction* act=new QAction(the,this);
        ui->menu_5->addAction(act);
        connect(act,&QAction::triggered,this,&MainWindow::themechange);
    }
}

void MainWindow::themechange()
{
    QAction* action = qobject_cast<QAction*>(sender());
    if (action)
    {
        QString text = action->text();
        text=text+".qss";
        // 现在你可以使用 text 变量来处理该 QAction 的文本
        QFile styleFile(":/qsstemplate/QSS/"+text);
        styleFile.open(QFile::ReadOnly);
        QString styleSheet = QLatin1String(styleFile.readAll());
        this->setStyleSheet(styleSheet);
    }



}

