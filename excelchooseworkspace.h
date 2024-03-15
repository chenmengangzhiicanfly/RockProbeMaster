#ifndef EXCELCHOOSEWORKSPACE_H
#define EXCELCHOOSEWORKSPACE_H

#include <QWidget>

namespace Ui {
class excelChooseWorkspace;
}

class excelChooseWorkspace : public QWidget
{
    Q_OBJECT

public:
    explicit excelChooseWorkspace(QWidget *parent = nullptr);
    ~excelChooseWorkspace();
    void addRow(QString rowtext);
    void workspaceInit();
signals:
    void workspacelist(QStringList workspace);

private slots:
    void on_pushButton_clicked();

private:
    Ui::excelChooseWorkspace *ui;
};

#endif // EXCELCHOOSEWORKSPACE_H
