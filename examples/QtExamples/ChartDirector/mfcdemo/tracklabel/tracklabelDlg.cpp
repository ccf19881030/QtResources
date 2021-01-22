// tracklabelDlg.cpp : implementation file
//

#include "stdafx.h"
#include "tracklabel.h"
#include "tracklabelDlg.h"
#include "chartdir.h"
#include <sstream>
#include <algorithm>

using namespace std;

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CtracklabelDlg dialog

CtracklabelDlg::CtracklabelDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CtracklabelDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

CtracklabelDlg::~CtracklabelDlg()
{
	delete m_ChartViewer.getChart();
}

void CtracklabelDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_ChartViewer, m_ChartViewer);
}

BEGIN_MESSAGE_MAP(CtracklabelDlg, CDialog)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_ERASEBKGND()
    ON_CONTROL(CVN_MouseMovePlotArea, IDC_ChartViewer, OnMouseMovePlotArea)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


// CtracklabelDlg message handlers

BOOL CtracklabelDlg::OnInitDialog()
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

void CtracklabelDlg::OnPaint()
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
HCURSOR CtracklabelDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

//
// Handle the ON_WM_ERASEBKGND message to set background color
//
BOOL CtracklabelDlg::OnEraseBkgnd(CDC* pDC) 
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
void CtracklabelDlg::OnMouseMovePlotArea()
{
    trackLineLabel((XYChart *)m_ChartViewer.getChart(), m_ChartViewer.getPlotAreaMouseX());
    m_ChartViewer.updateDisplay();

    // Hide the track cursor when the mouse leaves the plot area
    m_ChartViewer.removeDynamicLayer(CVN_MouseLeavePlotArea);
}

/////////////////////////////////////////////////////////////////////////////
// CtracklabelDlg methods

//
// Draw the chart and display it in the given viewer
//
void CtracklabelDlg::drawChart(CChartViewer *viewer)
{
    // Data for the chart as 3 random data series
    RanSeries r(127);
    DoubleArray data0 = r.getSeries(100, 100, -15, 15);
    DoubleArray data1 = r.getSeries(100, 150, -15, 15);
    DoubleArray data2 = r.getSeries(100, 200, -15, 15);
	DoubleArray timeStamps = r.getDateSeries(100, Chart::chartTime(2011, 1, 1), 86400);

    // Create a XYChart object of size 640 x 400 pixels
    XYChart *c = new XYChart(640, 400);

    // Add a title to the chart using 18 pts Times New Roman Bold Italic font
    c->addTitle("    Product Line Global Revenue", "timesbi.ttf", 18);

    // Set the plotarea at (50, 55) with width 70 pixels less than chart width, and height 90 pixels
    // less than chart height. Use a vertical gradient from light blue (f0f6ff) to sky blue (a0c0ff)
    // as background. Set border to transparent and grid lines to white (ffffff).
    c->setPlotArea(50, 55, c->getWidth() - 70, c->getHeight() - 90, c->linearGradientColor(0, 55, 0,
		c->getHeight() - 35, 0xf0f6ff, 0xa0c0ff), -1, Chart::Transparent, 0xffffff, 0xffffff);

    // Add a legend box at (50, 25) using horizontal layout. Use 10pts Arial Bold as font. Set the
    // background and border color to Transparent.
	c->addLegend(50, 25, false, "arialbd.ttf", 10)->setBackground(Chart::Transparent);

    // Set axis label style to 8pts Arial Bold
    c->xAxis()->setLabelStyle("arialbd.ttf", 8);
    c->yAxis()->setLabelStyle("arialbd.ttf", 8);

    // Set the axis stem to transparent
	c->xAxis()->setColors(Chart::Transparent);
	c->yAxis()->setColors(Chart::Transparent);

    // Configure x-axis label format
	c->xAxis()->setMultiFormat(Chart::StartOfYearFilter(), "{value|mm/yyyy} ", 
		Chart::StartOfMonthFilter(), "{value|mm}");

    // Add axis title using 10pts Arial Bold Italic font
    c->yAxis()->setTitle("USD millions", "arialbi.ttf", 10);

    // Add a line layer to the chart using a line width of 2 pixels.
    LineLayer *layer = c->addLineLayer();
    layer->setLineWidth(2);

    // Add 3 data series to the line layer
    layer->setXData(timeStamps);
    layer->addDataSet(data0, 0xff3333, "Alpha");
    layer->addDataSet(data1, 0x008800, "Beta");
    layer->addDataSet(data2, 0x3333cc, "Gamma");

	// Assign the chart to the WinChartViewer
    viewer->setChart(c);
}

//
// Draw track line with data labels
//
void CtracklabelDlg::trackLineLabel(XYChart *c, int mouseX)
{
    // Clear the current dynamic layer and get the DrawArea object to draw on it.
    DrawArea *d = c->initDynamicLayer();

    // The plot area object
    PlotArea *plotArea = c->getPlotArea();

    // Get the data x-value that is nearest to the mouse, and find its pixel coordinate.
    double xValue = c->getNearestXValue(mouseX);
    int xCoor = c->getXCoor(xValue);

    // Draw a vertical track line at the x-position
    d->vline(plotArea->getTopY(), plotArea->getBottomY(), xCoor, 
		d->dashLineColor(0x000000, 0x0101));

    // Draw a label on the x-axis to show the track line position.
	ostringstream xlabel;
	xlabel << "<*font,bgColor=000000*> " << c->xAxis()->getFormattedLabel(xValue, "mmm dd, yyyy") 
		<< " <*/font*>";
	TTFText *t = d->text(xlabel.str().c_str(), "arialbd.ttf", 8);

    // Restrict the x-pixel position of the label to make sure it stays inside the chart image.
    int xLabelPos = max(0, min(xCoor - t->getWidth() / 2, c->getWidth() - t->getWidth()));
	t->draw(xLabelPos, plotArea->getBottomY() + 6, 0xffffff);
	t->destroy();	

    // Iterate through all layers to draw the data labels
    for (int i = 0; i < c->getLayerCount(); ++i) {
        Layer *layer = c->getLayerByZ(i);

        // The data array index of the x-value
        int xIndex = layer->getXIndexOf(xValue);

        // Iterate through all the data sets in the layer
        for (int j = 0; j < layer->getDataSetCount(); ++j) 
		{
            DataSet *dataSet = layer->getDataSetByZ(j);
 			const char *dataSetName = dataSet->getDataName();

            // Get the color, name and position of the data label
            int color = dataSet->getDataColor();
            int yCoor = c->getYCoor(dataSet->getPosition(xIndex), dataSet->getUseYAxis());

            // Draw a track dot with a label next to it for visible data points in the plot area
            if ((yCoor >= plotArea->getTopY()) && (yCoor <= plotArea->getBottomY()) && (color !=
				Chart::Transparent) && dataSetName && *dataSetName)
			{
                d->circle(xCoor, yCoor, 4, 4, color, color);

				ostringstream label;
				label << "<*font,bgColor=" << hex << color << "*> " 
					<< c->formatValue(dataSet->getValue(xIndex), "{value|P4}") << " <*font*>";
				t = d->text(label.str().c_str(), "arialbd.ttf", 8);
				
				// Draw the label on the right side of the dot if the mouse is on the left side the
                // chart, and vice versa. This ensures the label will not go outside the chart image.
                if (xCoor <= (plotArea->getLeftX() + plotArea->getRightX()) / 2)
					t->draw(xCoor + 5, yCoor, 0xffffff, Chart::Left);
                else
					t->draw(xCoor - 5, yCoor, 0xffffff, Chart::Right);
                
				t->destroy();
            }
        }
    }
}
