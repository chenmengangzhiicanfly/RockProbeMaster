#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QTableWidget>  //要封装QTableWidget的更新函数，所以把这个类包含进来
#include <QThread>
#include <QProgressBar>
#include "excelreaderanddisplayer.h"
#include "databaseinsertpage.h"
#include <QCloseEvent>
#include "DetectLog.h"
#include "DetectorManager.h"
#include "VideoDetector.h"
#include <QtConcurrent/QtConcurrentRun>
#include <QMediaPlayer>
#include "workspacefilemanager.h"
#include "workspaceopener.h"
#include "detectormanagersingleton.h"
#include "detectorsizesettings.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void updateQTableWidget(QTableWidget* &qTableWidget);
    void markQTableWidget(QTableWidget* &qTableWidget);
    bool databaseIsEmpty(QTableWidget* qTableWidget,int row);

signals:
    void goBack();
    void detectAchieved();
    void tableOpened();
    void detectionComplete(int row,double wellPath);
    void setTotalVideoCount(int videoTotal);
    void detectionAllComplete();

private:
    //画面控件
    Ui::MainWindow *ui;
    QStatusBar *statusBar;
    QLabel *showTimeLabel;
    QProgressBar *videoDetectionProcessBar;

private:

    QMap<QString, QString> qTableWidgetToDatabaseMap;
    DetectLog currentDetectlog;
    QSqlDatabase db;

    void init();
    void initMenu();
    void initStatus();
    void initqTableWidgetToDatabaseMap(QTableWidget *qTable);

    void exportQtable();
    void importQtable();
    void addVideofileRow(const QString &fileName,const QString &filePath);
    void calculateDifference(QTableWidget *currentQtableWidget,int row);
    void updateInspectionDate(QTableWidget *currentQtableWidget, int row);
    void setupConnections();
    void updateCellInfo(QTableWidget *qTable,int row,int column,const QString &newText);

    void closeEvent(QCloseEvent *event) override;

    QAction *actionexcelFile;
    ExcelReaderAndDisplayer * excelReaderAndDisplayer;
    DatabaseInsertPage *databaseInsertPage;
    DetectorManager &detectorManager;
    QMediaPlayer *mediaPlayer;
    WorkspaceFileManager *workspaceFileManager;
    WorkspaceOpener *workspaceOpener;

    WorkspaceInfo currentWorkspace;

    DetectorSizeSettings *detectorSizeSettings;



    float p;
private slots:
    void TimeUpdate();
    void DetectorSizeSet(int NewSize);

    void handleDetectionCompleted(int row,double wellDepth);
    void handleSetTotalVideoCount(int videoTotal);
    void handleDetectionAllCompleted();


    void on_loadButton_clicked();
    void on_addButton_clicked();
    void on_deleteButton_clicked();
    void on_saveButton_clicked();
    void on_saveAllButton_clicked();
    void on_actionWatch_triggered();

    void on_action_Excel_triggered();
    void on_saveFileButton_clicked();
    void on_pushButton_2_clicked();
    void on_actionExit_triggered();

    void on_action_create_triggered();
    void on_openFileButton_clicked();
    void on_startDetectionButton_clicked();
    void on_action_D_triggered();
    void on_startDetectionButton_2_clicked();
    void on_action_open_workspace_triggered();
    void openWorkspaceTable(QString table);
    void loadTableToWidget(QString tableName,QString sqlstr,QTableWidget *qTableWidget);
    void loadQTableWidgettoDatabase(QString tableName,QTableWidget *qTableWidget);
    void on_stationnumberpushButton_clicked();
    void on_action_detectors_triggered();
    void updateProgressBar(int progress);

    void on_startDetectionButton_MainPage_clicked();
    void on_selectAllCheckBox_stateChanged(int state);
    void on_stationnumberlineSearch_textChanged(const QString &arg1);
    void connectDetector(int row, const std::string& videoPath, int totalCount, float *p);
    void on_videoInfoTableWidget_itemChanged(QTableWidgetItem *item);
    void on_action_main_triggered();
    void on_commitChangeToDatabasePushbutton_clicked();
};
#endif // MAINWINDOW_H
