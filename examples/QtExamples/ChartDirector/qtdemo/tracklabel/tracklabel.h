#ifndef TRACKLABEL_H
#define TRACKLABEL_H

#include <QDialog>
#include "qchartviewer.h"


class TrackLabel : public QDialog {
    Q_OBJECT
public:
    TrackLabel(QWidget *parent = 0);
    ~TrackLabel();

private:
    QChartViewer *m_ChartViewer;

    void drawChart(QChartViewer *viewer);           // Draw chart
    void trackLineLabel(XYChart *c, int mouseX);    // Draw Track Cursor

private slots:
    void onMouseMovePlotArea(QMouseEvent *event);
};

#endif // TRACKLABEL_H
