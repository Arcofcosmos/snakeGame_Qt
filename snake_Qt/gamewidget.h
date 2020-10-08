#ifndef GAMEWIDGET_H
#define GAMEWIDGET_H

#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QKeyEvent>
#include <QPaintEvent>
#include <QPainter>
#include <QButtonGroup>
#include <QImage>
#include <QTimer>
#include <ctime>
#include <QMessageBox>
#include <QDebug>

#define longnumber 20  //游戏网格横向数量
#define widthnumber 16  //游戏网格纵向数量
#define Maxbodycount 200  //贪吃蛇最大身体长度


class GameWidget : public QWidget
{
    Q_OBJECT
public:
    explicit GameWidget(QWidget *parent = nullptr);

    //方向按钮和游戏控制按钮
    QPushButton  *upbtn;
    QPushButton  *downbtn;
    QPushButton  *leftbtn;
    QPushButton  *rightbtn;
    QPushButton  *startbtn;
    QPushButton  *exitbtn;

    //得分标签和难度标签
    QLabel  *ScoreLabel;
    QLabel  *LevelLabel;

    QTimer *timer;  //创建一个定时器

    QMessageBox *exitMessBox;

    QButtonGroup *buttonGroup;  //创建一个按钮容器，放置方向按钮

    int  bodycount;  //蛇身体数量
    int  direction_index;  //蛇头方向对应值
    int  snake[Maxbodycount][2];  //贪吃蛇的坐标，snake[][0]为x坐标，snake[][1]为y坐标
    int  snake1[Maxbodycount][2];  //记忆贪吃蛇的坐标位置
    bool  state;  //游戏状态
    int  food_x;  //食物x坐标
    int  food_y;  //食物y坐标
    int score;  //得分
    int level;  //难度等级
    int speed;  //贪吃蛇移动速度


    void keyPressEvent(QKeyEvent *);  //键盘按键控制函数
    void paintEvent(QPaintEvent *);  //重写虚函数paintEvent()，绘制蛇移动后的图像


signals:

public slots:
    void m_timeout();  //定时器开启，游戏开始
    void startgame();  //开始按钮点击启动
    void pausegame();  //再次点击开始按钮暂停游戏
    void exitgame();  //退出按钮点击退出游戏
    void checkGameState();  //定时器开启后持续检查游戏状态
    void snake_direction(int index);  //按钮容器连接，控制蛇移动方向
};

#endif // GAMEWIDGET_H
