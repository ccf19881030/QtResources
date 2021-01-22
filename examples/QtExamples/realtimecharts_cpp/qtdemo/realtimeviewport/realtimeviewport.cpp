#include <QApplication>
#include <QButtonGroup>
#include <QIcon>
#include <QPushButton>
#include <QComboBox>
#include <QFileDialog>
#include "realtimeviewport.h"
#include "chartdir.h"
#include <math.h>
#include <vector>
#include <sstream>

using namespace std;


int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    app.setStyleSheet("* {font-family:arial;font-size:11px}");
    RealTimeViewPort demo;
    demo.show();
    return app.exec();
}


RealTimeViewPort::RealTimeViewPort(QWidget *parent) :
    QDialog(parent)
{
    //
    // Set up the GUI
    //

    setFixedSize(772, 430);
    setWindowTitle("Real-Time Chart with Viewport Control");

    QFrame *leftFrame = new QFrame(this);
    leftFrame->setGeometry(4, 4, 120, 422);
    leftFrame->setFrameShape(QFrame::StyledPanel);

    // Pointer push button
    QPushButton *pointerPB = new QPushButton(QIcon(":/pointer.png"), "Pointer", leftFrame);
    pointerPB->setGeometry(4, 8, 112, 28);
    pointerPB->setStyleSheet("text-align:left; padding:5px");
    pointerPB->setCheckable(true);

    // Zoom In push button
    QPushButton *zoomInPB = new QPushButton(QIcon(":/zoomin.png"), "Zoom In", leftFrame);
    zoomInPB->setGeometry(4, 36, 112, 28);
    zoomInPB->setStyleSheet("text-align:left; padding:5px");
    zoomInPB->setCheckable(true);

    // Zoom Out push button
    QPushButton *zoomOutPB = new QPushButton(QIcon(":/zoomout.png"), "Zoom Out", leftFrame);
    zoomOutPB->setGeometry(4, 64, 112, 28);
    zoomOutPB->setStyleSheet("text-align:left; padding:5px");
    zoomOutPB->setCheckable(true);

    // Save push button
    QPushButton *savePB = new QPushButton(QIcon(":/save.png"), "Save", leftFrame);
    savePB->setStyleSheet("text-align:left; padding:5px");
    savePB->setGeometry(4, 120, 112, 28);
    connect(savePB, SIGNAL(clicked(bool)), SLOT(onSave(bool)));

    // The Pointer/Zoom In/Zoom Out buttons form a button group
    QButtonGroup *mouseUsage = new QButtonGroup(leftFrame);
    mouseUsage->addButton(pointerPB, Chart::MouseUsageScroll);
    mouseUsage->addButton(zoomInPB, Chart::MouseUsageZoomIn);
    mouseUsage->addButton(zoomOutPB, Chart::MouseUsageZoomOut);
    connect(mouseUsage, SIGNAL(buttonPressed(int)), SLOT(onMouseUsageChanged(int)));

    QFrame *rightFrame = new QFrame(this);
    rightFrame->setGeometry(128, 4, 640, 422);
    rightFrame->setStyleSheet("background-color:white");

    // Chart Viewer
    m_ChartViewer = new QChartViewer(rightFrame);
    m_ChartViewer->setGeometry(0, 0, 640, 350);
    connect(m_ChartViewer, SIGNAL(viewPortChanged()), SLOT(onViewPortChanged()));
    connect(m_ChartViewer, SIGNAL(mouseMovePlotArea(QMouseEvent*)),
        SLOT(onMouseMovePlotArea(QMouseEvent*)));

    // Viewport Control
    m_ViewPortControl = new QViewPortControl(rightFrame);
    m_ViewPortControl->setGeometry(0, 355, 640, 64);
    m_ViewPortControl->setViewer(m_ChartViewer);

    //
    // Initialize member variables
    //
    m_currentIndex = 0;

    // Initially, auto-move the track line to make it follow the data series
    trackLineEndPos = 0;
    trackLineIsAtEnd = true;

    // Initially set the mouse to drag to scroll mode.
    pointerPB->click();

    // Enable mouse wheel zooming by setting the zoom ratio to 1.1 per wheel event
    m_ChartViewer->setMouseWheelZoomRatio(1.1);

    // Configure the initial viewport
    m_ChartViewer->setViewPortWidth(initialVisibleRange / (double)initialFullRange);

    // Start the random data generator
    dataSource = new RandomWalk(OnData, this);
    dataSource->start();

    // Set up the chart update timer
    m_ChartUpdateTimer = new QTimer(this);
    connect(m_ChartUpdateTimer, SIGNAL(timeout()), SLOT(onChartUpdateTimer()));

    // The chart update rate is set to 100ms
    m_ChartUpdateTimer->start(100);
}

