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
#include<QPushButton>
#include<QFileDialog>
#include<QLabel>
WorkspaceFileManager::WorkspaceFileManager(QWidget *parent) :
    QDialog(parent),workspace(new QLineEdit(this)),leader(new QLineEdit(this)),videoPath(new QLineEdit(this)),workspaceExcel(new QLineEdit(this)),
    ui(new Ui::WorkspaceFileManager)
{
    ui->setupUi(this);
    setWindowTitle("创建工区");

    QLineEdit *moreInfoQLineEdit = new QLineEdit(this);
    moreInfoQLineEdit->setFixedHeight(200);

    QHBoxLayout *videoLayout = new QHBoxLayout;
    videoLayout->addWidget(videoPath);
    QPushButton *browseButton = new QPushButton("...", this);
    videoLayout->addWidget(browseButton);
    browseButton->setFixedWidth(20);

    QHBoxLayout *workspaceExcelLayout =new QHBoxLayout;
    QPushButton *browseButtonExcel = new QPushButton("...", this);
    workspaceExcelLayout->addWidget(workspaceExcel);
    workspaceExcelLayout->addWidget(browseButtonExcel);

    browseButtonExcel ->setFixedWidth(20);
    connect(browseButton, &QPushButton::clicked, this, &WorkspaceFileManager::browseVideoPath);
    connect(browseButtonExcel,&QPushButton::clicked,this,&WorkspaceFileManager::browseWorkspaceExcelPath);
    QFormLayout *layout = new QFormLayout;

    layout->addRow("工区名称：",workspace);
    layout->addRow("负责人：",leader);
    layout->addRow("工区视频路径：",videoLayout);
    layout->addRow("工区设计文件：",workspaceExcelLayout);
    layout->addRow("工区更多信息：", moreInfoQLineEdit);

    QVBoxLayout *mainLayout = new QVBoxLayout;
    QDialogButtonBox *buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel,Qt::Horizontal,this);


    mainLayout->addLayout(layout);
    mainLayout->addWidget(buttonBox);

    connect(buttonBox, &QDialogButtonBox::accepted, this, &WorkspaceFileManager::accept);
    connect(buttonBox, &QDialogButtonBox::rejected, this, &WorkspaceFileManager::reject);
    this->videoPath->setText("F:/工区视频文件/不带txt/梓潼大队");
    this->workspaceExcel->setText("D:/DeskTop/梓潼大队.xlsx");
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

void WorkspaceFileManager::insertVideoData(const WorkspaceInfo &workspace,QTableWidget *tableWidget)
{
    QXlsx::Document xlsx(workspace.workspaceExcelPath);
    if (!xlsx.load()) {
        qDebug() << "Failed to load xlsx file.";
        return;
    }

    tableWidget->clear();
    tableWidget->setRowCount(0);
    QStringList header;
    tableWidget->setColumnCount(3);
    header <<"日期"<<"井监"<<"视频名";
    tableWidget->setHorizontalHeaderLabels(header);

    QDir dir(workspace.workspaceVideoPath);
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


                QString stationNumber = videoname;
                if (stationNumber.isEmpty()) {
                    qDebug() << "Failed to get stake number from video name: " << videoname;
                    continue;
                }
                QStringList videoInfo = this->getRowValueByStationNumber(xlsx,stationNumber);
                VideoInfo videoData;
                videoData.stationNumber = videoname;
                videoData.videoName = video;
                videoData.chargingDate =dateFolder;
                videoData.wellSupervisor = workerFolder;
                videoData.inspector = workspace.workspaceLeader;

                videoData.designDrillingDepth =videoInfo.at(2);
                videoData.designInitiationDepth = videoInfo.at(3);

                videoData.singleWellExplosiveAmount= videoInfo.at(4);
                videoData.quantityOfDetonatorsPerWell= videoInfo.at(5);
                videoData.numberOfWells = videoInfo.at(6);
                videoData.videoPath = videoFolderDir.absoluteFilePath(video);
                videoData.processingStatus = QString("未处理");
                videoData.reviewStatus = QString("否");

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
                      "numberOfWells, processingStatus, reviewStatus, depthOfCharging, difference, wellSupervisor, inspector, "
                      "chargingDate, inspectionDate, drillingEvaluation, remarks, videoPath) "
                      "VALUES "
                      "(:stationNumber, :videoName, :designDrillingDepth, :designInitiationDepth, :singleWellExplosiveAmount, :quantityOfDetonatorsPerWell, "
                      ":numberOfWells, :processingStatus, :reviewStatus, :depthOfCharging, :difference, :wellSupervisor, :inspector, "
                      ":chargingDate, :inspectionDate, :drillingEvaluation, :remarks, :videoPath)");


        query.bindValue(":stationNumber", video.stationNumber);
        query.bindValue(":videoName",video.videoName);
        query.bindValue(":designDrillingDepth",video.designDrillingDepth);
        query.bindValue(":designInitiationDepth", video.designInitiationDepth);
        query.bindValue(":singleWellExplosiveAmount", video.singleWellExplosiveAmount);
        query.bindValue(":quantityOfDetonatorsPerWell", video.quantityOfDetonatorsPerWell);
        query.bindValue(":numberOfWells", video.numberOfWells);
        query.bindValue(":processingStatus",video.processingStatus);
        query.bindValue(":reviewStatus",video.reviewStatus);
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
                                   "stationNumber VARCHAR(100) PRIMARY KEY,"
                                   "videoName TEXT,"
                                   "designDrillingDepth TEXT,"
                                   "designInitiationDepth TEXT,"
                                   "singleWellExplosiveAmount TEXT,"
                                   "quantityOfDetonatorsPerWell TEXT,"
                                   "numberOfWells TEXT,"
                                   "processingStatus TEXT,"
                                   "reviewStatus TEXT,"
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
                                           "workspaceVideoPath TEXT,"
                                           "workspaceExcelPath TEXT)";
    QSqlQuery query;
    if (!query.exec(createTableQuery)) {
        QMessageBox::warning(nullptr, "表创建失败", "无法创建表: " + query.lastError().text());
        return;
    }
    QByteArray workspaceNameBytes = workspaceinfo.workspaceName.toUtf8();
    const char *workspaceNameChar = workspaceNameBytes.constData();
    QString insertQuery = QString("INSERT INTO TableList (workspaceName,workspaceLeader,workspaceVideoPath,workspaceExcelPath) VALUES ('%1','%2','%3','%4')").arg(workspaceinfo.workspaceName)
                                                                                                                                     .arg(workspaceinfo.workspaceLeader)
                                                                                                                                     .arg(workspaceinfo.workspaceVideoPath)
                                                                                                                                     .arg(workspaceinfo.workspaceExcelPath);
        if (!query.exec(insertQuery)) {
            QMessageBox::warning(nullptr, "插入数据失败", "无法插入数据: " + query.lastError().text());
            return;
        }
}

