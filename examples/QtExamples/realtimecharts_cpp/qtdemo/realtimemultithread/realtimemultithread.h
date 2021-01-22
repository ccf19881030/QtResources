#ifndef RealTimeMultiThread_H
#define RealTimeMultiThread_H

#include <QDialog>
#include <QDateTime>
#include <QTimer>
#include <QLabel>
#include <QScrollbar>
#include "qchartviewer.h"
#include "qdoublebufferedqueue.h"
#include "randomwalk.h"


class RealTimeMultiThread : public QDialog {
    Q_OBJECT
public:
    RealTimeMultiThread(QWidget *parent = 0);
    ~RealTimeMultiThread();

private:

    // The random data source
    RandomWalk *dataSource;

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

    // The initial full range is set to 60 seconds of data.
    static const int initialFullRange = 60;

    // The maximum zoom in is 5 seconds.
    static const int zoomInLimit = 5;

    // If the track cursor is at the end of the data series, we will automatic move the track
    // line when new data arrives.
    double trackLineEndPos;
    bool trackLineIsAtEnd;

    double m_timeStamps[sampleSize];	// The timestamps for the data series
    double m_dataSeriesA[sampleSize];	// The values for the data series A
    double m_dataSeriesB[sampleSize];	// The values for the data series B

    int m_currentIndex;                 // Index of the array position to which new values are added.

    QChartViewer *m_ChartViewer;        // QChartViewer control
    QTimer *m_ChartUpdateTimer;         // The chart update timer
    QScrollBar *m_HScrollBar;           // The scroll bar

    void drawChart(QChartViewer *viewer);           // Draw chart
    double trackLineLabel(XYChart *c, int mouseX);    // Draw track cursor
    void updateControls(QChartViewer *viewer);      // Update other controls as viewport changes

private slots:
    void onMouseUsageChanged(int mouseUsage);       // Pointer/zoom in/zoom out button clicked
    void onSave(bool);                              // Save button clicked
    void onMouseMovePlotArea(QMouseEvent *event);   // Mouse move on plot area
    void onChartUpdateTimer();                      // Update the chart.
    void onViewPortChanged();                       // Viewport has changed
    void onHScrollBarChanged(int value);            // Scrollbar changed
};

#endif // RealTimeMultiThread_H

