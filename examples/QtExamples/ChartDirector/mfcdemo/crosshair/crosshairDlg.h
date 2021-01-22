// crosshairDlg.h : header file
//

#pragma once

#include "ChartViewer.h"


// CcrosshairDlg dialog
class CcrosshairDlg : public CDialog
{
// Construction
public:
	CcrosshairDlg(CWnd* pParent = NULL);	// standard constructor
	~CcrosshairDlg();

// Dialog Data
	enum { IDD = IDD_CROSSHAIR_DIALOG };

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
	void crosshair(XYChart *c, int mouseX, int mouseY);
};
