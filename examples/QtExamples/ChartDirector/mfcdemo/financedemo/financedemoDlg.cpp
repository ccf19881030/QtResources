// financedemoDlg.cpp : implementation file
//

#include "stdafx.h"
#include "financedemo.h"
#include "financedemoDlg.h"
#include "chartdir.h"
#include "FinanceChart.h"
#include "ChartViewer.h"
#include <math.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CFinancedemoDlg dialog

//
// Constructor
//
CFinancedemoDlg::CFinancedemoDlg(CWnd* pParent /*=0*/)
    : CDialog(CFinancedemoDlg::IDD, pParent)
{
    m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

    //
    // Initialize member variables
    //
    m_noOfPoints = 0;
    m_timeStamps = 0;
    m_highData = 0;
    m_lowData = 0;
    m_openData = 0;
    m_closeData = 0;
    m_volData = 0;

	m_resolution = 86400;

	m_compareData = 0;
    m_compareDataLen = 0;
}

//
// Destructor
//
CFinancedemoDlg::~CFinancedemoDlg()
{
    delete[] m_timeStamps;
    delete[] m_highData;
    delete[] m_lowData;
    delete[] m_openData;
    delete[] m_closeData;
    delete[] m_volData;
	delete[] m_compareData;
}

void CFinancedemoDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    //{{AFX_DATA_MAP(CFinancedemoDlg)
	DDX_Control(pDX, IDC_TICKERSYMBOL, m_TickerSymbol);
	DDX_Control(pDX, IDC_COMPAREWITH, m_CompareWith);
    DDX_Control(pDX, IDC_TIMERANGE, m_TimeRange);
    DDX_Control(pDX, IDC_CHARTSIZE, m_ChartSize);
    DDX_Control(pDX, IDC_VOLUME, m_Volume);
	DDX_Control(pDX, IDC_PABABOLICSAR, m_ParabolicSAR);
    DDX_Control(pDX, IDC_LOGSCALE, m_LogScale);
	DDX_Control(pDX, IDC_PERCENTAGESCALE, m_PercentageScale);
    DDX_Control(pDX, IDC_CHARTTYPE, m_ChartType);
    DDX_Control(pDX, IDC_BAND, m_Band);
    DDX_Control(pDX, IDC_AVGTYPE1, m_AvgType1);
    DDX_Control(pDX, IDC_AVGTYPE2, m_AvgType2);
    DDX_Control(pDX, IDC_MOVAVG1, m_MovAvg1);
    DDX_Control(pDX, IDC_MOVAVG2, m_MovAvg2);
    DDX_Control(pDX, IDC_INDICATOR1, m_Indicator1);
    DDX_Control(pDX, IDC_INDICATOR2, m_Indicator2);
    DDX_Control(pDX, IDC_INDICATOR3, m_Indicator3);
    DDX_Control(pDX, IDC_INDICATOR4, m_Indicator4);
    DDX_Control(pDX, IDC_CHARTVIEWER, m_ChartViewer);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CFinancedemoDlg, CDialog)
    //{{AFX_MSG_MAP(CFinancedemoDlg)
    ON_WM_PAINT()
    ON_WM_QUERYDRAGICON()
	ON_EN_KILLFOCUS(IDC_TICKERSYMBOL, OnTextChange)
	ON_EN_KILLFOCUS(IDC_COMPAREWITH, OnTextChange)
    ON_CBN_SELCHANGE(IDC_TIMERANGE, OnSelectChange)
    ON_CBN_SELCHANGE(IDC_CHARTSIZE, OnSelectChange)
    ON_BN_CLICKED(IDC_VOLUME, OnSelectChange)
	ON_BN_CLICKED(IDC_PABABOLICSAR, OnSelectChange)
 	ON_BN_CLICKED(IDC_PERCENTAGESCALE, OnSelectChange)
    ON_BN_CLICKED(IDC_LOGSCALE, OnSelectChange)
    ON_CBN_SELCHANGE(IDC_CHARTTYPE, OnSelectChange)
    ON_CBN_SELCHANGE(IDC_BAND, OnSelectChange)
    ON_CBN_SELCHANGE(IDC_AVGTYPE1, OnSelectChange)
    ON_CBN_SELCHANGE(IDC_AVGTYPE2, OnSelectChange)
    ON_EN_KILLFOCUS(IDC_MOVAVG1, OnTextChange)
    ON_EN_KILLFOCUS(IDC_MOVAVG2, OnTextChange)
    ON_CBN_SELCHANGE(IDC_INDICATOR1, OnSelectChange)
    ON_CBN_SELCHANGE(IDC_INDICATOR2, OnSelectChange)
    ON_CBN_SELCHANGE(IDC_INDICATOR3, OnSelectChange)
    ON_CBN_SELCHANGE(IDC_INDICATOR4, OnSelectChange)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

//
// Contents of the CFinancedemoDlg combo boxes
//

