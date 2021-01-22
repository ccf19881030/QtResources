#ifndef TRACKAXIS_H
#define TRACKAXIS_H

#include <QDialog>
#include "qchartviewer.h"


class TrackAxis : public QDialog {
    Q_OBJECT
public:
    TrackAxis(QWidget *parent = 0);
    ~TrackAxis();

private:
    QChartViewer *m_ChartViewer;

    void drawChart(QChartViewer *viewer);           // Draw chart
    void trackLineAxis(XYChart *c, int mouseX);     // Draw Track Cursor

private slots:
    void onMouseMovePlotArea(QMouseEvent *event);
};

#endif // TRACKAXIS_H
