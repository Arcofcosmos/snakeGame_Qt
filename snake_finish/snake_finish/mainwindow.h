#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QMessageBox>
#include <QMediaPlayer>
#include <QMediaPlaylist>
#include <QSound>

#include "gamewidget.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    QPushButton *startButton;  //开始按钮
    QPushButton *exitButton;  //退出按钮

    QMessageBox *exitMessBox;  //退出按钮的消息盒子

    QMediaPlayer *startSound;  //创建一个音乐播放器
    QMediaPlayer *buttonSound;  //创建按钮音效
    QMediaPlaylist *MusicList;  //创建音乐列表
    QSound *sound;

    GameWidget *gameWidget;  //创建一个游戏窗口




public slots:
    void startSlot();  //开始按钮槽函数
    void exitSlot();  //退出按钮槽函数

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
