#ifndef ZOOMSCROLLTRACK_H
#define ZOOMSCROLLTRACK_H

#include <QDialog>
#include <QScrollBar>
#include "qchartviewer.h"

class ZoomScrollTrack : public QDialog {
    Q_OBJECT
public:
    ZoomScrollTrack(QWidget *parent = 0);
    ~ZoomScrollTrack();

private:
    //
    // Data arrays for the scrollable / zoomable chart.
    // - In this demo, we just use a RanTable object to generate random data for the chart.
    //
    RanSeries *m_ranSeries;
    DoubleArray m_timeStamps;
    DoubleArray m_dataSeriesA;
    DoubleArray m_dataSeriesB;
    DoubleArray m_dataSeriesC;

    QScrollBar *m_HScrollBar;
    QChartViewer *m_ChartViewer;

    void loadData();                                // Load data into data arrays
    void initChartViewer(QChartViewer *viewer);     // Initialize the QChartViewer
    void drawChart(QChartViewer *viewer);           // Draw chart
    void trackLineLegend(XYChart *c, int mouseX);   // Draw Track Cursor
    void updateControls(QChartViewer *viewer);      // Update other controls

private slots:
    void onHScrollBarChanged(int value);
    void onMouseUsageChanged(int mouseUsage);
    void onViewPortChanged();
    void onMouseMovePlotArea(QMouseEvent *event);
    void onMouseWheelChart(QWheelEvent *event);
};

#endif // ZOOMSCROLLTRACK_H
