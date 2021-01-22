// realtimesweepDlg.h : header file
//

#pragma once


#include "afxwin.h"
#include "ChartViewer.h"
#include "doublebufferedqueue.h"


// Forward declaration
class RandomWave;


// CrealtimesweepDlg dialog
class CrealtimesweepDlg : public CDialog
{
// Construction
public:
	CrealtimesweepDlg(CWnd* pParent = NULL);	// standard constructor
	~CrealtimesweepDlg();

// Dialog Data
	enum { IDD = IDD_REALTIMESWEEP_DIALOG };
	CChartViewer m_ChartViewer;

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnViewPortChanged();

	DECLARE_MESSAGE_MAP()

private:

	// The random data source 
	RandomWave *dataSource;

	// Handles callback from the RandomWalk
	static void OnData(void *self, double elapsedTime, double series0, double series1);

	// A thread-safe queue with minimal read/write contention
	struct DataPacket
	{
		double elapsedTime;
		double series0;
		double series1;
	};
	DoubleBufferedQueue<DataPacket> buffer;

	// Handles timer events for updating the chart
    static const int ChartUpdateTimer = 1;
	void OnChartUpdateTimer();

	// The number of samples per data series used in this demo
	static const int sampleSize = 10000;

	// The time range of the sweep chart
    static const int timeRange = 60;

	double m_timeStamps[sampleSize];	// The timestamps for the data series
	double m_channel1[sampleSize];	    // The values for the channel 1
	double m_channel2[sampleSize];	    // The values for the channel 2

    // The index of the array position to which new data values are added.
    int m_currentIndex;

	// Draw chart
	void drawChart(CChartViewer *viewer);
public:
    afx_msg void OnSize(UINT nType, int cx, int cy);
};
