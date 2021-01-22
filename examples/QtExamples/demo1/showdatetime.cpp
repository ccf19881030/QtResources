#include "showdatetime.h"
#include <QTimer>
#include <QLabel>
#include <QDateTime>
#include <QLCDNumber>

#define DATETIME qPrintable (QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss"))

ShowDateTime::ShowDateTime(QObject *parent) : QObject(parent)
{
    labDateTime = 0;
    labLive = 0;
    lcdNumber = 0;

    day = 0;
    hour = 0;
    minute = 0;
    seconds = 0;

    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(ShowTime()));
}

ShowDateTime::~ShowDateTime()
{

}

void ShowDateTime::SetLab(QLabel *labDateTime, QLabel *labLive)
{
    this->labDateTime = labDateTime;
    this->labLive = labLive;
    this->SetTimeInfo();
}

void ShowDateTime::SetLcdNumber(QLCDNumber *lcdNumber)
{
    this->lcdNumber = lcdNumber;
    this->SetTimeInfo();
}

void ShowDateTime::Start(int interval)
{
    timer->start(interval);
}

void ShowDateTime::Stop()
{
    timer->stop();
}

void ShowDateTime::ShowTime()
{
    seconds++;
    if (seconds == 60) {
        minute++;
        seconds = 0;
    }
    if (minute == 60) {
        hour++;
        minute = 0;
    }
    if (hour == 24) {
        day++;
        hour = 0;
    }

    SetTimeInfo();
}

void ShowDateTime::SetTimeInfo()
{
    this->labLive->setText(QString("已运行 : %1天%2时%3分%4秒  |  ").arg(day).arg(hour).arg(minute).arg(seconds));
    this->labDateTime->setText(QDateTime::currentDateTime().toString("当前时间 : yyyy年MM月dd日 HH:mm:ss  "));
    if (lcdNumber != 0) {
        lcdNumber->display(DATETIME);
    }
}
