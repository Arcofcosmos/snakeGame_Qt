#include "gamewidget.h"

GameWidget::GameWidget(QWidget *parent) : QMainWindow(parent)
{
    srand(time(NULL));
    score = 0;  //得分
    level = 0;  //难度
    bodycount = 1;  //贪吃蛇身体长度初始值为1
    speed = 500;  //500为定时器间隔ms,间隔越低移动速度越快
    state = true;  //游戏状态
    direction_index = rand()%4 + 1;  //最初蛇的方向取随机值

    //食物坐标取随机值
    food_x = (rand()%20+1) * 30;
    food_y = (rand()%16+1) * 30;

    //最初蛇头坐标取随机值
    snake[0][0] = (rand()%20) * 30;
    snake[0][1] = (rand()%16) * 30;

    //按钮
    upbtn = new QPushButton(this);
    downbtn = new QPushButton(this);
    leftbtn = new QPushButton(this);
    rightbtn = new QPushButton(this);
    startbtn = new QPushButton(this);
    exitbtn = new QPushButton(this);

    //按钮容器
    buttonGroup = new QButtonGroup();

    //标签
    ScoreLabel = new QLabel(this);
    LevelLabel = new QLabel(this);

    //定时器
    timer = new QTimer(this);

    //消息盒子
    exitMessBox = new QMessageBox(this);


    //游戏窗口
    this->setWindowTitle("洲洲的贪吃蛇");
    this->setFixedSize(891, 508);
    this->setWindowIcon(QIcon(":/new/prefix1/img/WindowPicture.jpg"));
    this->setAutoFillBackground(true);  //设置父窗口背景可被覆盖填充,否则游戏窗口背景还是为主窗口背景
    QPalette palette;  //创建一个调色板
    palette.setBrush(QPalette::Background, QBrush(QPixmap(":/new/prefix1/img/GameBack.jpg")));  //添加背景
    this->setPalette(palette);

    /*按钮设置*/
    //上
    upbtn->setGeometry(this->width()-150, (this->height()/2)-100, 45, 90);
    upbtn->setFlat(true);  //设置按钮透明
    upbtn->setIconSize(QSize(45, 90));
    upbtn->setIcon(QIcon(":/new/prefix1/img/up.png"));

    //下
    downbtn->setGeometry(this->width()-150, (this->height()/2)+10, 45, 90);
    downbtn->setFlat(true);  //设置按钮透明
    downbtn->setIconSize(QSize(45, 90));
    downbtn->setIcon(QIcon(":/new/prefix1/img/down.png"));

    //左
    leftbtn->setGeometry(this->width()-240, (this->height()/2)-20, 90, 45);
    leftbtn->setFlat(true);  //设置按钮透明
    leftbtn->setIconSize(QSize(90, 45));
    leftbtn->setIcon(QIcon(":/new/prefix1/img/left.png"));

    //右
    rightbtn->setGeometry(this->width()-110, (this->height()/2)-20, 90, 45);
    rightbtn->setFlat(true);  //设置按钮透明
    rightbtn->setIconSize(QSize(90, 45));
    rightbtn->setIcon(QIcon(":/new/prefix1/img/right.png"));

    //开始
    startbtn->setGeometry(this->width()-240, this->height()-100, 90, 45);
    startbtn->setFlat(true);  //设置按钮透明
    startbtn->setIconSize(QSize(90, 95));
    startbtn->setIcon(QIcon(":/new/prefix1/img/Start.png"));

    //退出
    exitbtn->setGeometry(this->width()-110, this->height()-100, 90, 45);
    exitbtn->setFlat(true);  //设置按钮透明
    exitbtn->setIconSize(QSize(90, 45));
    exitbtn->setIcon(QIcon(":/new/prefix1/img/Exit.png"));

    //按钮容器添加方向按钮
    buttonGroup->addButton(upbtn, 1);
    buttonGroup->addButton(downbtn, 2);
    buttonGroup->addButton(leftbtn, 3);
    buttonGroup->addButton(rightbtn, 4);

    //标签
    ScoreLabel->setText("得分:  " + QString::number(score) + "分");
    LevelLabel->setText("难度:  " + QString::number(level) + "级");
    ScoreLabel->setGeometry(this->width() - 220, 30 , 120, 100);
    LevelLabel->setGeometry(this->width() - 220, 80, 120 ,100);

    //音乐和音效
    //失败音效
    overSound = new QMediaPlayer(this);
    overSound->setMedia(QUrl("qrc:/new/sound/sounds/gameover.mp3"));
    overSound->setVolume(80);

    //按钮音效
    buttonSound = new QSound("qrc:/new/sound/sounds/button.wav",this);

    //得分音效
    scoreSound = new QSound("qrc:/new/sound/sounds/di.wav", this);

    //背景音乐
    backSound = new QMediaPlayer(this);
    backSound->setMedia(QUrl("qrc:/new/sound/sounds/backmusic.mp3"));
    backSound->setVolume(80);


    //信号与槽
    //void (&GameWidget:: *singalButttongroup)(int) = &QButtonGroup::buttonClicked;
    connect(startbtn, &QPushButton::clicked, this, &GameWidget::startgame);  //开始按钮开启定时器
    connect(exitbtn, &QPushButton::clicked, this, &GameWidget::exitgame);  //退出按钮退出游戏
    connect(timer, &QTimer::timeout, this, &GameWidget::m_timeout);  //定时器控制游戏进行
    connect(timer, &QTimer::timeout, this, &GameWidget::checkGameState);  //检查游戏状态
    connect(buttonGroup,SIGNAL(buttonClicked(int)),this,SLOT(snake_direction(int)));

    this->repaint();  //更新画面

}
void GameWidget::paintEvent(QPaintEvent *)  //绘制贪吃蛇移动时的图像,每次窗口更新都会自动调用
{
    QPainter painter(this);  //创建一个画板
    if(snake[0][0] >= 0 && snake[0][0] <= 600 && snake[0][1] >= 0 && snake[0][1] <= 480 && state )
    {
        qDebug() << "(" << snake[0][0] << "," << snake[0][1] << ")" << endl;  //打印蛇头坐标
        qDebug() << "速度：" << speed;
        for(int i = bodycount; i > 0; i--)  //i表示蛇的第i块身体
        {

            if(i == bodycount)  //先绘制贪吃蛇的尾巴
                {
                    if(snake[i][0] == snake[i-1][0] && snake[i][1] > snake[i-1][1])
                       painter.drawImage(QRect(snake[i][0], snake[i][1], 30, 30), QImage(":/new/prefix1/img/tailup.png"));

                    else if(snake[i][0] == snake[i-1][0] && snake[i][1] < snake[i-1][1])
                       painter.drawImage(QRect(snake[i][0], snake[i][1], 30, 30), QImage(":/new/prefix1/img/taildown.png"));

                    else if(snake[i][0] > snake[i-1][0] && snake[i][1] == snake[i-1][1])
                       painter.drawImage(QRect(snake[i][0], snake[i][1], 30, 30), QImage(":/new/prefix1/img/tailleft.png"));

                    else if(snake[i][0] < snake[i-1][0] && snake[i][1] == snake[i-1][1])
                       painter.drawImage(QRect(snake[i][0], snake[i][1], 30, 30), QImage(":/new/prefix1/img/tailright.png"));
                }

            else   //绘制贪吃蛇身体其它部分
            {
                //蛇头在两端有两种情况

                //右上角
                if((snake[i][0] == snake[i+1][0] && snake[i][1] < snake[i+1][1] && snake[i][0] > snake[i-1][0] && snake[i][1] == snake[i-1][1]) ||
                    (snake[i][0] > snake[i+1][0] && snake[i][1] == snake[i+1][1] && snake[i][0] == snake[i-1][0] && snake[i][1] < snake[i-1][1]))
                    painter.drawImage(QRect(snake[i][0], snake[i][1], 30, 30), QImage(":/new/prefix1/img/leftdown.png"));

                //右下角
                else if((snake[i][0] > snake[i+1][0] && snake[i][1] == snake[i+1][1] && snake[i][0] == snake[i-1][0] && snake[i][1] > snake[i-1][1]) ||
                    (snake[i][0] == snake[i+1][0] && snake[i][1] > snake[i+1][1] && snake[i][0] > snake[i-1][0] && snake[i][1] == snake[i-1][1]))
                    painter.drawImage(QRect(snake[i][0], snake[i][1], 30, 30), QImage(":/new/prefix1/img/leftup.png"));

                //左上角
                else if((snake[i][0] == snake[i+1][0] && snake[i][1] < snake[i+1][1] && snake[i][0] < snake[i-1][0] && snake[i][1] == snake[i-1][1]) ||
                    (snake[i][0] < snake[i+1][0] && snake[i][1] == snake[i+1][1] && snake[i][0] == snake[i-1][0] && snake[i][1] < snake[i-1][1]))
                    painter.drawImage(QRect(snake[i][0], snake[i][1], 30, 30), QImage(":/new/prefix1/img/rightdown.png"));

                //左下角
                else if((snake[i][0] < snake[i+1][0] && snake[i][1] == snake[i+1][1] && snake[i][0] == snake[i-1][0] && snake[i][1] > snake[i-1][1]) ||
                    (snake[i][0] == snake[i+1][0] && snake[i][1] > snake[i+1][1] && snake[i][0] < snake[i-1][0] && snake[i][1] == snake[i-1][1]))
                    painter.drawImage(QRect(snake[i][0], snake[i][1], 30, 30), QImage(":/new/prefix1/img/rightup.png"));

                //横移
                else if((snake[i][0] < snake[i+1][0] && snake[i][1] == snake[i+1][1] && snake[i][0] > snake[i-1][0] && snake[i][1] == snake[i-1][1]) ||
                    (snake[i][0] > snake[i+1][0] && snake[i][1] == snake[i+1][1] && snake[i][0] < snake[i-1][0] && snake[i][1] == snake[i-1][1]))
                    painter.drawImage(QRect(snake[i][0], snake[i][1], 30, 30), QImage(":/new/prefix1/img/leftright.png"));

                //纵移
                else if((snake[i][0] == snake[i+1][0] && snake[i][1] < snake[i+1][1] && snake[i][0] == snake[i-1][0] && snake[i][1] > snake[i-1][1]) ||
                    (snake[i][0] == snake[i+1][0] && snake[i][1] > snake[i+1][1] && snake[i][0] == snake[i-1][0] && snake[i][1] < snake[i-1][1]))
                    painter.drawImage(QRect(snake[i][0], snake[i][1], 30, 30), QImage(":/new/prefix1/img/downup.png"));
            }
        }
    }

    painter.drawImage(QRect(food_x, food_y, 30, 30), QImage(":/new/prefix1/img/Apple.png"));  //游戏开始前在随机位置放置食物

    painter.setPen(Qt::green);  //设置画笔颜色
    for(int i = 0; i <= longnumber; i++)  //绘制游戏网格
    {
        for(int j = 0; j <= widthnumber; j++)
            painter.drawRect(QRect(i*30, j*30, 30 ,30));
    }

    switch (direction_index)  //绘制蛇移动前的图像
    {
        //上
        case 1:painter.drawImage(QRect(snake[0][0], snake[0][1], 30, 30), QImage(":/new/prefix1/img/headup.png"));
            if(bodycount==1) painter.drawImage(QRect(snake[0][0], snake[0][1] + 30, 30, 30), QImage(":/new/prefix1/img/tailup.png"));break;

        //下
        case 2:painter.drawImage(QRect(snake[0][0], snake[0][1], 30, 30), QImage(":/new/prefix1/img/headdown.png"));
            if(bodycount==1) painter.drawImage(QRect(snake[0][0], snake[0][1] - 30, 30, 30), QImage(":/new/prefix1/img/taildown.png"));break;

        //左
        case 3:painter.drawImage(QRect(snake[0][0], snake[0][1], 30, 30), QImage(":/new/prefix1/img/headleft.png"));
            if(bodycount==1) painter.drawImage(QRect(snake[0][0] + 30, snake[0][1], 30, 30), QImage(":/new/prefix1/img/tailleft.png"));break;

        //右
        case 4:painter.drawImage(QRect(snake[0][0], snake[0][1], 30, 30), QImage(":/new/prefix1/img/headright.png"));
            if(bodycount==1) painter.drawImage(QRect(snake[0][0] - 30, snake[0][1], 30, 30), QImage(":/new/prefix1/img/tailright.png"));break;

    }
}

