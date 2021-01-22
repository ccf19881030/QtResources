#include "showcpumemory.h"
#include <QTimer>
#include <QProcess>
#include <QLabel>

#ifdef Q_OS_WIN
#include "windows.h"
#endif
#define MB (1024 * 1024)
#define KB (1024)

ShowCPUMemory::ShowCPUMemory(QObject *parent) : QObject(parent)
{
    totalNew = idleNew = totalOld = idleOld = 0;
    cpuPercent = 0;

    memoryPercent = 0;
    memoryAll = 0;
    memoryUse = 0;
    labCPUMemory = 0;

    timerCPU = new QTimer(this);
    connect(timerCPU, SIGNAL(timeout()), this, SLOT(GetCPU()));

    timerMemory = new QTimer(this);
    connect(timerMemory, SIGNAL(timeout()), this, SLOT(GetMemory()));

    process = new QProcess(this);
    connect(process, SIGNAL(readyRead()), this, SLOT(ReadData()));
}

void ShowCPUMemory::SetLab(QLabel *labCPUMemory)
{
    this->labCPUMemory = labCPUMemory;
    GetCPU();    
    GetMemory();
}

void ShowCPUMemory::Start(int interval)
{
    timerCPU->start(interval);
    timerMemory->start(interval + 200);
}

void ShowCPUMemory::Stop()
{
    timerCPU->stop();
    timerMemory->stop();
}

void ShowCPUMemory::GetCPU()
{
#ifdef Q_OS_WIN
#if (QT_VERSION >= QT_VERSION_CHECK(4,8,7))

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
    idle = b -a;

    a = (prekernelTime.dwHighDateTime << 31) | prekernelTime.dwLowDateTime;
    b = (kernelTime.dwHighDateTime << 31) | kernelTime.dwLowDateTime;
    kernel = b -a;

    a = (preuserTime.dwHighDateTime << 31) | preuserTime.dwLowDateTime;
    b = (userTime.dwHighDateTime << 31) | userTime.dwLowDateTime;
    user = b -a;

    cpuPercent = (kernel + user - idle) * 100 / (kernel + user);

    preidleTime = idleTime;
    prekernelTime = kernelTime;
    preuserTime = userTime ;

    QString msg = QString("CPU : %1%  内存 : %2% ( 已用 %3 MB / 共 %4 MB )")
                  .arg(cpuPercent).arg(memoryPercent).arg(memoryUse).arg(memoryAll);
    labCPUMemory->setText(msg);
#endif
#else
    if (process->state() == QProcess::NotRunning) {
        totalNew = idleNew = 0;
        process->start("cat /proc/stat");
    }
#endif
}

void ShowCPUMemory::GetMemory()
{
#ifdef Q_OS_WIN
#if (QT_VERSION >= QT_VERSION_CHECK(4,8,7))
    MEMORYSTATUSEX statex;
    statex.dwLength = sizeof (statex);
    GlobalMemoryStatusEx(&statex);
    memoryPercent = statex.dwMemoryLoad;
    memoryAll = statex.ullTotalPhys / MB;
    memoryFree = statex.ullAvailPhys / MB;
    memoryUse = memoryAll - memoryFree;

    QString msg = QString("CPU : %1%  内存 : %2% ( 已用 %3 MB / 共 %4 MB )")
                  .arg(cpuPercent).arg(memoryPercent).arg(memoryUse).arg(memoryAll);
    labCPUMemory->setText(msg);    
#endif
#else
    if (process->state() == QProcess::NotRunning) {
        process->start("cat /proc/meminfo");
    }
#endif
}

void ShowCPUMemory::ReadData()
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

    QString msg = QString("CPU : %1%  内存 : %2% ( 已用 %3 MB / 共 %4 MB )")
                  .arg(cpuPercent).arg(memoryPercent).arg(memoryUse).arg(memoryAll);
    labCPUMemory->setText(msg);    
}
