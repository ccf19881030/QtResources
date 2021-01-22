#ifndef TRACKBOX_H
#define TRACKBOX_H

#include <QDialog>
#include "qchartviewer.h"


class TrackBox : public QDialog {
    Q_OBJECT
public:
    TrackBox(QWidget *parent = 0);
    ~TrackBox();

private:
    QChartViewer *m_ChartViewer;

    void drawChart(QChartViewer *viewer);                       // Draw chart
    void trackBoxLegend(XYChart *c, int mouseX, int mouseY);    // Draw Track Cursor

private slots:
    void onMouseMovePlotArea(QMouseEvent *event);
};

#endif // TRACKBOX_H