RealTimeViewPort::~RealTimeViewPort()
{
    delete m_ChartViewer->getChart();
    delete m_ViewPortControl->getChart();
    delete dataSource;
}

//
// The Pointer, Zoom In or Zoom out button is pressed
//
void RealTimeViewPort::onMouseUsageChanged(int mouseUsage)
{
    m_ChartViewer->setMouseUsage(mouseUsage);
}

//
// The Save button is pressed
//
void RealTimeViewPort::onSave(bool)
{
    QString fileName = QFileDialog::getSaveFileName(this, "Save", "chartdirector_demo",
        "PNG (*.png);;JPG (*.jpg);;GIF (*.gif);;BMP (*.bmp);;SVG (*.svg);;PDF (*.pdf)");

    if (!fileName.isEmpty())
    {
        // Save the chart
        BaseChart *c = m_ChartViewer->getChart();
        if (0 != c)
            c->makeChart(fileName.toUtf8().constData());
    }
}

//
// Handles realtime data from RandomWalk. The RandomWalk will call this method from its own thread.
// This is a static method.
//
void RealTimeViewPort::OnData(void *self, double elapsedTime, double series0, double series1)
{
    // Copy the data into a structure and store it in the queue.
    DataPacket packet;
    packet.elapsedTime = elapsedTime;
    packet.series0 = series0;
    packet.series1 = series1;

    ((RealTimeViewPort *)self)->buffer.put(packet);
}

//
// Get data from the queue, update the viewport and update the chart display if necessary.
//
void RealTimeViewPort::onChartUpdateTimer()
{
    QChartViewer *viewer = m_ChartViewer;

    // Enables auto scroll if the viewport is showing the latest data before the update
    bool autoScroll = (m_currentIndex > 0) && (0.001 + viewer->getValueAtViewPort("x",
        viewer->getViewPortLeft() + viewer->getViewPortWidth()) >= m_timeStamps[m_currentIndex - 1]);

    //
    // Get new data from the queue and append them to the data arrays
    //
    int count;
    DataPacket *packets;
    if ((count = buffer.get(&packets)) <= 0)
        return;

    // if data arrays have insufficient space, we need to remove some old data.
    if (m_currentIndex + count >= sampleSize)
    {
        // For safety, we check if the queue contains too much data than the entire data arrays. If
        // this is the case, we only use the latest data to completely fill the data arrays.
        if (count > sampleSize)
        {
            packets += count - sampleSize;
            count = sampleSize;
        }

        // Remove oldest data to leave space for new data. To avoid frequent removal, we ensure at
        // least 5% empty space available after removal.
        int originalIndex = m_currentIndex;
        m_currentIndex = sampleSize * 95 / 100 - 1;
        if (m_currentIndex > sampleSize - count)
            m_currentIndex = sampleSize - count;

        for (int i = 0; i < m_currentIndex; ++i)
        {
            int srcIndex = i + originalIndex - m_currentIndex;
            m_timeStamps[i] = m_timeStamps[srcIndex];
            m_dataSeriesA[i] = m_dataSeriesA[srcIndex];
            m_dataSeriesB[i] = m_dataSeriesB[srcIndex];
        }
    }

    // Append the data from the queue to the data arrays
    for (int n = 0; n < count; ++n)
    {
        m_timeStamps[m_currentIndex] = packets[n].elapsedTime;
        m_dataSeriesA[m_currentIndex] = packets[n].series0;
        m_dataSeriesB[m_currentIndex] = packets[n].series1;
        ++m_currentIndex;
    }

    //
    // As we added more data, we may need to update the full range of the viewport.
    //

    double startDate = m_timeStamps[0];
    double endDate = m_timeStamps[m_currentIndex - 1];

    // Use the initialFullRange (which is 60 seconds in this demo) if this is sufficient.
    double duration = endDate - startDate;
    if (duration < initialFullRange)
        endDate = startDate + initialFullRange;

    // Update the new full data range to include the latest data
    bool axisScaleHasChanged = viewer->updateFullRangeH("x", startDate, endDate,
        Chart::KeepVisibleRange);

    if (autoScroll)
    {
        // Scroll the viewport if necessary to display the latest data
        double viewPortEndPos = viewer->getViewPortAtValue("x", m_timeStamps[m_currentIndex - 1]);
        if (viewPortEndPos > viewer->getViewPortLeft() + viewer->getViewPortWidth())
        {
            viewer->setViewPortLeft(viewPortEndPos - viewer->getViewPortWidth());
            axisScaleHasChanged = true;
        }
    }

    // Set the zoom in limit as a ratio to the full range
    viewer->setZoomInWidthLimit(zoomInLimit / (viewer->getValueAtViewPort("x", 1) -
        viewer->getValueAtViewPort("x", 0)));

    // Trigger the viewPortChanged event. Updates the chart if the axis scale has changed
    // (scrolling or zooming) or if new data are added to the existing axis scale.
    viewer->updateViewPort(axisScaleHasChanged || (duration < initialFullRange), false);
}

