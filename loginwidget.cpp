#include "loginwidget.h"
#include "ui_loginwidget.h"
#include "registerwidget.h"
#include <QSettings>
#include <QDebug>
#include <QMessageBox>
#include <QDialog>
#include <QSqlQuery>
LoginWidget::LoginWidget(QWidget *parent)
    : QWidget(parent),
    ui(new Ui::LoginWidget)
{
    ui->setupUi(this);
    setWindowTitle("log in");
    this->clear();
    registerWidget = new RegisterWidget();


//    MainWindow *mainWindow = new MainWindow();
//    //    connect(ui->pushButton, &QPushButton::clicked, this, [=](){
//    //        this->hide();
//    //        // 显示主窗口
//    //        mainWindow->show();
//    //    });
    connect(ui->loginButton, &QPushButton::clicked, this, &LoginWidget::onLoginButtonClicked);
//    connect(ui->pushButton, &QPushButton::clicked, this, [=](){
//        this->close();
//        this->registerWidget=new RegisterWidget();
//        registerWidget->show();
//    });
    connect(ui->logupButton, &QPushButton::clicked, this, &LoginWidget::onRegisterButtonClicked);
    connect(registerWidget,&RegisterWidget::goback,this,[=](){
        registerWidget->close();
        this->show();
    });


}

LoginWidget::~LoginWidget()
{
    delete ui;
}

void LoginWidget::clear()
{
    ui->usernameEdit->clear();
    ui->passwordEdit->clear();
}

void LoginWidget::onLoginButtonClicked()
{
    if(ui->usernameEdit->text() != nullptr && ui->passwordEdit->text() != nullptr){
        QString username = ui->usernameEdit->text();
        QString password = ui->passwordEdit->text();

        QString sql = QString("select * from user where username = '%1' and password = '%2'")
                    .arg(username)
                    .arg(password);
        QSqlQuery query;
        query.exec(sql);
        if(query.next()){
            QMessageBox::information(this,"提示","登录成功");
            ui->usernameEdit->clear();
            ui->passwordEdit->clear();
            emit successLogin();
            this->close();
        }
        else {
            QMessageBox::critical(this,"提示","用户名或者密码错误，请重新输入");
            ui->usernameEdit->clear();
            ui->passwordEdit->clear();
        }
    }
    else {
        QMessageBox::critical(this,"提示","用户名或者密码为空，请重新输入");
    }
}
//void LoginWidget::onLoginButtonClicked(){

//    QString path = "./user.ini";
//    QSettings *config = new QSettings(path, QSettings::IniFormat);

//    //读取用户配置信息
//    QString uidsec = config -> value(QString("config/") + "uid").toString();
//    QByteArray uidb64 = QByteArray::fromBase64(uidsec.toLocal8Bit());
//    QString uid = QString::fromLocal8Bit(uidb64);

//    QString pwdsec = config -> value(QString("config/") + "pwd").toString();
//    QByteArray pwdb64 = QByteArray::fromBase64(pwdsec.toLocal8Bit());
//    QString pwd = QString::fromLocal8Bit(pwdb64);

//    if(uid == ui->lineEdit -> text() && pwd == ui->lineEdit_2 -> text())
//    {
//     accept();

//        //验证成功，跳转到homepage页面
//        this -> hide();  //这里可选 close（）;
//        MainWindow * m = new MainWindow();
//        m-> show();
//    }
//    else
//    {
//        QMessageBox::warning(this,tr("警告！"),tr("用户名或密码错误！"),QMessageBox::Yes);

//        //清空输入框内容
//        ui->lineEdit -> clear();
//        ui->lineEdit_2 -> clear();

//        //光标定位
//        ui->lineEdit -> setFocus();
//    }

//}

void LoginWidget::onRegisterButtonClicked(){
    this->hide();
    // 显示主窗口
    registerWidget->show();
}
