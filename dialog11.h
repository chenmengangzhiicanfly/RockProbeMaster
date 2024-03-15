#ifndef DIALOG11_H
#define DIALOG11_H

#include <QDialog>

namespace Ui {
class Dialog11;
}

class Dialog11 : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog11(QWidget *parent = nullptr);
    ~Dialog11();

private:
    Ui::Dialog11 *ui;
};

#endif // DIALOG11_H
