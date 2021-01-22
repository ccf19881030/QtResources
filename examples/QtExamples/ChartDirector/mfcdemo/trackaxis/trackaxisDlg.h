// trackaxisDlg.h : header file
//

#pragma once

#include "ChartViewer.h"


// CtrackaxisDlg dialog
class CtrackaxisDlg : public CDialog
{
// Construction
public:
	CtrackaxisDlg(CWnd* pParent = NULL);	// standard constructor
	~CtrackaxisDlg();

// Dialog Data
	enum { IDD = IDD_TRACKAXIS_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnMouseMovePlotArea();
	DECLARE_MESSAGE_MAP()


private:
	CChartViewer m_ChartViewer;
	void drawChart(CChartViewer *viewer);
	void trackLineAxis(XYChart *c, int mouseX);
};
