#include <QApplication>
#include "crosshair.h"
#include <sstream>

using namespace std;


int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    app.setStyleSheet("* {font-family:arial;font-size:11px}");
    CrossHair demo;
    demo.show();
    return app.exec();
}


CrossHair::CrossHair(QWidget *parent) :
    QDialog(parent)
{
    setWindowTitle("Crosshair with Axis Labels");

    // Create the QChartViewer and draw the chart
    m_ChartViewer = new QChartViewer(this);
    drawChart(m_ChartViewer);

    // Set the window to be of the same size as the chart
    setFixedSize(m_ChartViewer->width(), m_ChartViewer->height());

    // Set up the mouseMovePlotArea handler for drawing the track cursor
    connect(m_ChartViewer, SIGNAL(mouseMovePlotArea(QMouseEvent*)),
        SLOT(onMouseMovePlotArea(QMouseEvent*)));
}

CrossHair::~CrossHair()
{
    delete m_ChartViewer->getChart();
}

//
// Draw the chart and display it in the given viewer
//
void CrossHair::drawChart(QChartViewer *viewer)
{
    // The XY data of the first data series
    double dataX[] = {50, 55, 37, 24, 42, 49, 63, 72, 83, 59};
    double dataY[] = {3.6, 2.8, 2.5, 2.3, 3.8, 3.0, 3.8, 5.0, 6.0, 3.3};
	int noOfPoints = (int)(sizeof(dataX) / sizeof(*dataX));

    // Create a XYChart object of size 520 x 490 pixels
    XYChart *c = new XYChart(520, 490);

    // Set the plotarea at (60, 40) and of size 450 x 400 pixels, with white background and a light
    // grey border (0xc0c0c0). Turn on both horizontal and vertical grid lines with light grey color
    // (0xc0c0c0)
    c->setPlotArea(60, 40, 450, 400, 0xffffff, -1, 0xc0c0c0, 0xc0c0c0, -1);

    // Add a title to the chart using 18 point Times Bold Itatic font.
    c->addTitle("      Chemical X Thermal Conductivity", "timesbi.ttf", 18);

    // Add titles to the axes using 12 pts Arial Bold Italic font
    c->yAxis()->setTitle("Thermal Conductivity (W/K)", "arialbi.ttf", 12);
    c->xAxis()->setTitle("Concentration (g/liter)", "arialbi.ttf", 12);

    // Set the axes line width to 3 pixels
    c->yAxis()->setWidth(3);
    c->xAxis()->setWidth(3);

    // Add a scatter layer using (dataX, dataY)
    ScatterLayer *scatterLayer = c->addScatterLayer(DoubleArray(dataX, noOfPoints), 
		DoubleArray(dataY, noOfPoints), "", Chart::GlassSphereShape, 13, 0xcc0000);

    // Tooltip for the scatter layer
    scatterLayer->setHTMLImageMap("", "",
        "title='Concentration: {x} g/liter, Conductivity: {value} W/K'");

    // Add a trend line layer for (dataX, dataY)
    TrendLayer *trendLayer = c->addTrendLayer(DoubleArray(dataX, noOfPoints), 
		DoubleArray(dataY, noOfPoints), 0xcc0000);

    // Set the line width to 3 pixels
    trendLayer->setLineWidth(3);

    // Add a 95% confidence band for the line
    trendLayer->addConfidenceBand(0.95, 0x806666ff);

    // Add a 95% confidence band (prediction band) for the points
    trendLayer->addPredictionBand(0.95, 0x8066ff66);

    // Tool tip for the trend layer
    trendLayer->setHTMLImageMap("", "", "title='Trend Line: y = {slope|P4} x + {intercept|P4}'");

    // Add a legend box at (60, 35) (top of the chart) with horizontal layout. Use 10 pts Arial Bold
    // Italic font. Set the background and border color to Transparent and use line style legend
    // icons.
    LegendBox *legendBox = c->addLegend(60, 35, false, "arialbi.ttf", 9);
	legendBox->setBackground(Chart::Transparent);
    legendBox->setLineStyleKey(true);

    // Add entries to the legend box
    legendBox->addKey("95% Line Confidence", 0x806666ff);
    legendBox->addKey("95% Point Confidence", 0x8066ff66);

	ostringstream trendLegend;
	trendLegend << "Trend Line: y = " << c->formatValue(trendLayer->getSlope(), "{value|4}") << " x";
	trendLegend << " + " << c->formatValue(trendLayer->getIntercept(), "{value|4}");
    legendBox->addKey(trendLegend.str().c_str(), 0xcc0000, 3);

    // Set the chart image to the QChartViewer
    viewer->setChart(c);

    // Include tool tip for the chart
    viewer->setImageMap(c->getHTMLImageMap(""));
}

//
// Draw track cursor when mouse is moving over plotarea
//
void CrossHair::onMouseMovePlotArea(QMouseEvent *)
{
    crosshair((XYChart *)m_ChartViewer->getChart(), m_ChartViewer->getPlotAreaMouseX(),
        m_ChartViewer->getPlotAreaMouseY());
    m_ChartViewer->updateDisplay();
    
    // Hide the track cursor when the mouse leaves the plot area
    m_ChartViewer->removeDynamicLayer("mouseLeavePlotArea");
}

//
// Draw cross hair cursor with axis labels
//
void CrossHair::crosshair(XYChart *c, int mouseX, int mouseY)
{
    // Clear the current dynamic layer and get the DrawArea object to draw on it.
    DrawArea *d = c->initDynamicLayer();

    // The plot area object
    PlotArea *plotArea = c->getPlotArea();

    // Draw a vertical line and a horizontal line as the cross hair
    d->vline(plotArea->getTopY(), plotArea->getBottomY(), mouseX, d->dashLineColor(0x000000, 0x0101));
    d->hline(plotArea->getLeftX(), plotArea->getRightX(), mouseY, d->dashLineColor(0x000000, 0x0101));

    // Draw y-axis label
    ostringstream ylabel;
	ylabel << "<*block,bgColor=FFFFDD,margin=3,edgeColor=000000*>" << c->formatValue(c->getYValue(
        mouseY, c->yAxis()), "{value|P4}") << "<*/*>";
    TTFText *t = d->text(ylabel.str().c_str(), "arialbd.ttf", 8);
	t->draw(plotArea->getLeftX() - 5, mouseY, 0x000000, Chart::Right);
	t->destroy();

    // Draw x-axis label
    ostringstream xlabel;
	xlabel << "<*block,bgColor=FFFFDD,margin=3,edgeColor=000000*>" << c->formatValue(c->getXValue(
		mouseX), "{value|P4}") << "<*/*>";
    t = d->text(xlabel.str().c_str(), "arialbd.ttf", 8);
	t->draw(mouseX, plotArea->getBottomY() + 5, 0x000000, Chart::Top);
	t->destroy();
}
