/********************************************************************************
** Form generated from reading UI file 'videoreviewwidget.ui'
**
** Created by: Qt User Interface Compiler version 6.4.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_VIDEOREVIEWWIDGET_H
#define UI_VIDEOREVIEWWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_VideoReviewWidget
{
public:

    void setupUi(QWidget *VideoReviewWidget)
    {
        if (VideoReviewWidget->objectName().isEmpty())
            VideoReviewWidget->setObjectName("VideoReviewWidget");
        VideoReviewWidget->resize(400, 300);

        retranslateUi(VideoReviewWidget);

        QMetaObject::connectSlotsByName(VideoReviewWidget);
    } // setupUi

    void retranslateUi(QWidget *VideoReviewWidget)
    {
        VideoReviewWidget->setWindowTitle(QCoreApplication::translate("VideoReviewWidget", "Form", nullptr));
    } // retranslateUi

};

namespace Ui {
    class VideoReviewWidget: public Ui_VideoReviewWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_VIDEOREVIEWWIDGET_H
