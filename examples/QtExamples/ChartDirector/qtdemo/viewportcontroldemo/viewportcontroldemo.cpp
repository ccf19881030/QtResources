#include <QApplication>
#include <QPushButton>
#include <QButtonGroup>
#include <QMouseEvent>
#include <QFileDialog>
#include <math.h>
#include <sstream>
#include <algorithm>
#include "viewportcontroldemo.h"

using namespace std;


int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    app.setStyleSheet("* {font-family:arial;font-size:11px}");
    ViewportControlDemo demo;
    demo.show();
    return app.exec();
}

ViewportControlDemo::ViewportControlDemo(QWidget *parent) :
    QDialog(parent)
{
    //
    // Set up the GUI
    //

    setFixedSize(772, 478);
    setWindowTitle("Zooming and Scrolling with Viewport Control");

    // The frame on the left side
    QFrame *frame = new QFrame(this);
    frame->setGeometry(4, 4, 120, 470);
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

    // Save push button
    QPushButton *savePB = new QPushButton(QIcon(":/save.png"), "Save", frame);
    savePB->setStyleSheet("QPushButton { text-align:left; padding:5px}");
    savePB->setGeometry(4, 120, 112, 28);
    connect(savePB, SIGNAL(clicked(bool)), SLOT(onSave(bool)));

    // The Pointer/Zoom In/Zoom Out buttons form a button group
    QButtonGroup *mouseUsage = new QButtonGroup(frame);
    mouseUsage->addButton(pointerPB, Chart::MouseUsageScroll);
    mouseUsage->addButton(zoomInPB, Chart::MouseUsageZoomIn);
    mouseUsage->addButton(zoomOutPB, Chart::MouseUsageZoomOut);
    connect(mouseUsage, SIGNAL(buttonPressed(int)), SLOT(onMouseUsageChanged(int)));

    // Chart Viewer
    m_ChartViewer = new QChartViewer(this);
    m_ChartViewer->setGeometry(128, 4, 640, 400);
    connect(m_ChartViewer, SIGNAL(viewPortChanged()), SLOT(onViewPortChanged()));
    connect(m_ChartViewer, SIGNAL(mouseMovePlotArea(QMouseEvent*)), SLOT(onMouseMovePlotArea(QMouseEvent*)));

    m_ViewPortControl = new QViewPortControl(this);
    m_ViewPortControl->setGeometry(128, 403, 640, 70);

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

    // Draw and display the full chart in the CViewPortControl
    drawFullChart(m_ViewPortControl, m_ChartViewer);

    // Bind the CChartViewer to the CViewPortControl
    m_ViewPortControl->setViewer(m_ChartViewer);
}

ViewportControlDemo::~ViewportControlDemo()
{
    delete m_ranSeries;
    delete m_ChartViewer->getChart();
    delete m_ViewPortControl->getChart();
}

//
// Load the data
//
void ViewportControlDemo::loadData()
{
    // In this example, we just use random numbers as data.
    m_ranSeries = new RanSeries(127);
    m_timeStamps = m_ranSeries->getDateSeries(1827, Chart::chartTime(2010, 1, 1), 86400);
    m_dataSeriesA = m_ranSeries->getSeries(1827, 150, -10, 10);
    m_dataSeriesB = m_ranSeries->getSeries(1827, 200, -10, 10);
    m_dataSeriesC = m_ranSeries->getSeries(1827, 250, -8, 8);
}

//
// Initialize the QChartViewer
//
void ViewportControlDemo::initChartViewer(QChartViewer *viewer)
{
    // Set the full x range to be the duration of the data
    viewer->setFullRange("x", m_timeStamps[0], m_timeStamps[m_timeStamps.len - 1]);

    // Initialize the view port to show the latest 20% of the time range
    viewer->setViewPortWidth(0.2);
    viewer->setViewPortLeft(1 - viewer->getViewPortWidth());

    // Set the maximum zoom to 10 points
    viewer->setZoomInWidthLimit(10.0 / m_timeStamps.len);
    viewer->setMouseWheelZoomRatio(1.1);
}

//
// The ViewPortChanged event handler. This event occurs if the user scrolls or zooms in
// or out the chart by dragging or clicking on the chart. It can also be triggered by
// calling WinChartViewer.updateViewPort.
//
void ViewportControlDemo::onViewPortChanged()
{
    // Update chart if necessary
    if (m_ChartViewer->needUpdateChart())
        drawChart(m_ChartViewer);
}

