// realtimeviewportDlg.h : header file
//

#pragma once


#include "afxwin.h"
#include "ChartViewer.h"
#include "doublebufferedqueue.h"


// Forward declaration
class RandomWalk;


// CRealtimeviewportDlg dialog
class CRealtimeviewportDlg : public CDialog
{
// Construction
public:
	CRealtimeviewportDlg(CWnd* pParent = NULL);	// standard constructor
	~CRealtimeviewportDlg();

// Dialog Data
	enum { IDD = IDD_realtimeviewport_DIALOG };
	CButton m_PointerPB;
	CChartViewer m_ChartViewer;
    CViewPortControl m_ViewPortControl;

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

	// The full range is initialized to 180 seconds. It will extend when more data are available.
    static const int initialFullRange = 180;

    // The visible range is initialized to 30 seconds.
    static const int initialVisibleRange = 30;

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
	void drawFullChart(CViewPortControl *vpc);
    double trackLineLabel(XYChart *c, int mouseX);
	
	// utility to load icon resource to a button
	void loadButtonIcon(int buttonId, int iconId, int width, int height);
};
