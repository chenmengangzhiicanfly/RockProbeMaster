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
#include <QSqlQuery>
#include <QSqlError>
#include<QMessageBox>
WorkspaceFileManager::WorkspaceFileManager(QWidget *parent) :
    QDialog(parent),tableNameEdit(new QLineEdit(this)),leader(new QLineEdit(this)),videoPath(new QLineEdit(this)),
    ui(new Ui::WorkspaceFileManager)
{
    ui->setupUi(this);
    setWindowTitle("创建工区");
    QFormLayout *layout = new QFormLayout;
    layout->addRow("表名:",tableNameEdit);
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

void WorkspaceFileManager::insertVideoData(const QString &folderPath,WorkspaceInfo &workspace,QTableWidget *tableWidget)
{
    tableWidget->clear();
    tableWidget->setRowCount(0);

    QStringList header;
    tableWidget->setColumnCount(3);
    header <<"日期"<<"井监"<<"视频名";
    tableWidget->setHorizontalHeaderLabels(header);
    QDir dir(folderPath);
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

                QFileInfo fileInfo(video);
                QString videoname = fileInfo.completeBaseName();
                int row = tableWidget->rowCount();
                tableWidget->insertRow(row);
                QTableWidgetItem* videoItem = new QTableWidgetItem(video);
                QTableWidgetItem* workerItem = new QTableWidgetItem(workerFolder);
                QTableWidgetItem* dateItem = new QTableWidgetItem(dateFolder);
                tableWidget->setItem(row, 2, videoItem);
                tableWidget->setItem(row, 1, workerItem);
                tableWidget->setItem(row, 0, dateItem);
                VideoInfo videoData;
                videoData.stationNumber = videoname;
                videoData.videoName = video;
                videoData.inspector = workspace.workspaceLeader;
                videoData.designDrillingDepth = QString("10.0");
                videoData.designInitiationDepth = QString("8.0");
                videoData.numberOfWells = QString("1");
                videoData.singleWellExplosiveAmount= QString("8");
                videoData.quantityOfDetonatorsPerWell= QString("2");
                videoData.videoPath = fileInfo.absoluteFilePath();
                videoList.append(videoData);
            }
        }
    }
}

void WorkspaceFileManager::insertDataIntoTable(QVector<VideoInfo> &videoLists, WorkspaceInfo workspace)
{
    QSqlQuery query;
    qDebug()<<videoLists.size();
    for(auto video : videoLists){
        query.prepare("INSERT INTO "+workspace.workspaceName+
                      "(stationNumber, videoName, designDrillingDepth, designInitiationDepth, singleWellExplosiveAmount, quantityOfDetonatorsPerWell, "
                      "numberOfWells, depthOfCharging, difference, wellSupervisor, inspector, "
                      "chargingDate, inspectionDate, drillingEvaluation, remarks, videoPath) "
                      "VALUES "
                      "(:stationNumber, :videoName, :designDrillingDepth, :designInitiationDepth, :singleWellExplosiveAmount, :quantityOfDetonatorsPerWell, "
                      ":numberOfWells, :depthOfCharging, :difference, :wellSupervisor, :inspector, "
                      ":chargingDate, :inspectionDate, :drillingEvaluation, :remarks, :videoPath)");


        query.bindValue(":stationNumber", video.stationNumber.toInt());
        query.bindValue(":videoName",video.videoName);
        query.bindValue(":designDrillingDepth",video.designDrillingDepth);
        query.bindValue(":designInitiationDepth", video.designInitiationDepth);
        query.bindValue(":singleWellExplosiveAmount", video.singleWellExplosiveAmount);
        query.bindValue(":quantityOfDetonatorsPerWell", video.quantityOfDetonatorsPerWell);
        query.bindValue(":numberOfWells", video.numberOfWells);
        query.bindValue(":depthOfCharging", video.depthOfCharging);
        query.bindValue(":difference", video.difference);
        query.bindValue(":wellSupervisor", video.wellSupervisor);
        query.bindValue(":inspector", video.inspector);
        query.bindValue(":chargingDate", video.chargingDate);
        query.bindValue(":inspectionDate", video.inspectionDate);
        query.bindValue(":drillingEvaluation", video.drillingEvaluation);
        query.bindValue(":remarks", video.remarks);
        query.bindValue(":videoPath", video.videoPath);

        if (query.exec()) {
            qDebug() << "数据插入成功";

        } else {
            qDebug() << "数据插入失败: " << query.lastError().text();
        }
    }
}

void WorkspaceFileManager::createTableInDatabase(const QString &tableName)
{
 QString createTableQuery = "CREATE TABLE " + tableName + " ("
                                   "stationNumber INT PRIMARY KEY,"
                                   "videoName TEXT,"
                                   "designDrillingDepth TEXT,"
                                   "designInitiationDepth TEXT,"
                                   "singleWellExplosiveAmount TEXT,"
                                   "quantityOfDetonatorsPerWell TEXT,"
                                   "numberOfWells TEXT,"
                                   "depthOfCharging TEXT,"
                                   "difference TEXT,"
                                   "wellSupervisor TEXT,"
                                   "inspector TEXT,"
                                   "chargingDate TEXT,"
                                   "inspectionDate TEXT,"
                                   "drillingEvaluation TEXT,"
                                   "remarks TEXT,"
                                   "videoPath TEXT)";

        QSqlQuery query;

        if (query.exec(createTableQuery)) {
            QMessageBox::information(nullptr, "表创建成功", "新表成功创建！");
        } else {
            QMessageBox::warning(nullptr, "表创建失败", "无法创建表: " + query.lastError().text());
        }
}

void WorkspaceFileManager::createOrInsertMasterTable(WorkspaceInfo workspaceinfo)
{
    QString createTableQuery = "CREATE TABLE IF NOT EXISTS TableList ("
                                           "workspaceName VARCHAR(255) NOT NULL PRIMARY KEY,"
                                           "workspaceLeader TEXT,"
                                           "workspaceVideoPath TEXT)";
    QSqlQuery query;
    if (!query.exec(createTableQuery)) {
        QMessageBox::warning(nullptr, "表创建失败", "无法创建表: " + query.lastError().text());
        return;
    }
    QByteArray workspaceNameBytes = workspaceinfo.workspaceName.toUtf8();
    const char *workspaceNameChar = workspaceNameBytes.constData();
    QString insertQuery = QString("INSERT INTO TableList (workspaceName,workspaceLeader,workspaceVideoPath) VALUES ('%1','%2','%3')").arg(workspaceinfo.workspaceName)
                                                                                                                                     .arg(workspaceinfo.workspaceLeader)
                                                                                                                                     .arg(workspaceinfo.workspaceVideoPath);
        if (!query.exec(insertQuery)) {
            QMessageBox::warning(nullptr, "插入数据失败", "无法插入数据: " + query.lastError().text());
            return;
        }
}

void WorkspaceFileManager::createTable()
{

}
