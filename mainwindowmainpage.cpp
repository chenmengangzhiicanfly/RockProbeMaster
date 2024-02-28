#include"mainwindow.h"
#include "./ui_mainwindow.h"

void MainWindow::on_startDetectionButton_MainPage_clicked()
{
    ui->startDetectionButton_MainPage->setEnabled(false);
    int rowCount = ui->videoInfoTableWidget->rowCount();
    int columnCount = ui->videoInfoTableWidget->columnCount();
    // 记录已检测视频的数量
    int totalCount = 0; // 记录总视频数量
    int count=0;
    QStringList videoList;
    for(int row =0;row < rowCount;row++){
        QTableWidgetItem *checkBoxItem = ui->videoInfoTableWidget->item(row,0);
        if (checkBoxItem && checkBoxItem->checkState() == Qt::Checked) {
            // 复选框被选中，获取该行的数据并执行检测操作
            totalCount++;
        }
    }
    if(totalCount>0){
        videoDetectionProcessBar->setVisible(true);
        emit setTotalVideoCount(totalCount);
    }
    for(int row =0;row < rowCount;row++){
        QTableWidgetItem *checkBoxItem = ui->videoInfoTableWidget->item(row,0);
        if (checkBoxItem && checkBoxItem->checkState() == Qt::Checked) {
            // 复选框被选中，获取该行的数据并执行检测操作
            QString videoPath= ui->videoInfoTableWidget->item(row, 1)->toolTip();
                if (!videoPath.isEmpty()) {
                    videoList.append(videoPath);
                }
                std::string str = videoPath.toStdString();

                detectorManager.DetectAsync(str, p, [this,row,videoPath, totalCount](DetectLog detectlog) {
                    currentDetectlog = detectlog;
                    emit detectionComplete();
//                    qDebug()<<totalCount<<checkedCount;
//                    float progress = (float)checkedCount
//                                          / totalCount * 100; // 计算进度百分比

                    qDebug() <<QString::fromStdString(currentDetectlog.ToString());
                    QString temp = QString("视频%1:\n药柱数量为：%2,爆炸杆数量为: %3").arg(videoPath).arg(currentDetectlog.GetExplosiveRodCount()).arg(currentDetectlog.GetDepthRodCount());
                    QMetaObject::invokeMethod(this, [this,row,totalCount,temp]() {
                        // 完成的任务数加一
//                        checkedCount++;
//                        qDebug()<<temp<<totalCount<<checkedCount;
//                        float progress = (float)checkedCount
//                                         / totalCount * 100; // 计算进度百分比

                        float welldepth=0.5*currentDetectlog.GetExplosiveRodCount()+3.0*currentDetectlog.GetDepthRodCount();
                        QTableWidgetItem *wellDepthItem = new QTableWidgetItem(QString::number(welldepth));
                        this->ui->videoInfoTableWidget->setItem(row,8,wellDepthItem);
                        //                    this->ui->resultText->setText(QString::fromStdString(currentDetectlog.ToString()));
                    });
                });
            // 调用异步检测功能，传递当前行的数据
            qDebug() << "Starting detection for row:" << row;
        }
    }


    //统一收集再检测
//    for(QString video : videoList){
//            std::string str = video.toStdString();
//            detectorManager.DetectAsync(str, p, [this](DetectLog detectlog) {
//                currentDetectlog = detectlog;
//                qDebug() <<QString::fromStdString(currentDetectlog.ToString());

//                QMetaObject::invokeMethod(this, [this]() {
//                    // 完成的任务数加一

//                    float welldepth=0.5*currentDetectlog.GetExplosiveRodCount()+3.0*currentDetectlog.GetDepthRodCount();

//                    this->ui->resultText->setText(QString::fromStdString(currentDetectlog.ToString()));
//                });
//            });
//    }
}
