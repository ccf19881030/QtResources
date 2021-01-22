#include <QApplication>
#include <QPushButton>
#include <QButtonGroup>
#include <QMouseEvent>
#include <math.h>
#include <sstream>
#include <algorithm>
#include "zoomscrolltrack2.h"

using namespace std;


int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    app.setStyleSheet("* {font-family:arial;font-size:11px}");
    ZoomScrollTrack2 demo;
    demo.show();
    return app.exec();
}

//
// Because QT uses QDateTime, while ChartDirector uses Chart::chartTime, we need
// utilities to convert from one to another
//

// Convert from QDateTime to chartTime
static double QDateTimeToChartTime(QDateTime q)
{
    QDate d = q.date();
    QTime t = q.time();
    return Chart::chartTime(d.year(), d.month(), d.day(), t.hour(), t.minute(),
                            t.second()) + t.msec() / 1000.0;
}

// Convert from chartTime to QDateTime
static QDateTime ChartTimeToQDateTime(double t)
{
    double ymdhms = floor(t);
    int ms = (int)(floor((t - ymdhms) * 1000));
    int ymd = Chart::getChartYMD(ymdhms);
    int hms = (int)fmod(ymdhms, 86400);

    return QDateTime(QDate(ymd / 10000, (ymd % 10000) / 100, ymd % 100),
        QTime(hms / 3600, (hms % 3600) / 60, hms % 60, ms));
}

ZoomScrollTrack2::ZoomScrollTrack2(QWidget *parent) :
    QDialog(parent)
{
    //
    // Set up the GUI
    //

    setFixedSize(782, 376);
    setWindowTitle("Zooming and Scrolling with Track Line (2)");

    // The frame on the left side
    QFrame *frame = new QFrame(this);
    frame->setGeometry(4, 4, 120, 370);
    frame->setFrameShape(QFrame::StyledPanel);

    // Pointer push button
    QPushButton *pointerPB = new QPushButton(QIcon(":/pointer.png"), "Pointer", frame);
    pointerPB->setGeometry(4, 8, 112, 28);
    pointerPB->setStyleSheet("QPushButton { text-align:left; padding:5px}");
    pointerPB->setCheckable(true);

    // Zoom In push button
    QPushButton *zoomInPB = new QPushButton(QIcon(":/zoomin.png"), "Zoom In", frame);
    zoomInPB->setGeometry(4, 36, 112, 28);
    zoomInPB->setStyleSheet("QPushButton { text-align:left; padding:5px}");
    zoomInPB->setCheckable(true);

    // Zoom Out push button
    QPushButton *zoomOutPB = new QPushButton(QIcon(":/zoomout.png"), "Zoom Out", frame);
    zoomOutPB->setStyleSheet("QPushButton { text-align:left; padding:5px}");
    zoomOutPB->setGeometry(4, 64, 112, 28);
    zoomOutPB->setCheckable(true);

    // The Pointer/Zoom In/Zoom Out buttons form a button group
    QButtonGroup *mouseUsage = new QButtonGroup(frame);
    mouseUsage->addButton(pointerPB, Chart::MouseUsageScroll);
    mouseUsage->addButton(zoomInPB, Chart::MouseUsageZoomIn);
    mouseUsage->addButton(zoomOutPB, Chart::MouseUsageZoomOut);
    connect(mouseUsage, SIGNAL(buttonPressed(int)), SLOT(onMouseUsageChanged(int)));

    // Start Date control
    (new QLabel("Start Date", frame))->setGeometry(6, 230, 112, 18);
    m_StartDate = new QDateEdit(frame);
    m_StartDate->setGeometry(4, 248, 113, 22);
    connect(m_StartDate, SIGNAL(dateTimeChanged(QDateTime)), SLOT(onStartDateChanged(QDateTime)));

    // Duration control
    (new QLabel("End Date", frame))->setGeometry(6, 284, 112, 18);
    m_EndDate = new QDateEdit(frame);
    m_EndDate->setGeometry(4, 302, 113, 22);
    connect(m_EndDate, SIGNAL(dateTimeChanged(QDateTime)), SLOT(onEndDateChanged(QDateTime)));

    // Chart Viewer
    m_ChartViewer = new QChartViewer(this);
    m_ChartViewer->setGeometry(128, 4, 650, 350);
    connect(m_ChartViewer, SIGNAL(viewPortChanged()), SLOT(onViewPortChanged()));
    connect(m_ChartViewer, SIGNAL(mouseMovePlotArea(QMouseEvent*)), SLOT(onMouseMovePlotArea(QMouseEvent*)));
    connect(m_ChartViewer, SIGNAL(mouseWheel(QWheelEvent*)), SLOT(onMouseWheelChart(QWheelEvent*)));

    // Horizontal scroll bar
    m_HScrollBar = new QScrollBar(Qt::Horizontal, this);
    m_HScrollBar->setGeometry(128, 356, 650, 17);
    connect(m_HScrollBar, SIGNAL(valueChanged(int)), SLOT(onHScrollBarChanged(int)));

    //
    // Initialize the chart
    //

    // Load the data
    loadData();

    // Initialize the QChartViewer
    initChartViewer(m_ChartViewer);

    // Initially set the mouse to drag to scroll mode
    pointerPB->click();

    // Trigger the ViewPortChanged event to draw the chart
    m_ChartViewer->updateViewPort(true, true);
}