static const TCHAR *timeRanges[] = 
{
    _T("1"), _T("1 day"),
    _T("2"), _T("2 days"),
    _T("5"), _T("5 days"),
    _T("10"), _T("10 days"),
    _T("30"), _T("1 month"),
    _T("60"), _T("2 months"),
    _T("90"), _T("3 months"),
    _T("180"), _T("6 months"),
    _T("360"), _T("1 year"),
    _T("720"), _T("2 years"),
    _T("1080"), _T("3 years"),
    _T("1440"), _T("4 years"),
    _T("1800"), _T("5 years"),
    _T("3600"), _T("10 years")
};

static const TCHAR *chartSizes[] =
{
    _T("S"), _T("Small"),
    _T("M"), _T("Medium"),
    _T("L"), _T("Large"),
    _T("H"), _T("Huge")
};

static const TCHAR *chartTypes[] =
{
    _T("None"), _T("None"),
    _T("CandleStick"), _T("CandleStick"),
    _T("Close"), _T("Closing Price"),
    _T("Median"), _T("Median Price"),
    _T("OHLC"), _T("OHLC"),
    _T("TP"), _T("Typical Price"),
    _T("WC"), _T("Weighted Close")
};

static const TCHAR *bandTypes[] =
{
    _T("None"), _T("None"),
    _T("BB"), _T("Bollinger Band"),
    _T("DC"), _T("Donchain Channel"),
    _T("Envelop"), _T("Envelop (SMA 20 +/- 10%)")
};

static const TCHAR *avgTypes[] =
{
    _T("None"), _T("None"),
    _T("SMA"), _T("Simple"),
    _T("EMA"), _T("Exponential"),
    _T("TMA"), _T("Triangular"),
    _T("WMA"), _T("Weighted")
};

static const TCHAR *indicatorTypes[] =
{
    _T("None"), _T("None"),
    _T("AccDist"), _T("Accumulation/Distribution"),
    _T("AroonOsc"), _T("Aroon Oscillator"),
    _T("Aroon"), _T("Aroon Up/Down"),
    _T("ADX"), _T("Avg Directional Index"),
    _T("ATR"), _T("Avg True Range"),
    _T("BBW"), _T("Bollinger Band Width"),
    _T("CMF"), _T("Chaikin Money Flow"),
    _T("COscillator"), _T("Chaikin Oscillator"),
    _T("CVolatility"), _T("Chaikin Volatility"),
    _T("CLV"), _T("Close Location Value"),
    _T("CCI"), _T("Commodity Channel Index"),
    _T("DPO"), _T("Detrended Price Osc"),
    _T("DCW"), _T("Donchian Channel Width"),
    _T("EMV"), _T("Ease of Movement"),
    _T("FStoch"), _T("Fast Stochastic"),
    _T("MACD"), _T("MACD"),
    _T("MDX"), _T("Mass Index"),
    _T("Momentum"), _T("Momentum"),
    _T("MFI"), _T("Money Flow Index"),
    _T("NVI"), _T("Neg Volume Index"),
    _T("OBV"), _T("On Balance Volume"),
    _T("Performance"), _T("Performance"),
    _T("PPO"), _T("% Price Oscillator"),
    _T("PVO"), _T("% Volume Oscillator"),
    _T("PVI"), _T("Pos Volume Index"),
    _T("PVT"), _T("Price Volume Trend"),
    _T("ROC"), _T("Rate of Change"),
    _T("RSI"), _T("RSI"),
    _T("SStoch"), _T("Slow Stochastic"),
    _T("StochRSI"), _T("StochRSI"),
    _T("TRIX"), _T("TRIX"),
    _T("UO"), _T("Ultimate Oscillator"),
    _T("Vol"), _T("Volume"),
    _T("WilliamR"), _T("William's %R")
};

//
// Helper utility to initialize a combo box from an array of text
//
static void initComboBox(CComboBox &b, const TCHAR *list[], int count, const TCHAR *initial)
{
    b.Clear();
    for (int i = 0; i < count; i += 2)
        //The odd index are the display text, the even index are the keys
        b.SetItemDataPtr(b.AddString(list[i + 1]), (void *)(list[i]));
    b.SelectString(0, initial);
}

/////////////////////////////////////////////////////////////////////////////
// CFinancedemoDlg message handlers

