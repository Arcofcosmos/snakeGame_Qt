#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("洲洲的贪吃蛇");
    this->setFixedSize(891, 508);
    this->setWindowIcon(QIcon(":/new/prefix1/img/WindowPicture.jpg"));
    QPalette palette;  //创建画板
    palette.setBrush(QPalette::Background, QBrush(QPixmap(":/new/prefix1/img/Back2.jpg")));  //给窗口背景添加图片
    this->setPalette(palette);  //给主窗口设置画板



    startButton = new QPushButton(this);
    exitButton = new QPushButton(this);
    exitMessBox = new QMessageBox(this);
    startSound = new QMediaPlayer(this);  //音乐播放器
    buttonSound = new QMediaPlayer(this);  //按钮音效
    MusicList = new QMediaPlaylist(this);  //音乐列表



    startButton->setGeometry(this->width()/2 - 38, this->height()-150, 90, 45);
    startButton->setFlat(true);  //设置按钮边框不凸起,即透明
    startButton->setIcon(QIcon(":/new/prefix1/img/Start.png"));  //给开始按钮添加图标
    startButton->setIconSize(QSize(100, 60));   //设置按钮图标大小

    exitButton->setGeometry(this->width()/2 - 38, this->height()-90, 90, 45);
    exitButton->setFlat(true);  //设置按钮边框不凸起，即透明
    exitButton->setIcon(QIcon(":/new/prefix1/img/Exit.png"));  //给退出按钮添加图标
    exitButton->setIconSize(QSize(100, 60));   //设置按钮图标大小

//    MusicList->addMedia(QUrl("qrc:/new/sound/sounds/di.wav"));  //会轮流切换播放
//    MusicList->addMedia(QUrl("qrc:/new/sound/sounds/gameover.mp3"));
//    MusicList->addMedia(QUrl("qrc:/new/sound/sounds/music.wav"));
    MusicList->addMedia(QUrl("qrc:/new/sound/sounds/backmusic.mp3"));
    //MusicList->setCurrentIndex(3);
    MusicList->setPlaybackMode(QMediaPlaylist::CurrentItemInLoop);  //循环播放
//    startSound->setPlaylist(MusicList);
//    startSound->play();

    //背景音乐
//    connect(startSound,SIGNAL(positionChanged(qint64)),this,SLOT(postitionChanged(qint64)));
//    startSound->setMedia(QUrl("qrc:/new/sound/sounds/backmusic.mp3"));
//    startSound->setVolume(80);
//    startSound->play();
     startSound->setPlaylist(MusicList);
     startSound->play();

    sound = new QSound("qrc:/new/sound/sounds/button.wav", this);
//    sound->play();
//    sound->setLoops(-1);
    //按钮音效
    buttonSound->setMedia(QUrl("qrc:/new/sound/sounds/button.wav"));
    buttonSound->setVolume(100);


    connect(startButton, &QPushButton::clicked, this, &MainWindow::startSlot);
    connect(exitButton, &QPushButton::clicked, this, &MainWindow::exitSlot);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::startSlot()  //开始按钮槽函数
{
    startSound->stop();
    gameWidget = new GameWidget(this);  //创建游戏窗口
    gameWidget->show();
    //this->hide();
    sound->play();
    //sound->setLoops(-1);


}

void MainWindow::exitSlot()  //退出按钮槽函数
{
    startSound->stop();
    sound->play();
    //sound->setLoops(-1);
    //消息盒子
    if(exitMessBox->Yes == exitMessBox->question(this, "Tips", "Do you want to exit game?", exitMessBox->Yes, exitMessBox->No))
    {
        delete (this);  //关闭主窗口
        exit(0);
    }

    else {
        startSound->play();
    }
}
