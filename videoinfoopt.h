#ifndef VIDEOINFOOPT_H
#define VIDEOINFOOPT_H

#include <QWidget>

#include "qtpropertymanager.h"
#include "qtvariantproperty.h"
#include "qttreepropertybrowser.h"
namespace Ui {
class videoInfoOpt;
}

class videoInfoOpt : public QWidget
{
    Q_OBJECT

public:
    explicit videoInfoOpt(QWidget *parent = nullptr);
    ~videoInfoOpt();

    QtVariantPropertyManager* m_pVarManager;
    QtVariantEditorFactory *m_pVarFactory;
    QMap<QtProperty*, QString> m_property_dic;

//private slots:
//    void on_clear_pushButton_clicked();

//    void on_pushButton_2_clicked();

private:
    Ui::videoInfoOpt *ui;
};

#endif // VIDEOINFOOPT_H
