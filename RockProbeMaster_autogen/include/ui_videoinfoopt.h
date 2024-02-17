/********************************************************************************
** Form generated from reading UI file 'videoinfoopt.ui'
**
** Created by: Qt User Interface Compiler version 6.4.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_VIDEOINFOOPT_H
#define UI_VIDEOINFOOPT_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include <qttreepropertybrowser.h>

QT_BEGIN_NAMESPACE

class Ui_videoInfoOpt
{
public:
    QVBoxLayout *verticalLayout;
    QtTreePropertyBrowser *propertyTree;
    QHBoxLayout *horizontalLayout;
    QPushButton *pushButton_2;
    QSpacerItem *horizontalSpacer;
    QPushButton *pushButton;

    void setupUi(QWidget *videoInfoOpt)
    {
        if (videoInfoOpt->objectName().isEmpty())
            videoInfoOpt->setObjectName("videoInfoOpt");
        videoInfoOpt->resize(382, 565);
        QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(videoInfoOpt->sizePolicy().hasHeightForWidth());
        videoInfoOpt->setSizePolicy(sizePolicy);
        videoInfoOpt->setMaximumSize(QSize(400, 16777215));
        verticalLayout = new QVBoxLayout(videoInfoOpt);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setSizeConstraint(QLayout::SetDefaultConstraint);
        propertyTree = new QtTreePropertyBrowser(videoInfoOpt);
        propertyTree->setObjectName("propertyTree");
        sizePolicy.setHeightForWidth(propertyTree->sizePolicy().hasHeightForWidth());
        propertyTree->setSizePolicy(sizePolicy);
        propertyTree->setMinimumSize(QSize(280, 280));
        propertyTree->setAutoFillBackground(false);

        verticalLayout->addWidget(propertyTree);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        horizontalLayout->setContentsMargins(-1, 0, -1, -1);
        pushButton_2 = new QPushButton(videoInfoOpt);
        pushButton_2->setObjectName("pushButton_2");

        horizontalLayout->addWidget(pushButton_2);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        pushButton = new QPushButton(videoInfoOpt);
        pushButton->setObjectName("pushButton");

        horizontalLayout->addWidget(pushButton);


        verticalLayout->addLayout(horizontalLayout);


        retranslateUi(videoInfoOpt);

        QMetaObject::connectSlotsByName(videoInfoOpt);
    } // setupUi

    void retranslateUi(QWidget *videoInfoOpt)
    {
        videoInfoOpt->setWindowTitle(QCoreApplication::translate("videoInfoOpt", "Form", nullptr));
        pushButton_2->setText(QCoreApplication::translate("videoInfoOpt", "\345\210\240\351\231\244", nullptr));
        pushButton->setText(QCoreApplication::translate("videoInfoOpt", "\347\241\256\350\256\244", nullptr));
    } // retranslateUi

};

namespace Ui {
    class videoInfoOpt: public Ui_videoInfoOpt {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_VIDEOINFOOPT_H
