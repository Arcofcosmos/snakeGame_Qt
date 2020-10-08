# 基于Qt的贪吃蛇小游戏界面开发(c++)

开发环境：QtCreator5.12

## 游戏需求

### 初始界面

1. 开始按钮：点击变成游戏界面
2. 退出按钮：点击出现对话框
3. 对话框：有提示信息“Do you want to exit game?”，选择yes则退出游戏，选择no则对话框消失返回初始界面
4. 初始界面背景、按钮上均为游戏资源图片
5. 界面有自己的标题“洲洲的贪吃蛇”

### 游戏界面

1. 界面有自己的标题“洲洲的贪吃蛇”
2. 游戏界面分两部分，左边为游戏部分，右边为控制和显示分数部分
3. 右边部分有控制上下左右的按钮图标、开始按钮、返回按钮、得分标签、等级标签
4. 点击开始按钮游戏开始，同时开始按钮图标变成停止图标，再次点击游戏暂停
5. 点击返回按钮直接退回初始界面
6. 贪吃蛇每吃一个苹果得分增加，等级也慢慢增加
7. 左边游戏部分背景为网格
8. 蛇每吃一个苹果，苹果会随机换位置
9. 贪吃蛇无法反方向移动
10. 贪吃蛇如果撞到界面边缘或者撞到自己则游戏结束，显示“Game Over”,点击"Yes"确定返回游戏
11. 在键盘上操作也可控制蛇移动方向



## 开发流程

### 1.导入qrc文件

我们要将图片放入界面中，所以需要在项目中添加Resources文件，其包含了qrc文件，然后将图片导入qrc中，qmake和构建项目即可。

事先先把图片文件放入项目文件目录中。

![image-20201006133311177](C:\Users\TuZhou\AppData\Roaming\Typora\typora-user-images\image-20201006133311177.png)

在项目中添加新文件，选择Resource文件

![image-20201006133506254](C:\Users\TuZhou\AppData\Roaming\Typora\typora-user-images\image-20201006133506254.png)

随意输入一个文件名，下一步后点击完成即添加了qtc文件。

![image-20201006133719586](C:\Users\TuZhou\AppData\Roaming\Typora\typora-user-images\image-20201006133719586.png)

准备导入图片资源，在qrc界面添加前缀然后再点击添加文件，直接选中所有图片打开即可。



### 设计思路

该游戏主要工作在于游戏界面的开发设计，在项目中添加GameWidget类。

1. 创建方向按钮以及开始返回按钮、以及得分标签和难度标签。
2. 使用随机函数控制苹果坐标变化及蛇初始坐标位置
3. 使用一个二维数组代表蛇的坐标，显示蛇的位置变化
4. 变量bodycount表示蛇身体数量，State表示游戏是否停止，direction_index表示蛇头方向，常量longnumber表示横向网格数，widthnumber表示纵向网格数。
5. 在构造函数初始化所有属性，即初始化游戏开始前的属性，并调用repaint()函数。
6. 定义按键方法KeyPressEvent(QKeyEventt *e)，是能够键盘操作蛇的移动
7. 使用定时器控制游戏的开始，包括蛇头吃到苹果，蛇的移动，游戏失败
8. 蛇头坐标与苹果坐标相同时代表吃到，此时变化食物坐标、增加蛇的身体数量、增加得分和难度；每次定时器开启检测一次direction_index，相应加减蛇头坐标；将蛇身体前者的坐标赋值给后者，使蛇身可以连续移动；定时器开启后连接CheckGameState()函数，如果State为false则结束游戏。
9. 在paintEvent(QPaintEvent *)函数中绘制蛇移动的图像、蛇移动前的图像、游戏网格、食物图像
10. 开始按钮点击后开启定时器，此时开始按钮变成暂停，暂停按钮点击后暂停定时器并变回开始按钮。



## 项目打包

将项目打包成.exe文件即可脱离QtCreator环境独立运行，在其他电脑上也可使用。

具体方法参考

