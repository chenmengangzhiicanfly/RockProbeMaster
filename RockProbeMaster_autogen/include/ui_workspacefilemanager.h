/********************************************************************************
** Form generated from reading UI file 'workspacefilemanager.ui'
**
** Created by: Qt User Interface Compiler version 6.4.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WORKSPACEFILEMANAGER_H
#define UI_WORKSPACEFILEMANAGER_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>

QT_BEGIN_NAMESPACE

class Ui_WorkspaceFileManager
{
public:

    void setupUi(QDialog *WorkspaceFileManager)
    {
        if (WorkspaceFileManager->objectName().isEmpty())
            WorkspaceFileManager->setObjectName("WorkspaceFileManager");
        WorkspaceFileManager->resize(422, 340);

        retranslateUi(WorkspaceFileManager);

        QMetaObject::connectSlotsByName(WorkspaceFileManager);
    } // setupUi

    void retranslateUi(QDialog *WorkspaceFileManager)
    {
        WorkspaceFileManager->setWindowTitle(QCoreApplication::translate("WorkspaceFileManager", "Dialog", nullptr));
    } // retranslateUi

};

namespace Ui {
    class WorkspaceFileManager: public Ui_WorkspaceFileManager {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WORKSPACEFILEMANAGER_H
