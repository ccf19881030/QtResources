#include <QApplication>
#include "tracklegend.h"
#include <vector>
#include <sstream>

using namespace std;


int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    app.setStyleSheet("* {font-family:arial;font-size:11px}");
    TrackLegend demo;
    demo.show();
    return app.exec();
}


TrackLegend::TrackLegend(QWidget *parent) :
    QDialog(parent)
{
    setWindowTitle("Track Line with Legend");

    // Create the QChartViewer and draw the chart
    m_ChartViewer = new QChartViewer(this);
    drawChart(m_ChartViewer);

    // Set the window to be of the same size as the chart
    setFixedSize(m_ChartViewer->width(), m_ChartViewer->height());

    // Set up the mouseMovePlotArea handler for drawing the track cursor
    connect(m_ChartViewer, SIGNAL(mouseMovePlotArea(QMouseEvent*)),
        SLOT(onMouseMovePlotArea(QMouseEvent*)));
}

TrackLegend::~TrackLegend()
{
    delete m_ChartViewer->getChart();
}

//
// Draw the chart and display it in the given viewer
//
void TrackLegend::drawChart(QChartViewer *viewer)
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

    // Set legend icon style to use line style icon, sized for 8pt font
    c->getLegend()->setLineStyleKey();
    c->getLegend()->setFontSize(8);

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

    // Include track line with legend for the latest data values
    trackLineLegend(c, c->getPlotArea()->getRightX());

    // Set the chart image to the QChartViewer
    viewer->setChart(c);
}

//
// Draw track cursor when mouse is moving over plotarea
//
void TrackLegend::onMouseMovePlotArea(QMouseEvent *)
{
    trackLineLegend((XYChart *)m_ChartViewer->getChart(), m_ChartViewer->getPlotAreaMouseX());
    m_ChartViewer->updateDisplay();
}

//
// Draw the track line with legend
//
void TrackLegend::trackLineLegend(XYChart *c, int mouseX)
{
    // Clear the current dynamic layer and get the DrawArea object to draw on it.
    DrawArea *d = c->initDynamicLayer();

    // The plot area object
    PlotArea *plotArea = c->getPlotArea();

    // Get the data x-value that is nearest to the mouse, and find its pixel coordinate.
    double xValue = c->getNearestXValue(mouseX);
    int xCoor = c->getXCoor(xValue);

    // Draw a vertical track line at the x-position
    d->vline(plotArea->getTopY(), plotArea->getBottomY(), xCoor, d->dashLineColor(0x000000, 0x0101));

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
            if (dataName && *dataName && (color != (int)Chart::Transparent)) {
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
                    d->circle(xCoor, yCoor, 4, 4, color, color);
                }
            }
        }
    }

    // Create the legend by joining the legend entries
    ostringstream legendText;
    legendText << "<*block,maxWidth=" << plotArea->getWidth() << "*><*block*><*font=arialbd.ttf*>["
        << c->xAxis()->getFormattedLabel(xValue, "mmm dd, yyyy") << "]<*/*>";
    for (int i = ((int)legendEntries.size()) - 1; i >= 0; --i)
        legendText << "        " << legendEntries[i];

    // Display the legend on the top of the plot area
    TTFText *t = d->text(legendText.str().c_str(), "arial.ttf", 8);
    t->draw(plotArea->getLeftX() + 5, plotArea->getTopY() - 3, 0x000000, Chart::BottomLeft);
    t->destroy();
}
