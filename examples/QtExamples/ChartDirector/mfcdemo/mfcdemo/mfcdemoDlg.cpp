// mfcdemoDlg.cpp : implementation file
//

#include "stdafx.h"
#include "mfcdemo.h"
#include "mfcdemoDlg.h"
#include "mfccharts.h"
#include "HotSpotDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

//
// CmfcdemoDlg dialog
//

CmfcdemoDlg::CmfcdemoDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CmfcdemoDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

	// This demo view is capable of displaying 8 chart images at the same 
	// time. We store the m_ChartViewer in an array to facilitate processing
	// using loops
	m_ChartViewer[0] = &m_ChartViewer0;
	m_ChartViewer[1] = &m_ChartViewer1;
	m_ChartViewer[2] = &m_ChartViewer2;
	m_ChartViewer[3] = &m_ChartViewer3;
	m_ChartViewer[4] = &m_ChartViewer4;
	m_ChartViewer[5] = &m_ChartViewer5;
	m_ChartViewer[6] = &m_ChartViewer6;
	m_ChartViewer[7] = &m_ChartViewer7;
}

void CmfcdemoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CHART_LIST, m_ChartList);
	DDX_Control(pDX, IDC_CHARTVIEWER7, m_ChartViewer7);
	DDX_Control(pDX, IDC_CHARTVIEWER6, m_ChartViewer6);
	DDX_Control(pDX, IDC_CHARTVIEWER5, m_ChartViewer5);
	DDX_Control(pDX, IDC_CHARTVIEWER4, m_ChartViewer4);
	DDX_Control(pDX, IDC_CHARTVIEWER3, m_ChartViewer3);
	DDX_Control(pDX, IDC_CHARTVIEWER2, m_ChartViewer2);
	DDX_Control(pDX, IDC_CHARTVIEWER1, m_ChartViewer1);
	DDX_Control(pDX, IDC_CHARTVIEWER0, m_ChartViewer0);
}

BEGIN_MESSAGE_MAP(CmfcdemoDlg, CDialog)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_ERASEBKGND()
	ON_WM_SIZE()
	ON_CONTROL_RANGE(BN_CLICKED, IDC_CHARTVIEWER0, IDC_CHARTVIEWER7, OnClickHotSpot)
	//}}AFX_MSG_MAP
	ON_LBN_SELCHANGE(IDC_CHART_LIST, OnSelchangeChartList)
END_MESSAGE_MAP()

//
// CmfcdemoDlg message handlers
//

BOOL CmfcdemoDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// Initialize the demo chart selection list
	m_ChartList.ResetContent();
	for (DemoChart *d = demoCharts; d->name != 0; ++d)
		m_ChartList.AddString(CString(d->name));

	SetWindowPos(&wndTop, 0, 0, 1000, 720, SWP_NOMOVE);
	CenterWindow();
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CmfcdemoDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CmfcdemoDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

//
// Handle the ON_WM_ERASEBKGND message to set background color
//
BOOL CmfcdemoDlg::OnEraseBkgnd(CDC* pDC) 
{ 
	// Set brush to desired background color 
	CBrush backBrush(RGB(255, 255, 255)); 

	// Save old brush 
	CBrush* pOldBrush = pDC->SelectObject(&backBrush); 

	// Erase the area needed with the given background color
	CRect rect; 
	pDC->GetClipBox(&rect);
	pDC->PatBlt(rect.left, rect.top, rect.Width(), rect.Height(), PATCOPY); 

	// Restore old brush and exit
	pDC->SelectObject(pOldBrush); 
	return TRUE; 
} 

//
// Handles resize event
//
void CmfcdemoDlg::OnSize(UINT nType, int cx, int cy) 
{
	if (m_ChartList.m_hWnd != 0)
	{
		// Resize the list box to fit the window size
		m_ChartList.MoveWindow(0, 0, 200, cy);

		// Re-layout the charts when window size changes
		layoutCharts();
 	}

	CDialog::OnSize(nType, cx, cy);
}