//
// Initialization
//
BOOL CFinancedemoDlg::OnInitDialog()
{
    CDialog::OnInitDialog();

    // *** code automatically generated by VC++ MFC AppWizard ***
    // Set the icon for this dialog.  The framework does this automatically
    //  when the application's main window is not a dialog
    SetIcon(m_hIcon, TRUE);         // Set big icon
    SetIcon(m_hIcon, FALSE);        // Set small icon
    
    //
    // Intialialize the controls
    //
	m_TickerSymbol.SetWindowText(_T("ASE.SYMBOL"));
    initComboBox(m_TimeRange, timeRanges, 
        sizeof(timeRanges) / sizeof(*timeRanges), _T("6 months"));
    initComboBox(m_ChartSize, chartSizes, 
        sizeof(chartSizes) / sizeof(*chartSizes), _T("Large"));
    initComboBox(m_ChartType, chartTypes, 
        sizeof(chartTypes) / sizeof(*chartTypes), _T("CandleStick"));
    initComboBox(m_Band, bandTypes, 
        sizeof(bandTypes) / sizeof(*bandTypes), _T("Bollinger Band"));
    initComboBox(m_AvgType1, avgTypes, sizeof(avgTypes) / sizeof(*avgTypes), _T("Simple"));
    initComboBox(m_AvgType2, avgTypes, sizeof(avgTypes) / sizeof(*avgTypes), _T("Simple"));
    initComboBox(m_Indicator1, indicatorTypes, 
        sizeof(indicatorTypes) / sizeof(*indicatorTypes), _T("RSI"));
    initComboBox(m_Indicator2, indicatorTypes, 
        sizeof(indicatorTypes) / sizeof(*indicatorTypes), _T("MACD"));
    initComboBox(m_Indicator3, indicatorTypes, 
        sizeof(indicatorTypes) / sizeof(*indicatorTypes), _T("None"));
    initComboBox(m_Indicator4, indicatorTypes, 
        sizeof(indicatorTypes) / sizeof(*indicatorTypes), _T("None"));

    m_Volume.SetCheck(1);

    m_MovAvg1.SetWindowText(_T("5"));
    m_MovAvg2.SetWindowText(_T("20"));

    // Display the chart
    drawChart(&m_ChartViewer);
    return TRUE;
}