ZoomScrollTrack2::~ZoomScrollTrack2()
{
    delete m_ranSeries;
    delete m_ChartViewer->getChart();
}

//
// Load the data
//
void ZoomScrollTrack2::loadData()
{
    // In this example, we just use random numbers as data.
    m_ranSeries = new RanSeries(127);
    m_timeStamps = m_ranSeries->getDateSeries(1827, Chart::chartTime(2007, 1, 1), 86400);
    m_dataSeriesA = m_ranSeries->getSeries(1827, 150, -10, 10);
    m_dataSeriesB = m_ranSeries->getSeries(1827, 200, -10, 10);
    m_dataSeriesC = m_ranSeries->getSeries(1827, 250, -8, 8);
}

//
// Initialize the QChartViewer
//
void ZoomScrollTrack2::initChartViewer(QChartViewer *viewer)
{
    // Set the full x range to be the duration of the data
    viewer->setFullRange("x", m_timeStamps[0], m_timeStamps[m_timeStamps.len - 1]);

    // Initialize the view port to show the latest 20% of the time range
    viewer->setViewPortWidth(0.2);
    viewer->setViewPortLeft(1 - viewer->getViewPortWidth());

    // Set the maximum zoom to 10 points
    viewer->setZoomInWidthLimit(10.0 / m_timeStamps.len);
}

//
// The ViewPortChanged event handler. This event occurs if the user scrolls or zooms in
// or out the chart by dragging or clicking on the chart. It can also be triggered by
// calling WinChartViewer.updateViewPort.
//
void ZoomScrollTrack2::onViewPortChanged()
{
    // In addition to updating the chart, we may also need to update other controls that
    // changes based on the view port.
    updateControls(m_ChartViewer);

    // Update chart if necessary
    if (m_ChartViewer->needUpdateChart())
        drawChart(m_ChartViewer);
}

//
// Update controls in the user interface when the view port changed
//
void ZoomScrollTrack2::updateControls(QChartViewer *viewer)
{
    // The logical length of the scrollbar. It can be any large value. The actual value does
    // not matter.
    const int scrollBarLen = 1000000000;

    // Update the horizontal scroll bar
    m_HScrollBar->setEnabled(viewer->getViewPortWidth() < 1);
    m_HScrollBar->setPageStep((int)ceil(viewer->getViewPortWidth() * scrollBarLen));
    m_HScrollBar->setSingleStep(min(scrollBarLen / 100, m_HScrollBar->pageStep()));
    m_HScrollBar->setRange(0, scrollBarLen - m_HScrollBar->pageStep());
    m_HScrollBar->setValue((int)(0.5 + viewer->getViewPortLeft() * scrollBarLen));

    //
    // Update the m_StartDate QDataEdit control.
    //
    m_StartDate->setDateTimeRange(ChartTimeToQDateTime(viewer->getValueAtViewPort("x", 0)),
        ChartTimeToQDateTime(viewer->getValueAtViewPort("x", 1)));
    m_StartDate->setDateTime(
        ChartTimeToQDateTime(viewer->getValueAtViewPort("x", viewer->getViewPortLeft())));

    //
    // Update the m_EndDate QDataEdit control.
    //
    m_EndDate->setDateTimeRange(ChartTimeToQDateTime(viewer->getValueAtViewPort("x", 0)),
        ChartTimeToQDateTime(viewer->getValueAtViewPort("x", 1)));
    m_EndDate->setDateTime(ChartTimeToQDateTime(
        viewer->getValueAtViewPort("x", viewer->getViewPortLeft() + viewer->getViewPortWidth())));
}

