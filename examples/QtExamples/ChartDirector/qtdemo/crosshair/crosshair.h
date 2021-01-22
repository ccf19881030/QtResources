#ifndef CROSSHAIR_H
#define CROSSHAIR_H

#include <QDialog>
#include "qchartviewer.h"


class CrossHair : public QDialog {
    Q_OBJECT
public:
    CrossHair(QWidget *parent = 0);
    ~CrossHair();

private:
    QChartViewer *m_ChartViewer;

    void drawChart(QChartViewer *viewer);                  // Draw chart
    void crosshair(XYChart *c, int mouseX, int mouseY);    // Draw Track Cursor

private slots:
    void onMouseMovePlotArea(QMouseEvent *event);
};

#endif // CROSSHAIR_H
