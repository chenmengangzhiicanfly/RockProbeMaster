#include"mainwindow.h"
#include "./ui_mainwindow.h"
#include<QTimer>
//void MainWindow::on_startDetectionButton_MainPage_clicked()
//{
//    ui->startDetectionButton_MainPage->setEnabled(false);
//    int rowCount = ui->videoInfoTableWidget->rowCount();
//    int columnCount = ui->videoInfoTableWidget->columnCount();
//    // 记录已检测视频的数量
//    int totalCount = 0; // 记录总视频数量
//    int count=0;
//    QStringList videoList;
//    for(int row =0;row < rowCount;row++){
//        QTableWidgetItem *checkBoxItem = ui->videoInfoTableWidget->item(row,0);
//        if (checkBoxItem && checkBoxItem->checkState() == Qt::Checked) {
//            // 复选框被选中，获取该行的数据并执行检测操作
//            totalCount++;
//        }
//    }
//    if(totalCount>0){
//        videoDetectionProcessBar->setVisible(true);
//        emit setTotalVideoCount(totalCount);
//    }
//    for(int row =0;row < rowCount;row++){
//        QTimer *progressTimer = new QTimer(this);
//        progressTimer->setInterval(500);
//        // 连接定时器的槽函数

//        progressTimer->start();
//        ui->detectProgressBar->setRange(0, 100);  // 设置进度条范围
//        ui->detectProgressBar->setValue(0);

//        QTableWidgetItem *checkBoxItem = ui->videoInfoTableWidget->item(row,0);
//        if (checkBoxItem && checkBoxItem->checkState() == Qt::Checked) {
//            // 复选框被选中，获取该行的数据并执行检测操作
//            QString videoPath= ui->videoInfoTableWidget->item(row, 1)->toolTip();
//                if (!videoPath.isEmpty()) {
//                    videoList.append(videoPath);
//                }
//                std::string str = videoPath.toStdString();
//                float p=0.0;
//                connect(progressTimer, &QTimer::timeout, this, [this,p,row]() {
//                    // 直接使用 p2 引用更新进度条
//                    int progressValue = static_cast<int>(p * 100);
//                    QTableWidgetItem *item =new QTableWidgetItem(QString::number(progressValue));
//                    ui->videoInfoTableWidget->setItem(row,15,item);

//                    // 在这里可以进行其他与 p2 相关的操作
//                    // 例如：this->ui->resultText->setText(QString::fromStdString(currentDetectlog.ToString()));
//                });
//                detectorManager.DetectAsync(str, p, [this,row,videoPath, totalCount](DetectLog detectlog) {
//                    currentDetectlog = detectlog;
//                    emit detectionComplete();
////                    qDebug()<<totalCount<<checkedCount;

//                    qDebug() <<QString::fromStdString(currentDetectlog.ToString());
//                    QString temp = QString("视频%1:\n药柱数量为：%2,爆炸杆数量为: %3").arg(videoPath).arg(currentDetectlog.GetExplosiveRodCount()).arg(currentDetectlog.GetDepthRodCount());
//                    QMetaObject::invokeMethod(this, [this,row,totalCount,temp]() {

//                        float welldepth=0.5*currentDetectlog.GetExplosiveRodCount()+3.0*currentDetectlog.GetDepthRodCount();
//                        QTableWidgetItem *wellDepthItem = new QTableWidgetItem(QString::number(welldepth));
//                        this->ui->videoInfoTableWidget->setItem(row,8,wellDepthItem);
//                        //                    this->ui->resultText->setText(QString::fromStdString(currentDetectlog.ToString()));
//                    });
//                });
//            // 调用异步检测功能，传递当前行的数据
//            qDebug() << "Starting detection for row:" << row;
//        }
//    }


//    //统一收集再检测
////    for(QString video : videoList){
////            std::string str = video.toStdString();
////            detectorManager.DetectAsync(str, p, [this](DetectLog detectlog) {
////                currentDetectlog = detectlog;
////                qDebug() <<QString::fromStdString(currentDetectlog.ToString());

////                QMetaObject::invokeMethod(this, [this]() {
////                    // 完成的任务数加一

////                    float welldepth=0.5*currentDetectlog.GetExplosiveRodCount()+3.0*currentDetectlog.GetDepthRodCount();

////                    this->ui->resultText->setText(QString::fromStdString(currentDetectlog.ToString()));
////                });
////            });
////    }
//}
void MainWindow::on_startDetectionButton_MainPage_clicked()
{
    ui->startDetectionButton_MainPage->setEnabled(false);
    int rowCount = ui->videoInfoTableWidget->rowCount();
    int totalCount = 0; // 记录总视频数量
    QStringList videoList;

    for(int row = 0; row < rowCount; row++)
    {
        QTableWidgetItem *checkBoxItem = ui->videoInfoTableWidget->item(row, 0);
        if (checkBoxItem && checkBoxItem->checkState() == Qt::Checked)
        {
            totalCount++;
            QString videoPath = ui->videoInfoTableWidget->item(row, 1)->toolTip();
            if (!videoPath.isEmpty()) {
                videoList.append(videoPath);
            }

            std::string str = videoPath.toStdString();

            float* p=new float(0.0);    //内存泄露
            // 使用 lambda 表达式来捕获当前行的信息，以及新的 p 变量
            connectDetector(row, str, totalCount, p);
        }
    }

    if (totalCount > 0)
    {
        videoDetectionProcessBar->setVisible(true);
        emit setTotalVideoCount(totalCount);
    }
}


void MainWindow::connectDetector(int row, const std::string& videoPath, int totalCount, float *p)
{
    QTimer *progressTimer = new QTimer(this);
    progressTimer->setInterval(0.05);

    // 连接定时器的槽函数
    //
    connect(progressTimer, &QTimer::timeout, this, [this, row, p]() {
        int progressValue = (*p) * 100;
        ui->videoInfoTableWidget->item(row, 15)->setText(QString::number(progressValue)+'%');
    });

    // 启动定时器
    progressTimer->start();

    // 调用异步检测功能，传递当前行的数据
    detectorManager.DetectAsync(videoPath, *p, [this, row, totalCount,videoPath,p,progressTimer](DetectLog detectlog) {

        emit detectionComplete();


//        QString temp = QString("视频%1:\n药柱数量为：%2,爆炸杆数量为: %3").arg(videoPath).arg(currentDetectlog.GetExplosiveRodCount()).arg(currentDetectlog.GetDepthRodCount());
        float welldepth = 0.5 * detectlog.GetExplosiveRodCount() + 3.0 * detectlog.GetDepthRodCount();
        QMetaObject::invokeMethod(this, [this, row,welldepth]() {
            QTableWidgetItem *wellDepthItem = new QTableWidgetItem(QString::number(welldepth));
            ui->videoInfoTableWidget->setItem(row, 8, wellDepthItem);

        });
        progressTimer->stop();
        delete p;


    });
}
void MainWindow::on_videoInfoTableWidget_itemChanged(QTableWidgetItem *item)
{
    if (item && item->column() == 15) { // 检查是否为指定的列
        // 获取单元格的当前值
        QString value = item->text();
        int curRow = item->row();
        int curColumn = item->column();
        // 检查值是否满足条件
        if (value == "100%") {
            // 创建一个图标
            QIcon icon(":/videoWidget/images/achieved.jpg");
            // 在单元格中设置图标和文本
            QTableWidgetItem *newItem = new QTableWidgetItem(icon, "已处理");
            ui->videoInfoTableWidget->setItem(curRow, curColumn, newItem);
        }
    }
}

