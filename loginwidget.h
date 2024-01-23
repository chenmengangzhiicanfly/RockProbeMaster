#ifndef LOGINWIDGET_H
#define LOGINWIDGET_H

#include <QWidget>
#include "registerwidget.h"
namespace Ui {
class LoginWidget;
}

class LoginWidget : public QWidget
{
    Q_OBJECT

public:
    explicit LoginWidget(QWidget *parent = nullptr);
    ~LoginWidget();

private:
    Ui::LoginWidget *ui;
    RegisterWidget *registerWidget;
    void clear();
private slots:
    void onLoginButtonClicked ();
    void onRegisterButtonClicked();
signals:
    void successLogin();

};

#endif // LOGINWIDGET_H