//
// View port changed event
//
void RealTimeViewPort::onViewPortChanged()
{
    // Update the chart if necessary
    if (m_ChartViewer->needUpdateChart())
        drawChart(m_ChartViewer);

    // Update the full chart
    drawFullChart(m_ViewPortControl);
}

//
// Draw chart
//
void RealTimeViewPort::drawChart(QChartViewer *viewer)
{
    // Get the start date and end date that are visible on the chart.
    double viewPortStartDate = viewer->getValueAtViewPort("x", viewer->getViewPortLeft());
    double viewPortEndDate = viewer->getValueAtViewPort("x", viewer->getViewPortLeft() +
        viewer->getViewPortWidth());

    // Extract the part of the data arrays that are visible.
    DoubleArray viewPortTimeStamps;
    DoubleArray viewPortDataSeriesA;
    DoubleArray viewPortDataSeriesB;

    if (m_currentIndex > 0)
    {
        // Get the array indexes that corresponds to the visible start and end dates
        int startIndex = (int)floor(Chart::bSearch(DoubleArray(m_timeStamps, m_currentIndex), viewPortStartDate));
        int endIndex = (int)ceil(Chart::bSearch(DoubleArray(m_timeStamps, m_currentIndex), viewPortEndDate));
        int noOfPoints = endIndex - startIndex + 1;

        // Extract the visible data
        if (m_timeStamps[endIndex] >= viewPortStartDate)
        {
            viewPortTimeStamps = DoubleArray(m_timeStamps+ startIndex, noOfPoints);
            viewPortDataSeriesA = DoubleArray(m_dataSeriesA + startIndex, noOfPoints);
            viewPortDataSeriesB = DoubleArray(m_dataSeriesB + startIndex, noOfPoints);
        }

        // Keep track of the latest available data at chart plotting time
        trackLineEndPos = m_timeStamps[m_currentIndex - 1];
    }

    //
    // At this stage, we have extracted the visible data. We can use those data to plot the chart.
    //

    //================================================================================
    // Configure overall chart appearance.
    //================================================================================

    // Create an XYChart object of size 640 x 350 pixels
    XYChart *c = new XYChart(640, 350);

    // Set the plotarea at (20, 30) with width 41 pixels less than chart width, and height 50 pixels
    // less than chart height. Use a vertical gradient from light blue (f0f6ff) to sky blue (a0c0ff)
    // as background. Set border to transparent and grid lines to white (ffffff).
    c->setPlotArea(20, 30, c->getWidth() - 41, c->getHeight() - 50, c->linearGradientColor(0, 30, 0,
        c->getHeight() - 50, 0xf0f6ff, 0xa0c0ff), -1, Chart::Transparent, 0xffffff, 0xffffff);

     // As the data can lie outside the plotarea in a zoomed chart, we need enable clipping.
    c->setClipping();

    // Add a title to the chart using 18pt Arial font
    c->addTitle("   Multithreading Real-Time Chart", "arial.ttf", 18);

    // Add a legend box at (55, 25) using horizontal layout. Use 10pt Arial Bold as font. Set the
    // background and border color to transparent and use line style legend key.
    LegendBox *b = c->addLegend(55, 25, false, "arialbd.ttf", 10);
    b->setBackground(Chart::Transparent);
    b->setLineStyleKey();

    // Set the x and y axis stems to transparent and the label font to 10pt Arial
    c->xAxis()->setColors(Chart::Transparent);
    c->yAxis()->setColors(Chart::Transparent);
    c->xAxis()->setLabelStyle("arial.ttf", 10);
    c->yAxis()->setLabelStyle("arial.ttf", 10, 0x336699);

    // Set the y-axis tick length to 0 to disable the tick and put the labels closer to the axis.
    c->yAxis()->setTickLength(0);

    // Add axis title using 10pt Arial Bold Italic font
    c->yAxis()->setTitle("Ionic Temperature (C)", "arialbd.ttf", 10);

    // Configure the y-axis label to be inside the plot area and above the horizontal grid lines
    c->yAxis()->setLabelGap(-1);
    c->yAxis()->setLabelAlignment(1);
    c->yAxis()->setMargin(20);

    // Configure the x-axis labels to be to the left of the vertical grid lines
    c->xAxis()->setLabelAlignment(1);

    //================================================================================
    // Add data to chart
    //================================================================================

    //
    // In this example, we represent the data by lines. You may modify the code below to use other
    // representations (areas, scatter plot, etc).
    //

    // Add a line layer for the lines, using a line width of 2 pixels
    LineLayer *layer = c->addLineLayer();
    layer->setLineWidth(2);
    layer->setFastLineMode();

    // Now we add the 2 data series to the line layer with red (ff0000) and green (00cc00) colors
    layer->setXData(viewPortTimeStamps);
    layer->addDataSet(viewPortDataSeriesA, 0xff0000, "Alpha");
    layer->addDataSet(viewPortDataSeriesB, 0x00cc00, "Beta");

    //================================================================================
    // Configure axis scale and labelling
    //================================================================================

    // Set the x-axis as a date/time axis with the scale according to the view port x range.
    if (m_currentIndex > 0)
        c->xAxis()->setDateScale(viewPortStartDate, viewPortEndDate);

    // For the automatic axis labels, set the minimum spacing to 75/30 pixels for the x/y axis.
    c->xAxis()->setTickDensity(75);
    c->yAxis()->setTickDensity(30);

    // We use "hh:nn:ss" as the axis label format.
    c->xAxis()->setLabelFormat("{value|hh:nn:ss}");

    // We make sure the tick increment must be at least 1 second.
    c->xAxis()->setMinTickInc(1);

    // Set the auto-scale margin to 0.05, and the zero affinity to 0.6
    c->yAxis()->setAutoScale(0.05, 0.05, 0.6);

    //================================================================================
    // Output the chart
    //================================================================================

    // We need to update the track line too. If the mouse is moving on the chart (eg. if
    // the user drags the mouse on the chart to scroll it), the track line will be updated
    // in the MouseMovePlotArea event. Otherwise, we need to update the track line here.
    if (!viewer->isInMouseMoveEvent())
        trackLineLabel(c, trackLineIsAtEnd ? c->getWidth() : viewer->getPlotAreaMouseX());

    // Set the chart image to the QChartViewer
    delete viewer->getChart();
    viewer->setChart(c);
}