QStringList WorkspaceFileManager::getRowValueByStationNumber(QXlsx::Document &xlsx, const QString &stationNumber)
{
        QStringList rowValues;

        // 遍历第二列，查找确定值所在的行
        for (int row = 2; row <= xlsx.dimension().lastRow(); ++row) { // 从第二行开始，假设第一行是表头
            QString value = xlsx.read(row, 2).toString(); // 读取第二列的值
            if (value == stationNumber) {
            // 如果找到确定值所在的行，获取该行的所有列的值并保存到 rowValues 中
            for (int col = 1; col <= xlsx.dimension().lastColumn(); ++col) {
                QString cellValue = xlsx.read(row, col).toString();
                rowValues.append(cellValue);
            }
            break; // 找到指定值后退出循环
            }
        }

        return rowValues;
}

void WorkspaceFileManager::createTable()
{

}

void WorkspaceFileManager::browseVideoPath() {
    QString folderPath = QFileDialog::getExistingDirectory(this, tr("选择视频文件夹"), QDir::homePath());
    if (!folderPath.isEmpty()) {
        QDir directory(folderPath);

        // 获取日期文件夹
        QStringList dateFolders;
        for (const QFileInfo &info : directory.entryInfoList(QDir::Dirs | QDir::NoDotAndDotDot)) {
            QString folderName = info.fileName();
            if (folderName.isEmpty())
                continue;
            dateFolders.append(folderName);
        }

        // 如果不存在日期文件夹，则显示警告
        if (dateFolders.isEmpty()) {
            QMessageBox::warning(this, tr("警告"), tr("未找到日期文件夹。"));
            return;
        }

        // 遍历日期文件夹
        for (const QString &dateFolder : dateFolders) {
            QDir dateDir(directory.absoluteFilePath(dateFolder));

            // 获取人名文件夹
            QStringList nameFolders;
            for (const QFileInfo &info : dateDir.entryInfoList(QDir::Dirs | QDir::NoDotAndDotDot)) {
                QString folderName = info.fileName();
                if (folderName.isEmpty())
                    continue;
                nameFolders.append(folderName);
            }

            // 如果没有人名文件夹，则显示警告
            if (nameFolders.isEmpty()) {
                QMessageBox::warning(this, tr("警告"), tr("日期文件夹内未找到人名文件夹。"));
                return;
            }

            // 遍历人名文件夹
            for (const QString &nameFolder : nameFolders) {
                QDir nameDir(dateDir.absoluteFilePath(nameFolder));
                QStringList videoFiles;

                // 遍历人名文件夹中的视频文件
                for (const QFileInfo &info : nameDir.entryInfoList(QDir::Files)) {
                    QString fileName = info.fileName();
                    if (fileName.isEmpty() || !fileName.endsWith(".mp4", Qt::CaseInsensitive)
                            && !fileName.endsWith(".avi", Qt::CaseInsensitive) && !fileName.endsWith(".mov", Qt::CaseInsensitive)) {
                        QMessageBox::warning(this, tr("警告"), tr("人名文件夹内所有文件必须都是视频文件（.mp4, .avi, .mov）。"));
                        return;
                    }
                    videoFiles.append(fileName);
                }

                // 如果人名文件夹内没有视频文件，则显示警告
                if (videoFiles.isEmpty()) {
                    QMessageBox::warning(this, tr("警告"), tr("人名文件夹内未找到视频文件。"));
                    return;
                }
            }
        }

        videoPath->setText(folderPath);
    }
}

void WorkspaceFileManager::browseWorkspaceExcelPath()
{
    QString folderPath = this->videoPath->text();
    if (folderPath.isEmpty()) {
        QMessageBox::warning(this, tr("警告"), tr("请先选择工区视频文件夹。"));
        return;
    }
    QString filePath = QFileDialog::getOpenFileName(this, tr("选择工区视频文件"), QDir::homePath(), tr("Excel 文件 (*.xlsx *.xls)"));
    if (!filePath.isEmpty()) {
        // 在这里调用读取 Excel 文件名的方法

        QXlsx::Document xlsx(filePath);
        if (xlsx.load()) {
            QFileInfo fileInfo(filePath);
            QString fileName = fileInfo.baseName();

            QFileInfo workspaceInfo(this->videoPath->text());
            QString workspace = workspaceInfo.fileName();

            if (fileName != workspace) {
                QMessageBox::warning(this, tr("警告"), tr("Excel 文件名与工区名称不一致。"));
                return;
            }
        workspaceExcel->setText(filePath);

        } else {
            qDebug() << "无法打开 Excel 文件：" << filePath;
        }
    }
}