//
// Draw the chart and display it in the given viewer
//
void ViewportControlDemo::drawChart(QChartViewer *viewer)
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

    // Create an XYChart object of size 640 x 400 pixels
    XYChart *c = new XYChart(640, 400);

    // Set the plotarea at (55, 55) with width 80 pixels less than chart width, and height 92 pixels
    // less than chart height. Use a vertical gradient from light blue (f0f6ff) to sky blue (a0c0ff)
    // as background. Set border to transparent and grid lines to white (ffffff).
    c->setPlotArea(55, 55, c->getWidth() - 80, c->getHeight() - 92, c->linearGradientColor(0, 55, 0,
        c->getHeight() - 35, 0xf0f6ff, 0xa0c0ff), -1, Chart::Transparent, 0xffffff, 0xffffff);

    // As the data can lie outside the plotarea in a zoomed chart, we need enable clipping.
    c->setClipping();

    // Add a title box using dark grey (0x333333) 15pt Arial Bold font
    c->addTitle("   Zooming and Scrolling with Viewport Control", "arialbd.ttf", 15, 0x333333);

    // Set legend icon style to use line style icon, sized for 10pt font
    c->getLegend()->setLineStyleKey();
    c->getLegend()->setFontSize(10);

    // Set the x and y axis stems to transparent and the label font to 10pt Arial
    c->xAxis()->setColors(Chart::Transparent);
    c->yAxis()->setColors(Chart::Transparent);
    c->xAxis()->setLabelStyle("arial.ttf", 10);
    c->yAxis()->setLabelStyle("arial.ttf", 10);

    // Add axis title using 10pt Arial Bold font
    c->yAxis()->setTitle("Ionic Temperature (C)", "arialbd.ttf", 10);

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

    // Now we add the 3 data series to a line layer, using the color red (0xff3333), green
    // (0x008800) and blue (0x3333cc)
    layer->setXData(viewPortTimeStamps);
    layer->addDataSet(viewPortDataSeriesA, 0xff3333, "Alpha");
    layer->addDataSet(viewPortDataSeriesB, 0x008800, "Beta");
    layer->addDataSet(viewPortDataSeriesC, 0x3333cc, "Gamma");

    ///////////////////////////////////////////////////////////////////////////////////////
    // Configure axis scale and labelling
    ///////////////////////////////////////////////////////////////////////////////////////

    // Set the x-axis as a date/time axis with the scale according to the view port x range.
    viewer->syncDateAxisWithViewPort("x", c->xAxis());

    // For the automatic y-axis labels, set the minimum spacing to 30 pixels.
    c->yAxis()->setTickDensity(30);

    //
    // In this demo, the time range can be from a few years to a few days. We demonstrate how to
    // set up different date/time format based on the time range.
    //

    // If all ticks are yearly aligned, then we use "yyyy" as the label format.
    c->xAxis()->setFormatCondition("align", 360 * 86400);
    c->xAxis()->setLabelFormat("{value|yyyy}");

    // If all ticks are monthly aligned, then we use "mmm yyyy" in bold font as the first
    // label of a year, and "mmm" for other labels.
    c->xAxis()->setFormatCondition("align", 30 * 86400);
    c->xAxis()->setMultiFormat(Chart::StartOfYearFilter(), "<*font=bold*>{value|mmm<*br*>yyyy}",
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
    c->xAxis()->setMultiFormat(Chart::StartOfDayFilter(), "<*font=bold*>{value|hh:nn<*br*>mmm dd}",
        Chart::AllPassFilter(), "{value|hh:nn}");

    ///////////////////////////////////////////////////////////////////////////////////////
    // Output the chart
    ///////////////////////////////////////////////////////////////////////////////////////
    
    // We need to update the track line too. If the mouse is moving on the chart (eg. if 
    // the user drags the mouse on the chart to scroll it), the track line will be updated
    // in the MouseMovePlotArea event. Otherwise, we need to update the track line here.
    if (!viewer->isInMouseMoveEvent()) 
    {
        trackLineLegend(c, (0 == viewer->getChart()) ? c->getPlotArea()->getRightX() :
            viewer->getPlotAreaMouseX()); 
    }
    delete viewer->getChart();
    viewer->setChart(c);
}

