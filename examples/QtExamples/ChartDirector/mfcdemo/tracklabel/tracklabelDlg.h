// tracklabelDlg.h : header file
//

#pragma once

#include "ChartViewer.h"


// CtracklabelDlg dialog
class CtracklabelDlg : public CDialog
{
// Construction
public:
	CtracklabelDlg(CWnd* pParent = NULL);	// standard constructor
	~CtracklabelDlg();

// Dialog Data
	enum { IDD = IDD_TRACKLABEL_DIALOG };

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
	void trackLineLabel(XYChart *c, int mouseX);
};
