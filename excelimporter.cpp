#include "excelimporter.h"
#include <QMessageBox>
ExcelImporter::ExcelImporter()
{

}
void ExcelImporter::Excel2qTableWidget(QTableWidget *&table)
{
    table->clearContents();
    QString defaultFilePath = QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation);
    QString filepath = QFileDialog::getOpenFileName(table,
                                                    "选择Excel文件",
                                                    defaultFilePath,
                                                    "Excel文件(*.xlsx)");
    QXlsx::Document xlsxR(filepath);
    if(xlsxR.load()){
        int row = xlsxR.dimension().rowCount();
        int column = xlsxR.dimension().columnCount();

        for(int i=2;i<=row;i++){
            for(int j=1;j<=column;j++){
                QVariant cellData = xlsxR.read(i, j);
                // 将数据设置到 QTableWidget 的对应单元格
                QTableWidgetItem *item = new QTableWidgetItem(cellData.toString());
//                QTableWidgetItem *item = new QTableWidgetItem(cellData);
                table->setRowCount(i-1);
                table->setItem(i-2,j-1,item);
                table->item(i-2,j-1)->setTextAlignment(Qt::AlignVCenter|Qt::AlignHCenter);
            }
        }
    }
    else {
        QMessageBox::warning(table,"错误","Failed to load Excel FIle");
    }

}
