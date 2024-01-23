#ifndef EXCELIMPORTER_H
#define EXCELIMPORTER_H
#include "xlsxdocument.h"
#include <QTableWidget>
#include <QStandardPaths>
#include <QString>
#include <QFileDialog>
class ExcelImporter
{
public:
    ExcelImporter();
    void Excel2qTableWidget(QTableWidget *&table);
};

#endif // EXCELIMPORTER_H
