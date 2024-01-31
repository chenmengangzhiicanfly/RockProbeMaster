/********************************************************************************
** Form generated from reading UI file 'workspaceopener.ui'
**
** Created by: Qt User Interface Compiler version 6.4.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WORKSPACEOPENER_H
#define UI_WORKSPACEOPENER_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>

QT_BEGIN_NAMESPACE

class Ui_WorkspaceOpener
{
public:

    void setupUi(QDialog *WorkspaceOpener)
    {
        if (WorkspaceOpener->objectName().isEmpty())
            WorkspaceOpener->setObjectName("WorkspaceOpener");
        WorkspaceOpener->resize(400, 300);

        retranslateUi(WorkspaceOpener);

        QMetaObject::connectSlotsByName(WorkspaceOpener);
    } // setupUi

    void retranslateUi(QDialog *WorkspaceOpener)
    {
        WorkspaceOpener->setWindowTitle(QCoreApplication::translate("WorkspaceOpener", "Dialog", nullptr));
    } // retranslateUi

};

namespace Ui {
    class WorkspaceOpener: public Ui_WorkspaceOpener {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WORKSPACEOPENER_H
