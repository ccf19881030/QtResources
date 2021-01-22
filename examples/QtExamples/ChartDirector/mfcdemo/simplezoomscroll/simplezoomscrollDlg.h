// simplezoomscrollDlg.h : header file
//

#pragma once

#include "ChartViewer.h"
#include <afxmt.h>


// CSimplezoomscrollDlg dialog
class CSimplezoomscrollDlg : public CDialog
{
// Construction
public:
	CSimplezoomscrollDlg(CWnd* pParent = NULL);	// standard constructor
	~CSimplezoomscrollDlg();

// Dialog Data
	enum { IDD = IDD_SIMPLEZOOMSCROLL_DIALOG };
	CButton m_PointerPB;
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
	afx_msg void OnViewPortChanged();	
	DECLARE_MESSAGE_MAP()


private:
	int m_extBgColor;	// The default background color.

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
	void updateImageMap(CChartViewer *viewer);

	// utility to get default background color
	int getDefaultBgColor();
	// utility to load icon resource to a button
	void loadButtonIcon(int buttonId, int iconId, int width, int height);
};
