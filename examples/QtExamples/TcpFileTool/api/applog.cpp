#include "applog.h"
#include "myhelper.h"

//输出所有打印调试信息到日志文件
#if (QT_VERSION <= QT_VERSION_CHECK(5,0,0))
void Log(QtMsgType type, const char *msg)
{
    QString content;
    switch (type) {
    case QtDebugMsg:
        content = QString("%1").arg(msg);
        break;
    case QtWarningMsg:
        content = QString("%1").arg(msg);
        break;
    case QtCriticalMsg:
        content = QString("%1").arg(msg);
        break;
    case QtFatalMsg:
        content = QString("%1").arg(msg);
        exit(0);
    }

    QString logFile = QString("%1/LOG/%2_Log_%3.txt")
                      .arg(App::AppPath)
                      .arg(App::AppName)
                      .arg(DATE);
    QFile log(logFile);
    log.open(QIODevice::WriteOnly | QIODevice::Append | QFile::Text);
    QTextStream logStream(&log);
    logStream << content << "\n";
}
#else
void Log(QtMsgType type, const QMessageLogContext &, const QString &msg)
{
    QString content;
    switch (type) {
    case QtDebugMsg:
        content = QString("%1").arg(msg);
        break;
    case QtWarningMsg:
        content = QString("%1").arg(msg);
        break;
    case QtCriticalMsg:
        content = QString("%1").arg(msg);
        break;
    case QtFatalMsg:
        content = QString("%1").arg(msg);
        exit(0);
    }

    QString logFile = QString("%1/LOG/%2_Log_%3.txt")
                      .arg(App::AppPath)
                      .arg(App::AppName)
                      .arg(DATE);
    QFile log(logFile);
    log.open(QIODevice::WriteOnly | QIODevice::Append | QFile::Text);
    QTextStream logStream(&log);
    logStream << content << "\n";
}
#endif

AppLog::AppLog(QObject *parent) : QObject(parent)
{

}

void AppLog::Load()
{
    //如果日志文件夹不存在则创建
    QString logDir = QString("%1/LOG").arg(App::AppPath);
    QDir log(logDir);
    if (!log.exists()) {
        log.mkpath(logDir);
    }

    //安装日志钩子,输出调试信息到文件,便于调试
#if (QT_VERSION <= QT_VERSION_CHECK(5,0,0))
    qInstallMsgHandler(Log);
#else
    qInstallMessageHandler(Log);
#endif
}

