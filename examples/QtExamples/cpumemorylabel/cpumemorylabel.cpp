#pragma execution_character_set("utf-8")

#include "cpumemorylabel.h"
#include "qtimer.h"
#include "qprocess.h"

#ifdef Q_OS_WIN
#ifndef _WIN32_WINNT
#define _WIN32_WINNT 0x502
#endif
#include "windows.h"
#endif
#define MB (1024 * 1024)
#define KB (1024)

CpuMemoryLabel::CpuMemoryLabel(QWidget *parent) : QLabel(parent)
{
    totalNew = idleNew = totalOld = idleOld = 0;
    cpuPercent = 0;

    memoryPercent = 0;
    memoryAll = 0;
    memoryUse = 0;

    timerCPU = new QTimer(this);
    connect(timerCPU, SIGNAL(timeout()), this, SLOT(getCPU()));

    timerMemory = new QTimer(this);
    connect(timerMemory, SIGNAL(timeout()), this, SLOT(getMemory()));

    process = new QProcess(this);
    connect(process, SIGNAL(readyRead()), this, SLOT(readData()));
}

CpuMemoryLabel::~CpuMemoryLabel()
{
    stop();
}

void CpuMemoryLabel::start(int interval)
{
    getCPU();
    getMemory();
    timerCPU->start(interval);
    timerMemory->start(interval + 200);
}

void CpuMemoryLabel::stop()
{
    timerCPU->stop();
    timerMemory->stop();
}

void CpuMemoryLabel::getCPU()
{
#ifdef Q_OS_WIN
    static FILETIME preidleTime;
    static FILETIME prekernelTime;
    static FILETIME preuserTime;

    FILETIME idleTime;
    FILETIME kernelTime;
    FILETIME userTime;

    GetSystemTimes(&idleTime, &kernelTime, &userTime);

    quint64 a, b;
    int idle, kernel, user;

    a = (preidleTime.dwHighDateTime << 31) | preidleTime.dwLowDateTime;
    b = (idleTime.dwHighDateTime << 31) | idleTime.dwLowDateTime;
    idle = b - a;

    a = (prekernelTime.dwHighDateTime << 31) | prekernelTime.dwLowDateTime;
    b = (kernelTime.dwHighDateTime << 31) | kernelTime.dwLowDateTime;
    kernel = b - a;

    a = (preuserTime.dwHighDateTime << 31) | preuserTime.dwLowDateTime;
    b = (userTime.dwHighDateTime << 31) | userTime.dwLowDateTime;
    user = b - a;

    cpuPercent = (kernel + user - idle) * 100 / (kernel + user);

    preidleTime = idleTime;
    prekernelTime = kernelTime;
    preuserTime = userTime ;

    setData();
#else

    if (process->state() == QProcess::NotRunning) {
        totalNew = idleNew = 0;
        process->start("cat /proc/stat");
    }

#endif
}

void CpuMemoryLabel::getMemory()
{
#ifdef Q_OS_WIN
    MEMORYSTATUSEX statex;
    statex.dwLength = sizeof(statex);
    GlobalMemoryStatusEx(&statex);
    memoryPercent = statex.dwMemoryLoad;
    memoryAll = statex.ullTotalPhys / MB;
    memoryFree = statex.ullAvailPhys / MB;
    memoryUse = memoryAll - memoryFree;

    setData();
#else

    if (process->state() == QProcess::NotRunning) {
        process->start("cat /proc/meminfo");
    }

#endif
}

void CpuMemoryLabel::readData()
{
    while (!process->atEnd()) {
        QString s = QLatin1String(process->readLine());

        if (s.startsWith("cpu")) {
            QStringList list = s.split(" ");
            idleNew = list.at(5).toInt();

            foreach (QString value, list) {
                totalNew += value.toInt();
            }

            int total = totalNew - totalOld;
            int idle = idleNew - idleOld;
            cpuPercent = 100 * (total - idle) / total;
            totalOld = totalNew;
            idleOld = idleNew;
            break;
        } else if (s.startsWith("MemTotal")) {
            s = s.replace(" ", "");
            s = s.split(":").at(1);
            memoryAll = s.left(s.length() - 3).toInt() / KB;
        } else if (s.startsWith("MemFree")) {
            s = s.replace(" ", "");
            s = s.split(":").at(1);
            memoryFree = s.left(s.length() - 3).toInt() / KB;
        } else if (s.startsWith("Buffers")) {
            s = s.replace(" ", "");
            s = s.split(":").at(1);
            memoryFree += s.left(s.length() - 3).toInt() / KB;
        } else if (s.startsWith("Cached")) {
            s = s.replace(" ", "");
            s = s.split(":").at(1);
            memoryFree += s.left(s.length() - 3).toInt() / KB;
            memoryUse = memoryAll - memoryFree;
            memoryPercent = 100 * memoryUse / memoryAll;
            break;
        }
    }

    setData();
}

void CpuMemoryLabel::setData()
{
    cpuPercent = (cpuPercent < 0 ? 0 : cpuPercent);

    QString msg = QString("CPU %1%  Mem %2% ( 已用 %3 MB / 共 %4 MB )")
                  .arg(cpuPercent).arg(memoryPercent).arg(memoryUse).arg(memoryAll);
    this->setText(msg);
    emit textChanged(msg);
    emit valueChanged(cpuPercent, memoryPercent, memoryAll, memoryUse, memoryFree);
}

QSize CpuMemoryLabel::sizeHint() const
{
    return QSize(300, 30);
}

QSize CpuMemoryLabel::minimumSizeHint() const
{
    return QSize(30, 10);
}
