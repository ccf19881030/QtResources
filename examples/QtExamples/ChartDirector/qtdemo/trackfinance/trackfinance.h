#ifndef TRACKFINANCE_H
#define TRACKFINANCE_H

#include <QDialog>
#include "qchartviewer.h"


class TrackFinance : public QDialog {
    Q_OBJECT
public:
    TrackFinance(QWidget *parent = 0);
    ~TrackFinance();

private:
    QChartViewer *m_ChartViewer;

    void drawChart(QChartViewer *viewer);            // Draw chart
    void trackFinance(MultiChart *m, int mouseX);    // Draw Track Cursor

private slots:
    void onMouseMovePlotArea(QMouseEvent *event);
};

#endif // TRACKFINANCE_H
