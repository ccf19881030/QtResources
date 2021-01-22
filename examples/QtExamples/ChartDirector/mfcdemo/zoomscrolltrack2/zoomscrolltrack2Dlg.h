// zoomscrolltrack2Dlg.h : header file
//

#pragma once

#include "ChartViewer.h"
#include <afxmt.h>
#include "afxdtctl.h"


// CZoomscrolltrack2Dlg dialog
class CZoomscrolltrack2Dlg : public CDialog
{
// Construction
public:
	CZoomscrolltrack2Dlg(CWnd* pParent = NULL);	// standard constructor
	~CZoomscrolltrack2Dlg();

// Dialog Data
	enum { IDD = IDD_ZOOMSCROLLTRACK2_DIALOG };
	CButton m_PointerPB;
	CDateTimeCtrl m_StartDate;
	CDateTimeCtrl m_EndDate;
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
	afx_msg void OnStartDateChanged(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnEndDateChanged(NMHDR* pNMHDR, LRESULT* pResult);
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
    void trackLineLabel(XYChart *c, int mouseX);

	// Moves the scroll bar when the user clicks on it
	double moveScrollBar(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);

	// Update controls when the view port changed
    void updateControls(CChartViewer *viewer);

	// utility to load icon resource to a button
	void loadButtonIcon(int buttonId, int iconId, int width, int height);
};
