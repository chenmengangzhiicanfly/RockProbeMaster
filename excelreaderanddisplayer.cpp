#include "excelreaderanddisplayer.h"
#include "ui_excelreaderanddisplayer.h"
#include <QAxObject>
#include <QFileDialog>
#include <QStandardItemModel>
ExcelReaderAndDisplayer::ExcelReaderAndDisplayer(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ExcelReaderAndDisplayer)
{

    setWindowTitle("Excel Reader");     //设置程序的窗口标题为“Excel Reader”。
    setGeometry(QRect(QPoint(300, 300), QSize(1000, 600)));     //设置窗口的位置和大小。

    button1 = new QPushButton("打开文件", this);               //创建一个QPushButton对象，文本标签为“ ”，并将它添加到MainWindow类的窗口中。
    button1->setGeometry(QRect(QPoint(550, 20), QSize(100, 30)));//设置按钮的位置和大小。

    button2 = new QPushButton("退出", this);               //创建一个QPushButton对象，文本标签为“ ”，并将它添加到MainWindow类的窗口中。
    button2->setGeometry(QRect(QPoint(900, 20), QSize(100, 30)));//设置按钮的位置和大小。

    tableView1 = new QTableView(this);                  //创建一个QTableView对象，并将它添加到MainWindow类的窗口中。
    tableView1->setGeometry(QRect(QPoint(10, 100), QSize(900, 400)));  //设置表格视图的位置和大小。
    //        tableView2 = new QTableView(this);                  //创建一个QTableView对象，并将它添加到MainWindow类的窗口中。
    //        tableView2->setGeometry(QRect(QPoint(600, 100), QSize(100, 65)));  //设置表格视图的位置和大小。

    lineText = new QLineEdit(this);
    lineText->setGeometry(QRect(QPoint(10, 20), QSize(500, 30)));  //设置表格视图的位置和大小。

    //        spinBox1 = new QSpinBox(this);
    //        spinBox1->setMaximum(999);
    //        spinBox1->setMinimum(1);
    //        spinBox1->setGeometry(QRect(QPoint(440, 100), QSize(50, 30)));  //设置表格视图的位置和大小。

    //        spinBox2 = new QSpinBox(this);
    //        spinBox2->setMaximum(999);
    //        spinBox2->setMinimum(1);
    //        spinBox2->setGeometry(QRect(QPoint(500, 100), QSize(50, 30)));  //设置表格视图的位置和大小。


    connect(button1, SIGNAL(clicked()), this, SLOT( loadExcelData() ) );
    connect(button2,&QPushButton::clicked,this,[=](){
        this->close();                                               });
    //
}


ExcelReaderAndDisplayer::~ExcelReaderAndDisplayer()
{
    delete ui;
}
void ExcelReaderAndDisplayer::loadExcelData()
{
    QString filePath = QFileDialog::getOpenFileName(this, tr("Open Excel file"), "", tr("Excel Files (*.xlsx *.xls)"));
    if (!filePath.isEmpty())
    {
        lineText->setText(filePath);
        //创建Excel 应用程序对象
        excel = new QAxObject("Excel.Application", this);                       //创建了一个QAxObject对象，用于访问Excel应用程序的COM接口。
        excel->setProperty("Visible", true);                                    //设置Excel应用程序的可见性为false，即不显示Excel应用程序的窗口。

        // 打开Excel工作簿
        QAxObject *workbooks = excel->querySubObject("Workbooks");              //创建了一个QAxObject对象，用于访问Excel应用程序的Workbooks对象。
        QAxObject *workbook = workbooks->querySubObject("Open(const QString&)", filePath); //使用Workbooks对象的querySubObject函数打开指定的Excel文件，并返回一个QAxObject对象，用于访问打开的Excel文件。
        //打开第一个工作表
        QAxObject *worksheet = workbook->querySubObject("Worksheets(int)", 1);   //使用打开的Excel文件的querySubObject函数访问其中的第一个工作表，并返回一个QAxObject对象，用于访问这个工作表。

        QAxObject *usedRange = worksheet->querySubObject("UsedRange");
        QAxObject *rows = usedRange->querySubObject("Rows");
        QAxObject *columns = usedRange->querySubObject("Columns");
        int row_count = rows->property("Count").toInt();       // 获取Excel文件中的行数
        int column_count = columns->property("Count").toInt(); // 获取Excel文件中的列数

        //读取元素
        QStringList data_list;
        for (int i = 1; i <= row_count; i++) {
            QString row_data;
            for (int j = 1; j <= column_count; j++) {
                QAxObject *cell = worksheet->querySubObject("Cells(int, int)", i, j);
                QString cell_value = cell->dynamicCall("Value()").toString();
                row_data += cell_value + "\t";
                cell->clear();
                delete cell;
            }
            data_list << row_data;
        }

        QStandardItemModel *model = new QStandardItemModel();
        for (int i = 0; i < data_list.count(); i++) {
            QStringList row_data = data_list.at(i).split("\t", Qt::SkipEmptyParts);
            for (int j = 0; j < row_data.count(); j++) {
                QStandardItem *item = new QStandardItem(row_data.at(j));
                model->setItem(i, j, item);
            }
        }

        tableView1->setModel(model);

        workbook->dynamicCall("Close()");
        excel->dynamicCall("Quit()");
    }

}
