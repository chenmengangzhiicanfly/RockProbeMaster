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
private:
    Ui::MainWindow *ui;
    QStatusBar *statusBar;

    QLabel *showTimeLabel;
private:
    void init();
    void initMenu();
    void initStatus();

    void exportQtable();
    void importQtable();


    void closeEvent(QCloseEvent *event) override;
    QAction *actionexcelFile;
    ExcelReaderAndDisplayer * excelReaderAndDisplayer;
    DatabaseInsertPage *databaseInsertPage;

    DetectorManager *detectorManager;
    QMediaPlayer *mediaPlayer;
    WorkspaceFileManager *workspaceFileManager;
    WorkspaceOpener *workspaceOpener;
private slots:
    void TimeUpdate();
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
    void openWorkspaceTable(WorkspaceInfo workspace);
};
#endif // MAINWINDOW_H
