#ifndef WORKSPACEFILEMANAGER_H
#define WORKSPACEFILEMANAGER_H

#include <QDialog>
#include <QLineEdit>
#include <QDir>
#include <QTableWidget>
#include <QTableWidgetItem>
struct WorkspaceInfo{
    QString workspaceName;
    QString workspaceStationNumber;
    QString workspaceLeader;
    QString workspaceVideoPath;
    WorkspaceInfo(QString tableName,QString leader,QString videoPath,QString id):workspaceName(tableName),workspaceLeader(leader),workspaceVideoPath(videoPath),
        workspaceStationNumber(id){}
    WorkspaceInfo(){}
};
struct VideoInfo{
    QString stationNumber;
    QString worker;
    QString workDate;
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
    QLineEdit *stationNumber;
    QLineEdit *leader;
    QLineEdit *videoPath;
    void saveWorkspaceInfoTOJson(const WorkspaceInfo &workspaceInfo);
    void insertVideoData(const QString& folderPath,QTableWidget* tableWidget);

    QVector<VideoInfo> videoList;
private:
    Ui::WorkspaceFileManager *ui;


private slots:
    void createTable();
};

#endif // WORKSPACEFILEMANAGER_H
