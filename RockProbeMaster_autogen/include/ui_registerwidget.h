/********************************************************************************
** Form generated from reading UI file 'registerwidget.ui'
**
** Created by: Qt User Interface Compiler version 6.4.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_REGISTERWIDGET_H
#define UI_REGISTERWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_RegisterWidget
{
public:
    QLineEdit *usernameEdit;
    QLineEdit *passwordEdit;
    QPushButton *registerButton;
    QPushButton *backButton;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;

    void setupUi(QWidget *RegisterWidget)
    {
        if (RegisterWidget->objectName().isEmpty())
            RegisterWidget->setObjectName("RegisterWidget");
        RegisterWidget->resize(340, 336);
        RegisterWidget->setStyleSheet(QString::fromUtf8("*{\n"
"font-size:24px;\n"
"font-family:Century Gothic;\n"
"}\n"
"QFrame{\n"
"background:rgba(0,0,0,0.8);\n"
"border-radius:15px;\n"
"}\n"
"Widget{\n"
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
        usernameEdit = new QLineEdit(RegisterWidget);
        usernameEdit->setObjectName("usernameEdit");
        usernameEdit->setGeometry(QRect(172, 100, 111, 21));
        passwordEdit = new QLineEdit(RegisterWidget);
        passwordEdit->setObjectName("passwordEdit");
        passwordEdit->setGeometry(QRect(170, 160, 113, 21));
        registerButton = new QPushButton(RegisterWidget);
        registerButton->setObjectName("registerButton");
        registerButton->setGeometry(QRect(40, 240, 101, 28));
        backButton = new QPushButton(RegisterWidget);
        backButton->setObjectName("backButton");
        backButton->setGeometry(QRect(200, 240, 60, 28));
        label = new QLabel(RegisterWidget);
        label->setObjectName("label");
        label->setGeometry(QRect(40, 100, 111, 21));
        label_2 = new QLabel(RegisterWidget);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(40, 160, 111, 21));
        label_3 = new QLabel(RegisterWidget);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(140, 30, 71, 41));
        label_3->setStyleSheet(QString::fromUtf8("QLabel{\n"
"color:rgb(85, 170, 255);\n"
"background:transparent;\n"
"font: 24pt \"\351\273\221\344\275\223\";\n"
"}"));

        retranslateUi(RegisterWidget);

        QMetaObject::connectSlotsByName(RegisterWidget);
    } // setupUi

    void retranslateUi(QWidget *RegisterWidget)
    {
        RegisterWidget->setWindowTitle(QCoreApplication::translate("RegisterWidget", "Form", nullptr));
        usernameEdit->setText(QCoreApplication::translate("RegisterWidget", "Username", nullptr));
        passwordEdit->setText(QCoreApplication::translate("RegisterWidget", "Password", nullptr));
        registerButton->setText(QCoreApplication::translate("RegisterWidget", "Register", nullptr));
        backButton->setText(QCoreApplication::translate("RegisterWidget", "back", nullptr));
        label->setText(QCoreApplication::translate("RegisterWidget", "usename", nullptr));
        label_2->setText(QCoreApplication::translate("RegisterWidget", "password", nullptr));
        label_3->setText(QCoreApplication::translate("RegisterWidget", "\346\263\250\345\206\214", nullptr));
    } // retranslateUi

};

namespace Ui {
    class RegisterWidget: public Ui_RegisterWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_REGISTERWIDGET_H
