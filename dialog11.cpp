#include "dialog11.h"
#include "ui_dialog11.h"

Dialog11::Dialog11(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog11)
{
    ui->setupUi(this);
}

Dialog11::~Dialog11()
{
    delete ui;
}
