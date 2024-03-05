#include "detectorsizesettings.h"
#include "ui_detectorsizesettings.h"
#include <QVBoxLayout>

DetectorSizeSettings::DetectorSizeSettings(QWidget *parent) :
    QDialog(parent),spinBox(new QSpinBox(this)),pushButton(new QPushButton("Qpply",this)),label(new QLabel("Detector Size:",this)),
    ui(new Ui::DetectorSizeSettings)
{
    ui->setupUi(this);
    setWindowTitle("系统设置");
    QVBoxLayout *verticalLayout = new QVBoxLayout(this);
    spinBox->setMinimum(1);
    spinBox->setMaximum(100);
    QHBoxLayout *horizontalLayout = new QHBoxLayout;
    horizontalLayout->addWidget(label);
    horizontalLayout->addWidget(spinBox);

    verticalLayout->addLayout(horizontalLayout);
    verticalLayout->addWidget(pushButton);
    setLayout(verticalLayout);

    connect(pushButton,&QPushButton::clicked,this,[this](){
        this->setSize(spinBox->value());
        emit detectSizeChanged(this->getSize());
        qDebug()<<this->getSize();
    });
}

DetectorSizeSettings::~DetectorSizeSettings()
{
    delete ui;
}

void DetectorSizeSettings::setSize(int size)
{
    detectorSize =size;
}

int DetectorSizeSettings::getSize() const
{
    return detectorSize;
}
