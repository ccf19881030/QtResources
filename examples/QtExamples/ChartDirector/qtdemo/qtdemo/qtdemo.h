#ifndef QTDEMO_H
#define QTDEMO_H

#include <QDialog>
#include "qchartviewer.h"

const int noOfChartViewers = 8;

class QTDemo : public QDialog {
    Q_OBJECT
public:
    QTDemo(QWidget *parent = 0);

protected:
    void resizeEvent(QResizeEvent * event);
    void flowLayoutCharts();

private:
    QChartViewer *chartViewers[noOfChartViewers];

private slots:
    void onSelectionChanged();
    void onChartClicked(QMouseEvent *event);
};

#endif // QTDEMO_H
