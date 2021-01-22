#ifndef SIMPLEZOOMSCROLL_H
#define SIMPLEZOOMSCROLL_H

#include <QDialog>
#include "qchartviewer.h"

class SimpleZoomScroll : public QDialog {
    Q_OBJECT
public:
    SimpleZoomScroll(QWidget *parent = 0);
    ~SimpleZoomScroll();

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

    QChartViewer *m_ChartViewer;

    void loadData();                                // Load data into data arrays
    void initChartViewer(QChartViewer *viewer);     // Initialize the QChartViewer
    void drawChart(QChartViewer *viewer);           // Draw chart
    void updateImageMap(QChartViewer *viewer);      // Update the image map

private slots:
    void onMouseUsageChanged(int mouseUsage);
    void onViewPortChanged();
};

#endif // SIMPLEZOOMSCROLL_H
