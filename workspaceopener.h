#ifndef WORKSPACEOPENER_H
#define WORKSPACEOPENER_H

#include <QDialog>
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QPushButton>
#include <QVBoxLayout>
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QTextStream>
#include <QMessageBox>
#include "workspacefilemanager.h"

#define TABLE_COLUMN 3;
namespace Ui {
class WorkspaceOpener;
}

class WorkspaceOpener : public QDialog
{
    Q_OBJECT

public:
    explicit WorkspaceOpener(QWidget *parent = nullptr);
    ~WorkspaceOpener();
    void addWorkspaceInfo(const WorkspaceInfo &workspaceInfo);
    bool loadWorkspacesFromJson();
    bool loadWorkspaceInfoFromDatabase();

private:
    Ui::WorkspaceOpener *ui;
    QTableWidget *tableWidget;
    QVector<WorkspaceInfo> workspaces;
    void setupConnections();
public slots:
    void onTableItemDoubleClicked();
signals:
    void onTableItemDoubleClickedtoMain(QString table);
};

#endif // WORKSPACEOPENER_H
