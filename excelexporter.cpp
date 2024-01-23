#include "excelexporter.h"
#include <QString>
#include <QFileDialog>
ExcelExporter::ExcelExporter()
{

}

void ExcelExporter::qTableWidget2Excel(QTableWidget *table)
{
    QString defaultFilePath = QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation);
    QString fileName = QFileDialog::getSaveFileName(table,
                                       "保存",
                                        defaultFilePath,
                                       "Excel FIle(*.xlsx)");
    if(fileName!=""){
        QXlsx::Document xlsx;
        QXlsx::Format format;
        format.setHorizontalAlignment(QXlsx::Format::AlignHCenter);
        format.setVerticalAlignment(QXlsx::Format::AlignVCenter);
        int row = table->rowCount();
        int column = table->columnCount();

        for(int j=0;j<column;j++){
            xlsx.write(1,j+1,table->horizontalHeaderItem(j)->text(),format);
        }

        for(int i=0;i<row;i++){
            for(int j=0;j<column;j++){
                if(QTableWidgetItem *item = table->item(i,j)){
                    xlsx.write(i+2,j+1,item->text(),format);
                }
            }
        }
        xlsx.saveAs(fileName);
    }
}
