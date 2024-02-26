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
    QString worker;
    QString workDate;
    QString videoName;
    QString processing_status;
    QString design_depth;
    QString design_explosive_quantity;
    QString video_evaluation;
    QString review_status;
    QString measured_depth;
    QString explosive_amount_deployed;
    QString identification_result;
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
    QVector<VideoInfo> videoList;
private:
    Ui::WorkspaceFileManager *ui;


private slots:
    void createTable();
};

#endif // WORKSPACEFILEMANAGER_H
