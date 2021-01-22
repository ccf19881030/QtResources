// trackboxDlg.cpp : implementation file
//

#include "stdafx.h"
#include "trackbox.h"
#include "trackboxDlg.h"
#include "chartdir.h"
#include <vector>
#include <sstream>
#include <algorithm>

using namespace std;

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CtrackboxDlg dialog

CtrackboxDlg::CtrackboxDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CtrackboxDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

CtrackboxDlg::~CtrackboxDlg()
{
	delete m_ChartViewer.getChart();
}

void CtrackboxDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_ChartViewer, m_ChartViewer);
}

BEGIN_MESSAGE_MAP(CtrackboxDlg, CDialog)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_ERASEBKGND()
    ON_CONTROL(CVN_MouseMovePlotArea, IDC_ChartViewer, OnMouseMovePlotArea)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


// CtrackboxDlg message handlers

BOOL CtrackboxDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	drawChart(&m_ChartViewer);

    CRect winSize;
    m_ChartViewer.GetWindowRect(winSize);
    m_ChartViewer.MoveWindow(5, 5, winSize.Width(), winSize.Height());

    CalcWindowRect(&winSize, CWnd::adjustBorder);
    SetWindowPos(&wndTop, 0, 0, winSize.Width() + 10, winSize.Height() + 10, SWP_NOMOVE);
 
	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CtrackboxDlg::OnPaint()
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
HCURSOR CtrackboxDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

//
// Handle the ON_WM_ERASEBKGND message to set background color
//
BOOL CtrackboxDlg::OnEraseBkgnd(CDC* pDC) 
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
// Draw track cursor when mouse is moving over plotarea
//
void CtrackboxDlg::OnMouseMovePlotArea()
{
	trackBoxLegend((XYChart *)m_ChartViewer.getChart(), m_ChartViewer.getPlotAreaMouseX(), 
		m_ChartViewer.getPlotAreaMouseY()); 
    m_ChartViewer.updateDisplay();

    // Hide the track cursor when the mouse leaves the plot area
    m_ChartViewer.removeDynamicLayer(CVN_MouseLeavePlotArea);
}

/////////////////////////////////////////////////////////////////////////////
// CtrackboxDlg methods

//
// Draw the chart and display it in the given viewer
//
void CtrackboxDlg::drawChart(CChartViewer *viewer)
{
    // The data for the bar chart
    double data0[] = {100, 125, 245, 147, 67};
    double data1[] = {85, 156, 179, 211, 123};
    double data2[] = {97, 87, 56, 267, 157};
    const char *labels[] = {"Mon", "Tue", "Wed", "Thur", "Fri"};
	int noOfPoints = (int)(sizeof(data0)/sizeof(*data0));

    // Create a XYChart object of size 540 x 375 pixels
    XYChart *c = new XYChart(540, 375);

    // Add a title to the chart using 18 pts Times Bold Italic font
    c->addTitle("Average Weekly Network Load", "timesbi.ttf", 18);

    // Set the plotarea at (50, 55) and of 440 x 280 pixels in size. Use a vertical gradient color
    // from light blue (f9f9ff) to blue (6666ff) as background. Set border and grid lines to white
    // (ffffff).
    c->setPlotArea(50, 55, 440, 280, c->linearGradientColor(0, 55, 0, 335, 0xf9f9ff, 0x6666ff), -1,
        0xffffff, 0xffffff);

    // Add a legend box at (50, 28) using horizontal layout. Use 10pts Arial Bold as font, with
    // transparent background.
	c->addLegend(50, 28, false, "arialbd.ttf", 10)->setBackground(Chart::Transparent);

    // Set the x axis labels
    c->xAxis()->setLabels(StringArray(labels, noOfPoints));

    // Draw the ticks between label positions (instead of at label positions)
    c->xAxis()->setTickOffset(0.5);

    // Set axis label style to 8pts Arial Bold
    c->xAxis()->setLabelStyle("arialbd.ttf", 8);
    c->yAxis()->setLabelStyle("arialbd.ttf", 8);

    // Set axis line width to 2 pixels
    c->xAxis()->setWidth(2);
    c->yAxis()->setWidth(2);

    // Add axis title
    c->yAxis()->setTitle("Throughput (MBytes Per Hour)");

    // Add a multi-bar layer with 3 data sets
	BarLayer *layer = c->addBarLayer(Chart::Side);
    layer->addDataSet(DoubleArray(data0, noOfPoints), 0xff0000, "Server #1");
    layer->addDataSet(DoubleArray(data1, noOfPoints), 0x00ff00, "Server #2");
    layer->addDataSet(DoubleArray(data2, noOfPoints), 0xff8800, "Server #3");

    // Set bar border to transparent. Use glass lighting effect with light direction from left.
	layer->setBorderColor(Chart::Transparent, Chart::glassEffect(Chart::NormalGlare, Chart::Left));

    // Configure the bars within a group to touch each others (no gap)
	layer->setBarGap(0.2, Chart::TouchBar);

	// Assign the chart to the WinChartViewer
    viewer->setChart(c);
}

