#include"videoreviewwidget.h"
#include<QFileDialog>>
#include <QDebug>
void VideoReviewWidget::getPlayResource()
{
    QString str = QFileDialog::getOpenFileName(this,tr("选择播放源"),"F:/video/",tr("MP4 Files(*.mp4 *.avi);;MP4 Files(*.mp4)"));
    player->setSource(QUrl::fromLocalFile(str));
    player->play();
}
//bug stop
void VideoReviewWidget::togglePlayPause()
{
    auto status = player->playbackState();
//    auto status=player;
    if(status == QMediaPlayer::PlayingState){
        player->pause();
        m_palybutton->setIcon(QIcon(":/videoWidget/images/stop.png"));
//        player->playbackRateChanged(QMediaPlayer::StoppedState);
    }
    else{
        player->play();
        m_palybutton->setIcon(QIcon(":/videoWidget/images/play.png"));
//        player->playbackRateChanged(QMediaPlayer::PlayingState);
    }
}
void VideoReviewWidget::onDurationChanged(qint64 duration)
{
    QTime totalTime = QTime(0, 0, 0, 0);
    totalTime = totalTime.addMSecs(duration);
    totalFormattedTime = totalTime.toString("mm:ss");

    // 更新显示
    m_timelabel->setText(currentFormattedTime + " / " + totalFormattedTime);

    // 设置进度条范围
    m_Progressslider->setRange(0, static_cast<int>(duration));
}
void VideoReviewWidget::onPositionChanged(qint64 position)
{
    QTime currentTime = QTime(0, 0, 0, 0);
    currentTime = currentTime.addMSecs(position);
    currentFormattedTime = currentTime.toString("mm:ss");

    // 更新显示
    m_timelabel->setText(currentFormattedTime + " / " + totalFormattedTime);

    // 更新进度条
    m_Progressslider->setValue(static_cast<int>(position));
}
void VideoReviewWidget::videobySlider(int position)
{
    player->setPosition(position);
}

void VideoReviewWidget::voicechange(int voice)
{
//    qDebug()<<voice<<"\n";
    float volume=voice/100.0;
    audiooutput->setVolume(volume);

}
/*快进10秒*/
void VideoReviewWidget::aheadClick(){
    qint64 currentpos = player->position();
    player->setPosition(currentpos + 10000);//在原来的基础上前进10s
}
void VideoReviewWidget::backClick(){
    qint64 currentpos = player->position();
    player->setPosition(currentpos - 10000);//在原来的基础上前进10s
}
void VideoReviewWidget::speedChange(int value){
    m_speedlabel->setText(QString::number(value * 2.0 / 8.0, 'g', 3) + QString("倍速"));
    player->setPlaybackRate(value * 2.0 / 8.0);//设置倍速播放
}