//
// Draw track cursor when mouse is moving over plotarea
//
void RealTimeViewPort::onMouseMovePlotArea(QMouseEvent *)
{
    double trackLinePos = trackLineLabel((XYChart *)m_ChartViewer->getChart(),
        m_ChartViewer->getPlotAreaMouseX());
    trackLineIsAtEnd = (m_currentIndex <= 0) || (trackLinePos == trackLineEndPos);

    m_ChartViewer->updateDisplay();    
}

//
// Draw the track line with data point labels
//
double RealTimeViewPort::trackLineLabel(XYChart *c, int mouseX)
{
    // Clear the current dynamic layer and get the DrawArea object to draw on it.
    DrawArea *d = c->initDynamicLayer();

    // The plot area object
    PlotArea *plotArea = c->getPlotArea();

    // Get the data x-value that is nearest to the mouse, and find its pixel coordinate.
    double xValue = c->getNearestXValue(mouseX);
    int xCoor = c->getXCoor(xValue);
    if (xCoor < plotArea->getLeftX())
        return xValue;

    // Draw a vertical track line at the x-position
    d->vline(plotArea->getTopY(), plotArea->getBottomY(), xCoor, 0x888888);

    // Draw a label on the x-axis to show the track line position.
    ostringstream xlabel;
    xlabel << "<*font,bgColor=000000*> " << c->xAxis()->getFormattedLabel(xValue + 0.00499,
        "hh:nn:ss.ff") << " <*/font*>";
    TTFText *t = d->text(xlabel.str().c_str(), "arialbd.ttf", 10);

    // Restrict the x-pixel position of the label to make sure it stays inside the chart image.
    int xLabelPos = max(0, min(xCoor - t->getWidth() / 2, c->getWidth() - t->getWidth()));
    t->draw(xLabelPos, plotArea->getBottomY() + 2, 0xffffff);
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
                t = d->text(label.str().c_str(), "arialbd.ttf", 10);

                // Draw the label on the right side of the dot if the mouse is on the left side the
                // chart, and vice versa. This ensures the label will not go outside the chart image.
                if (xCoor <= (plotArea->getLeftX() + plotArea->getRightX()) / 2)
                    t->draw(xCoor + 6, yCoor, 0xffffff, Chart::Left);
                else
                    t->draw(xCoor - 6, yCoor, 0xffffff, Chart::Right);

                t->destroy();
            }
        }
    }

    return xValue;
}