void ViewportControlDemo::drawFullChart(QViewPortControl *vpc, QChartViewer *viewer)
{
    // Create an XYChart object of size 640 x 70 pixels
    XYChart *c = new XYChart(640, 70);

    // Set the plotarea with the same horizontal position as that in the main chart for alignment.
    c->setPlotArea(55, 5, c->getWidth() - 80, c->getHeight() - 11, 0xc0d8ff, -1, 0x888888,
        Chart::Transparent, 0xffffff);

    // Set the x axis stem to transparent and the label font to 10pt Arial
    c->xAxis()->setColors(Chart::Transparent);
    c->xAxis()->setLabelStyle("arial.ttf", 10);

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
    layer->setXData(m_timeStamps);
    layer->addDataSet(m_dataSeriesA, 0xff3333);
    layer->addDataSet(m_dataSeriesB, 0x008800);
    layer->addDataSet(m_dataSeriesC, 0x3333cc);

    // The x axis scales should reflect the full range of the view port
    c->xAxis()->setDateScale(viewer->getValueAtViewPort("x", 0), viewer->getValueAtViewPort("x", 1));

    // For the automatic x-axis labels, set the minimum spacing to 75 pixels.
    c->xAxis()->setTickDensity(75);

    // For the auto-scaled y-axis, as we hide the labels, we can disable axis rounding. This can
    // make the axis scale fit the data tighter.
    c->yAxis()->setRounding(false, false);

    // Output the chart
    vpc->setChart(c);
}

//
// The Pointer, Zoom In or Zoom out button is pressed
//
void ViewportControlDemo::onMouseUsageChanged(int mouseUsage)
{
    m_ChartViewer->setMouseUsage(mouseUsage);
}

//
// The Save button is pressed
//
void ViewportControlDemo::onSave(bool)
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
// Draw track cursor when mouse is moving over plotarea
//
void ViewportControlDemo::onMouseMovePlotArea(QMouseEvent *)
{
    trackLineLegend((XYChart *)m_ChartViewer->getChart(), m_ChartViewer->getPlotAreaMouseX());
    m_ChartViewer->updateDisplay();
}

//
// Draw track line with data labels
//
void ViewportControlDemo::trackLineLegend(XYChart *c, int mouseX)
{
    // Clear the current dynamic layer and get the DrawArea object to draw on it.
    DrawArea *d = c->initDynamicLayer();

    // The plot area object
    PlotArea *plotArea = c->getPlotArea();

    // Get the data x-value that is nearest to the mouse, and find its pixel coordinate.
    double xValue = c->getNearestXValue(mouseX);
    int xCoor = c->getXCoor(xValue);

    // Draw a vertical track line at the x-position
    d->vline(plotArea->getTopY(), plotArea->getBottomY(), xCoor, 0xaaaaaa);

    // Container to hold the legend entries
    vector<string> legendEntries;

    // Iterate through all layers to build the legend array
    for (int i = 0; i < c->getLayerCount(); ++i) {
        Layer *layer = c->getLayerByZ(i);

        // The data array index of the x-value
        int xIndex = layer->getXIndexOf(xValue);

        // Iterate through all the data sets in the layer
        for (int j = 0; j < layer->getDataSetCount(); ++j) {
            DataSet *dataSet = layer->getDataSetByZ(j);

            // We are only interested in visible data sets with names
            const char *dataName = dataSet->getDataName();
            int color = dataSet->getDataColor();
            if (dataName && *dataName && (color != Chart::Transparent)) {
                // Build the legend entry, consist of the legend icon, name and data value.
                double dataValue = dataSet->getValue(xIndex);
                ostringstream legendEntry;
                legendEntry << "<*block*>" << dataSet->getLegendIcon() << " " << dataName << ": " <<
                    ((dataValue == Chart::NoValue) ? "N/A" : c->formatValue(dataValue, "{value|P4}"))
                    << "<*/*>";
                legendEntries.push_back(legendEntry.str());

                // Draw a track dot for data points within the plot area
                int yCoor = c->getYCoor(dataSet->getPosition(xIndex), dataSet->getUseYAxis());
                if ((yCoor >= plotArea->getTopY()) && (yCoor <= plotArea->getBottomY())) {
                    d->circle(xCoor, yCoor, 5, 5, color, color);
                }
            }
        }
    }

    // Create the legend by joining the legend entries
    ostringstream legendText;
    legendText << "<*block,maxWidth=" << plotArea->getWidth() << "*><*block*><*font=arialbd.ttf*>["
        << c->xAxis()->getFormattedLabel(xValue, "mm/dd/yyyy") << "]<*/*>";
    for (int i = ((int)legendEntries.size()) - 1; i >= 0; --i)
        legendText << "        " << legendEntries[i];

    // Display the legend on the top of the plot area
    TTFText *t = d->text(legendText.str().c_str(), "arialbd.ttf", 10);
    t->draw(plotArea->getLeftX() + 5, plotArea->getTopY() - 3, 0x333333, Chart::BottomLeft);
    t->destroy();
}

