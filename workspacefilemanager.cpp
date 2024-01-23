#include "workspacefilemanager.h"
#include "ui_workspacefilemanager.h"
#include "QString"
#include <QFormLayout>
#include <QDialogButtonBox>
#include <QFile>
#include <QIODevice>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
WorkspaceFileManager::WorkspaceFileManager(QWidget *parent) :
    QDialog(parent),tableNameEdit(new QLineEdit(this)),stationNumber(new QLineEdit(this)),leader(new QLineEdit(this)),videoPath(new QLineEdit(this)),
    ui(new Ui::WorkspaceFileManager)
{
    ui->setupUi(this);
    setWindowTitle("创建工区");
    QFormLayout *layout = new QFormLayout;
    layout->addRow("表名:",tableNameEdit);
    layout->addRow("桩号:",stationNumber);
    layout->addRow("负责人:",leader);
    layout->addRow("工区视频路径:",videoPath);

    QVBoxLayout *mainLayout = new QVBoxLayout;
    QDialogButtonBox *buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel,Qt::Horizontal,this);


    mainLayout->addLayout(layout);
    mainLayout->addWidget(buttonBox);

    connect(buttonBox, &QDialogButtonBox::accepted, this, &WorkspaceFileManager::accept);
    connect(buttonBox, &QDialogButtonBox::rejected, this, &WorkspaceFileManager::reject);
    setLayout(mainLayout);
}

WorkspaceFileManager::~WorkspaceFileManager()
{
    delete ui;
}

void WorkspaceFileManager::saveWorkspaceInfoTOJson(const WorkspaceInfo &workspaceInfo)
{
    QFile file("workspaceInfo.json");
    if(file.open(QIODevice::ReadWrite| QIODevice::Text)){
        QByteArray jsonData = file.readAll();
        file.resize(0);
        QJsonDocument jsonDoc;
        QJsonParseError jsonError;
        if (!jsonData.isEmpty()) {
            jsonDoc = QJsonDocument::fromJson(jsonData, &jsonError);
            if (jsonError.error != QJsonParseError::NoError) {
                qDebug() << "Error parsing existing JSON data:" << jsonError.errorString();
                return;
            }
        }
        else qDebug()<<"error";
//        if (!jsonDoc.isArray()) {
//            jsonDoc = QJsonDocument::array();
//        }
        QJsonArray jsonArray = jsonDoc.array();
        QJsonObject jsonObject;
        jsonObject.insert("workspaceName",workspaceInfo.workspaceName);
        jsonObject.insert("workspaceStationNumber",workspaceInfo.workspaceStationNumber);
        jsonObject.insert("workspaceLeader",workspaceInfo.workspaceLeader);
        jsonObject.insert("workspaceVideoPath",workspaceInfo.workspaceVideoPath);

        jsonArray.append(jsonObject);
        jsonDoc.setArray(jsonArray);
        QByteArray byteArray = jsonDoc.toJson(QJsonDocument::Compact);
        QString strJson(byteArray);
        qDebug() << strJson;
//        QTextStream stream(&file);
//        stream << strJson;
        QTextStream stream(&file);
        stream << jsonDoc.toJson();
        file.close();

//        QJsonParseError jsonError;
//        QJsonDocument doucment = QJsonDocument::fromJson(byteArray, &jsonError);  // 转化为 JSON 文档
//        if (!doucment.isNull() && (jsonError.error == QJsonParseError::NoError)) {  // 解析未发生错误
//            if (doucment.isObject()) { // JSON 文档为对象
//                QJsonObject object = doucment.object();  // 转化为对象
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
//        }
    }
}

void WorkspaceFileManager::insertVideoData(const QString &folder, QTableWidget *tableWidget)
{
    tableWidget->clear();
    tableWidget->setRowCount(0);

    QStringList header;
    tableWidget->setColumnCount(3);
    header <<"日期"<<"人名"<<"视频名";
    tableWidget->setHorizontalHeaderLabels(header);
    QDir dir(folder);
    if(!dir.exists()){
        qDebug()<<"Directory not found";
        return ;
    }
    QStringList dateFolders = dir.entryList(QDir::Dirs | QDir::NoDotAndDotDot);
    for(const QString& dateFolder :dateFolders){
        QString workerFolderPath = dir.filePath(dateFolder);
        QDir workerFolderDir(workerFolderPath);
        QStringList workerFolders =workerFolderDir.entryList(QDir::Dirs | QDir::NoDotAndDotDot);
        for(const QString& workerFolder : workerFolders){
        // 获取文件夹下所有视频文件
            QString videoFolderPath = workerFolderDir.filePath(workerFolder);
            QDir videoFolderDir(videoFolderPath);
            QStringList videos = videoFolderDir.entryList(QStringList() << "*.mp4" << "*.avi" << "*.mkv" << "*.mov", QDir::Files);
        for(const QString& video :videos){
            int row = tableWidget->rowCount();
            tableWidget->insertRow(row);
            QTableWidgetItem* videoItem = new QTableWidgetItem(video);
            QTableWidgetItem* workerItem = new QTableWidgetItem(workerFolder);
            QTableWidgetItem* dateItem = new QTableWidgetItem(dateFolder);
            tableWidget->setItem(row, 2, videoItem);
            tableWidget->setItem(row, 1, workerItem);
            tableWidget->setItem(row, 0, dateItem);

            VideoInfo videoData;
            videoData.stationNumber =video;
            videoData.worker = workerFolder;
            videoData.workDate = dateFolder;
            videoData.workspaceInfo.workspaceLeader ="1";
            videoData.workspaceInfo.workspaceVideoPath="1";
            videoData.workspaceInfo.workspaceName="1";
            videoData.workspaceInfo.workspaceStationNumber="1";
            videoList.append(videoData);
        }
        }
    }
}

void WorkspaceFileManager::createTable()
{

}
