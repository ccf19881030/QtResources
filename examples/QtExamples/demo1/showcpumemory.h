#ifndef SHOWCPUMEMORY_H
#define SHOWCPUMEMORY_H

#include <QObject>

class QLabel;
class QTimer;
class QProcess;

class ShowCPUMemory : public QObject
{
    Q_OBJECT
public:
    explicit ShowCPUMemory(QObject *parent = 0);

    void SetLab(QLabel *labCPUMemory);
    void Start(int interval);
    void Stop();

private:
    int totalNew, idleNew, totalOld, idleOld;
    int cpuPercent;

    int memoryPercent;
    int memoryAll;
    int memoryUse;
    int memoryFree;

    QTimer *timerCPU;       //定时器获取CPU信息
    QTimer *timerMemory;    //定时器获取内存信息
    QLabel *labCPUMemory;   //显示CPU内存信息的控件
    QProcess *process;

private slots:
    void GetCPU();
    void GetMemory();
    void ReadData();

signals:

public slots:
};

#endif // SHOWCPUMEMORY_H
