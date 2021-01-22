#ifndef REALTIMETRACK_H
#define REALTIMETRACK_H

#include <QDialog>
#include <QDateTime>
#include <QTimer>
#include <QLabel>
#include "qchartviewer.h"

// The number of samples per data series used in this demo
const int sampleSize = 240;

class RealtimeTrack : public QDialog {
    Q_OBJECT
public:
    RealtimeTrack(QWidget *parent = 0);
    ~RealtimeTrack();

private:
    int m_currentIndex;                 // Index of the array position to which new values are added.

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

    void trackLineLegend(XYChart *c, int mouseX);   // Draw Track Cursor

private slots:
    void onRunFreezeChanged(int);                   // The "Run" or "Freeze" button has been pressed
    void onUpdatePeriodChanged(QString);            // The chart update timer interval has changed.
    void onMouseMovePlotArea(QMouseEvent *event);   // Mouse move on plot area
    void getData();                                 // Get new data values
    void updateChart();                             // Update the chart.
    void drawChart();                               // Draw chart

};

#endif // REALTIMETRACK_H
