#ifndef WORKSPACEFILEMANAGER_H
#define WORKSPACEFILEMANAGER_H

#include <QDialog>
#include <QLineEdit>
#include <QDir>
#include <QTableWidget>
#include <QTableWidgetItem>
#include<QStandardItem>
#include "xlsxdocument.h"
struct WorkspaceInfo{
    QString workspaceName;
    QString workspaceLeader;
    QString workspaceVideoPath;
    QString workspaceExcelPath;
    QStandardItem* workspaceItem;
    WorkspaceInfo(QString tableName,QString leader,QString videoPath,QString excelPath):workspaceName(tableName),workspaceLeader(leader),
        workspaceVideoPath(videoPath),workspaceExcelPath(excelPath)
    {}
    WorkspaceInfo(){}
};


struct VideoInfo{
   QString stationNumber;
   QString videoName;
   QString designDrillingDepth;
   QString designInitiationDepth;
   QString singleWellExplosiveAmount;
   QString quantityOfDetonatorsPerWell;
   QString numberOfWells;
   QString processingStatus;
   QString reviewStatus;
   QString depthOfCharging;
   QString difference;
   QString wellSupervisor;
   QString inspector;
   QString chargingDate;
   QString inspectionDate;
   QString drillingEvaluation;
   QString remarks;
   QString videoPath;

   struct WorkspaceInfo workspaceInfo;
};

namespace Ui {
class WorkspaceFileManager;
}

class WorkspaceFileManager : public QDialog
{
    Q_OBJECT

public:
    explicit WorkspaceFileManager(QWidget *parent = nullptr);
    ~WorkspaceFileManager();

    QLineEdit *workspace;
    QLineEdit *leader;
    QLineEdit *videoPath;
    QLineEdit *workspaceExcel;
    void saveWorkspaceInfoTOJson(const WorkspaceInfo &workspaceInfo);
    void insertVideoData(const WorkspaceInfo &workspace,QTableWidget* tableWidget);
    void insertDataIntoTable(QVector<VideoInfo> &videoLists,WorkspaceInfo workspace);
    void createTableInDatabase(const QString& tableName);
    void createOrInsertMasterTable(WorkspaceInfo workspaceinfo);

    QStringList getRowValueByStationNumber(QXlsx::Document &xlsx, const QString &stationNumber);
    QVector<VideoInfo> videoList;
private:
    Ui::WorkspaceFileManager *ui;

private slots:
    void createTable();
    void browseVideoPath();
    void browseWorkspaceExcelPath();
};

#endif // WORKSPACEFILEMANAGER_H
