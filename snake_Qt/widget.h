#ifndef WIDGET_H
#define WIDGET_H

#include <QPushButton>
#include <QMessageBox>
#include <QWidget>


#include "gamewidget.h"

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = nullptr);
    ~Widget();

    QPushButton *startButton;  //开始按钮
    QPushButton *exitButton;  //退出按钮

    QMessageBox *exitMessBox;  //退出按钮的消息盒子

    GameWidget *gameWidget;  //创建一个游戏窗口


public slots:
    void startSlot();  //开始按钮槽函数
    void exitSlot();  //退出按钮槽函数


private:
    Ui::Widget *ui;
};

#endif // WIDGET_H
