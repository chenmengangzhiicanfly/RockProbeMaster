#ifndef WORKSPACEFILEMANAGER_H
#define WORKSPACEFILEMANAGER_H

#include <QDialog>
#include <QLineEdit>
#include <QDir>
#include <QTableWidget>
#include <QTableWidgetItem>
struct WorkspaceInfo{
    QString workspaceName;
    QString workspaceLeader;
    QString workspaceVideoPath;
    WorkspaceInfo(QString tableName,QString leader,QString videoPath):workspaceName(tableName),workspaceLeader(leader),workspaceVideoPath(videoPath)
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

    QLineEdit *tableNameEdit;
    QLineEdit *leader;
    QLineEdit *videoPath;
    void saveWorkspaceInfoTOJson(const WorkspaceInfo &workspaceInfo);
    void insertVideoData(const QString& folderPath,WorkspaceInfo &workspace,QTableWidget* tableWidget);
    void insertDataIntoTable(QVector<VideoInfo> &videoLists,WorkspaceInfo workspace);
    void createTableInDatabase(const QString& tableName);
    void createOrInsertMasterTable(WorkspaceInfo workspaceinfo);

    QVector<VideoInfo> videoList;
private:
    Ui::WorkspaceFileManager *ui;

private slots:
    void createTable();
};

#endif // WORKSPACEFILEMANAGER_H
