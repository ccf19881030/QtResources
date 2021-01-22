#ifndef RealTimeZoomScroll_H
#define RealTimeZoomScroll_H

#include <QDialog>
#include <QDateTime>
#include <QTimer>
#include <QLabel>
#include <QScrollBar>
#include "qchartviewer.h"


class RealTimeZoomScroll : public QDialog {
    Q_OBJECT
public:
    RealTimeZoomScroll(QWidget *parent = 0);
    ~RealTimeZoomScroll();

private:
    // The number of samples per data series used in this demo
    static const int sampleSize = 10000;

    // The initial full range is set to 60 seconds of data.
    static const int initialFullRange = 60;

    // The maximum zoom in is 10 seconds.
    static const int zoomInLimit = 10;

    double m_timeStamps[sampleSize];	// The timestamps for the data series
    double m_dataSeriesA[sampleSize];	// The values for the data series A
    double m_dataSeriesB[sampleSize];	// The values for the data series B
    double m_dataSeriesC[sampleSize];	// The values for the data series C

    int m_currentIndex;                 // Index of the array position to which new values are added.

    QDateTime m_nextDataTime;           // Used by the random number generator to generate realtime data.

    QLabel *m_ValueA;                   // Label to display the realtime value A
    QLabel *m_ValueB;                   // Label to display the realtime value B
    QLabel *m_ValueC;                   // Label to display the realtime value C

    QChartViewer *m_ChartViewer;        // QChartViewer control
    QTimer *m_ChartUpdateTimer;         // The chart update timer
    QScrollBar *m_HScrollBar;           // The scroll bar

    void drawChart(QChartViewer *viewer);           // Draw chart
    void trackLineLabel(XYChart *c, int mouseX);    // Draw track cursor
    void updateControls(QChartViewer *viewer);      // Update other controls as viewport changes

private slots:
    void onMouseUsageChanged(int mouseUsage);       // Pointer/zoom in/zoom out button clicked
    void onSave(bool);                              // Save button clicked
    void onUpdatePeriodChanged(QString);            // The chart update timer interval has changed.
    void onMouseMovePlotArea(QMouseEvent *event);   // Mouse move on plot area
    void onDataTimer();                             // Get new data values
    void onChartUpdateTimer();                      // Update the chart.
    void onViewPortChanged();                       // Viewport has changed
    void onHScrollBarChanged(int value);            // Scrollbar changed
};

#endif // RealTimeZoomScroll_H
