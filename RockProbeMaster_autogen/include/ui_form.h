/********************************************************************************
** Form generated from reading UI file 'form.ui'
**
** Created by: Qt User Interface Compiler version 6.4.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FORM_H
#define UI_FORM_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Form
{
public:
    QAction *action1;
    QAction *action2;

    void setupUi(QWidget *Form)
    {
        if (Form->objectName().isEmpty())
            Form->setObjectName("Form");
        Form->resize(1270, 776);
        action1 = new QAction(Form);
        action1->setObjectName("action1");
        action2 = new QAction(Form);
        action2->setObjectName("action2");

        retranslateUi(Form);

        QMetaObject::connectSlotsByName(Form);
    } // setupUi

    void retranslateUi(QWidget *Form)
    {
        Form->setWindowTitle(QCoreApplication::translate("Form", "Form", nullptr));
        action1->setText(QCoreApplication::translate("Form", "1", nullptr));
#if QT_CONFIG(tooltip)
        action1->setToolTip(QCoreApplication::translate("Form", "1", nullptr));
#endif // QT_CONFIG(tooltip)
        action2->setText(QCoreApplication::translate("Form", "2", nullptr));
#if QT_CONFIG(tooltip)
        action2->setToolTip(QCoreApplication::translate("Form", "2", nullptr));
#endif // QT_CONFIG(tooltip)
    } // retranslateUi

};

namespace Ui {
    class Form: public Ui_Form {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FORM_H
