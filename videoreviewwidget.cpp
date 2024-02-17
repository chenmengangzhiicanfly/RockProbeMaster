#include "videoreviewwidget.h"
#include "ui_videoreviewwidget.h"

VideoReviewWidget::VideoReviewWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::VideoReviewWidget)
{
    ui->setupUi(this);
    setWindowTitle(tr("视频复查"));
    audiooutput = new QAudioOutput;

    player = new QMediaPlayer;
    player->setPlaybackRate(1.0);    //设置播放速度

    all_hlayout = new QHBoxLayout(this);
    vlayout = new QVBoxLayout(this);
    hlayout = new QHBoxLayout(this);

//    QVBoxLayout *vlayout1 = new QVBoxLayout(this);
//    all_hlayout->setDirection(QBoxLayout::LeftToRight);

    videoWidget = new QVideoWidget(this);
//    videoWidget->setAspectRatioMode(Qt::IgnoreAspectRatio);//缩放适应videoWidget的大小
//    videoinfoopt=new videoInfoOpt(this);


    player->setVideoOutput(videoWidget);
    player->setAudioOutput(audiooutput);
    audiooutput->setVolume(50);
    Init();
    buttonStyleInit();



    vlayout->addWidget(videoWidget,1);
    vlayout->addWidget(m_Progressslider,1);
    vlayout->addLayout(hlayout, 0);

//    vlayout->addWidget(videoinfoopt,1);
//    vlayout1->addWidget(videoinfoopt,1);

    all_hlayout->addLayout(vlayout,0);
//    all_hlayout->addStretch();
//    all_hlayout->addLayout(vlayout1,1);
    videoinfoopt=new videoInfoOpt(this);
    all_hlayout->addWidget(videoinfoopt,1);




    resize(1500,600);


    connect(player,&QMediaPlayer::durationChanged,this,&VideoReviewWidget::onDurationChanged);

    connect(player,&QMediaPlayer::positionChanged,this,&VideoReviewWidget::onPositionChanged);

    connect(m_Progressslider,&QSlider::sliderMoved,this,&VideoReviewWidget::videobySlider);


}

VideoReviewWidget::~VideoReviewWidget()
{
    delete ui;
}




void VideoReviewWidget::Init()
{
    m_voicebutton = new QPushButton();
    ButtonStyleSet(m_voicebutton,":/videoWidget/images/videoWidget/voice.png");
//    m_voicebutton->setStyleSheet("QPushButton { background-color: blue; }"
//                         "QPushButton:hover { background-color: red; }"
//                         "QPushButton:pressed { background-color: green; }");

    m_voiceslider = new QSlider(Qt::Horizontal);
    m_voiceslider->setValue(50);
    m_voiceslider->setRange(0, 100);
    m_voiceslider->setStyleSheet("QSlider::groove:horizontal { border: 1px solid #999999; height: 10px; background: #dddddd; margin: 0px; }"
                                 "QSlider::handle:horizontal { background: #aaaaaa; border: 1px solid #666666; width: 20px; margin: -5px 0; border-radius: 5px; }"
                                 );


    /*倍速控件*/
    m_speedlabel = new QLabel();
    m_speedlabel->setFixedSize(60,20);
    m_speedbutton = new QPushButton();


    m_speedslider = new QSlider(Qt::Horizontal);
    m_speedslider->setRange(0,8);
    m_speedslider->setTickInterval(1);
    m_speedslider->setValue(4);
    m_speedslider->setStyleSheet("QSlider::groove:horizontal { border: 1px solid #999999; height: 10px; background: #dddddd; margin: 0px; }"
                                 "QSlider::handle:horizontal { background: #aaaaaa; border: 1px solid #666666; width: 20px; margin: -5px 0; border-radius: 5px; }");

    m_speedlabel->setText(QString::number(4.0*2.0/8.0,'g',3)+QString("倍速"));

    /*控制视频播放按键*/
    m_palybutton = new QPushButton();
//    m_stopbutton = new QPushButton();

    m_backbutton = new QPushButton();

    m_aheadbutton = new QPushButton();

    m_fullscreen = new QPushButton();

    m_selectbutton = new QPushButton();


    /*视频进度条*/
    m_Progressslider = new QSlider(Qt::Horizontal);
    m_Progressslider->setRange(0, 100);//设置进度条范围
    m_Progressslider->setValue(0);//初始值为0
    m_Progressslider->setStyleSheet("QSlider::groove:horizontal { border: 1px solid #999999; height: 10px; background: #dddddd; margin: 0px; }"
                                    "QSlider::handle:horizontal { background: #aaaaaa; border: 1px solid #666666; width: 20px; margin: -5px 0; border-radius: 5px; }"
                                    "QSlider::sub-page:horizontal { background: #55aaff; border-radius: 5px; }"
                                    "QSlider::add-page:horizontal { background: #aaaaaa; border-radius: 5px; }");

    /*显示时间label*/
    m_timelabel = new QLabel();
    hlayout->addWidget(m_voicebutton);
    hlayout->addWidget(m_voiceslider);
    hlayout->addStretch();
    hlayout->addWidget(m_speedbutton);
    hlayout->addWidget(m_speedslider);
    hlayout->addWidget(m_speedlabel);
    hlayout->addStretch();
    hlayout->addWidget(m_palybutton);
//    hlayout->addWidget(m_stopbutton);
    hlayout->addWidget(m_backbutton);
    hlayout->addWidget(m_aheadbutton);
    hlayout->addWidget(m_fullscreen);
    hlayout->addWidget(m_selectbutton);
    hlayout->addWidget(m_timelabel);
    /*选择视频播放文件*/
    connect(m_selectbutton,&QPushButton::clicked,this,&VideoReviewWidget::getPlayResource);
    /*暂停*/
    connect(m_palybutton,&QPushButton::clicked,this,&VideoReviewWidget::togglePlayPause);
    /*声音*/
    connect(m_voiceslider, &QAbstractSlider::valueChanged, this, &VideoReviewWidget::voicechange);
    /*快进*/
    connect(m_aheadbutton,&QPushButton::clicked,this,&VideoReviewWidget::aheadClick);
    connect(m_backbutton,&QPushButton::clicked,this,&VideoReviewWidget::backClick);
    connect(m_speedslider,&QAbstractSlider::valueChanged,this,&VideoReviewWidget::speedChange);

}

void VideoReviewWidget::ButtonStyleSet(QPushButton *button, QString IconPath)
{
    button->setIcon(QIcon(IconPath));
    button->setFlat(true);
    button->setStyleSheet("QPushButton:hover { background-color: red; }"
                          "QPushButton:pressed { background-color: darkGrey; }");
}

void VideoReviewWidget::buttonStyleInit()
{
    ButtonStyleSet(m_voicebutton,":/videoWidget/images/voice.png");

    ButtonStyleSet(m_speedbutton,":/videoWidget/images/speed.png");

    ButtonStyleSet(m_palybutton, ":/videoWidget/images/play.png");

//    ButtonStyleSet(m_stopbutton, ":/videoWidget/images/stop.png");

    ButtonStyleSet(m_backbutton, ":/videoWidget/images/back.png");

    ButtonStyleSet(m_aheadbutton, ":/videoWidget/images/ahead.png");

    ButtonStyleSet(m_fullscreen, ":/videoWidget/images/Fullscreen.png");

    ButtonStyleSet(m_selectbutton, ":/videoWidget/images/select.png");
}
