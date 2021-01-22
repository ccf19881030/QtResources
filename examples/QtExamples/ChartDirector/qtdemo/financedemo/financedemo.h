#ifndef FINANCEDEMO_H
#define FINANCEDEMO_H

#include <QDialog>
#include <QLineEdit>
#include <QComboBox>
#include <QCheckBox>
#include "qchartviewer.h"

class FinanceDemo : public QDialog
{
    Q_OBJECT
public:
    FinanceDemo(QWidget *parent = 0);
    ~FinanceDemo();

private:
    // TimeStamps, volume, high, low, open and close data
    QString m_tickerKey;
    double *m_timeStamps;
    double *m_volData;
    double *m_highData;
    double *m_lowData;
    double *m_openData;
    double *m_closeData;
    int m_noOfPoints;

    // An extra data series to compare with the close data
    QString m_compareKey;
    double *m_compareData;
    int m_compareDataLen;

    // The resolution of the data in seconds. 1 day = 86400 seconds.
    int m_resolution;

    // The moving average periods
    int m_avgPeriod1;
    int m_avgPeriod2;

    // Routines to get data into the data arrays
    virtual bool getData(const QString &ticker, QDateTime startDate, QDateTime endDate,
            int durationInDays, int extraPoints);
    virtual void get15MinData(const QString &ticker, QDateTime startDate, QDateTime endDate);
    virtual void getDailyData(const QString &ticker, QDateTime startDate, QDateTime endDate);
    virtual void getWeeklyData(const QString &ticker, QDateTime startDate, QDateTime endDate);
    virtual void getMonthlyData(const QString &ticker, QDateTime startDate, QDateTime endDate);

    // Utilities to aggregate data if the data source do not already have aggregated data
    virtual void convertDailyToWeeklyData();
    virtual void convertDailyToMonthlyData();
    virtual void aggregateData(ArrayMath &aggregator);

    // In the demo, we just use random numbers for data.
    virtual void generateRandomData(const QString &ticker, QDateTime startDate,
                                    QDateTime endDate, int resolution);

    // The user interface
    QLineEdit *m_TickerSymbol;
    QLineEdit *m_CompareWith;
    QComboBox *m_TimeRange;
    QComboBox *m_ChartSize;
    QCheckBox *m_VolumeBars;
    QCheckBox *m_ParabolicSAR;
    QCheckBox *m_LogScale;
    QCheckBox *m_PercentageScale;
    QComboBox *m_ChartType;
    QComboBox *m_PriceBand;
    QComboBox *m_AvgType1;
    QComboBox *m_AvgType2;
    QLineEdit *m_MovAvg1;
    QLineEdit *m_MovAvg2;
    QComboBox *m_Indicator1;
    QComboBox *m_Indicator2;
    QComboBox *m_Indicator3;
    QComboBox *m_Indicator4;
    QChartViewer *m_ChartViewer;

    virtual void drawChart(QChartViewer *viewer);

private slots:
    void onComboBoxChanged(int);
    void onCheckBoxChanged();
    void onLineEditChanged();
};

#endif // FINANCEDEMO_H
