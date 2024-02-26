#include "mainwindow.h"
#include"form.h"
#include <QApplication>
#include <QSplashScreen>
#include <QTimer>
#include <QSqlQuery>
#include <QSqlError>
#include "loginwidget.h"
#include "databaseconnector.h"
#include "excelreaderanddisplayer.h"
#include "excelexporter.h"
#include "DetectLog.h"
#include "DetectorManager.h"
#include "VideoDetector.h"
#include <opencv2/opencv.hpp>
#include "test.h"
#include <QtConcurrent/QtConcurrentRun>
#include "detectormanagersingleton.h"
#include "videoreviewwidget.h"
#include "detectorsizesettings.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    qDebug()<<"主界面的线程地址是："<<QThread::currentThread();
            //    QPixmap splashImage(":/images/D:/DeskTop/zy/00001-00100/images/zy-00001.png");  // 替换为你的启动图片路径
            //    QSplashScreen splash(splashImage);
            //    splash.show();
            // 设置一些启动时的信息，例如版本号等
            //    splash.showMessage("Version 1.0", Qt::AlignBottom | Qt::AlignRight, Qt::white);

                //    qDebug()<<"available drivers:";
                //    QStringList drivers = QSqlDatabase::drivers();
                //    foreach(QString driver, drivers)
                //        qDebug()<<driver;

    DatabaseConnector databaseConnector;


    MainWindow w;
    w.show();

//    DetectorSizeSettings d;
//    d.show();


    // 在这里添加你的初始化代码，例如加载资源、配置等
    // 模拟应用程序启动的耗时操作
    // 这里使用 QTimer 来延迟关闭启动画面，你可以根据实际情况修改
    // first
    //    LoginWidget l;
    //    l.show();
    //    splash.finish(&l);

//    VideoReviewWidget v;
//    v.show();

    //seconnd







    //    float progress = 0;
    //    VideoDetector videoDetector;
    //    videoDetector.InitEngine();
    //        //		cout << "请输入视频路径" << endl;
    //    QString file="F:/video/1.mp4";
    //        //		cin >> file;


    //    auto log = videoDetector.DetectVideo(file.toStdString().c_str(),progress);

    //    QThread *thread1 = new QThread;
    //    DetectorManager detectorManager;
    //    detectorManager.moveToThread(thread1);
    //    Test test;
    //    test.moveToThread(thread1);

    //    QObject::connect(thread1, &QThread::started, [&](){
    //        float p1 =0;
    //        test.DetectAsync("F:/video/1.mp4", p1, [](DetectLog detectlog){
    //            qDebug()<<"end";
    //        });

    //    });
    //    thread1->start();
    //            DetectorManager detectorManager;
    //            detectorManager.Init(3);
    //            QString file="F:/video/1.mp4";
    //            float p1 = 0, p2 = 0, p3 = 0, p4 = 0;

    //                detectorManager.DetectAsync("F:/video/1.mp4", p1, [](DetectLog detectlog) {
    ////                    qDebug() <<QString::fromStdString(detectlog.ToString());
    //                qDebug()<<"1";
    //                });


    //                detectorManager.DetectAsync(file.toStdString().c_str(), p2, [](DetectLog detectlog) {
    ////                    qDebug() <<QString::fromStdString(detectlog.ToString());
    //                                    qDebug()<<"3";
    //                });
    //                char*  ch;
    //                QByteArray ba = file.toLatin1(); // must
    //                ch=ba.data();
    //                detectorManager.DetectAsync(ch, p4, [](DetectLog detectlog) {
    //                    //                    qDebug() <<QString::fromStdString(detectlog.ToString());
    //                    qDebug()<<"4";
    //                });

    //        QtConcurrent::run([&]() {
    //            DetectorManager detectorManager;
    //            detectorManager.Init(1);
    //        });


    //        std::thread t(&DetectorManager::DetectAsync,detectorManager,"F:/video/2.MP4", p1, [](DetectLog detectlog){
    //            qDebug()<<QString::fromStdString(detectlog.ToString());
    //        });








    //    cv::Mat image = cv::imread("../1.png");
    //    cv::imshow("test",image);

    // 测试3
    //    ExcelReaderAndDisplayer excel;
    //    excel.show();
    //     测试4
    //        Form f;
    //        f.show();

    return a.exec();
}