//
// Draw the chart and display it in the given viewer
//
void ZoomScrollTrack2::drawChart(QChartViewer *viewer)
{
    // Get the start date and end date that are visible on the chart.
    double viewPortStartDate = viewer->getValueAtViewPort("x", viewer->getViewPortLeft());
    double viewPortEndDate = viewer->getValueAtViewPort("x", viewer->getViewPortLeft() +
        viewer->getViewPortWidth());

    // Get the array indexes that corresponds to the visible start and end dates
    int startIndex = (int)floor(Chart::bSearch(m_timeStamps, viewPortStartDate));
    int endIndex = (int)ceil(Chart::bSearch(m_timeStamps, viewPortEndDate));
    int noOfPoints = endIndex - startIndex + 1;

    // Extract the part of the data array that are visible.
    DoubleArray viewPortTimeStamps = DoubleArray(m_timeStamps.data + startIndex, noOfPoints);
    DoubleArray viewPortDataSeriesA = DoubleArray(m_dataSeriesA.data + startIndex, noOfPoints);
    DoubleArray viewPortDataSeriesB = DoubleArray(m_dataSeriesB.data + startIndex, noOfPoints);
    DoubleArray viewPortDataSeriesC = DoubleArray(m_dataSeriesC.data + startIndex, noOfPoints);

    //
    // At this stage, we have extracted the visible data. We can use those data to plot the chart.
    //

    ///////////////////////////////////////////////////////////////////////////////////////
    // Configure overall chart appearance.
    ///////////////////////////////////////////////////////////////////////////////////////

    // Create an XYChart object of size 650 x 350 pixels, with a white (ffffff) background and grey
    // (aaaaaa) border
    XYChart *c = new XYChart(650, 350, 0xffffff, 0xaaaaaa);

    // Set the plotarea at (55, 55) with width 90 pixels less than chart width, and height 90 pixels
    // less than chart height. Use a vertical gradient from light blue (f0f6ff) to sky blue (a0c0ff)
    // as background. Set border to transparent and grid lines to white (ffffff).
    c->setPlotArea(55, 55, c->getWidth() - 90, c->getHeight() - 90, c->linearGradientColor(0, 55, 0,
        c->getHeight() - 35, 0xf0f6ff, 0xa0c0ff), -1, Chart::Transparent, 0xffffff, 0xffffff);

    // As the data can lie outside the plotarea in a zoomed chart, we need enable clipping.
    c->setClipping();

    // Add a title to the chart using 18 pts Times New Roman Bold Italic font
    c->addTitle("   Zooming and Scrolling with Track Line (2)", "timesbi.ttf", 18);

    // Add a legend box at (55, 30) using horizontal layout. Use 8pts Arial Bold as font. Set the
    // background and border color to Transparent and use line style legend key.
    LegendBox *b = c->addLegend(55, 30, false, "arialbd.ttf", 8);
    b->setBackground(Chart::Transparent);
    b->setLineStyleKey();

    // Set the axis stem to transparent
    c->xAxis()->setColors(Chart::Transparent);
    c->yAxis()->setColors(Chart::Transparent);

    // Add axis title using 10pts Arial Bold Italic font
    c->yAxis()->setTitle("Ionic Temperature (C)", "arialbi.ttf", 10);

    ///////////////////////////////////////////////////////////////////////////////////////
    // Add data to chart
    ///////////////////////////////////////////////////////////////////////////////////////

    //
    // In this example, we represent the data by lines. You may modify the code below to use other
    // representations (areas, scatter plot, etc).
    //

    // Add a line layer for the lines, using a line width of 2 pixels
    LineLayer *layer = c->addLineLayer();
    layer->setLineWidth(2);

    // In this demo, we do not have too many data points. In real code, the chart may contain a lot
    // of data points when fully zoomed out - much more than the number of horizontal pixels in this
    // plot area. So it is a good idea to use fast line mode.
    layer->setFastLineMode();

    // Now we add the 3 data series to a line layer, using the color red (ff0000), green
    // (00cc00) and blue (0000ff)
    layer->setXData(viewPortTimeStamps);
    layer->addDataSet(viewPortDataSeriesA, 0xff3333, "Alpha");
    layer->addDataSet(viewPortDataSeriesB, 0x008800, "Beta");
    layer->addDataSet(viewPortDataSeriesC, 0x3333CC, "Gamma");

    ///////////////////////////////////////////////////////////////////////////////////////
    // Configure axis scale and labelling
    ///////////////////////////////////////////////////////////////////////////////////////

    // Set the x-axis as a date/time axis with the scale according to the view port x range.
    viewer->syncDateAxisWithViewPort("x", c->xAxis());

    //
    // In this demo, the time range can be from a few years to a few days. We demonstrate how to set
    // up different date/time format based on the time range.
    //

    // If all ticks are yearly aligned, then we use "yyyy" as the label format.
    c->xAxis()->setFormatCondition("align", 360 * 86400);
    c->xAxis()->setLabelFormat("{value|yyyy}");

    // If all ticks are monthly aligned, then we use "mmm yyyy" in bold font as the first
    // label of a year, and "mmm" for other labels.
    c->xAxis()->setFormatCondition("align", 30 * 86400);
    c->xAxis()->setMultiFormat(Chart::StartOfYearFilter(), "<*font=bold*>{value|mmm yyyy}",
        Chart::AllPassFilter(), "{value|mmm}");

    // If all ticks are daily algined, then we use "mmm dd<*br*>yyyy" in bold font as the
    // first label of a year, and "mmm dd" in bold font as the first label of a month, and
    // "dd" for other labels.
    c->xAxis()->setFormatCondition("align", 86400);
    c->xAxis()->setMultiFormat(Chart::StartOfYearFilter(),
        "<*block,halign=left*><*font=bold*>{value|mmm dd<*br*>yyyy}",
        Chart::StartOfMonthFilter(), "<*font=bold*>{value|mmm dd}");
    c->xAxis()->setMultiFormat(Chart::AllPassFilter(), "{value|dd}");

    // For all other cases (sub-daily ticks), use "hh:nn<*br*>mmm dd" for the first label of
    // a day, and "hh:nn" for other labels.
    c->xAxis()->setFormatCondition("else");
    c->xAxis()->setMultiFormat(Chart::StartOfDayFilter(),
        "<*font=bold*>{value|hh:nn<*br*>mmm dd}", Chart::AllPassFilter(), "{value|hh:nn}");

    ///////////////////////////////////////////////////////////////////////////////////////
    // Output the chart
    ///////////////////////////////////////////////////////////////////////////////////////

    // We need to update the track line too. If the mouse is moving on the chart (eg. if 
    // the user drags the mouse on the chart to scroll it), the track line will be updated
    // in the MouseMovePlotArea event. Otherwise, we need to update the track line here.
    if ((!viewer->isInMouseMoveEvent()) && viewer->isMouseOnPlotArea())
        trackLineLabel(c, viewer->getPlotAreaMouseX());

    delete viewer->getChart();
    viewer->setChart(c);
}

