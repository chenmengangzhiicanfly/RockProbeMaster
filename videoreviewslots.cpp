#include"videoreviewwidget.h"
#include<QFileDialog>>

void VideoReviewWidget::getPlayResource()
{
    QString str = QFileDialog::getOpenFileName(this,tr("选择播放源"),"F:/video/",tr("MP4 Files(*.mp4 *.avi);;MP4 Files(*.mp4)"));
    player->setSource(QUrl::fromLocalFile(str));
    player->play();
}

void VideoReviewWidget::togglePlayPause()
{
    auto status = player->playbackRate();
    if(status == QMediaPlayer::PlayingState){
        player->pause();
        m_palybutton->setIcon(QIcon(":/videoWidget/images/stop.png"));
    }
    else {
        player->play();
        m_palybutton->setIcon(QIcon(":/videoWidget/images/play.png"));
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


