#ifndef VIDEOREVIEWWIDGET_H
#define VIDEOREVIEWWIDGET_H

#include <QWidget>
#include <QMediaPlayer>
#include <QVideoWidget>
#include <QAudioOutput>
#include <QPushButton>
#include <QSlider>
#include <QHBoxLayout>
#include <QLabel>
#include <QTime>

//该模块为视频复查模块，功能为弹出新的窗口，打开输入的视频，进行视频的播放快进暂停并可修改视频对应信息
namespace Ui {
class VideoReviewWidget;
}

class VideoReviewWidget : public QWidget
{
    Q_OBJECT

    QMediaPlayer* player;
    QVideoWidget* videoWidget;
    QAudioOutput* audiooutput;

    QPushButton* m_voicebutton;
    QSlider* m_voiceslider;

    QPushButton* m_speedbutton;
    QLabel* m_speedlabel;
    QSlider* m_speedslider;

    QSlider* m_Progressslider;

    QPushButton* m_palybutton;
    QPushButton* m_stopbutton;
    QPushButton* m_backbutton;
    QPushButton* m_aheadbutton;
    QPushButton* m_selectbutton;
    QPushButton* m_fullscreen;

    QLabel* m_timelabel;

    QHBoxLayout* hlayout;

    QString m_resource;

    int m_voice;

    QString totalFormattedTime;
    QString currentFormattedTime;

    void Init();

    void ButtonStyleSet(QPushButton* button, QString IconPath);

    void buttonStyleInit();

public:
    explicit VideoReviewWidget(QWidget *parent = nullptr);
    ~VideoReviewWidget();

private:
    Ui::VideoReviewWidget *ui;
private slots:
    void onDurationChanged(qint64 duration);
    void onPositionChanged(qint64 duration);
    void videobySlider(int position);


    void getPlayResource();
    void togglePlayPause();
    void voicechange(int voice);
    void aheadClick();
    void backClick();
    void speedChange(int value);
};



#endif // VIDEOREVIEWWIDGET_H
