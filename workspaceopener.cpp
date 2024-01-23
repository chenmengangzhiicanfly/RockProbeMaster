#include "workspaceopener.h"
#include "ui_workspaceopener.h"
#include <QMessageBox>
WorkspaceOpener::WorkspaceOpener(QWidget *parent) :
    QDialog(parent),tableWidget(new QTableWidget(this)),
    ui(new Ui::WorkspaceOpener)
{
    ui->setupUi(this);
    tableWidget->setColumnCount(2);
    tableWidget->setHorizontalHeaderLabels({"Workspace Name","Station Number"});
    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(tableWidget);
    setWindowTitle("打开工区");
    setLayout(mainLayout);
    setupConnections();
}

WorkspaceOpener::~WorkspaceOpener()
{
    delete ui;
}

void WorkspaceOpener::addWorkspaceInfo(const WorkspaceInfo &workspaceInfo)
{
    int row =tableWidget->rowCount();
    tableWidget->insertRow(row);
    QTableWidgetItem *nameItem = new QTableWidgetItem(workspaceInfo.workspaceName);
    QTableWidgetItem *stationItem = new QTableWidgetItem(workspaceInfo.workspaceStationNumber);
    tableWidget->setItem(row,0,nameItem);
    tableWidget->setItem(row,1,stationItem);
    workspaces.append(workspaceInfo);
}

bool WorkspaceOpener::loadWorkspacesFromJson()
{
    QFile file("workspaceInfo.json");
    QJsonParseError error;
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)){
        //        QByteArray value=file.readAll();
        //        QString strJson(value);
        //        qDebug()<<strJson;
        QJsonDocument jsonDoc = QJsonDocument::fromJson(file.readAll(),&error);
        file.close();
        if(!jsonDoc.isNull() &&(error.error ==QJsonParseError::NoError)){
            if(jsonDoc.isArray()){
                QJsonArray array = jsonDoc.array();
                int asize = array.size();
                for(int i=0;i < asize;i++){
                    WorkspaceInfo workspace;
                    QJsonObject obj = array.at(i).toObject();
                    workspace.workspaceName = obj.value("workspaceName").toString();
                    workspace.workspaceStationNumber = obj.value("workspaceStationNumber").toString();
                    workspace.workspaceLeader = obj.value("workspaceLeader").toString();
                    workspace.workspaceVideoPath = obj.value("workspaceVideoPath").toString();

                    addWorkspaceInfo(workspace);
                }
            }

            //            if (jsonDoc.isObject()) { // JSON 文档为对象
            //                QJsonObject object = jsonDoc.object();  // 转化为对象
            //                if (object.contains("workspaceName")) {  // 包含指定的 key
            //                    QJsonValue value = object.value("workspaceName");  // 获取指定 key 对应的 value
            //                    if (value.isString()) {  // 判断 value 是否为字符串
            //                        QString strName = value.toString();  // 将 value 转化为字符串
            //                        qDebug() << "workspaceName : " << strName;
            //                    }
            //                }
            //                if (object.contains("workspaceStationNumber")) {
            //                    QJsonValue value = object.value("workspaceStationNumber");
            //                    if (value.isString()) {
            //                        QString nFrom = value.toVariant().toString();
            //                        qDebug() << "workspaceStationNumber : " << nFrom;
            //                    }
            //                }
            //            }

            //            addWorkspaceInfo(workspace);
        }
        else qDebug()<<error.errorString();
    }
    else {
        return false;
    }
    return true;
}

void WorkspaceOpener::setupConnections()
{
    connect(tableWidget,&QTableWidget::itemDoubleClicked,this,&WorkspaceOpener::onTableItemDoubleClicked);
}

void WorkspaceOpener::onTableItemDoubleClicked()
{
    QString temp_workspace =tableWidget->item(tableWidget->currentRow(),0)->text();
    WorkspaceInfo workspace;
    for(auto temp : workspaces){
        if(temp_workspace==temp.workspaceName){
            workspace=temp;
            break;
        }
    }
    emit onTableItemDoubleClickedtoMain(workspace);
}