//
// Draw the track box with legend
//
void CtrackboxDlg::trackBoxLegend(XYChart *c, int mouseX, int mouseY)
{
   // Clear the current dynamic layer and get the DrawArea object to draw on it.
    DrawArea *d = c->initDynamicLayer();

    // The plot area object
    PlotArea *plotArea = c->getPlotArea();

    // Get the data x-value that is nearest to the mouse
    double xValue = c->getNearestXValue(mouseX);

    // Compute the position of the box. This example assumes a label based x-axis, in which the
    // labeling spacing is one x-axis unit. So the left and right sides of the box is 0.5 unit from
    // the central x-value.
    int boxLeft = c->getXCoor(xValue - 0.5);
    int boxRight = c->getXCoor(xValue + 0.5);
    int boxTop = plotArea->getTopY();
    int boxBottom = plotArea->getBottomY();

    // Draw the track box
	d->rect(boxLeft, boxTop, boxRight, boxBottom, 0x000000, Chart::Transparent);

    // Container to hold the legend entries
	vector<string> legendEntries;

    // Iterate through all layers to build the legend array
    for(int i = 0; i < c->getLayerCount(); ++i) {
        Layer *layer = c->getLayerByZ(i);

        // The data array index of the x-value
        int xIndex = layer->getXIndexOf(xValue);

        // Iterate through all the data sets in the layer
        for(int j = 0; j < layer->getDataSetCount(); ++j) {
            DataSet *dataSet = layer->getDataSetByZ(j);

            // Build the legend entry, consist of the legend icon, the name and the data value.
            double dataValue = dataSet->getValue(xIndex);
			if ((dataValue != Chart::NoValue) && (dataSet->getDataColor() != Chart::Transparent)) {
				ostringstream legendEntry;
				legendEntry << dataSet->getLegendIcon() << " " << dataSet->getDataName() << ": " 
					<< c->formatValue(dataValue, "{value|P4}");
				legendEntries.push_back(legendEntry.str());
            }
        }
    }

    // Create the legend by joining the legend entries
    if (legendEntries.size() > 0) {
		ostringstream legend;
		legend << "<*block,bgColor=FFFFCC,edgeColor=000000,margin=5*><*font,underline=1*>" << 
			c->xAxis()->getFormattedLabel(xValue) << "<*/font*>";
		for (int i = ((int)legendEntries.size()) - 1; i >= 0; --i)
			legend << "<*br*>" << legendEntries[i];
		legend << "<*/*>";

        // Display the legend at the bottom-right side of the mouse cursor, and make sure the legend
        // will not go outside the chart image.
        TTFText *t = d->text(legend.str().c_str(), "arialbd.ttf", 8);
		t->draw(min(mouseX + 12, c->getWidth() - t->getWidth()), min(mouseY + 18, c->getHeight()
			- t->getHeight()), 0x000000, Chart::TopLeft);
		t->destroy();
    }
}