// *** code automatically generated by VC++ MFC AppWizard ***
// If you add a minimize button to your dialog, you will need the code below
// to draw the icon.  For MFC applications using the document/view model,
// this is automatically done for you by the framework.
void CFinancedemoDlg::OnPaint() 
{
    if (IsIconic())
    {
        CPaintDC dc(this); // device context for painting

        SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

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

// *** code automatically generated by VC++ MFC AppWizard ***
// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CFinancedemoDlg::OnQueryDragIcon()
{
    return (HCURSOR) m_hIcon;
}

//
// User selection has changed - update the chart
//
void CFinancedemoDlg::OnSelectChange() 
{
    drawChart(&m_ChartViewer);  
}

//
// User has entered text for the moving average window size
// - update chart if they are changed
//
void CFinancedemoDlg::OnTextChange() 
{
    CString avgText;
    m_MovAvg1.GetWindowText(avgText);
    int new_avgPeriod1 = (int)_tcstol(avgText, 0, 0);
    
    m_MovAvg2.GetWindowText(avgText);
    int new_avgPeriod2 = (int)_tcstol(avgText, 0, 0);

	CString tickerKey;
	m_TickerSymbol.GetWindowText(tickerKey);

	CString compareKey;
	m_CompareWith.GetWindowText(compareKey);

    if ((new_avgPeriod1 != m_avgPeriod1) || (new_avgPeriod2 != m_avgPeriod2) ||
		(m_tickerKey != tickerKey) || (m_compareKey != compareKey))
        OnSelectChange();
}

//
// User hit ENTER key. May be because user has entered into the moving average text field.
//
void CFinancedemoDlg::OnOK()
{
    OnTextChange();
}

/////////////////////////////////////////////////////////////////////////////
// Data source

/// <summary>
/// Get the timeStamps, highData, lowData, openData, closeData and volData.
/// </summary>
/// <param name="ticker">The ticker symbol for the data series.</param>
/// <param name="startDate">The starting date/time for the data series.</param>
/// <param name="endDate">The ending date/time for the data series.</param>
/// <param name="durationInDays">The number of trading days to get.</param>
/// <param name="extraPoints">The extra leading data points needed in order to
/// compute moving averages.</param>
/// <returns>True if successfully obtain the data, otherwise false.</returns>
bool CFinancedemoDlg::getData(const CString &ticker, double startDate,
	double endDate, int durationInDays, int extraPoints)
{
    // This method should return false if the ticker symbol is invalid. In this
    // sample code, as we are using a random number generator for the data, all
    // ticker symbol is allowed, but we still assumed an empty symbol is invalid.
    if (ticker.IsEmpty())
        return false;

    // In this demo, we can get 15 min, daily, weekly or monthly data depending on
    // the time range.
    m_resolution = 86400;
    if (durationInDays <= 10) 
    {
        // 10 days or less, we assume 15 minute data points are available
        m_resolution = 900;

        // We need to adjust the startDate backwards for the extraPoints. We assume 
        // 6.5 hours trading time per day, and 5 trading days per week.
        double dataPointsPerDay = 6.5 * 3600 / m_resolution;
        double adjustedStartDate = startDate - fmod(startDate, 86400) - 
            (int)(extraPoints / dataPointsPerDay * 7 / 5 + 2.9999999) * 86400;

        // Get the required 15 min data
        get15MinData(ticker, adjustedStartDate, endDate);
    }
    else if (durationInDays >= 4.5 * 360)
    {
        // 4 years or more - use monthly data points.
        m_resolution = 30 * 86400;
            
        // Adjust startDate backwards to cater for extraPoints
        int YMD = Chart::getChartYMD(startDate);
        int adjustedMonth = (YMD / 100) % 100 - extraPoints;
        int adjustedYear = YMD / 10000;
        while (adjustedMonth < 1)
        {
            --adjustedYear;
            adjustedMonth += 12;
        }
        double adjustedStartDate = Chart::chartTime(adjustedYear, adjustedMonth, 1);
        
        // Get the required monthly data
        getMonthlyData(ticker, adjustedStartDate, endDate);
    }
    else if (durationInDays >= 1.5 * 360)
    {
        // 1 year or more - use weekly points. 
        m_resolution = 7 * 86400;
 
        //Note that we need to add extra points by shifting the starting weeks backwards
        double adjustedStartDate = startDate - (extraPoints * 7 + 6) * 86400;
            
        // Get the required weekly data
        getWeeklyData(ticker, adjustedStartDate, endDate);
    }
    else
    {
        // Default - use daily points
        m_resolution = 86400;
            
        // Adjust startDate backwards to cater for extraPoints. We multiply the days 
        // by 7/5 as we assume 1 week has 5 trading days.
        double adjustedStartDate = startDate - fmod(startDate, 86400) - 
            ((extraPoints * 7 + 4) / 5 + 2) * 86400;

        // Get the required daily data
        getDailyData(ticker, adjustedStartDate, endDate);
    }

	return true;
}


/// <summary>
/// Get 15 minutes data series into the timeStamps, highData, lowData, openData, closeData 
/// and volData arrays.
/// </summary>
/// <param name="startDate">The starting date/time for the data series.</param>
/// <param name="endDate">The ending date/time for the data series.</param>
void CFinancedemoDlg::get15MinData(const CString &ticker, double startDate, double endDate)
{
    //
    // In this demo, we use a random number generator to generate the data. In practice,
    // you may get the data from a database or by other means. If you do not have 15 
    // minute data, you may modify the "drawChart" method below to not using 15 minute
    // data.
    //
    generateRandomData(ticker, startDate, endDate, 900);
}

/// <summary>
/// Get daily data series into the timeStamps, highData, lowData, openData, closeData and
/// volData arrays.
/// </summary>
/// <param name="startDate">The starting date/time for the data series.</param>
/// <param name="endDate">The ending date/time for the data series.</param>
void CFinancedemoDlg::getDailyData(const CString &ticker, double startDate, double endDate)
{
    //
    // In this demo, we use a random number generator to generate the data. In practice,
    // you may get the data from a database or by other means. Replace the code below
    // with your own data acquisition code.
    //
    
    generateRandomData(ticker, startDate, endDate, 86400);
}

/// <summary>
/// Get weekly data series into the timeStamps, highData, lowData, openData, closeData and
/// volData arrays.
/// </summary>
/// <param name="startDate">The starting date/time for the data series.</param>
/// <param name="endDate">The ending date/time for the data series.</param>
void CFinancedemoDlg::getWeeklyData(const CString &ticker, double startDate, double endDate)
{
    //
    // In this demo, we use a random number generator to generate the data. In practice,
    // you may get the data from a database or by other means. If you do not have weekly
    // data, you may call "getDailyData" to get daily data first, and then call 
    // "convertDailyToWeeklyData" to convert it to weekly data, like:
    //
    //      getDailyData(startDate, endDate);
    //      convertDailyToWeeklyData();
    //
    generateRandomData(ticker, startDate, endDate, 86400 * 7);
}

/// <summary>
/// Get monthly data series into the timeStamps, highData, lowData, openData, closeData and
/// volData arrays.
/// </summary>
/// <param name="startDate">The starting date/time for the data series.</param>
/// <param name="endDate">The ending date/time for the data series.</param>
void CFinancedemoDlg::getMonthlyData(const CString &ticker, double startDate, double endDate)
{
    //
    // In this demo, we use a random number generator to generate the data. In practice,
    // you may get the data from a database or by other means. If you do not have monthly
    // data, you may call "getDailyData" to get daily data first, and then call 
    // "convertDailyToMonthlyData" to convert it to monthly data, like:
    //
    //      getDailyData(startDate, endDate);
    //      convertDailyToMonthlyData();
    //
    generateRandomData(ticker, startDate, endDate, 86400 * 30);
}

/// <summary>
/// A random number generator designed to generate realistic financial data.
/// </summary>
/// <param name="startDate">The starting date/time for the data series.</param>
/// <param name="endDate">The ending date/time for the data series.</param>
/// <param name="resolution">The period of the data series.</param>
void CFinancedemoDlg::generateRandomData(const CString &ticker, double startDate, double endDate, 
    int resolution)
{
    // free the previous data arrays
    delete[] m_timeStamps;
    delete[] m_highData;
    delete[] m_lowData;
    delete[] m_openData;
    delete[] m_closeData;
    delete[] m_volData; 
    
    // The financial simulator
    FinanceSimulator db(TCHARtoUTF8(ticker), startDate, endDate, resolution);

    // Allocate the data arrays
    m_noOfPoints = db.getTimeStamps().len;
    m_timeStamps = new double[m_noOfPoints];
    m_highData = new double[m_noOfPoints];
    m_lowData = new double[m_noOfPoints];
    m_openData = new double[m_noOfPoints];
    m_closeData = new double[m_noOfPoints];
    m_volData = new double[m_noOfPoints];   

    // Copy data to the data arrays
    memcpy(m_timeStamps, db.getTimeStamps().data, m_noOfPoints * sizeof(double));
    memcpy(m_highData, db.getHighData().data, m_noOfPoints * sizeof(double));
    memcpy(m_lowData, db.getLowData().data, m_noOfPoints * sizeof(double));
    memcpy(m_openData, db.getOpenData().data, m_noOfPoints * sizeof(double));
    memcpy(m_closeData, db.getCloseData().data, m_noOfPoints * sizeof(double));
    memcpy(m_volData, db.getVolData().data, m_noOfPoints * sizeof(double));
}

/// <summary>
/// A utility to convert daily to weekly data.
/// </summary>
void CFinancedemoDlg::convertDailyToWeeklyData()
{
    aggregateData(ArrayMath(DoubleArray(m_timeStamps, m_noOfPoints)).selectStartOfWeek());
}
    
/// <summary>
/// A utility to convert daily to monthly data.
/// </summary>
void CFinancedemoDlg::convertDailyToMonthlyData()
{
    aggregateData(ArrayMath(DoubleArray(m_timeStamps, m_noOfPoints)).selectStartOfMonth());
}

/// <summary>
/// An internal method used to aggregate daily data.
/// </summary>
void CFinancedemoDlg::aggregateData(ArrayMath &aggregator)
{
    aggregator.aggregate(DoubleArray(m_highData, m_noOfPoints), Chart::AggregateMax);
    aggregator.aggregate(DoubleArray(m_lowData, m_noOfPoints), Chart::AggregateMin);
    aggregator.aggregate(DoubleArray(m_openData, m_noOfPoints), Chart::AggregateFirst);
    aggregator.aggregate(DoubleArray(m_closeData, m_noOfPoints), Chart::AggregateLast);
    aggregator.aggregate(DoubleArray(m_volData, m_noOfPoints), Chart::AggregateSum);
    m_noOfPoints = aggregator.aggregate(DoubleArray(m_timeStamps, m_noOfPoints), 
        Chart::AggregateFirst).len;
}    

/////////////////////////////////////////////////////////////////////////////
// Chart Creation

/// <summary>
/// Add a moving average line to the FinanceChart object.
/// </summary>
/// <param name="m">The FinanceChart object to add the line to.</param>
/// <param name="avgType">The moving average type (SMA/EMA/TMA/WMA).</param>
/// <param name="avgPeriod">The moving average period.</param>
/// <param name="color">The color of the line.</param>
static LineLayer* addMovingAvg(FinanceChart *m, CString avgType, int avgPeriod, int color)
{
    if (avgPeriod > 1)
    {
        if (avgType == _T("SMA"))
            return m->addSimpleMovingAvg(avgPeriod, color);
        else if (avgType == _T("EMA"))
            return m->addExpMovingAvg(avgPeriod, color);
        else if (avgType == _T("TMA"))
            return m->addTriMovingAvg(avgPeriod, color);
        else if (avgType == _T("WMA"))
            return m->addWeightedMovingAvg(avgPeriod, color);
    }

	return 0;
}

/// <summary>
/// Add an indicator chart to the FinanceChart object. In this demo example, the indicator
/// parameters (such as the period used to compute RSI, colors of the lines, etc.) are hard
/// coded to commonly used values. You are welcome to design a more complex user interface 
/// to allow users to set the parameters.
/// </summary>
/// <param name="m">The FinanceChart object to add the line to.</param>
/// <param name="indicator">The selected indicator.</param>
/// <param name="height">Height of the chart in pixels</param>
static XYChart* addIndicator(FinanceChart *m, CString indicator, int height)
{
    if (indicator == _T("RSI"))
        return m->addRSI(height, 14, 0x800080, 20, 0xff6666, 0x6666ff);
    else if (indicator == _T("StochRSI"))
        return m->addStochRSI(height, 14, 0x800080, 30, 0xff6666, 0x6666ff);
    else if (indicator == _T("MACD"))
        return m->addMACD(height, 26, 12, 9, 0xff, 0xff00ff, 0x8000);
    else if (indicator == _T("FStoch"))
        return m->addFastStochastic(height, 14, 3, 0x6060, 0x606000);
    else if (indicator == _T("SStoch"))
        return m->addSlowStochastic(height, 14, 3, 0x6060, 0x606000);
    else if (indicator == _T("ATR"))
        return m->addATR(height, 14, 0x808080, 0xff);
    else if (indicator == _T("ADX"))
        return m->addADX(height, 14, 0x8000, 0x800000, 0x80);
    else if (indicator == _T("DCW"))
        return m->addDonchianWidth(height, 20, 0xff);
    else if (indicator == _T("BBW"))
        return m->addBollingerWidth(height, 20, 2, 0xff);
    else if (indicator == _T("DPO"))
        return m->addDPO(height, 20, 0xff);
    else if (indicator == _T("PVT"))
        return m->addPVT(height, 0xff);
    else if (indicator == _T("Momentum"))
        return m->addMomentum(height, 12, 0xff);
    else if (indicator == _T("Performance"))
        return m->addPerformance(height, 0xff);
    else if (indicator == _T("ROC"))
        return m->addROC(height, 12, 0xff);
    else if (indicator == _T("OBV"))
        return m->addOBV(height, 0xff);
    else if (indicator == _T("AccDist"))
        return m->addAccDist(height, 0xff);
    else if (indicator == _T("CLV"))
        return m->addCLV(height, 0xff);
    else if (indicator == _T("WilliamR"))
        return m->addWilliamR(height, 14, 0x800080, 30, 0xff6666, 0x6666ff);
    else if (indicator == _T("Aroon"))
        return m->addAroon(height, 14, 0x339933, 0x333399);
    else if (indicator == _T("AroonOsc"))
        return m->addAroonOsc(height, 14, 0xff);
    else if (indicator == _T("CCI"))
        return m->addCCI(height, 20, 0x800080, 100, 0xff6666, 0x6666ff);
    else if (indicator == _T("EMV"))
        return m->addEaseOfMovement(height, 9, 0x6060, 0x606000);
    else if (indicator == _T("MDX"))
        return m->addMassIndex(height, 0x800080, 0xff6666, 0x6666ff);
    else if (indicator == _T("CVolatility"))
        return m->addChaikinVolatility(height, 10, 10, 0xff);
    else if (indicator == _T("COscillator"))
        return m->addChaikinOscillator(height, 0xff);
    else if (indicator == _T("CMF"))
        return m->addChaikinMoneyFlow(height, 21, 0x8000);
    else if (indicator == _T("NVI"))
        return m->addNVI(height, 255, 0xff, 0x883333);
    else if (indicator == _T("PVI"))
        return m->addPVI(height, 255, 0xff, 0x883333);
    else if (indicator == _T("MFI"))
        return m->addMFI(height, 14, 0x800080, 30, 0xff6666, 0x6666ff);
    else if (indicator == _T("PVO"))
        return m->addPVO(height, 26, 12, 9, 0xff, 0xff00ff, 0x8000);
    else if (indicator == _T("PPO"))
        return m->addPPO(height, 26, 12, 9, 0xff, 0xff00ff, 0x8000);
    else if (indicator == _T("UO"))
        return m->addUltimateOscillator(height, 7, 14, 28, 0x800080, 20, 0xff6666, 0x6666ff);
    else if (indicator == _T("Vol"))
        return m->addVolIndicator(height, 0x99ff99, 0xff9999, 0xc0c0c0);
    else if (indicator == _T("TRIX"))
        return m->addTRIX(height, 12, 0xff);
	else
		return 0;
}

/// <summary>
/// Creates a dummy chart to show an error message.
/// </summary>
/// <param name="viewer">The WinChartViewer to display the error message.</param>
/// <param name="msg">The error message</param>
static void errMsg(CChartViewer* viewer, const char *msg)
{
     MultiChart m(400, 200);
     m.addTitle(Chart::Center, msg, "Arial", 10)->setMaxWidth(m.getWidth());
     viewer->setChart(&m);
}

/// <summary>
/// Draw the chart according to user selection and display it in the ChartViewer.
/// </summary>
/// <param name="viewer">The ChartViewer object to display the chart.</param>
void CFinancedemoDlg::drawChart(CChartViewer *viewer)
{
    // In this demo, we just assume we plot up to the latest time. So endDate is now.
    double endDate = Chart::chartTime2((int)time(0));

    // If the trading day has not yet started (before 9:30am), or if the end date is on
    // on Sat or Sun, we set the end date to 4:00pm of the last trading day     
    while ((fmod(endDate, 86400) < 9 * 3600 + 30 * 60) || 
        (Chart::getChartWeekDay(endDate) == 0)
        || (Chart::getChartWeekDay(endDate) == 6))
        endDate = endDate - fmod(endDate, 86400) - 86400 + 16 * 3600;

     // The duration selected by the user
    int durationInDays = (int)_tcstol((const TCHAR *)m_TimeRange.GetItemDataPtr(
        m_TimeRange.GetCurSel()), 0, 0);

    // Compute the start date by subtracting the duration from the end date.
    double startDate;
    if (durationInDays >= 30)
    {
        // More or equal to 30 days - so we use months as the unit
        int YMD = Chart::getChartYMD(endDate);
        int startMonth = (YMD / 100) % 100 - durationInDays / 30;
        int startYear = YMD / 10000;
        while (startMonth < 1)
        {
            --startYear;
            startMonth += 12;
        }
        startDate = Chart::chartTime(startYear, startMonth, 1);
    }
    else
    {
        // Less than 30 days - use day as the unit. The starting point of the axis is
        // always at the start of the day (9:30am). Note that we use trading days, so
        // we skip Sat and Sun in counting the days.
        startDate = endDate - fmod(endDate, 86400) + 9 * 3600 + 30 * 60;
        for (int i = 1; i < durationInDays; ++i)
        {
            if (Chart::getChartWeekDay(startDate) == 1)
                startDate -= 3 * 86400;
            else
                startDate -= 86400;
        }
    }

    // The first moving average period selected by the user.
    CString avgText;
    m_MovAvg1.GetWindowText(avgText);
    m_avgPeriod1 = (int)_tcstol(avgText, 0, 0);
    if (m_avgPeriod1 < 0)
        m_avgPeriod1 = 0;
    if (m_avgPeriod1 > 300)
        m_avgPeriod1 = 300;

    // The second moving average period selected by the user.
    m_MovAvg2.GetWindowText(avgText);
    m_avgPeriod2 = (int)_tcstol(avgText, 0, 0);
    if (m_avgPeriod2 < 0)
        m_avgPeriod2 = 0;
    if (m_avgPeriod2 > 300)
        m_avgPeriod2 = 300;

    // We need extra leading data points in order to compute moving averages.
    int extraPoints = (m_avgPeriod1 > m_avgPeriod2) ? m_avgPeriod1 : m_avgPeriod2;
    if (extraPoints < 25)
        extraPoints = 25;

	// Get the data series to compare with, if any.
	m_CompareWith.GetWindowText(m_compareKey);
	delete[] m_compareData;
	m_compareData = 0;
	if (getData(m_compareKey, startDate, endDate, durationInDays, extraPoints)) 
	{
		m_compareData = m_closeData;
		m_compareDataLen = m_noOfPoints;
		m_closeData = 0;
	}

	// The data series we want to get.
	m_TickerSymbol.GetWindowText(m_tickerKey);
	if (!getData(m_tickerKey, startDate, endDate, durationInDays, extraPoints)) 
	{
		errMsg(viewer, "Please enter a valid ticker symbol");
		return;
	}

    // We now confirm the actual number of extra points (data points that are before
    // the start date) as inferred using actual data from the database.
    for (extraPoints = 0; extraPoints < m_noOfPoints; ++extraPoints)
    {
        if (m_timeStamps[extraPoints] >= startDate)
            break;
    }

    // Check if there is any valid data
    if (extraPoints >= m_noOfPoints)
    {
        // No data - just display the no data message.
		errMsg(viewer, "No data available for the specified time period");
        return;
    }

    // In some finance chart presentation style, even if the data for the latest day 
    // is not fully available, the axis for the entire day will still be drawn, where
    // no data will appear near the end of the axis.
    int extraTrailingPoints = 0;
    if (m_resolution <= 86400)
    {
        // Add extra points to the axis until it reaches the end of the day. The end
        // of day is assumed to be 16:00 (it depends on the stock exchange).
        double lastTime = m_timeStamps[m_noOfPoints - 1];
        extraTrailingPoints = (int)((16 * 3600 - fmod(lastTime, 86400)) / m_resolution);
        if (extraTrailingPoints > 0)
        {
            double *extendedTimeStamps = new double[m_noOfPoints + extraTrailingPoints];
            memcpy(extendedTimeStamps, m_timeStamps, sizeof(double) * m_noOfPoints);
            for (int i = 0; i < extraTrailingPoints; ++i)
                extendedTimeStamps[m_noOfPoints + i] = lastTime + m_resolution * (i + 1);
            delete[] m_timeStamps;
            m_timeStamps = extendedTimeStamps;
        }
    }

    //
    // At this stage, all data is available. We can draw the chart as according to 
    // user input.
    //

    //
    // Determine the chart size. In this demo, user can select 4 different chart sizes.
    // Default is the large chart size.
    //
    int width = 780;
    int mainHeight = 255;
    int indicatorHeight = 80;

    CString selectedSize = (const TCHAR *)m_ChartSize.GetItemDataPtr(m_ChartSize.GetCurSel());
    if (selectedSize == _T("S"))
    {
        // Small chart size
        width = 450;
        mainHeight = 160;
        indicatorHeight = 60;
    }
    else if (selectedSize == _T("M"))
    {
        // Medium chart size
        width = 620;
        mainHeight = 215;
        indicatorHeight = 70;
    }
    else if (selectedSize == _T("H"))
    {
        // Huge chart size
        width = 1000;
        mainHeight = 320;
        indicatorHeight = 90;
    }

    // Create the chart object using the selected size
    FinanceChart m(width);

    // Set the data into the chart object
    m.setData(DoubleArray(m_timeStamps, m_noOfPoints + extraTrailingPoints), 
        DoubleArray(m_highData, m_noOfPoints), DoubleArray(m_lowData, m_noOfPoints), 
        DoubleArray(m_openData, m_noOfPoints), DoubleArray(m_closeData, m_noOfPoints),
        DoubleArray(m_volData, m_noOfPoints), extraPoints);

    //
    // We configure the title of the chart. In this demo chart design, we put the
    // company name as the top line of the title with left alignment.
    //
    CString companyName;
    m_TickerSymbol.GetWindowText(companyName);
    m.addPlotAreaTitle(Chart::TopLeft, TCHARtoUTF8(companyName));

    // We displays the current date as well as the data resolution on the next line.
    const char *resolutionText = "";
    if (m_resolution == 30 * 86400)
        resolutionText = "Monthly";
    else if (m_resolution == 7 * 86400)
        resolutionText = "Weekly";
    else if (m_resolution == 86400)
        resolutionText = "Daily";
    else if (m_resolution == 900)
        resolutionText = "15-min";

    char buffer[1024];
    sprintf(buffer, "<*font=arial.ttf,size=8*>%s - %s chart", 
        m.formatValue(Chart::chartTime2((int)time(0)), "mmm dd, yyyy"), resolutionText);
    m.addPlotAreaTitle(Chart::BottomLeft, buffer);

    // A copyright message at the bottom left corner the title area
    m.addPlotAreaTitle(Chart::BottomRight, 
        "<*font=arial.ttf,size=8*>(c) Advanced Software Engineering");

    //
    // Add the first techical indicator according. In this demo, we draw the first
    // indicator on top of the main chart.
    //
    addIndicator(&m, (const TCHAR *)m_Indicator1.GetItemDataPtr(m_Indicator1.GetCurSel()), 
        indicatorHeight);

	//
    // Add the main chart
	//
    m.addMainChart(mainHeight);

    //
    // Set log or linear scale according to user preference
    //
    m.setLogScale(m_LogScale.GetCheck() != 0);

	//
	// Set axis labels to show data values or percentage change to user preference
	//
	if (m_PercentageScale.GetCheck())
		m.setPercentageAxis();

	//
    // Draw the main chart depending on the chart type the user has selected
    //
    CString selectedType = (const TCHAR *)m_ChartType.GetItemDataPtr(m_ChartType.GetCurSel());
    if (selectedType == _T("Close"))
        m.addCloseLine(0x000040);
    else if (selectedType == _T("TP"))
        m.addTypicalPrice(0x000040);
    else if (selectedType == _T("WC"))
        m.addWeightedClose(0x000040);
    else if (selectedType == _T("Median"))
        m.addMedianPrice(0x000040);

	//
	// Add comparison line if there is data for comparison
	//
	if (m_compareData != 0) {
		if (m_compareDataLen > extraPoints) {
			m.addComparison(DoubleArray(m_compareData, m_compareDataLen), 0x0000ff, 
				TCHARtoUTF8(m_compareKey));
		}
	}

    //
    // Add moving average lines.
    //
    addMovingAvg(&m, (const TCHAR *)m_AvgType1.GetItemDataPtr(m_AvgType1.GetCurSel()), 
        m_avgPeriod1, 0x663300);
    addMovingAvg(&m, (const TCHAR *)m_AvgType2.GetItemDataPtr(m_AvgType2.GetCurSel()), 
        m_avgPeriod2, 0x9900ff);

    //
    // Draw the main chart if the user has selected CandleStick or OHLC. We
    // draw it here to make sure it is drawn behind the moving average lines
    // (that is, the moving average lines stay on top.)
    //
    if (selectedType == _T("CandleStick"))
        m.addCandleStick(0x33ff33, 0xff3333);
    else if (selectedType == _T("OHLC"))
        m.addHLOC(0x8000, 0x800000);

	//
	// Add parabolic SAR if necessary
	//
	if (m_ParabolicSAR.GetCheck())
		m.addParabolicSAR(0.02, 0.02, 0.2, Chart::DiamondShape, 5, 0x008800, 0x000000);

    //
    // Add price band/channel/envelop to the chart according to user selection
    //
    CString selectedBand = (const TCHAR *)m_Band.GetItemDataPtr(m_Band.GetCurSel());
    if (selectedBand == _T("BB"))
        m.addBollingerBand(20, 2, 0x9999ff, 0xc06666ff);
    else if (selectedBand == _T("DC"))
        m.addDonchianChannel(20, 0x9999ff, 0xc06666ff);
    else if (selectedBand == _T("Envelop"))
        m.addEnvelop(20, 0.1, 0x9999ff, 0xc06666ff);

    //
    // Add volume bars to the main chart if necessary
    //
    if (m_Volume.GetCheck())
        m.addVolBars(indicatorHeight, 0x99ff99, 0xff9999, 0xc0c0c0);

    //
    // Add additional indicators as according to user selection.
    //
    addIndicator(&m, (const TCHAR *)m_Indicator2.GetItemDataPtr(m_Indicator2.GetCurSel()), 
        indicatorHeight);
    addIndicator(&m, (const TCHAR *)m_Indicator3.GetItemDataPtr(m_Indicator3.GetCurSel()), 
        indicatorHeight);
    addIndicator(&m, (const TCHAR *)m_Indicator4.GetItemDataPtr(m_Indicator4.GetCurSel()), 
        indicatorHeight);

    // Set the chart to the viewer
    viewer->setChart(&m);

    // Set image map (for tool tips) to the viewer
    sprintf(buffer, "title='%s {value|P}'", m.getToolTipDateFormat());
    viewer->setImageMap(m.getHTMLImageMap("", "", buffer));
}

