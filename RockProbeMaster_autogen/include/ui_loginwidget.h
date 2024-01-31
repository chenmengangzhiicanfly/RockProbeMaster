/********************************************************************************
** Form generated from reading UI file 'loginwidget.ui'
**
** Created by: Qt User Interface Compiler version 6.4.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LOGINWIDGET_H
#define UI_LOGINWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_LoginWidget
{
public:
    QPushButton *loginButton;
    QPushButton *logupButton;
    QCheckBox *checkBox;
    QLabel *label_2;
    QLabel *label_3;
    QLineEdit *usernameEdit;
    QLabel *label;
    QLineEdit *passwordEdit;

    void setupUi(QWidget *LoginWidget)
    {
        if (LoginWidget->objectName().isEmpty())
            LoginWidget->setObjectName("LoginWidget");
        LoginWidget->resize(445, 489);
        LoginWidget->setStyleSheet(QString::fromUtf8("*{\n"
"font-size:24px;\n"
"font-family:Century Gothic;\n"
"}\n"
"QFrame{\n"
"background:rgba(0,0,0,0.8);\n"
"border-radius:15px;\n"
"}\n"
"#Widget{\n"
"background:url(D:/pictures/sunrise.jpg);\n"
"}\n"
"\n"
"QToolButton{\n"
"background:red;\n"
"border-radius:60px;\n"
"}\n"
"QLabel{\n"
"color:rgb(0, 0, 127);\n"
"background:transparent;\n"
"}\n"
"QPushButton{\n"
"background:white;\n"
"border-radius:15px;\n"
"}\n"
"QPushButton:hover{\n"
"background:#333;\n"
"border-radius:15px;\n"
"background:#49ebff;\n"
"}\n"
"QLineEdit{\n"
"background:transparent;\n"
"border:none;\n"
"color:#717072;\n"
"border-bottom:1px solid #717072;\n"
"}"));
        loginButton = new QPushButton(LoginWidget);
        loginButton->setObjectName("loginButton");
        loginButton->setGeometry(QRect(50, 380, 141, 51));
        logupButton = new QPushButton(LoginWidget);
        logupButton->setObjectName("logupButton");
        logupButton->setGeometry(QRect(250, 380, 141, 51));
        checkBox = new QCheckBox(LoginWidget);
        checkBox->setObjectName("checkBox");
        checkBox->setGeometry(QRect(60, 240, 141, 41));
        label_2 = new QLabel(LoginWidget);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(90, 170, 111, 21));
        label_3 = new QLabel(LoginWidget);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(190, 40, 71, 41));
        label_3->setStyleSheet(QString::fromUtf8("QLabel{\n"
"color:rgb(85, 170, 255);\n"
"background:transparent;\n"
"font: 24pt \"\351\273\221\344\275\223\";\n"
"}"));
        usernameEdit = new QLineEdit(LoginWidget);
        usernameEdit->setObjectName("usernameEdit");
        usernameEdit->setGeometry(QRect(222, 110, 121, 21));
        label = new QLabel(LoginWidget);
        label->setObjectName("label");
        label->setGeometry(QRect(90, 110, 111, 21));
        passwordEdit = new QLineEdit(LoginWidget);
        passwordEdit->setObjectName("passwordEdit");
        passwordEdit->setGeometry(QRect(220, 170, 121, 21));

        retranslateUi(LoginWidget);

        QMetaObject::connectSlotsByName(LoginWidget);
    } // setupUi

    void retranslateUi(QWidget *LoginWidget)
    {
        LoginWidget->setWindowTitle(QCoreApplication::translate("LoginWidget", "Form", nullptr));
        loginButton->setText(QCoreApplication::translate("LoginWidget", "log in", nullptr));
        logupButton->setText(QCoreApplication::translate("LoginWidget", "log up", nullptr));
        checkBox->setText(QCoreApplication::translate("LoginWidget", "CheckBox", nullptr));
        label_2->setText(QCoreApplication::translate("LoginWidget", "password", nullptr));
        label_3->setText(QCoreApplication::translate("LoginWidget", "\347\231\273\345\275\225", nullptr));
        usernameEdit->setText(QCoreApplication::translate("LoginWidget", "Username", nullptr));
        label->setText(QCoreApplication::translate("LoginWidget", "usename", nullptr));
        passwordEdit->setText(QCoreApplication::translate("LoginWidget", "Password", nullptr));
    } // retranslateUi

};

namespace Ui {
    class LoginWidget: public Ui_LoginWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOGINWIDGET_H
