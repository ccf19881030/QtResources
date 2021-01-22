// financedemoDlg.h : header file
//

#pragma once

#include "ChartViewer.h"


// CFinancedemoDlg dialog
class CFinancedemoDlg : public CDialog
{
// Construction
public:
	CFinancedemoDlg(CWnd* pParent = NULL);	// standard constructor
	virtual ~CFinancedemoDlg();

// Dialog Data
	enum { IDD = IDD_FINANCEDEMO_DIALOG };
	CEdit	m_TickerSymbol;
	CEdit	m_CompareWith;
	CComboBox	m_TimeRange;
	CComboBox	m_ChartSize;
	CButton	m_Volume;
	CButton	m_ParabolicSAR;
	CButton	m_LogScale;
	CButton	m_PercentageScale;
	CComboBox	m_ChartType;
	CComboBox	m_Band;
	CComboBox	m_AvgType1;
	CComboBox	m_AvgType2;
	CEdit	m_MovAvg1;
	CEdit	m_MovAvg2;
	CComboBox	m_Indicator1;
	CComboBox	m_Indicator2;
	CComboBox	m_Indicator3;
	CComboBox	m_Indicator4;
	CChartViewer	m_ChartViewer;

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	virtual void OnOK();


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnSelectChange();
	afx_msg void OnTextChange();
	DECLARE_MESSAGE_MAP()

	// The ticker symbol, timeStamps, volume, high, low, open and close data    
	CString m_tickerKey;
	double *m_timeStamps;	
	double *m_volData;
	double *m_highData;
	double *m_lowData;
	double *m_openData;
	double *m_closeData;
	int m_noOfPoints;

    // An extra data series to compare with the close data
	CString m_compareKey;
    double *m_compareData;
    int m_compareDataLen;

    // The resolution of the data in seconds. 1 day = 86400 seconds.
 	int m_resolution;
	
	// The moving average periods
	int m_avgPeriod1;
	int m_avgPeriod2;

	// Routines to get data into the data arrays
	virtual bool getData(const CString &ticker, double startDate, double endDate,
		int durationInDays, int extraPoints);
	virtual void get15MinData(const CString &ticker, double startDate, double endDate);
	virtual void getDailyData(const CString &ticker, double startDate, double endDate);
	virtual void getWeeklyData(const CString &ticker, double startDate, double endDate);
	virtual void getMonthlyData(const CString &ticker, double startDate, double endDate);

	// Utilities to aggregate data if the data source do not already have aggregated data
	virtual void convertDailyToWeeklyData();
	virtual void convertDailyToMonthlyData();
	virtual void aggregateData(ArrayMath &aggregator);

	// In the demo, we just use random numbers for data.
	virtual void generateRandomData(const CString &ticker, double startDate, double endDate, 
		int resolution);

	// Draw the chart
	virtual void drawChart(CChartViewer *viewer);
};
