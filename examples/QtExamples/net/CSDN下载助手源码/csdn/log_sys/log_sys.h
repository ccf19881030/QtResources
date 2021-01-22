/*
 *      文件名: log_sys.h
 *      功能:  实现文件日志
 *      作者: wu5151
 *      博客地址: http://blog.csdn.net/wu5151
 */
#ifndef LOG_SYS_H
#define LOG_SYS_H

#include <QtDebug>
#include <QFile>
#include <QTextStream>
#include <QDateTime>
#include <windows.h>

void myMsgHandler (QtMsgType type, const char * msg)
{
    QString str;

    QDateTime dateTime = QDateTime::currentDateTime();

    str = dateTime.toString("yyyy-MM-dd hh:mm::s");

    switch (type) {

    // 调试信息
    case QtDebugMsg: {

        str += QString("  Debug:  %1").arg(msg);

       /* // 将调试信息打印到控制台下   注意转换字符
        str += "\n";
        wchar_t temp[1000] = L"";
        str.toWCharArray(temp);
        OutputDebugStringW(temp);*/
    }
        break;

    // 一般的错误信息提示
    case QtWarningMsg:
        str += QString("  Warning:  %1").arg(msg);
        break;

    // 严重错误信息提示
    case QtCriticalMsg:
        str += QString("  Critical:  %1 ").arg(msg);
        break;

    // 致命错误信息提示
    case QtFatalMsg:
        str += QString("  Fatal:  %1 ").arg(msg);
        abort();
    }

    QFile logFile("systemLog.log");
    logFile.open(QFile::Append);
    QTextStream out(&logFile);
    out << str<< "\r\n";
    logFile.close();
}



#endif // LOG_SYS_H
