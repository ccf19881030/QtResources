## 1、QT：打印当前文件名，行号和函数名称

定义：

```c++
#include <QDebug>
#define myDebug()    qDebug() << tr("文件名: ") <<  __FILE__ << tr("行号: ")<<  __LINE__ << tr("函数名: ") <<  __FUNCTION__;
```

在函数中执行myDebug()即可：

```c++
void MainWindow::doActionNew_slot()
{
    ui->statusBar->showMessage(tr("新建文件"));
    myDebug();
}
```

执行结果：

```c++
"文件名: " ..\mainwindow.cpp "行号: " 39 "函数名: " doActionNew_slot 
```

总结：在C语言中 __FILE__ __LINE__ __FUNCTION__ 是编译器内置宏，这些宏定义不仅可以帮助我们完成跨平台的源码编写，灵活使用也可以巧妙地帮我们输出非常有用的调试信息。
__FILE__：代表源当前源文件路径及文件名；
__LINE__：代表该行代码的所在行号
__FUNCTION__：代表当前函数的函数名



## 2、Qt获取当前时间日期或时间戳QDateTime

```c++
获取系统时间 QDateTime timeCur = QDateTime::currentDateTime();//获取系统现在的时间

设置显示格式 QString timeStr = timeCur.toString("yyyy-MM-dd hh:mm:ss ddd"); //秒

设置显示格式 QString timeStr = timeCur.toString("yyyy-MM-dd hh:mm:ss.zzz"); //毫秒

获取时间戳(毫秒) QString timestamp = QString::number(QDateTime::currentMSecsSinceEpoch())

获取时间戳(秒) int timeT = time.toTime_t();   //将当前时间转为时间戳 
```



## 3、Qt下编写日志模块（同时记录文件名、函数名、行数）

https://blog.csdn.net/lusanshui/article/details/94551189

### 简述
说来惭愧，一直以来，我都是使用一个单例模式来完成日志模块，具体操作就是调用单例的写文件函数，自己编辑日志内容，记录在日志文件里。
这种做法不利于查找调试。而使用qt内置的qInstallMessageHandler函数，重新编辑调试函数的输出内容才是简单高效的做法。

### 调试级别
名字很高大上，其实大家都在使用的qDebug()就是。
qDebug() – 调试信息输出；
qInfo() – 信息消息；
qWarning() – 警告消息和可恢复的错误；
qCritical() – 关键错误和系统错误；
qFatal() – 致命错误。
一共有五类，用法和qDebug()一致。需要特别说明的只有qFatal()，每当程序执行到这句话时会自动报错并终止。

### 代码之路
一个工程项目会出现很多的调试信息和日志信息，供我们查找调试，如果能提供信息所在的文件、函数和行号，那就太方便了。
下面，我们就可以使用qt内置的qInstallMessageHandler函数在自定义消息处理，通过各调试级别的信息输出，直接输出到屏幕并记录到日志文件。

```c++
#include <QApplication>
#include <stdio.h>
#include <stdlib.h>

#include <QMutex>
#include <QFile>
#include <QTextStream>
#include <QDateTime>

QtMessageHandler gDefaultHandler = NULL;
//自定义消息处理函数
void myMessageOutput(QtMsgType type, const QMessageLogContex &context, const QString &msg)
{
  QDateTime time = QDateTime::currentDateTime();
  QString strTime = time.toString("yyyy-MM-dd hh:mm:ss");
  QString strMessage = QString("%1 File:%2 Line:%3 Function:%4\r\n %5")
  		.arg(strTime).arg(context.file).arg(context.line).arg(context.function).arg(msg);
  QString strMsg;
  switch(type)
  {
  	case QtDebugMsg:
  		strMsg = QString("Debug ");
  		break;
  	case QtInfoMsg:
  		strMsg = QString("Info ");
  		break;
  	case QtWarningMsg:
  		strMsg = QString("Warning ");
  		break;
  	case QtCriticalMsg:
  		strMsg = QString("Critical ");
  		break;
  	case QtFatalMsg:
  		strMsg = QString("Fatal ");
  		break;
  	default:
  		strMsg = QString("Err");
  		break;
  }
  strMessage = strMsg + strMessage;
  
  //加锁输出文件
  static QMutex mutex;
  mutex.lock();
  QFile file("D:\\log.txt");
  file.open(QIODevice::WriteOnly|QIODevice::Append);
  QTextStream stream(&file);
  stream << strMessage << "\r\n";
  file.flush();
  file.close();
  mutex.unlock();
  
  //同时用系统原来的函数完成输出打印
  if(gDefaultHandler)
  {
  	gDefaultHandler(type, context, msg);
  }
}

int main(int argc, char **argv)
{
  QApplication app(argc, argv);
  //安装消息处理函数
  qInstallMessageHandler(myMessageOutput);
  //打印信息
  qDebug() << "This is a debug message.";
  qWarning() << "This is a warning message.";
  qCritical() << "This is a critical message.";
  qFatal() << "This is a fatal message.";
  ...
  return app.exec();
}
```

界面输出的内容如下：

```shell
This is a debug msg.
This is a info msg.
This is a warning msg.
This is a critical msg.
```

文件记录的内容如下：

```shel
Debug 2019-07-03 10:59:32 File:…\LogMsg\main.cpp Line:74 Function:int __cdecl main(int,char *[])
This is a debug msg.
Info 2019-07-03 10:59:32 File:…\LogMsg\main.cpp Line:75 Function:int __cdecl main(int,char *[])
This is a info msg.
Warning 2019-07-03 10:59:32 File:…\LogMsg\main.cpp Line:76 Function:int __cdecl main(int,char *[])
This is a warning msg.
Critical 2019-07-03 10:59:32 File:…\LogMsg\main.cpp Line:77 Function:int __cdecl main(int,char *[])
This is a critical msg.
```

### 写在最后

Release版本默认不包含文件名、函数名和行数信息，需要在.pro文件中加入一行代码,重新make运行后生效。
DEFINES += QT_MESSAGELOGCONTEXT