//
// The Pointer, Zoom In or Zoom out button is pressed
//
void ZoomScrollTrack2::onMouseUsageChanged(int mouseUsage)
{
    m_ChartViewer->setMouseUsage(mouseUsage);
}

//
// User selects a start date from the QDateEdit control
//
void ZoomScrollTrack2::onStartDateChanged(QDateTime date)
{
    if (!m_ChartViewer->isInViewPortChangedEvent())
    {
        // The updated view port width
        double vpWidth = m_ChartViewer->getViewPortLeft() + m_ChartViewer->getViewPortWidth() -
            m_ChartViewer->getViewPortAtValue("x", QDateTimeToChartTime(date));

        // Make sure the updated view port width is within bounds
        vpWidth = max(m_ChartViewer->getZoomInWidthLimit(), min(vpWidth,
            m_ChartViewer->getViewPortLeft() + m_ChartViewer->getViewPortWidth()));

        // Update view port and trigger a view port changed event to update the chart
        m_ChartViewer->setViewPortLeft(m_ChartViewer->getViewPortLeft() +
            m_ChartViewer->getViewPortWidth() - vpWidth);
        m_ChartViewer->setViewPortWidth(vpWidth);
        m_ChartViewer->updateViewPort(true, false);
    }
}

//
// User selects an end date from the QDateEdit control
//
void ZoomScrollTrack2::onEndDateChanged(QDateTime date)
{
    if (!m_ChartViewer->isInViewPortChangedEvent())
    {
        // The updated view port width
        double vpWidth = m_ChartViewer->getViewPortAtValue("x", QDateTimeToChartTime(date)) -
            m_ChartViewer->getViewPortLeft();

        // Make sure the updated view port width is within bounds
        vpWidth = max(m_ChartViewer->getZoomInWidthLimit(), min(vpWidth,
            1 - m_ChartViewer->getViewPortLeft()));

        // Update view port and trigger a view port changed event to update the chart
        m_ChartViewer->setViewPortWidth(vpWidth);
        m_ChartViewer->updateViewPort(true, false);
    }
}

