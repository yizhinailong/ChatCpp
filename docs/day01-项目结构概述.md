## 简介
本项目为C++全栈聊天项目实战，包括PC端QT界面编程，asio异步服务器设计，beast网络库搭建http网关，nodejs搭建验证服务，各服务间用grpc通信，server和client用asio通信等，也包括用户信息的录入等。实现跨平台设计，先设计Windows的server，之后再考虑移植到Linux中。较为全面的展示C++ 在实际项目中的应用，可作为项目实践学习案例，也可写在简历中。

## 架构设计

一个概要的结构设计如下图

![](https://gitee.com/yizhinailong/images/raw/master/images/test/202502151420803.jpg)

1. GateServer为网关服务，主要应对客户端的连接和注册请求，因为服务器是是分布式，所以GateServer收到用户连接请求后会查询状态服务选择一个负载较小的Server地址给客户端，客户端拿着这个地址直接和Server通信建立长连接。
2. 当用户注册时会发送给GateServer, GateServer调用VarifyServer验证注册的合理性并发送验证码给客户端，客户端拿着这个验证码去GateServer注册即可。
3. StatusServer， ServerA， ServerB都可以直接访问Redis和Mysql服务。

## 创建应用
我们先创建客户端的登录界面，先用qt创建qt application widgets

![https://cdn.llfc.club/1709012628800.jpg](https://cdn.llfc.club/1709012628800.jpg)

项目名称叫做llfcchat，位置大家自己选择。

接下来一路同意，最后生成项目。

![https://cdn.llfc.club/1709014472288.jpg](https://cdn.llfc.club/1709014472288.jpg)

为了增加项目可读性，我们增加注释模板

选择“工具”->“选项”，再次选择“文本编辑器”->“片段”->“添加”，按照下面的模板编排

``` bash
/******************************************************************************
 *
 * @file       %{CurrentDocument:FileName}
 * @brief      XXXX Function
 *
 * @author     恋恋风辰
 * @date       %{CurrentDate:yyyy\/MM\/dd}
 * @history    
 *****************************************************************************/
```
如下图
![https://cdn.llfc.club/1709014829278.jpg](https://cdn.llfc.club/1709014829278.jpg)

以后输入header custom就可以弹出注释模板了.

修改mainwindow.ui属性,长宽改为300*500
![https://cdn.llfc.club/1709017541569.jpg](https://cdn.llfc.club/1709017541569.jpg)

将window title 改为llfcchat

大家自己找个icon.ico文件放到项目根目录，或者用我的也行，然后在项目pro里添加输出目录文件和icon图标
``` cpp
RC_ICONS = icon.ico
DESTDIR = ./bin
```

将图片资源添加ice.png添加到文件夹res里，然后右键项目选择添加新文件，选择qt resource files， 添加qt的资源文件，名字设置为rc。

添加成功后邮件rc.qrc选择添加现有资源文件，

选择res文件夹下的ice.png，这样ice.png就导入项目工程了。

## 创建登录界面
右键项目，选择创建，点击设计师界面类

![https://cdn.llfc.club/1709018322347.jpg](https://cdn.llfc.club/1709018322347.jpg)

选择 dialog without buttons

![https://cdn.llfc.club/1709018398183.jpg](https://cdn.llfc.club/1709018398183.jpg)

创建的名字就叫做LoginDialog

![https://cdn.llfc.club/1709018587338.jpg](https://cdn.llfc.club/1709018587338.jpg)


将LoginDialog.ui修改为如下布局

![https://cdn.llfc.club/1709019305029.jpg](https://cdn.llfc.club/1709019305029.jpg)

在mainwindow.h中添加LoginDialog指针成员，然后在构造函数将LoginDialog设置为中心部件
``` cpp
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //创建一个CentralWidget, 并将其设置为MainWindow的中心部件
    _login_dlg = new LoginDialog();
    setCentralWidget(_login_dlg);
    _login_dlg->show();
}
```
## 创建注册界面

注册界面创建方式和登录界面类似，我们创建的界面如下:

![https://cdn.llfc.club/1709030381543.jpg](https://cdn.llfc.club/1709030381543.jpg)

创建好界面后接下来在LoginDialog类声明里添加信号切换注册界面

``` cpp
signals:
    void switchRegister();
```
在LoginDialog的构造函数里连接按钮点击事件
``` cpp
connect(ui->reg_btn, &QPushButton::clicked, this, &LoginDialog::switchRegister);
```
按钮点击后LoginDialog发出switchRegister信号，该信号发送给MainWindow用来切换界面。

我们在MainWindow里声明注册类变量
``` cpp
private:
    RegisterDialog* _reg_dlg;
```
在其构造函数中添加注册类对象的初始化以及连接switchRegister信号
``` cpp
    //创建和注册消息的链接
    connect(_login_dlg, &LoginDialog::switchRegister,
            this, &MainWindow::SlotSwitchReg);

    _reg_dlg = new RegisterDialog();
```
接下来实现槽函数SlotSwitchReg
``` cpp
void MainWindow::SlotSwitchReg(){
    setCentralWidget(_reg_dlg);
    _login_dlg->hide();
    _reg_dlg->show();
}
```
这样启动程序主界面优先显示登录界面，点击注册后跳转到注册界面

## 优化样式

我们在项目根目录下创建style文件夹，在文件夹里创建stylesheet.qss文件，然后在qt项目中的rc.qrc右键添加现有文件，选择stylesheet.qss，这样qss就被导入到项目中了。

在主程序启动后加载qss
``` cpp
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QFile qss(":/style/stylesheet.qss");

    if( qss.open(QFile::ReadOnly))
    {
        qDebug("open success");
        QString style = QLatin1String(qss.readAll());
        a.setStyleSheet(style);
        qss.close();
    }else{
         qDebug("Open failed");
     }

    MainWindow w;
    w.show();

    return a.exec();
}
```

然后我们写qss样式美化界面
``` qss
QDialog#LoginDialog{
background-color:rgb(255,255,255)
}
```
主界面有一道灰色的是toolbar造成的，去mainwindow.ui里把那个toolbar删了就行了。