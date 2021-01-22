// xyzoomscrollDlg.h : header file
//

#pragma once

#include "ChartViewer.h"
#include <afxmt.h>
#include <vector>


// CXyzoomscrollDlg dialog
class CXyzoomscrollDlg : public CDialog
{
public:
	// Constructor and Destructor
	CXyzoomscrollDlg(CWnd* pParent = NULL);
	~CXyzoomscrollDlg();

	// Dialog Data
	enum { IDD = IDD_XYZOOMSCROLL_DIALOG };
	CButton	m_CenterPB;
	CButton	m_PointerPB;
	CSliderCtrl	m_ZoomBar;
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
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnChartViewer();
	afx_msg void OnViewPortChanged();
	afx_msg void OnMouseMovePlotArea();
	DECLARE_MESSAGE_MAP()

private:
	// The default background color.
	int m_extBgColor;

	// Data arrays for the scrollable / zoomable chart.
	std::vector<double> dataX0;
	std::vector<double> dataY0;
	std::vector<double> dataX1;
	std::vector<double> dataY1;
	std::vector<double> dataX2;
	std::vector<double> dataY2;

	// Load data into data arrays
	void loadData();

	// Draw chart
	void drawChart(CChartViewer *viewer);
	void drawFullChart(CViewPortControl *vpc, CChartViewer *viewer);
	void crossHair(XYChart *c, int mouseX, int mouseY);

	// Update image map 
	void updateImageMap(CChartViewer *viewer);
	// Update other controls when viewport changed
	void updateControls(CChartViewer *viewer);
	
	// utility to get default background color
	int getDefaultBgColor();
	// utility to load icon resource to a button
	void loadButtonIcon(int buttonId, int iconId, int width, int height);
	// utility to convert std::vector to a DoubleArray
	DoubleArray vectorToArray(std::vector<double> &v);
};
