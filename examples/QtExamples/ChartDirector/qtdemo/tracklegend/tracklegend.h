#ifndef TRACKLEGEND_H
#define TRACKLEGEND_H

#include <QDialog>
#include "qchartviewer.h"


class TrackLegend : public QDialog {
    Q_OBJECT
public:
    TrackLegend(QWidget *parent = 0);
    ~TrackLegend();

private:
    QChartViewer *m_ChartViewer;

    void drawChart(QChartViewer *viewer);           // Draw chart
    void trackLineLegend(XYChart *c, int mouseX);   // Draw Track Cursor

private slots:
    void onMouseMovePlotArea(QMouseEvent *event);
};

#endif // TRACKLEGEND_H
