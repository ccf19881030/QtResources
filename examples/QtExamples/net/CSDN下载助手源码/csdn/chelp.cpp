#include "chelp.h"
#include <QDateTime>
#include <QMutexLocker>

CHelp::CHelp(QObject *parent) :
    QObject(parent)
{

}

void CHelp::setLog(const QString content)
{
    // 加锁
    QMutexLocker locker(&m_Mutex);

    // 输出的日志前面添加时间
    QString str;

    QDateTime dateTime = QDateTime::currentDateTime();

    str = dateTime.toString("hh:mm::s   ");
    g_pLineEdit->append(str + content);
}

QTextEdit* CHelp::g_pLineEdit;
QMutex CHelp::m_Mutex;
