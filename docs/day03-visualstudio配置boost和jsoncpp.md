## GateServer
网关服务器主要应答客户端基本的连接请求，包括根据服务器负载情况选择合适服务器给客户端登录，注册，获取验证服务等，接收http请求并应答。
## boost库安装
boost库的安装分为Windows和Linux两部分，Linux部分放在后面再讲解。因为Windows比较直观，便于我们编写代码，所以优先在windows平台搭建环境并编写代码，测试无误后再移植到linux。

boost官网地址：

Boost库官网[https://www.boost.org/](https://www.boost.org/)，首先进入官网下载对应的Boost库文件。点击下图所示红框中Download进入下载页面。更多版本点击链接下载。

![https://cdn.llfc.club/1709188088318.jpg](https://cdn.llfc.club/1709188088318.jpg)

点击进入页面后，接下来选择7z或者zip文件都可以。

![https://cdn.llfc.club/1709188365491.jpg](https://cdn.llfc.club/1709188365491.jpg)

如果下载缓慢，大家可以去我的网盘下载
链接：[https://pan.baidu.com/s/1Uf-7gZxWpCOl7dnYzlYRHg?pwd=xt01](https://pan.baidu.com/s/1Uf-7gZxWpCOl7dnYzlYRHg?pwd=xt01) 

提取码：xt01 

我的是boost_1_81_0版本，大家可以和我的版本匹配，也可以自己用最新版。

下载好后解压, 其中booststrap.bat点击后生成编译程序

![https://cdn.llfc.club/1709189119436.jpg](https://cdn.llfc.club/1709189119436.jpg)

点击后，生成b2.exe，我们执行如下命令

``` bash
.\b2.exe install --toolset=msvc-14.2 --build-type=complete --prefix="D:\cppsoft\boost_1_81_0" link=static runtime-link=shared threading=multi debug release
```
先逐一解释各参数含义

1. install可以更改为stage, stage表示只生成库(dll和lib), install还会生成包含头文件的include目录。一般来说用stage就可以了，我们将生成的lib和下载的源码包的include头文件夹放到项目要用的地方即可。
2. toolset 指定编译器，`gcc`用来编译生成linux用的库，`msvc-14.2（VS2019）`用来编译windows使用的库，版本号看你的编译器比如`msvc-10.0（VS2010）`，我的是`VS2019`所以是`msvc-14.2`。
3. 如果选择的是install 命令，指定生成的库文件夹要用`--prefix`，如果使用的是stage命令，需要用`--stagedir`指定。
4. `link` 表示生成动态库还是静态库，`static`表示生成lib库，`shared`表示生成dll库。
5. `runtime-link` 表示用于指定运行时链接方式为静态库还是动态库，指定为`static`就是`MT`模式，指定`shared`就是`MD`模式。`MD` 和 `MT` 是微软 Visual C++ 编译器的选项，用于指定运行时库的链接方式。这两个选项有以下区别：

    - `/MD`：表示使用多线程 DLL（Dynamic Link Library）版本的运行时库。这意味着你的应用程序将使用动态链接的运行时库（MSVCRT.dll）。这样的设置可以减小最终可执行文件的大小，并且允许应用程序与其他使用相同运行时库版本的程序共享代码和数据。
    - `/MT`：表示使用多线程静态库（Static Library）版本的运行时库。这意味着所有的运行时函数将被静态链接到应用程序中，使得应用程序不再依赖于动态链接的运行时库。这样可以确保应用程序在没有额外依赖的情况下独立运行，但可能会导致最终可执行文件的体积增大。

执行上述命令后就会在指定目录生成lib库了，我们将lib库拷贝到要使用的地方即可。

一句话简化上面的含义，就是我们生成的是lib库，运行时采用的md加载模式。

下面是编译界面

![https://cdn.llfc.club/1709190169393.jpg](https://cdn.llfc.club/1709190169393.jpg)

编译后生成如下目录和文件, 我的是D盘 cppsoft目录下的boost文件夹，大家可以根据自己的设置去指定文件夹查看。

![https://cdn.llfc.club/1709192144529.jpg](https://cdn.llfc.club/1709192144529.jpg)

为了兼容我之前做的旧项目，我创建了一个stage文件夹，将lib文件夹和内容移动到stage中了。然后将include文件夹下的boost文件夹移出到boost_1_81_0目录下，整体看就就是如下

![https://cdn.llfc.club/1709192797632.jpg](https://cdn.llfc.club/1709192797632.jpg)

接下来我们创建项目并配置boost

## 配置boost

打开visual studio 创建项目 

![https://cdn.llfc.club/1709193315698.jpg](https://cdn.llfc.club/1709193315698.jpg)

接下来配置boost到项目中,右键项目选择属性，配置VC++包含目录，添加`D:\cppsoft\boost_1_81_0`（根据你自己的boost目录配置）

![https://cdn.llfc.club/1709193680525.jpg](https://cdn.llfc.club/1709193680525.jpg)

再配置VC++库目录, 添加`D:\cppsoft\boost_1_81_0\stage\lib`

![https://cdn.llfc.club/1709194005921.jpg](https://cdn.llfc.club/1709194005921.jpg)

写个代码测试一下

``` cpp
#include <iostream>
#include <string>
#include "boost/lexical_cast.hpp"
int main()
{
    using namespace std;
    cout << "Enter your weight: ";
    float weight;
    cin >> weight;
    string gain = "A 10% increase raises ";
    string wt = boost::lexical_cast<string> (weight);
    gain = gain + wt + " to ";      // string operator()
    weight = 1.1 * weight;
    gain = gain + boost::lexical_cast<string>(weight) + ".";
    cout << gain << endl;
    system("pause");
    return 0;
}
```
运行成功，可以看到弹出了窗口

![https://cdn.llfc.club/1675233803676.jpg](https://cdn.llfc.club/1675233803676.jpg)

## 配置jsoncpp

因为要用到json解析，所以我们选择jsoncpp来做后端json解析工作

jsoncpp下载地址：
[https://github.com/open-source-parsers/jsoncpp](https://github.com/open-source-parsers/jsoncpp)
官方文档：
[http://jsoncpp.sourceforge.net/old.html](http://jsoncpp.sourceforge.net/old.html)

选择windows版本的下载。

如果下载速度很慢，可以去我的网盘地址下载
[https://pan.baidu.com/s/1Yg9Usdc3T-CYhyr9GiePCw?pwd=ng6x](https://pan.baidu.com/s/1Yg9Usdc3T-CYhyr9GiePCw?pwd=ng6x)

验证码ng6x
下载后我们解压文件夹，解压后文件夹如下图
![https://cdn.llfc.club/1684638346874.jpg](https://cdn.llfc.club/1684638346874.jpg)

然后进行编译，编译需要进入makefile文件夹下

![https://cdn.llfc.club/1684638830012.jpg](https://cdn.llfc.club/1684638830012.jpg)

找到jsoncpp.sln文件，用visual studio打开，因为我的是visual studio2019版本，所以会提示我升级。

![https://cdn.llfc.club/1684638950615.jpg](https://cdn.llfc.club/1684638950615.jpg)


点击确定升级，之后我们选择编译lib_json即可，当然偷懒可以选择编译整个解决方案。
![https://cdn.llfc.club/1684639169065.jpg](https://cdn.llfc.club/1684639169065.jpg)

然后我们配置编译属性，我想要用x64位的，所以配置编译平台为X64位，编译模式为debug模式，大家最好把release版和debug版都编译一遍。

右键lib_json属性里选择C++，再选择代码生成，之后在右侧选择运行库，选择md(release版), mdd(debug版).

![https://cdn.llfc.club/1709197886189.jpg](https://cdn.llfc.club/1709197886189.jpg)


编译生成后，我们的json库生成在项目同级目录的x64文件夹下的debug目录下
![https://cdn.llfc.club/1684640251160.jpg](https://cdn.llfc.club/1684640251160.jpg)

接下来我们在D盘cppsoft新建一个文件夹libjson，然后在其内部分别建立include和lib文件夹

![https://cdn.llfc.club/1684640531206.jpg](https://cdn.llfc.club/1684640531206.jpg)

将jsoncpp-src-0.5.0源码文件夹下include文件夹里的内容copy到libjson下的include文件夹内。

将jsoncpp-src-0.5.0源码文件夹下x64位debug文件夹和Release文件夹下生成的库copy到libjson下的lib文件夹内。

![https://cdn.llfc.club/1709198276119.jpg](https://cdn.llfc.club/1709198276119.jpg)

我们生成的是mdd和md版本的库，但是名字却是mt，这个是visual studio生成的小bug先不管了。

接下来我们新建一个项目，在项目属性中配置jsoncpp

项目属性中，VC++包含目录设置为 D:\cppsoft\libjson\include

库目录选择为 VC++库目录设置为 D:\cppsoft\libjson\lib

![https://cdn.llfc.club/1684641520042.jpg](https://cdn.llfc.club/1684641520042.jpg)

另外我们还要设置链接器->输入->附加依赖项里设置json_vc71_libmtd.lib

![https://cdn.llfc.club/1684641902273.jpg](https://cdn.llfc.club/1684641902273.jpg)

我们写个程序测试一下json库安装的情况
``` cpp
#include <iostream>
#include <json/json.h>
#include <json/value.h>
#include <json/reader.h>

int main()
{
    Json::Value root;
    root["id"] = 1001;
    root["data"] = "hello world";
    std::string request = root.toStyledString();
    std::cout << "request is " << request << std::endl;

    Json::Value root2;
    Json::Reader reader;
    reader.parse(request, root2);
    std::cout << "msg id is " << root2["id"] << " msg is " << root2["data"] << std::endl;
}
```

从这段代码中，我们先将root序列化为字符串，再将字符串反序列化为root2.

输出如下

![https://cdn.llfc.club/1684642765063.jpg](https://cdn.llfc.club/1684642765063.jpg)


