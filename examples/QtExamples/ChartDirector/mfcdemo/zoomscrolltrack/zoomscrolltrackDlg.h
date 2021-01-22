// zoomscrolltrackDlg.h : header file
//

#pragma once

#include "ChartViewer.h"
#include <afxmt.h>


// CZoomscrolltrackDlg dialog
class CZoomscrolltrackDlg : public CDialog
{
// Construction
public:
	CZoomscrolltrackDlg(CWnd* pParent = NULL);	// standard constructor
	~CZoomscrolltrackDlg();

// Dialog Data
	enum { IDD = IDD_ZOOMSCROLLTRACK_DIALOG };
	CButton m_PointerPB;
	CScrollBar m_HScrollBar;
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
	afx_msg void OnPointerPB();
	afx_msg void OnZoomInPB();
	afx_msg void OnZoomOutPB();
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
	afx_msg void OnViewPortChanged();	
	afx_msg void OnMouseMovePlotArea();
	DECLARE_MESSAGE_MAP()


private:
	//
	// Data arrays for the scrollable / zoomable chart.
	// - In this demo, we just use a RanSeries object to generate random data for the chart.
	//
	RanSeries *m_ranSeries;
	DoubleArray m_timeStamps;
	DoubleArray m_dataSeriesA;
	DoubleArray m_dataSeriesB;
	DoubleArray m_dataSeriesC;
	
 	// Load data into data arrays
	void loadData();
	
    // Initialize the CChartViewer
    void initChartViewer(CChartViewer *viewer);

	// Draw chart
	void drawChart(CChartViewer *viewer);
    void trackLineLegend(XYChart *c, int mouseX);

	// Moves the scroll bar when the user clicks on it
	double moveScrollBar(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);

	// Update controls when the view port changed
    void updateControls(CChartViewer *viewer);

	// utility to load icon resource to a button
	void loadButtonIcon(int buttonId, int iconId, int width, int height);
};
