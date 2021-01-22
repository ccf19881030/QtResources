#ifndef REALTIMEDEMO_H
#define REALTIMEDEMO_H

#include <QDialog>
#include <QDateTime>
#include <QTimer>
#include <QLabel>
#include "qchartviewer.h"

// The number of samples per data series used in this demo
const int sampleSize = 240;

class RealtimeDemo : public QDialog {
    Q_OBJECT
public:
    RealtimeDemo(QWidget *parent = 0);

private:
    double m_timeStamps[sampleSize];	// The timestamps for the data series
    double m_dataSeriesA[sampleSize];	// The values for the data series A
    double m_dataSeriesB[sampleSize];	// The values for the data series B
    double m_dataSeriesC[sampleSize];	// The values for the data series C

    QDateTime m_nextDataTime;           // Used by the random number generator to generate realtime data.

    QLabel *m_ValueA;                   // Label to display the realtime value A
    QLabel *m_ValueB;                   // Label to display the realtime value B
    QLabel *m_ValueC;                   // Label to display the realtime value C

    QChartViewer *m_ChartViewer;        // QChartViewer control
    QTimer *m_ChartUpdateTimer;         // The chart update timer

private slots:
    void onRunFreezeChanged(int);       // The "Run" or "Freeze" button has been pressed
    void onUpdatePeriodChanged(QString);// The chart update timer interval has changed.
    void getData();                     // Get new data values
    void updateChart();                 // Update the chart.
    void drawChart();                   // Draw the chart.
};

#endif // REALTIMEDEMO_H
