// trackfinanceDlg.h : header file
//

#pragma once

#include "ChartViewer.h"


// CtrackfinanceDlg dialog
class CtrackfinanceDlg : public CDialog
{
// Construction
public:
	CtrackfinanceDlg(CWnd* pParent = NULL);	// standard constructor
	~CtrackfinanceDlg();

// Dialog Data
	enum { IDD = IDD_TRACKFINANCE_DIALOG };

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
	void trackFinance(MultiChart *m, int mouseX);
};
