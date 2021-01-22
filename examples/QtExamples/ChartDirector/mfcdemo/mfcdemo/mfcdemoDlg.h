// mfcdemoDlg.h : header file
//

#pragma once
#include "afxwin.h"
#include "ChartViewer.h"


// CmfcdemoDlg dialog
class CmfcdemoDlg : public CDialog
{
// Construction
public:
	CmfcdemoDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_MFCDEMO_DIALOG };

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
	afx_msg void OnSize(UINT nType, int cx, int cy); 
	DECLARE_MESSAGE_MAP()


private:
	CListBox m_ChartList;
	afx_msg void OnSelchangeChartList();

	CChartViewer m_ChartViewer7;
	CChartViewer m_ChartViewer6; 
	CChartViewer m_ChartViewer5;
	CChartViewer m_ChartViewer4;
	CChartViewer m_ChartViewer3;
	CChartViewer m_ChartViewer2;
	CChartViewer m_ChartViewer1;
	CChartViewer m_ChartViewer0;

	// An array to hold the 8 CChartViewer objects in the demo to facilitate
	// processing using loops.
	CChartViewer* m_ChartViewer[8];
	afx_msg void OnClickHotSpot(UINT nID);

	// Flow layout the charts
	void layoutCharts();
};
