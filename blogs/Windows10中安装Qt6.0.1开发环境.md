# 一、环境介绍
操作系统: Win10 64位

QT版本: 6.0.1

VS版本:  2019

# 二、安装Qt 6.0.1
## 1、下载QT在线安装包
首先从[Getting Started with Qt](https://doc.qt.io/qt-5/gettingstarted.html)页面中可以知道，QT分为[在线](https://doc.qt.io/qt-5/gettingstarted.html#online-installation)或者[离线](https://doc.qt.io/qt-5/gettingstarted.html#offline-installation)安装或[自行编译源码包](https://doc.qt.io/qt-5/build-sources.html)三种：
![Getting Started with Qt](https://img-blog.csdnimg.cn/20210110130627296.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L2NjZjE5ODgxMDMw,size_16,color_FFFFFF,t_70)
从[Qt for Windows](https://doc.qt.io/qt-5/windows.html)可以看到Windows下Qt安装和使用的一些前提条件：
![Qt for Windows](https://img-blog.csdnimg.cn/20210110130750656.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L2NjZjE5ODgxMDMw,size_16,color_FFFFFF,t_70)
我本次的操作系统是Windows10，并且同时安装了VS2017和VS2019这两款软件。

接下来，从[Qt Download](https://www.qt.io/download)页面下载QT，页面如下图所示：
![Qt Download](https://img-blog.csdnimg.cn/20210110131037447.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L2NjZjE5ODgxMDMw,size_16,color_FFFFFF,t_70)
选择Try Qt中的[Download Qt Now]按钮，进行下载，此时会弹出一张表单让你填写，如下图所示：
![Free Evaluation](https://img-blog.csdnimg.cn/20210110131233734.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L2NjZjE5ODgxMDMw,size_16,color_FFFFFF,t_70)
稍微有点麻烦，需要注意的是：Business Email需要填写正确有效的邮箱格式
![Free Evaluation](https://img-blog.csdnimg.cn/20210110131447960.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L2NjZjE5ODgxMDMw,size_16,color_FFFFFF,t_70)
表单填好后点击最下面的【Submit】按钮，会进入到[Install Qt]页面，如下：
![Install Qt](https://img-blog.csdnimg.cn/20210110131558154.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L2NjZjE5ODgxMDMw,size_16,color_FFFFFF,t_70)
点击上图中的【Download】按钮，
![Thank you for downloading Qt!](https://img-blog.csdnimg.cn/2021011013171985.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L2NjZjE5ODgxMDMw,size_16,color_FFFFFF,t_70)
会下载`qt-unified-windows-x86-4.0.1-online.exe`在线Qt安装文件，如下图所示：
![在这里插入图片描述](https://img-blog.csdnimg.cn/2021011013222762.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L2NjZjE5ODgxMDMw,size_16,color_FFFFFF,t_70)

## 2、安装Qt
鼠标双击`qt-unified-windows-x86-4.0.1-online.exe`，可以安装Qt
![Qt Setup-Welcome](https://img-blog.csdnimg.cn/20210110132548666.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L2NjZjE5ODgxMDMw,size_16,color_FFFFFF,t_70)
输入注册的QT邮箱和密码进行登录，点击【Next】进行下一步：
![Qt Setup-Setup Qt](https://img-blog.csdnimg.cn/20210110132747178.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L2NjZjE5ODgxMDMw,size_16,color_FFFFFF,t_70)
点击【Next】按钮进行下一步
![Qt Setup-Setup Qt 002](https://img-blog.csdnimg.cn/20210110132851315.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L2NjZjE5ODgxMDMw,size_16,color_FFFFFF,t_70)

![Qt Setup-Setup Qt 003](https://img-blog.csdnimg.cn/20210110132938539.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L2NjZjE5ODgxMDMw,size_16,color_FFFFFF,t_70)
点击[Next]，来到选择安装目录这一步，如下图所示：
![Installation Folder](https://img-blog.csdnimg.cn/20210110133020317.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L2NjZjE5ODgxMDMw,size_16,color_FFFFFF,t_70)
Window中默认的Qt安装目录是C:\Qt，这里可以自行指定Qt安装目录，由于我电脑上C盘已经差不多满了，我选择D:\software\Qt作为安装目录，
![Installation Folder 002](https://img-blog.csdnimg.cn/20210110133317901.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L2NjZjE5ODgxMDMw,size_16,color_FFFFFF,t_70)
注意这里可以根据需要自定义安装组件，如果选择【Default desktop installation】，则只会安装基于桌面开发的MinGW 8.1.0.64
点击【Next】下一步,来到[Select Components】这一步，如下图所示：
![在这里插入图片描述](https://img-blog.csdnimg.cn/20210110133508188.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L2NjZjE5ODgxMDMw,size_16,color_FFFFFF,t_70)

![Select Components](https://img-blog.csdnimg.cn/20210110134620663.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L2NjZjE5ODgxMDMw,size_16,color_FFFFFF,t_70)

这里，我选择了同时安装Qt6.0.1这个版本，当然你可以根据自己的实际开发需要选择需要安装的组件。选好后点击【Next】按钮进行下一步，来到【License Agreement]】对话框界面，如下图所示：
![License Agreement](https://img-blog.csdnimg.cn/20210110134030662.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L2NjZjE5ODgxMDMw,size_16,color_FFFFFF,t_70)
勾选上面【I have read and agree to the terms contained in the license agrements.】，再点击【Next】按钮开始安装
![Start Menu shortcuts](https://img-blog.csdnimg.cn/20210110134254157.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L2NjZjE5ODgxMDMw,size_16,color_FFFFFF,t_70)
点击【Next】按钮

![Ready to Install](https://img-blog.csdnimg.cn/20210110134822321.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L2NjZjE5ODgxMDMw,size_16,color_FFFFFF,t_70)点击上图右下角的【Install】按钮进行安装，

![Install Qt 001](https://img-blog.csdnimg.cn/20210110134917935.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L2NjZjE5ODgxMDMw,size_16,color_FFFFFF,t_70)
你可以点击中间的【Show Details】查看安装进度中安装了哪些文件，如下图所示：
![在这里插入图片描述](https://img-blog.csdnimg.cn/20210110134958180.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L2NjZjE5ODgxMDMw,size_16,color_FFFFFF,t_70)
安装过程有些慢，你可以喝杯咖啡耐心等到，等待QT6.0.1安装完成，完成之后界面如下图所示：
![Finished](https://img-blog.csdnimg.cn/2021011015091158.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L2NjZjE5ODgxMDMw,size_16,color_FFFFFF,t_70)
点击【Next】，
![Finished 002](https://img-blog.csdnimg.cn/20210110151012295.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L2NjZjE5ODgxMDMw,size_16,color_FFFFFF,t_70)
点击【Finish】，打开Qt Creator
![Launch Qt Creator](https://img-blog.csdnimg.cn/20210110151213241.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L2NjZjE5ODgxMDMw,size_16,color_FFFFFF,t_70)
安装完成后会在安装目录比如我的安装目录`D:\software\Qt`目录下会生成如下图所示的文件：![Qt 6.0.1安装目录](https://img-blog.csdnimg.cn/20210110151355268.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L2NjZjE5ODgxMDMw,size_16,color_FFFFFF,t_70)


# 三、使用`Qt Creator`创建一个QT控制台程序进行测试
打开桌面上的`qtcreator.exe`图标，输入QT注册邮箱和密码登录，
![Qt Creator](https://img-blog.csdnimg.cn/20210110151705476.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L2NjZjE5ODgxMDMw,size_16,color_FFFFFF,t_70)
![Qt Creator界面](https://img-blog.csdnimg.cn/20210110151813203.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L2NjZjE5ODgxMDMw,size_16,color_FFFFFF,t_70)
点击左上角的【File】菜单->
![Qt Creator界面 002](https://img-blog.csdnimg.cn/20210110151846387.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L2NjZjE5ODgxMDMw,size_16,color_FFFFFF,t_70)
![创建一个基于控制台的项目](https://img-blog.csdnimg.cn/2021011015223497.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L2NjZjE5ODgxMDMw,size_16,color_FFFFFF,t_70)
选择编译系统qmake、Cmake、Qbs
![Qt Creator 001](https://img-blog.csdnimg.cn/20210110152324879.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L2NjZjE5ODgxMDMw,size_16,color_FFFFFF,t_70)
![Qt Creator 002](https://img-blog.csdnimg.cn/20210110152519522.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L2NjZjE5ODgxMDMw,size_16,color_FFFFFF,t_70)
![Qt Creator 003](https://img-blog.csdnimg.cn/20210110152542107.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L2NjZjE5ODgxMDMw,size_16,color_FFFFFF,t_70)
![Qt Creator 004](https://img-blog.csdnimg.cn/2021011015255879.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L2NjZjE5ODgxMDMw,size_16,color_FFFFFF,t_70)
![Qt Creator 005](https://img-blog.csdnimg.cn/20210110152625671.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L2NjZjE5ODgxMDMw,size_16,color_FFFFFF,t_70)
![在这里插入图片描述](https://img-blog.csdnimg.cn/20210110152734368.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L2NjZjE5ODgxMDMw,size_16,color_FFFFFF,t_70)
编写`main.cpp`，代码如下：
```cpp
#include <QCoreApplication>
#include <QDebug>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    qDebug() << "hello, qt";

    return a.exec();
}

```
![执行结果 ](https://img-blog.csdnimg.cn/20210110152843119.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L2NjZjE5ODgxMDMw,size_16,color_FFFFFF,t_70)

## 四、安装VS2019、CMake、qt-vsaddin-msvc2019插件
如果需要在VS2019中使用QT，或者需要使用CMake作为项目编译构建工具，还得安装VS2019、CMake、qt-vsaddin-msvc2019插件,
具体内容包括QT6.0.1、QT5.12.0、CMake-3.19.2、VS2017在线安装包、VS2019在线安装包、qt-vsaddin-msvc2019-2.6.0.vsix等等，我已经下载好了，如下图所示：
![Qt相关软件](https://img-blog.csdnimg.cn/20210110160214380.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L2NjZjE5ODgxMDMw,size_16,color_FFFFFF,t_70)
CMake-3.19.2下载地址为：[https://cmake.org/download/](https://cmake.org/download/)，可以根据需要安装，我安装的是[cmake-3.19.2-win64-x64.msi](https://github.com/Kitware/CMake/releases/download/v3.19.2/cmake-3.19.2-win64-x64.msi)
![CMake-3.19.2下载页面](https://img-blog.csdnimg.cn/2021011016055335.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L2NjZjE5ODgxMDMw,size_16,color_FFFFFF,t_70)
下载[qt-vsaddin-msvc2019-2.6.0.vsix](https://download.qt.io/official_releases/vsaddin/2.6.0/qt-vsaddin-msvc2019-2.6.0.vsix)插件，如下图所示：
![Qt VS插件](https://img-blog.csdnimg.cn/20210110161015694.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L2NjZjE5ODgxMDMw,size_16,color_FFFFFF,t_70)


为了方便我已经上传到百度网盘上了，
链接：[https://pan.baidu.com/s/1SxZnOTHfwog6f9F8bi-GSw](https://pan.baidu.com/s/1SxZnOTHfwog6f9F8bi-GSw)
提取码：j98u 
复制这段内容后打开百度网盘手机App，操作更方便哦

![QT资料-百度网盘](https://img-blog.csdnimg.cn/20210110161512636.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L2NjZjE5ODgxMDMw,size_16,color_FFFFFF,t_70)



# 五、参考资料
- [Qt 6.0 Released(https://www.qt.io/blog/qt-6.0-released)
- [Getting Started with Qt](https://doc.qt.io/qt-5/gettingstarted.html)
- [Offline Qt Downloads](https://www.qt.io/offline-installers)
- [Qt Project Git Repository Browser](https://code.qt.io/cgit/qt/)
- [Porting to Qt 6](https://doc.qt.io/qt-6/portingguide.html)
- [What's New in Qt 6.0](https://doc.qt.io/qt-6/whatsnew60.html) - overview of the changes in Qt 6.0
- [Qt Creator Manual](http://doc.qt.io/qtcreator/index.html)
- [Qt Overviews](https://doc.qt.io/qt-6/overviews-main.html)
- [Qt Examples And Tutorials](https://doc.qt.io/qt-6/qtexamplesandtutorials.html)
- [Build System Changes in Qt 6](https://doc.qt.io/qt-6/qt6-buildsystem.html) - for building Qt 6 from source
- [《C++ Qt 编程视频教程》(C++ Qt Programming)[MP4]](https://blog.csdn.net/xiaofeixiall/article/details/82117909)
- [Qt for Windows - Building from Source](https://doc.qt.io/qt-5/windows-building.html)
- [Qt 6 Build System](https://www.qt.io/blog/qt-6-build-system)
- [Qt Downloads](http://download.qt.io/)
- [Introduction to Qt - Download and Installation {tutorial}](https://resources.qt.io/development-topic-getting-started-with-qt/introduction-to-qt-installing-qt-creator)
- [Qt Downloads](http://download.qt.io/official_releases/qt/)
- [Qt Visual Studio Tools Insights](https://resources.qt.io/development-topic-getting-started-with-qt/qt-visual-studio-tools-insights)
- [qt-vsaddin-msvc2019-2.6.0下载](https://download.qt.io/official_releases/vsaddin/2.6.0/)
- [qt-vsaddin-msvc2019-2.6.0.vsix](https://download.qt.io/official_releases/vsaddin/2.6.0/qt-vsaddin-msvc2019-2.6.0.vsix)
- [qt-vsaddin-msvc2017-2.6.0.vsix](https://download.qt.io/official_releases/vsaddin/2.6.0/qt-vsaddin-msvc2017-2.6.0.vsix)
- [Qt  在线安装器下载地址](http://download.qt.io/archive/online_installers/4.0/)
