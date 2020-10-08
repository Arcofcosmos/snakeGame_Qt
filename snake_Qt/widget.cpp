#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
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


    startButton->setGeometry(this->width()/2 - 38, this->height()-150, 90, 45);
    startButton->setFlat(true);  //设置按钮边框不凸起,即透明
    startButton->setIcon(QIcon(":/new/prefix1/img/Start.png"));  //给开始按钮添加图标
    startButton->setIconSize(QSize(100, 60));   //设置按钮图标大小

    exitButton->setGeometry(this->width()/2 - 38, this->height()-90, 90, 45);
    exitButton->setFlat(true);  //设置按钮边框不凸起，即透明
    exitButton->setIcon(QIcon(":/new/prefix1/img/Exit.png"));  //给退出按钮添加图标
    exitButton->setIconSize(QSize(100, 60));   //设置按钮图标大小

    connect(startButton, &QPushButton::clicked, this, &Widget::startSlot);
    connect(exitButton, &QPushButton::clicked, this, &Widget::exitSlot);

}

Widget::~Widget()
{
    delete ui;
}


void Widget::startSlot()  //开始按钮槽函数
{
    gameWidget = new GameWidget(this);  //创建游戏窗口
    gameWidget->show();

}

void Widget::exitSlot()  //退出按钮槽函数
{
    //消息盒子
    if(exitMessBox->Yes == exitMessBox->question(this, "Tips", "Do you want to exit game?", exitMessBox->Yes, exitMessBox->No))
    {
        delete (this);  //关闭主窗口
        exit(0);
    }
}
