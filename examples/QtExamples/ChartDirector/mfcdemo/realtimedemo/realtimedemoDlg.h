// realtimedemoDlg.h : header file
//

#pragma once

#include "ChartViewer.h"
#include <afxmt.h>


// The number of samples per data series used in this demo
const int sampleSize = 240;


// CRealtimedemoDlg dialog
class CRealtimedemoDlg : public CDialog
{
// Construction
public:
	CRealtimedemoDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_REALTIMEDEMO_DIALOG };
	CStatic	m_ValueC;
	CStatic	m_ValueB;
	CStatic	m_ValueA;
	CChartViewer m_ChartViewer;
	CButton	m_RunPB;
	CSpinButtonCtrl	m_AlarmSpin;
	CComboBox	m_UpdatePeriod;

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnRunPB();
	afx_msg void OnFreezePB();
	afx_msg void OnSelchangeUpdatePeriod();
	afx_msg void OnViewPortChanged();
	DECLARE_MESSAGE_MAP()


private:
	double m_timeStamps[sampleSize];	// The timestamps for the data series
	double m_dataSeriesA[sampleSize];	// The values for the data series A
	double m_dataSeriesB[sampleSize];	// The values for the data series B
	double m_dataSeriesC[sampleSize];	// The values for the data series C

	double m_nextDataTime;	// Used by the random number generator to generate real time data.
	int m_extBgColor;		// The default background color.

	// Shift new data values into the real time data series 
	void getData();
	
	// Draw chart
	void drawChart(CChartViewer *viewer);

	// utility to get default background color
	int getDefaultBgColor();
	// utility to load icon resource to a button
	void loadButtonIcon(int buttonId, int iconId, int width, int height);
};
