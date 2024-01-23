#ifndef EXCELEXPORTER_H
#define EXCELEXPORTER_H
#include "xlsxdocument.h"
#include <QTableWidget>
#include <QStandardPaths>
class ExcelExporter
{
public:
    ExcelExporter();

    void qTableWidget2Excel(QTableWidget *table);
private:

};

#endif // EXCELEXPORTER_H
