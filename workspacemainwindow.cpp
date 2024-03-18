#include "workspacemainwindow.h"
#include "ui_workspacemainwindow.h"

workspacemainwindow::workspacemainwindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::workspacemainwindow)
{
    ui->setupUi(this);
}

workspacemainwindow::~workspacemainwindow()
{
    delete ui;
}
