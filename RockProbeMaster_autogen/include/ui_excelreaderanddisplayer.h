/********************************************************************************
** Form generated from reading UI file 'excelreaderanddisplayer.ui'
**
** Created by: Qt User Interface Compiler version 6.4.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_EXCELREADERANDDISPLAYER_H
#define UI_EXCELREADERANDDISPLAYER_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ExcelReaderAndDisplayer
{
public:

    void setupUi(QWidget *ExcelReaderAndDisplayer)
    {
        if (ExcelReaderAndDisplayer->objectName().isEmpty())
            ExcelReaderAndDisplayer->setObjectName("ExcelReaderAndDisplayer");
        ExcelReaderAndDisplayer->resize(400, 300);

        retranslateUi(ExcelReaderAndDisplayer);

        QMetaObject::connectSlotsByName(ExcelReaderAndDisplayer);
    } // setupUi

    void retranslateUi(QWidget *ExcelReaderAndDisplayer)
    {
        ExcelReaderAndDisplayer->setWindowTitle(QCoreApplication::translate("ExcelReaderAndDisplayer", "Form", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ExcelReaderAndDisplayer: public Ui_ExcelReaderAndDisplayer {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_EXCELREADERANDDISPLAYER_H
