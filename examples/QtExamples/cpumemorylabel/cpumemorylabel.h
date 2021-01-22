#ifndef CPUMEMORYLABEL_H
#define CPUMEMORYLABEL_H

/**
 * CPU内存显示控件 作者:feiyangqingyun(QQ:517216493) 2016-11-18
 * 1:实时显示当前CPU及内存使用情况,包括共多少内存已使用多少内存
 * 2:全平台通用,包括windows,linux,ARM
 */

#include <QLabel>

class QProcess;

#ifdef quc
#if (QT_VERSION < QT_VERSION_CHECK(5,7,0))
#include <QtDesigner/QDesignerExportWidget>
#else
#include <QtUiPlugin/QDesignerExportWidget>
#endif

class QDESIGNER_WIDGET_EXPORT CpuMemoryLabel : public QLabel
#else
class CpuMemoryLabel : public QLabel
#endif

{
	Q_OBJECT
public:
	CpuMemoryLabel(QWidget *parent = 0);
    ~CpuMemoryLabel();

private:
	int totalNew, idleNew, totalOld, idleOld;
	int cpuPercent;

	int memoryPercent;
	int memoryAll;
	int memoryUse;
	int memoryFree;

	QTimer *timerCPU;       //定时器获取CPU信息
	QTimer *timerMemory;    //定时器获取内存信息
	QProcess *process;      //linux执行命令

private slots:
	void getCPU();          //获取cpu
	void getMemory();       //获取内存
	void readData();        //读取数据
	void setData();         //设置数据

public:
    QSize sizeHint()                const;
    QSize minimumSizeHint()         const;

public Q_SLOTS:
	void start(int interval);
	void stop();

Q_SIGNALS:
	void textChanged(QString text);
	void valueChanged(int cpuPercent, int memoryPercent, int memoryAll, int memoryUse, int memoryFree);
};

#endif // CPUMEMORYLABEL_H