void GameWidget::m_timeout()  //定时器开启后游戏开始
{
    if(snake[0][0] == food_x && snake[0][1] == food_y)  //蛇吃到了食物
        {
            scoreSound->play();
            //食物位置变化
            food_x = (rand()%20+1) * 30;
            food_y = (rand()%16+1) * 30;
            bodycount++;  //蛇身体数量加1
            score++;  //得分加1
            if(score%3==0)  //每得3分难度加一,贪吃蛇速度提升
            {
                level++;
                if(speed - 150 > 0)
                    speed  -= 150;
            }
            timer->start(speed);  //刷新一次定时器

            ScoreLabel->setText("得分:  " + QString::number(score, 10) + "分");
            LevelLabel->setText("难度:  " + QString::number(level) + "级");
        }

    memcpy(snake1, snake, sizeof(snake));  //将snake的坐标复制一遍

    for(int i=bodycount;i>0;i--)//将蛇身体的前一个坐标赋值给后一个坐标，实现蛇身体的连续出现
    {

        snake[i][0]=snake[i-1][0];
        snake[i][1]=snake[i-1][1];
    }
    QPainter painter(this);
    switch (direction_index)  //移动蛇头
    {
        case 1:snake[0][1] -= 30; painter.drawImage(QRect(snake[0][0], snake[0][1], 30, 30), QImage("::/new/prefix1/img/headup.png")); break;
        case 2:snake[0][1] += 30; painter.drawImage(QRect(snake[0][0], snake[0][1], 30, 30), QImage("::/new/prefix1/img/headup.png")); break;
        case 3:snake[0][0] -= 30; painter.drawImage(QRect(snake[0][0], snake[0][1], 30, 30), QImage("::/new/prefix1/img/headup.png")); break;
        case 4:snake[0][0] += 30; painter.drawImage(QRect(snake[0][0], snake[0][1], 30, 30), QImage("::/new/prefix1/img/headup.png")); break;
    }

    for(int i = bodycount; i > 3 ; i--)  //贪吃蛇撞到自己则结束，身体4节才会撞
    {
        if(snake[0][0] == snake[i][0] && snake[0][1] == snake[i][1])
        {
            state = false;
            overSound->play();
            memcpy(snake, snake1, sizeof(snake1));
        }
    }

    if(snake[0][0] < 0 || snake[0][0] > 600 || snake[0][1] < 0 || snake[0][1] > 480)  //贪吃蛇出网格范围
        {
        state = false;
        overSound->play();
        memcpy(snake, snake1, sizeof(snake1));  //避免蛇头在网格外
    }

    this->update();  //蛇移动要调用paintEvent函数
}