//
// Handles user selection from the listbox control
//
void CmfcdemoDlg::OnSelchangeChartList()
{
	// Get the demo chart function based on the list box selection
	DemoChart demoChart = demoCharts[m_ChartList.GetCurSel()];
	if (demoChart.noOfCharts == 0)
		return; // Just a separator line - not a real demo chart

	// Hide and clear the old charts
	int i;
	for (i = 0; i < 8; ++i)
	{
		m_ChartViewer[i]->ShowWindow(FALSE);
		m_ChartViewer[i]->setChart(0);
	}

	// Create the demo charts
	for (i = 0; i < demoChart.noOfCharts; ++i)
	{
		// Get the chart and the image map
		const char *imageMap = 0;
		BaseChart *c = demoChart.createChart(i, &imageMap);
			
		// Set the chart and the image map
		m_ChartViewer[i]->setChart(c);
		m_ChartViewer[i]->setImageMap(imageMap);
	
		// Can free the demo chart now after setting everything to the control
		delete c;
	}
	
	// Flow layout the charts on the screen
	layoutCharts();
}

//
// Handles mouse clicks on the chart image
//
void CmfcdemoDlg::OnClickHotSpot(UINT nID)
{
	// In this demo program, all ChartViewers are handled by this handler. We need to 
	// retrieve the ChartViewer that generates the message and get its ImageMapHandler.
	int chartViewerIndex = nID - IDC_CHARTVIEWER0;
	ImageMapHandler *handler = m_ChartViewer[chartViewerIndex]->getImageMapHandler();
	
	if (0 != handler)
	{
		// Query the ImageMapHandler to see if the mouse is on a clickable hot spot. We 
		// consider the hot spot as clickable if its href ("path") parameter is not empty.
		const char *path = handler->getValue("path");
		if ((0 != path) && (0 != *path))
		{
			// In this sample code, we just show all hot spot parameters.
			CHotSpotDlg hs;
			hs.SetData(handler);
			hs.DoModal();
		}
	}
}

/////////////////////////////////////////////////////////////////////////////
// CmfcdemoDlg methods

//
// Flow layout the charts
//
void CmfcdemoDlg::layoutCharts()
{
	// Get the size of the window
	CRect winRect;
	GetWindowRect(&winRect);

	// Get the size and position of the list box
	CRect listRect;
	m_ChartList.GetWindowRect(&listRect);

	// The margin between charts. 
	int margin = 5;

	// The first chart is at the right side of the list box.
	int cursorX = listRect.right - winRect.left + margin;

	// The first chart is align with the top of the window.
	int cursorY = margin;
	
	int maxWidth = 0;
	int lineHeight = 0;

	int i;
	for (i = 0; i < 8; ++i)
	{
		if (m_ChartViewer[i]->GetBitmap() == 0)
			break;	// No more charts, can break now
	
		// Get the size of the chart
		CRect chartRect;
		m_ChartViewer[i]->GetWindowRect(&chartRect);

		if ((i > 0) && (cursorX + (chartRect.right - chartRect.left) > 
			(winRect.right - winRect.left)))
		{
			// There is not enough space left for the chart, so move to next line
			cursorY += (lineHeight + margin);
			cursorX = listRect.right - winRect.left + margin;
			lineHeight = 0;
		}

		// Put the chart in the current cursor position
		m_ChartViewer[i]->MoveWindow(cursorX, cursorY, chartRect.right - chartRect.left,
			chartRect.bottom - chartRect.top);
		
		// Advance the x cursor
		cursorX += (chartRect.right - chartRect.left + margin);
		
		// Update the maximum line width
		if (cursorX > maxWidth)
			maxWidth = cursorX;
		
		// Update the line height
		if (chartRect.bottom - chartRect.top > lineHeight)
			lineHeight = chartRect.bottom - chartRect.top;
	}

	// Show the charts
	for (i = 0; i < 8; ++i)
		m_ChartViewer[i]->ShowWindow(TRUE);
}
