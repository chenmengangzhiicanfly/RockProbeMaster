#ifndef WORKSPACEMAINWINDOW_H
#define WORKSPACEMAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class workspacemainwindow;
}

class workspacemainwindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit workspacemainwindow(QWidget *parent = nullptr);
    ~workspacemainwindow();

private:
    Ui::workspacemainwindow *ui;
};

#endif // WORKSPACEMAINWINDOW_H