void GameWidget::keyPressEvent(QKeyEvent *event)  //按键时间管理，通过按键可控制方向
{
    switch (event->key())
    {
        //if语句防止蛇可以反向移动
        case Qt::Key_Up:if(direction_index != 2) direction_index = 1; break;
        case Qt::Key_W:if(direction_index != 2) direction_index = 1; break;
        case Qt::Key_Down:if(direction_index != 1) direction_index = 2; break;
        case Qt::Key_S:if(direction_index != 1) direction_index = 2; break;
        case Qt::Key_Left:if(direction_index != 4) direction_index = 3; break;
        case Qt::Key_A:if(direction_index != 4) direction_index = 3; break;
        case Qt::Key_Right:if(direction_index != 3) direction_index = 4; break;
        case Qt::Key_D:if(direction_index != 3) direction_index = 4; break;
    }

}


void GameWidget::snake_direction(int index)  //按钮容器连接，按钮索引值控制方向
{
    switch (index)
    {
        case 1:direction_index = 1; break;
        case 2:direction_index = 2; break;
        case 3:direction_index = 3; break;
        case 4:direction_index = 4; break;
    }
}


void GameWidget::startgame()  //开始按钮槽函数，开启定时器
{
    buttonSound->play();
    timer->start(speed);  //开启定时器，初始600ms一次间隔
    startbtn->setIcon(QIcon(":/new/prefix1/img/Pause.png"));  //开始图标变成暂停
    disconnect(startbtn, &QPushButton::clicked, this, &GameWidget::startgame);
    connect(startbtn, &QPushButton::clicked, this, &GameWidget::pausegame);

}

void GameWidget::pausegame()  //暂停游戏槽函数
{
    buttonSound->play();
    timer->stop();
    startbtn->setIcon(QIcon(":/new/prefix1/img/Start.png"));
    disconnect(startbtn, &QPushButton::clicked, this, &GameWidget::pausegame);
    connect(startbtn, &QPushButton::clicked, this, &GameWidget::startgame);
}

void GameWidget::exitgame()  //退出按钮控制游戏退出
{
//    buttonSound->play();
//    backSound->play();
//    sleep(100);
    delete (this);

    //this->close();
}

void GameWidget::checkGameState()  //利用定时器连接，游戏开始后时刻检查游戏状态,游戏失败返回主窗口
{
    if(!state)
    {
        if(exitMessBox->Yes == exitMessBox->question(this, "Tips", "GameOver!", exitMessBox->Yes))
        {
            delete (this);
            //this->close();
        }
    }
}

