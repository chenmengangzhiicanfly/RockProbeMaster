#ifndef EXCELREADERANDDISPLAYER_H
#define EXCELREADERANDDISPLAYER_H

#include <QMainWindow>
#include <QPushButton>
#include <QTableView>
#include <QLineEdit>
#include <QSpinBox>
#include <QAxObject>
namespace Ui {
class ExcelReaderAndDisplayer;
}

class ExcelReaderAndDisplayer : public QWidget
{
    Q_OBJECT

public:
    explicit ExcelReaderAndDisplayer(QWidget *parent = nullptr);
    ~ExcelReaderAndDisplayer();

private:
    Ui::ExcelReaderAndDisplayer *ui;
private slots:
    void loadExcelData();
//   void showCellData();

private:
    QPushButton *button1;
    QPushButton *button2;
    QTableView *tableView1;
    QTableView *tableView2;
    QLineEdit *lineText;
    QSpinBox *spinBox1;
    QSpinBox *spinBox2;
    QAxObject *excel;
};

#endif // EXCELREADERANDDISPLAYER_H