[参考1]([https://blog.csdn.net/windsnow1/article/details/78004265?biz_id=102&utm_term=qtcreator%E7%A8%8B%E5%BA%8F%E6%89%93%E5%8C%85%E6%88%90exe&utm_medium=distribute.pc_search_result.none-task-blog-2~all~sobaiduweb~default-1-78004265&spm=1018.2118.3001.4187](https://blog.csdn.net/windsnow1/article/details/78004265?biz_id=102&utm_term=qtcreator程序打包成exe&utm_medium=distribute.pc_search_result.none-task-blog-2~all~sobaiduweb~default-1-78004265&spm=1018.2118.3001.4187))

[参考2]([https://blog.csdn.net/u010058695/article/details/100153249?ops_request_misc=%257B%2522request%255Fid%2522%253A%2522160213785919195188309600%2522%252C%2522scm%2522%253A%252220140713.130102334.pc%255Fall.%2522%257D&request_id=160213785919195188309600&biz_id=0&utm_medium=distribute.pc_search_result.none-task-blog-2~all~first_rank_v2~rank_v28-1-100153249.pc_first_rank_v2_rank_v28&utm_term=qtcreator%E7%A8%8B%E5%BA%8F%E6%89%93%E5%8C%85%E6%88%90exe&spm=1018.2118.3001.4187](https://blog.csdn.net/u010058695/article/details/100153249?ops_request_misc=%7B%22request%5Fid%22%3A%22160213785919195188309600%22%2C%22scm%22%3A%2220140713.130102334.pc%5Fall.%22%7D&request_id=160213785919195188309600&biz_id=0&utm_medium=distribute.pc_search_result.none-task-blog-2~all~first_rank_v2~rank_v28-1-100153249.pc_first_rank_v2_rank_v28&utm_term=qtcreator程序打包成exe&spm=1018.2118.3001.4187))



#### QMessageBox:消息盒子类，提供一个对话框

`int QMessageBox::question(QWidget *parent, const QString &title, const QString &text, int button0, int button1 = 0, int button2 = 0)  //提供一个对话框，返回对话框中的按钮值`

`QMessageBox::Ok
QMessageBox::Cancel
QMessageBox::Yes
QMessageBox::No
QMessageBox::Abort
QMessageBox::Retry
QMessageBox::Ignore
QMessageBox::YesAll
QMessageBox::NoAll`  //均为对话框的按钮，其返回一个整型值



#### QIcon:图标类

`QIcon(const QString &filename)  //从图像文件中构造图标`

`this->setWindowIcon(QIcon(const QString &filename))  //给窗口添加个图标`

`QPushButton->setIcon(QIcon(const QString &filename))  //给按钮添加图标`  



#### QSize:代表一个矩形区域尺寸

`QSize(w, h)  //返回一个矩形尺寸`



#### QPushButton:按钮类

`QPushButton->setIconSize(QSize(w, h))  //设置按钮中图标尺寸`

`QPushButton->setFlat(bool)  //控制按钮的边框是否凸起和透明，true为不凸起并透明，默认为false`



#### QButtonGroup:按钮容器类

`buttonGroup=new QButtonGroup(this)  //创建一个按钮容器，可放置按钮`

`QButtonGroup.addButton(QPushButton, index)  //在容器中放置按钮，index为对应的索引`

`connect(buttonGroup,SIGNAL(buttonClicked(int)),this,SLOT(M_setDiretion(int)))  //buttonClicked信号会传递被点击按钮的索引值给槽函数参数`



#### QPixmap:图像类

`QPixmap(const QString &filename)  //生成一个像素图像`

`QPixmap(const QSize &size);   // 构造大小为 size 的图像，图像数据未初始化`

`QPixmap(int width, int height);  // 等价于 QPixmap(QSize(width, height));`

`QPixmap(const QString &filename, const char *format = 0, Qt::ImageConversionFlags flags = Qt::AutoColor)`

1) filename： 文件名。

2) format： 字符串，表示图像文件的格式，如果为 0，将进行自动识别。

3) flags：表示颜色的转换模式。



如果图像文件加载失败则产生空图像，这里 flags 参数有以下取值。

1) Qt::AutoColor：由系统自动决定。

2) Qt::ColorOnly：彩色模式。

3) Qt::MonoOnly：单色模式。



#### QPalette:画板类

`QPalette.setBrush(QPalette::Background,QBrush(QPixmap(const QString &filename)))  //给画板背景刷上图片，QBrush()将图片构造成一个图片刷子`

`QWidget->setPalette(palette)  //给窗口设置上调色板`



#### QString:字符串类

`QString::number(int)  //将int值转换成字符串`



#### QKeyEvent:键盘按键事件处理类

`QKeyEvent *e  //当键盘按键变化时，会作为事件发给e`

`QKeyEvent.key()  //返回接收到的按键编码值`



#### QPaintEvent:绘图事件类

`void QWidget::paintEvent(QPaintEvent *event)  //虚函数，用于接收绘制事件，每当窗口重绘都会自动调用此函数，例如repaint()和update()函数` 



#### QPainter:绘图类

`QPainter.drawImage(QRect(x,y,w,h), QImage(const QString &filename))  在指定的矩形区域中绘制图像，QRect()创建一个矩形`

`QPainter.setPen(Qt::color)  //设置画笔颜色`

`QPainter.drawRect(QRect(x,y,w,h))  //用画笔绘制矩形`











####  



