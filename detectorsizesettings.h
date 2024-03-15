#ifndef DETECTORSIZESETTINGS_H
#define DETECTORSIZESETTINGS_H

#include <QDialog>
#include <QSpinBox>
#include <QPushButton>
#include <QLabel>
namespace Ui {
class DetectorSizeSettings;
}

class DetectorSizeSettings : public QDialog
{
    Q_OBJECT

public:
    explicit DetectorSizeSettings(QWidget *parent = nullptr);
    ~DetectorSizeSettings();

    void setSize(int size);
    int getSize() const;
signals:
    void detectSizeChanged(int newSize);
private:
    Ui::DetectorSizeSettings *ui;
    int detectorSize;
    QSpinBox *spinBox;
    QPushButton *pushButton;
    QLabel *label;



};

#endif // DETECTORSIZESETTINGS_H