//
// Draw the full thumbnail chart and display it in the given QViewPortControl
//
void RealTimeViewPort::drawFullChart(QViewPortControl *vpc)
{
    // Create an XYChart object of size 640 x 60 pixels
    XYChart *c = new XYChart(640, 60);

    // Set the plotarea with the same horizontal position as that in the main chart for alignment.
    c->setPlotArea(20, 0, c->getWidth() - 41, c->getHeight() - 1, 0xc0d8ff, -1, 0xcccccc,
        Chart::Transparent, 0xffffff);

    // Set the x axis stem to transparent and the label font to 10pt Arial
    c->xAxis()->setColors(Chart::Transparent);
    c->xAxis()->setLabelStyle("Arial", 10);

    // Put the x-axis labels inside the plot area by setting a negative label gap. Use
    // setLabelAlignment to put the label at the right side of the tick.
    c->xAxis()->setLabelGap(-1);
    c->xAxis()->setLabelAlignment(1);

    // Set the y axis stem and labels to transparent (that is, hide the labels)
    c->yAxis()->setColors(Chart::Transparent, Chart::Transparent);

    // Add a line layer for the lines with fast line mode enabled
    LineLayer *layer = c->addLineLayer();
    layer->setFastLineMode();

    // Now we add the 3 data series to a line layer, using the color red (0xff3333), green
    // (0x008800) and blue (0x3333cc)
    layer->setXData(DoubleArray(m_timeStamps, m_currentIndex));
    layer->addDataSet(DoubleArray(m_dataSeriesA, m_currentIndex), 0xff3333);
    layer->addDataSet(DoubleArray(m_dataSeriesB, m_currentIndex), 0x008800);

    // The x axis scales should reflect the full range of the view port
    c->xAxis()->setDateScale(vpc->getViewer()->getValueAtViewPort("x", 0),
        vpc->getViewer()->getValueAtViewPort("x", 1));
    c->xAxis()->setLabelFormat("{value|nn:ss}");

    // For the automatic x-axis labels, set the minimum spacing to 75 pixels.
    c->xAxis()->setTickDensity(75);

    // For the auto-scaled y-axis, as we hide the labels, we can disable axis rounding. This can
    // make the axis scale fit the data tighter.
    c->yAxis()->setRounding(false, false);

    // Output the chart
    delete vpc->getChart();
    vpc->setChart(c);
}

