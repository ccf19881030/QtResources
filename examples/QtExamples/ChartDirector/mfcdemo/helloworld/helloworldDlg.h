// helloworldDlg.h : header file
//

#pragma once

#include "ChartViewer.h"


// CHelloworldDlg dialog
class CHelloworldDlg : public CDialog
{
// Construction
public:
	CHelloworldDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_HELLOWORLD_DIALOG };
	CChartViewer	m_ChartViewer;

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
};