//
// User clicks on the the horizontal scroll bar
//
void ZoomScrollTrack2::onHScrollBarChanged(int value)
{
    if (!m_ChartViewer->isInViewPortChangedEvent())
    {
        // Set the view port based on the scroll bar
        int scrollBarLen = m_HScrollBar->maximum() + m_HScrollBar->pageStep();
        m_ChartViewer->setViewPortLeft(value / (double)scrollBarLen);

        // Update the chart display without updating the image maps. (We can delay updating
        // the image map until scrolling is completed and the chart display is stable.)
        m_ChartViewer->updateViewPort(true, false);
    }
}

//
// When the mouse enters the chart, we will generate an image map for hot spots and tooltips
// support if it has not already been generated.
//
void ZoomScrollTrack2::onMouseWheelChart(QWheelEvent *event)
{
    // Process the mouse wheel only if the mouse is over the plot area
    if (!m_ChartViewer->isMouseOnPlotArea())
    {
        event->ignore();
        return;
    }

    // We zoom in or out by 10% depending on the mouse wheel direction.
    double newVpWidth = m_ChartViewer->getViewPortWidth() * (event->delta() > 0 ? 0.9 : 1 / 0.9);
    double newVpHeight = m_ChartViewer->getViewPortHeight() * (event->delta() > 0 ? 0.9 : 1 / 0.9);

    // We do not zoom beyond the zoom width or height limits.
    newVpWidth = max(m_ChartViewer->getZoomInWidthLimit(), min(newVpWidth,
        m_ChartViewer->getZoomOutWidthLimit()));
    newVpHeight = max(m_ChartViewer->getZoomInHeightLimit(), min(newVpWidth,
        m_ChartViewer->getZoomOutHeightLimit()));

    if ((newVpWidth != m_ChartViewer->getViewPortWidth()) ||
            (newVpHeight != m_ChartViewer->getViewPortHeight()))
    {
        // Set the view port position and size so that the point under the mouse remains under
        // the mouse after zooming.

        double deltaX = (m_ChartViewer->getPlotAreaMouseX() - m_ChartViewer->getPlotAreaLeft()) *
            (m_ChartViewer->getViewPortWidth() - newVpWidth) / m_ChartViewer->getPlotAreaWidth();
        m_ChartViewer->setViewPortLeft(m_ChartViewer->getViewPortLeft() + deltaX);
        m_ChartViewer->setViewPortWidth(newVpWidth);

        double deltaY = (m_ChartViewer->getPlotAreaMouseY() - m_ChartViewer->getPlotAreaTop()) *
            (m_ChartViewer->getViewPortHeight() - newVpHeight) / m_ChartViewer->getPlotAreaHeight();
        m_ChartViewer->setViewPortTop(m_ChartViewer->getViewPortTop() + deltaY);
        m_ChartViewer->setViewPortHeight(newVpHeight);

        m_ChartViewer->updateViewPort(true, false);
    }
}

//
// Draw track cursor when mouse is moving over plotarea
//
void ZoomScrollTrack2::onMouseMovePlotArea(QMouseEvent *)
{
    trackLineLabel((XYChart *)m_ChartViewer->getChart(), m_ChartViewer->getPlotAreaMouseX());
    m_ChartViewer->updateDisplay();

    // Hide the track cursor when the mouse leaves the plot area
    m_ChartViewer->removeDynamicLayer("mouseLeavePlotArea");
}

//
// Draw track line with data labels
//
void ZoomScrollTrack2::trackLineLabel(XYChart *c, int mouseX)
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
                (int)Chart::Transparent) && dataSetName && *dataSetName)
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

