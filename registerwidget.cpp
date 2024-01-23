#include "registerwidget.h"
#include "ui_registerwidget.h"
#include <QSettings>
#include <QDebug>
#include <QSqlQuery>
#include <QMessageBox>
RegisterWidget::RegisterWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::RegisterWidget)
{
    ui->setupUi(this);
    setWindowTitle("log up");
    clear();
    connect(ui->registerButton,&QPushButton::clicked,this,&RegisterWidget::registerUser);
    connect(ui->backButton,&QPushButton::clicked,this,&RegisterWidget::goback);
}

RegisterWidget::~RegisterWidget()
{
    delete ui;
}

void RegisterWidget::clear()
{
    ui->usernameEdit->clear();
    ui->passwordEdit->clear();
}


//非数据库版本


//void RegisterWidget::registerUser(){
//    qDebug()<<"正在注册" ;
//    QString path = "./user.ini";
//    QSettings *config = new QSettings(path, QSettings::IniFormat);

//    //用户名base64加密
//    QString uidsec = ui->usernameEdit->text();
//    QByteArray uidb64 = uidsec.toLocal8Bit().toBase64();
//    QString uid = QString::fromLocal8Bit(uidb64);

//    //密码base64加密
//    QString pwdsec = ui->passwordEdit -> text();
//    QByteArray pwdb64 = pwdsec.toLocal8Bit().toBase64();
//    QString pwd = QString::fromLocal8Bit(pwdb64);

//    //将信息写入配置文件
//    config -> beginGroup("config");
//    config -> setValue("uid", uid);
//    config -> setValue("pwd", pwd);
//    config -> endGroup();

//}

void RegisterWidget::registerUser(){
    if(ui->usernameEdit->text() != nullptr && ui->passwordEdit->text() != nullptr){
        QString username =ui->usernameEdit->text();
        QString password =ui->passwordEdit->text();
        QString qs1 = QString("select * from mydata.user where username ='%1'").arg(username);
        QString qs2 = QString("insert into user(username,password) values('%1','%2')").arg(username).arg(password);
        QSqlQuery query;

        query.exec(qs1); //查询用户名是否重复

        if(!query.next())   //如果没有找到该用户名
        {
            query.exec(qs2);
            QMessageBox::information(this, "提示", "注册成功！");
            ui->usernameEdit->clear();
            ui->passwordEdit->clear();
        }
        else
        {
            QMessageBox::critical(this,"提示","用户名已存在，请重新输入！");
            ui->usernameEdit->clear();
            ui->passwordEdit->clear();
        }

    }
    else    QMessageBox::critical(this,"提示","用户名或密码为空，请重新输入！");


}





