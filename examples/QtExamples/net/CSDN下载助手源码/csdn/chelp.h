/*
 *      文件名: chelp.h
 *
 *      功能: 助手类，实现窗口日志输出
 *
 *      作者: wu5151
 *      博客地址: http://blog.csdn.net/wu5151
 */


#ifndef CHELP_H
#define CHELP_H

#include <QObject>
#include <QString>
#include <QTextEdit>
#include <QMutex>
#include <QTime>
#include <QCoreApplication>

class CHelp : public QObject
{
    Q_OBJECT
public:
    explicit CHelp(QObject *parent = 0);
    
    static void setLog(const QString content);

    //延时函数  此函数来源于网络，作者: 游龙 （此程序修改后并未使用此函数）
    //   不删除，供学习
    static void Sleep(int sec) {
        QTime dieTime = QTime::currentTime().addMSecs(sec);
        while ( QTime::currentTime() < dieTime ) {
            QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
        }
    }

    static QTextEdit* g_pLineEdit;

    static QMutex m_Mutex;

};

#endif // CHELP_H
