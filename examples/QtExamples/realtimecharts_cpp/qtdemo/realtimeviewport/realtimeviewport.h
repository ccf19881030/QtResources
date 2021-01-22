#ifndef RealTimeViewPort_H
#define RealTimeViewPort_H

#include <QDialog>
#include <QDateTime>
#include <QTimer>
#include <QLabel>
#include <QScrollbar>
#include "qchartviewer.h"
#include "qdoublebufferedqueue.h"
#include "randomwalk.h"


class RealTimeViewPort : public QDialog {
    Q_OBJECT
public:
    RealTimeViewPort(QWidget *parent = 0);
    ~RealTimeViewPort();

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

    // The full range is initialized to 180 seconds. It will extend when more data are available.
    static const int initialFullRange = 180;

    // The visible range is initialized to 30 seconds.
    static const int initialVisibleRange = 30;

    // The maximum zoom in is 5 seconds.
    static const int zoomInLimit = 5;

    // If the track cursor is at the end of the data series, we will automatic move the track
    // line when new data arrives.
    double trackLineEndPos;
    bool trackLineIsAtEnd;

    double m_timeStamps[sampleSize];        // The timestamps for the data series
    double m_dataSeriesA[sampleSize];       // The values for the data series A
    double m_dataSeriesB[sampleSize];       // The values for the data series B

    int m_currentIndex;                     // Index of the array position to which new values are added.

    QChartViewer *m_ChartViewer;            // QChartViewer control
    QViewPortControl *m_ViewPortControl;    // QViewPortControl
    QTimer *m_ChartUpdateTimer;             // The chart update timer

    void drawChart(QChartViewer *viewer);           // Draw chart
    void drawFullChart(QViewPortControl *vpc);      // Draw full chart
    double trackLineLabel(XYChart *c, int mouseX);  // Draw track cursor

private slots:
    void onMouseUsageChanged(int mouseUsage);       // Pointer/zoom in/zoom out button clicked
    void onSave(bool);                              // Save button clicked
    void onMouseMovePlotArea(QMouseEvent *event);   // Mouse move on plot area
    void onChartUpdateTimer();                      // Update the chart.
    void onViewPortChanged();                       // Viewport has changed
};

#endif // RealTimeViewPort_H

