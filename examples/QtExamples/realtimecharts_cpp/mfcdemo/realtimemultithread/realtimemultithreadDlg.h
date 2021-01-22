// realtimemultithreadDlg.h : header file
//

#pragma once


#include "afxwin.h"
#include "ChartViewer.h"
#include "doublebufferedqueue.h"


// Forward declaration
class RandomWalk;


// CRealtimemultithreadDlg dialog
class CRealtimemultithreadDlg : public CDialog
{
// Construction
public:
	CRealtimemultithreadDlg(CWnd* pParent = NULL);	// standard constructor
	~CRealtimemultithreadDlg();

// Dialog Data
	enum { IDD = IDD_REALTIMEMULTITHREAD_DIALOG };
	CButton m_PointerPB;
	CChartViewer m_ChartViewer;
	CScrollBar m_HScrollBar;

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
	afx_msg void OnMouseMovePlotArea();
	afx_msg void OnPointerPB();
	afx_msg void OnZoomInPB();
	afx_msg void OnZoomOutPB();
	afx_msg void OnSavePB();
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);

	DECLARE_MESSAGE_MAP()

private:

	// The random data source 
	RandomWalk *dataSource;

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

	// The initial full range is set to 60 seconds of data.
    static const int initialFullRange = 60;

	// The maximum zoom in is 5 seconds.
    static const int zoomInLimit = 5;

    // If the track cursor is at the end of the data series, we will automatic move the track 
	// line when new data arrives.
    double trackLineEndPos;
    bool trackLineIsAtEnd;

	double m_timeStamps[sampleSize];	// The timestamps for the data series
	double m_dataSeriesA[sampleSize];	// The values for the data series A
	double m_dataSeriesB[sampleSize];	// The values for the data series B

    // The index of the array position to which new data values are added.
    int m_currentIndex;

	// Draw chart
	void drawChart(CChartViewer *viewer);
	double trackLineLabel(XYChart *c, int mouseX);
	
	// Update controls when the view port changed
	void updateControls(CChartViewer *viewer);
	// Moves the scroll bar when the user clicks on it
	double moveScrollBar(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);

	// utility to load icon resource to a button
	void loadButtonIcon(int buttonId, int iconId, int width, int height);
};
