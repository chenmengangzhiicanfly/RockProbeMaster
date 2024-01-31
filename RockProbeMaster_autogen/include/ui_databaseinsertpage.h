/********************************************************************************
** Form generated from reading UI file 'databaseinsertpage.ui'
**
** Created by: Qt User Interface Compiler version 6.4.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DATABASEINSERTPAGE_H
#define UI_DATABASEINSERTPAGE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_DatabaseInsertPage
{
public:
    QWidget *layoutWidget;
    QFormLayout *formLayout;
    QVBoxLayout *verticalLayout;
    QLineEdit *id_2;
    QLineEdit *pilenumber_2;
    QLineEdit *responsible_person_2;
    QLineEdit *date_2;
    QLineEdit *charge_count_2;
    QLineEdit *rod_count_2;
    QLineEdit *detonator_count_2;
    QLineEdit *well_depth_2;
    QLineEdit *charge_count_detected_2;
    QLineEdit *rod_count_detected_2;
    QLineEdit *manual_inspection_2;
    QLineEdit *status_2;
    QVBoxLayout *verticalLayout_2;
    QLabel *id;
    QLabel *pilenumber;
    QLabel *responsible_person;
    QLabel *date;
    QLabel *charge_count;
    QLabel *rod_count;
    QLabel *detonator_count;
    QLabel *well_depth;
    QLabel *charge_count_detected;
    QLabel *rod_count_detected;
    QLabel *manual_inspection;
    QLabel *status;
    QWidget *widget;
    QHBoxLayout *horizontalLayout;
    QPushButton *cancelButton;
    QSpacerItem *horizontalSpacer;
    QPushButton *verifyButton;

    void setupUi(QDialog *DatabaseInsertPage)
    {
        if (DatabaseInsertPage->objectName().isEmpty())
            DatabaseInsertPage->setObjectName("DatabaseInsertPage");
        DatabaseInsertPage->resize(452, 420);
        layoutWidget = new QWidget(DatabaseInsertPage);
        layoutWidget->setObjectName("layoutWidget");
        layoutWidget->setGeometry(QRect(90, 10, 291, 331));
        formLayout = new QFormLayout(layoutWidget);
        formLayout->setObjectName("formLayout");
        formLayout->setContentsMargins(0, 0, 0, 0);
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName("verticalLayout");
        id_2 = new QLineEdit(layoutWidget);
        id_2->setObjectName("id_2");

        verticalLayout->addWidget(id_2);

        pilenumber_2 = new QLineEdit(layoutWidget);
        pilenumber_2->setObjectName("pilenumber_2");

        verticalLayout->addWidget(pilenumber_2);

        responsible_person_2 = new QLineEdit(layoutWidget);
        responsible_person_2->setObjectName("responsible_person_2");

        verticalLayout->addWidget(responsible_person_2);

        date_2 = new QLineEdit(layoutWidget);
        date_2->setObjectName("date_2");

        verticalLayout->addWidget(date_2);

        charge_count_2 = new QLineEdit(layoutWidget);
        charge_count_2->setObjectName("charge_count_2");

        verticalLayout->addWidget(charge_count_2);

        rod_count_2 = new QLineEdit(layoutWidget);
        rod_count_2->setObjectName("rod_count_2");

        verticalLayout->addWidget(rod_count_2);

        detonator_count_2 = new QLineEdit(layoutWidget);
        detonator_count_2->setObjectName("detonator_count_2");

        verticalLayout->addWidget(detonator_count_2);

        well_depth_2 = new QLineEdit(layoutWidget);
        well_depth_2->setObjectName("well_depth_2");

        verticalLayout->addWidget(well_depth_2);

        charge_count_detected_2 = new QLineEdit(layoutWidget);
        charge_count_detected_2->setObjectName("charge_count_detected_2");

        verticalLayout->addWidget(charge_count_detected_2);

        rod_count_detected_2 = new QLineEdit(layoutWidget);
        rod_count_detected_2->setObjectName("rod_count_detected_2");

        verticalLayout->addWidget(rod_count_detected_2);

        manual_inspection_2 = new QLineEdit(layoutWidget);
        manual_inspection_2->setObjectName("manual_inspection_2");

        verticalLayout->addWidget(manual_inspection_2);

        status_2 = new QLineEdit(layoutWidget);
        status_2->setObjectName("status_2");

        verticalLayout->addWidget(status_2);


        formLayout->setLayout(0, QFormLayout::FieldRole, verticalLayout);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName("verticalLayout_2");
        id = new QLabel(layoutWidget);
        id->setObjectName("id");

        verticalLayout_2->addWidget(id);

        pilenumber = new QLabel(layoutWidget);
        pilenumber->setObjectName("pilenumber");

        verticalLayout_2->addWidget(pilenumber);

        responsible_person = new QLabel(layoutWidget);
        responsible_person->setObjectName("responsible_person");

        verticalLayout_2->addWidget(responsible_person);

        date = new QLabel(layoutWidget);
        date->setObjectName("date");

        verticalLayout_2->addWidget(date);

        charge_count = new QLabel(layoutWidget);
        charge_count->setObjectName("charge_count");

        verticalLayout_2->addWidget(charge_count);

        rod_count = new QLabel(layoutWidget);
        rod_count->setObjectName("rod_count");

        verticalLayout_2->addWidget(rod_count);

        detonator_count = new QLabel(layoutWidget);
        detonator_count->setObjectName("detonator_count");

        verticalLayout_2->addWidget(detonator_count);

        well_depth = new QLabel(layoutWidget);
        well_depth->setObjectName("well_depth");

        verticalLayout_2->addWidget(well_depth);

        charge_count_detected = new QLabel(layoutWidget);
        charge_count_detected->setObjectName("charge_count_detected");

        verticalLayout_2->addWidget(charge_count_detected);

        rod_count_detected = new QLabel(layoutWidget);
        rod_count_detected->setObjectName("rod_count_detected");

        verticalLayout_2->addWidget(rod_count_detected);

        manual_inspection = new QLabel(layoutWidget);
        manual_inspection->setObjectName("manual_inspection");

        verticalLayout_2->addWidget(manual_inspection);

        status = new QLabel(layoutWidget);
        status->setObjectName("status");

        verticalLayout_2->addWidget(status);


        formLayout->setLayout(0, QFormLayout::LabelRole, verticalLayout_2);

        widget = new QWidget(DatabaseInsertPage);
        widget->setObjectName("widget");
        widget->setGeometry(QRect(120, 370, 222, 25));
        horizontalLayout = new QHBoxLayout(widget);
        horizontalLayout->setObjectName("horizontalLayout");
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        cancelButton = new QPushButton(widget);
        cancelButton->setObjectName("cancelButton");

        horizontalLayout->addWidget(cancelButton);

        horizontalSpacer = new QSpacerItem(58, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        verifyButton = new QPushButton(widget);
        verifyButton->setObjectName("verifyButton");

        horizontalLayout->addWidget(verifyButton);


        retranslateUi(DatabaseInsertPage);

        QMetaObject::connectSlotsByName(DatabaseInsertPage);
    } // setupUi

    void retranslateUi(QDialog *DatabaseInsertPage)
    {
        DatabaseInsertPage->setWindowTitle(QCoreApplication::translate("DatabaseInsertPage", "Dialog", nullptr));
        id->setText(QCoreApplication::translate("DatabaseInsertPage", "id", nullptr));
        pilenumber->setText(QCoreApplication::translate("DatabaseInsertPage", "pilenumber", nullptr));
        responsible_person->setText(QCoreApplication::translate("DatabaseInsertPage", "responsible_person", nullptr));
        date->setText(QCoreApplication::translate("DatabaseInsertPage", "date", nullptr));
        charge_count->setText(QCoreApplication::translate("DatabaseInsertPage", "charge_count", nullptr));
        rod_count->setText(QCoreApplication::translate("DatabaseInsertPage", "rod_count", nullptr));
        detonator_count->setText(QCoreApplication::translate("DatabaseInsertPage", "detonator_count", nullptr));
        well_depth->setText(QCoreApplication::translate("DatabaseInsertPage", "well_depth", nullptr));
        charge_count_detected->setText(QCoreApplication::translate("DatabaseInsertPage", "charge_count_detected", nullptr));
        rod_count_detected->setText(QCoreApplication::translate("DatabaseInsertPage", "rod_count_detected", nullptr));
        manual_inspection->setText(QCoreApplication::translate("DatabaseInsertPage", "manual_inspection", nullptr));
        status->setText(QCoreApplication::translate("DatabaseInsertPage", "status", nullptr));
        cancelButton->setText(QCoreApplication::translate("DatabaseInsertPage", "\345\217\226\346\266\210", nullptr));
        verifyButton->setText(QCoreApplication::translate("DatabaseInsertPage", "\347\241\256\345\256\232", nullptr));
    } // retranslateUi

};

namespace Ui {
    class DatabaseInsertPage: public Ui_DatabaseInsertPage {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DATABASEINSERTPAGE_H
