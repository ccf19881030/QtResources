#ifndef XYZOOMSCROLL_H
#define XYZOOMSCROLL_H

#include <QDialog>
#include <QSlider>
#include <QTimer>
#include <QPushButton>
#include "qchartviewer.h"
#include <vector>


class XYZoomScroll : public QDialog {
    Q_OBJECT
public:
    XYZoomScroll(QWidget *parent = 0);
    ~XYZoomScroll();

private:

    // Data arrays for the scrollable / zoomable chart.
    std::vector<double> dataX0;
    std::vector<double> dataY0;
    std::vector<double> dataX1;
    std::vector<double> dataY1;
    std::vector<double> dataX2;
    std::vector<double> dataY2;

    // The widgets in this demo
    QSlider *m_ZoomBar;
    QChartViewer *m_ChartViewer;
    QViewPortControl *m_ViewPortControl;

    // Load data into data arrays
    void loadData();

    // Draw chart
    void drawChart(QChartViewer *viewer);
    void drawFullChart(QViewPortControl *vpc, QChartViewer *viewer);
    void crossHair(XYChart *c, int mouseX, int mouseY);

    // Update image map
    void updateImageMap(QChartViewer *viewer);
    // Update other controls when viewport changed
    void updateControls(QChartViewer *viewer);

    // utility to convert std::vector to a DoubleArray
    DoubleArray vectorToArray(std::vector<double> &v);

private slots:
    void onMouseUsageChanged(int mouseUsage);
    void onSave(bool);
    void onZoomBarChanged(int value);
    void onMouseMovePlotArea(QMouseEvent *event);
    void onViewPortChanged();
    void onClickChart(QMouseEvent *event);
};

#endif // XYZOOMSCROLL_H
