#include "videoinfoopt.h"
#include "ui_videoinfoopt.h"
#include <QDate>
videoInfoOpt::videoInfoOpt(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::videoInfoOpt)
{
    ui->setupUi(this);

    m_pVarManager = new QtVariantPropertyManager(ui->propertyTree);
    m_pVarFactory = new QtVariantEditorFactory(ui->propertyTree);

////       connect(m_pVarManager, &QtVariantPropertyManager::valueChanged, this, &MainWindow::variantPropertyValueChanged);
    QtProperty *groupItem = m_pVarManager->addProperty(QtVariantPropertyManager::groupTypeId(),QStringLiteral("Group1"));

    QtVariantProperty *item = m_pVarManager->addProperty(QVariant::Double, QStringLiteral("设计井深（m）"));
    item->setValue(10.0);
    groupItem->addSubProperty(item);

    item = m_pVarManager->addProperty(QVariant::Int,QStringLiteral("杆子数"));
    item->setValue(0);
    groupItem->addSubProperty(item);

    item = m_pVarManager->addProperty(QVariant::Double,QStringLiteral("捅井井深"));
    item->setValue(1.0);
    groupItem->addSubProperty(item);

    item = m_pVarManager->addProperty(QVariant::Double,QStringLiteral("实际药量"));
//    item->setValue(QStringLiteral("hello world"));
    item->setValue(1.0);
    groupItem->addSubProperty(item);

    item = m_pVarManager->addProperty(QVariant::Int, QStringLiteral("视频雷管"));
    item->setValue(1);
    groupItem->addSubProperty(item);

    QtProperty *groupItem1 = m_pVarManager->addProperty(QtVariantPropertyManager::groupTypeId(),QStringLiteral("Group2"));

    QtVariantProperty *item1 = m_pVarManager->addProperty(QVariant::String,QStringLiteral("下药班长"));
    item1->setValue(QStringLiteral("x"));
    groupItem1->addSubProperty(item1);


    item1 = m_pVarManager->addProperty(QVariant::Date,QStringLiteral("下药日期"));
    item1->setValue(QDate::currentDate());
    groupItem1->addSubProperty(item1);

    item1 = m_pVarManager->addProperty(QVariant::Bool,QStringLiteral("是否复核"));
    item1->setValue(true);
    groupItem1->addSubProperty(item1);

//       item1 = m_pVarManager->addProperty(QVariant::String,QStringLiteral("String: "));
//       item1->setValue(QStringLiteral("hello world"));
//       groupItem1->addSubProperty(item1);

//       item1 = m_pVarManager->addProperty(QVariant::Color, QStringLiteral("Color: "));
//       item1->setValue(QColor(255, 0, 0));
//       groupItem1->addSubProperty(item1);

//       item1 = m_pVarManager->addProperty(QtVariantPropertyManager::enumTypeId(), QLatin1String("Enum Property"));
//       QStringList enumNames;
//       enumNames << "Enum0" << "Enum1" << "Enum2";
//       item1->setAttribute(QLatin1String("enumNames"), enumNames);
//       item1->setValue(1);
//       groupItem1->addSubProperty(item1);

       ui->propertyTree->addProperty(groupItem);
       ui->propertyTree->addProperty(groupItem1);
       ui->propertyTree->setFactoryForManager(m_pVarManager, m_pVarFactory);

}

videoInfoOpt::~videoInfoOpt()
{
//    delete m_pVarManager;
//        delete m_pVarFactory;
    delete ui;
}
