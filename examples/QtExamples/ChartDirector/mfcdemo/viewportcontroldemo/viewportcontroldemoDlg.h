// viewportcontroldemoDlg.h : header file
//

#pragma once
#include "afxwin.h"
#include "ChartViewer.h"


// CViewportcontroldemoDlg dialog
class CViewportcontroldemoDlg : public CDialog
{
public:
	// Constructor and Destructor
	CViewportcontroldemoDlg(CWnd* pParent = NULL);
	~CViewportcontroldemoDlg();

	// Dialog Data
	enum { IDD = IDD_VIEWPORTCONTROLDEMO_DIALOG };
	CButton m_PointerPB;
	CChartViewer m_ChartViewer;
	CViewPortControl m_ViewPortControl;

protected:
	HICON m_hIcon;

	// DDX/DDV support
	virtual void DoDataExchange(CDataExchange* pDX);

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnPointerPB();
	afx_msg void OnZoomInPB();
	afx_msg void OnZoomOutPB();
	afx_msg void OnSavePB();
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
	void drawFullChart(CViewPortControl *vpc, CChartViewer *viewer);
    void trackLineLegend(XYChart *c, int mouseX);

	// utility to load icon resource to a button
	void loadButtonIcon(int buttonId, int iconId, int width, int height);
};
