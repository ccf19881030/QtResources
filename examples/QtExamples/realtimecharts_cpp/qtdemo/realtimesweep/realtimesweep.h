#ifndef RealTimeSweep_H
#define RealTimeSweep_H

#include <QDialog>
#include <QDateTime>
#include <QTimer>
#include <QLabel>
#include "qchartviewer.h"
#include "qdoublebufferedqueue.h"
#include "randomwave.h"


class RealTimeSweep : public QDialog {
    Q_OBJECT
public:
    RealTimeSweep(QWidget *parent = 0);
    ~RealTimeSweep();

private:

    // The random data source
    RandomWave *dataSource;

    // Handles callback from the RandomWalk
    static void OnData(void *self, double elapsedTime, double series0, double series1);

    // A thread-safe queue with minimal read/write contention
    struct DataPacket
    {
        double elapsedTime;
        double series0;
        double series1;
    };
    QDoubleBufferedQueue<DataPacket> buffer;

    // The number of samples per data series used in this demo
    static const int sampleSize = 10000;

    // The time range of the sweep chart
    static const int timeRange = 60;

    double m_timeStamps[sampleSize];	// The timestamps for the data series
    double m_channel1[sampleSize];	// The values for the data series A
    double m_channel2[sampleSize];	// The values for the data series B

    int m_currentIndex;                 // Index of the array position to which new values are added.

    QChartViewer *m_ChartViewer;        // QChartViewer control
    QTimer *m_ChartUpdateTimer;         // The chart update timer

    void drawChart(QChartViewer *viewer);           // Draw chart
    void resizeEvent(QResizeEvent *e);              // Handle resize event

private slots:
    void onChartUpdateTimer();                      // Update the chart.
    void onViewPortChanged();                       // Viewport has changed

};

#endif // RealTimeMultiThread_H

