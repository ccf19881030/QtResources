#include <QApplication>
#include <QButtonGroup>
#include <QMouseEvent>
#include <QFileDialog>
#include "xyzoomscroll.h"
#include "hotspotdialog.h"
#include <sstream>
#include <algorithm>

using namespace std;


int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    app.setStyleSheet("* {font-family:arial;font-size:11px}");
    XYZoomScroll demo;
    demo.show();
    return app.exec();
}


XYZoomScroll::XYZoomScroll(QWidget *parent) :
    QDialog(parent)
{
    setWindowTitle("XY Zooming and Scrolling");
    setFixedSize(644, 488);

    QFrame *frame = new QFrame(this);
    frame->setGeometry(4, 4, 120, 481);
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
    zoomOutPB->setGeometry(4, 64, 112, 28);
    zoomOutPB->setStyleSheet("QPushButton { text-align:left; padding:5px}");
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

    // Zoom Mode label
    QLabel *zoomModeLabel = new QLabel("Zoom Level", frame);
    zoomModeLabel->setGeometry(6, 180, 110, 18);
    zoomModeLabel->setAlignment(Qt::AlignHCenter);

    // Zoom level bar
    m_ZoomBar = new QSlider(Qt::Horizontal, frame);
    m_ZoomBar->setGeometry(12, 205, 102, 41);
    m_ZoomBar->setRange(1, 100);
    m_ZoomBar->setTickPosition(QSlider::TicksBothSides);
    m_ZoomBar->setInvertedAppearance(true);
    connect(m_ZoomBar, SIGNAL(valueChanged(int)), SLOT(onZoomBarChanged(int)));

    // Viewport Control
    m_ViewPortControl = new QViewPortControl(frame);
    m_ViewPortControl->setGeometry(QRect(5, 334, 112, 112));

    // Chart Viewer
    m_ChartViewer = new QChartViewer(this);
    m_ChartViewer->setGeometry(QRect(136, 4, 500, 480));
    connect(m_ChartViewer, SIGNAL(viewPortChanged()), SLOT(onViewPortChanged()));
    connect(m_ChartViewer, SIGNAL(mouseMovePlotArea(QMouseEvent*)), SLOT(onMouseMovePlotArea(QMouseEvent*)));
    connect(m_ChartViewer, SIGNAL(clicked(QMouseEvent*)), SLOT(onClickChart(QMouseEvent*)));

    //
    // Initialize member variables
    //

    // Set initial zoom/scroll direction
    m_ChartViewer->setScrollDirection(Chart::DirectionHorizontalVertical);
    m_ChartViewer->setZoomDirection(Chart::DirectionHorizontalVertical);

    // Initially set the mouse to drag to scroll mode
    pointerPB->click();

    // Enable mouse wheel zooming by setting the zoom ratio to 1.1 per wheel event
    m_ChartViewer->setMouseWheelZoomRatio(1.1);

    // Load the data
    loadData();

    // Can update chart now
    m_ChartViewer->updateViewPort(true, true);

    // Configure the CViewPortControl to use transparent black for region outside the viewport,
    // that is, to darken the outside region.
    m_ViewPortControl->setViewPortExternalColor(0x7f000000);
    m_ViewPortControl->setViewPortBorderColor(0x7fffffff);
    m_ViewPortControl->setSelectionBorderColor(0x7fffffff); 

    // Draw and display the full chart in the QViewPortControl
    drawFullChart(m_ViewPortControl, m_ChartViewer);

    // Bind the QChartViewer to the QViewPortControl
    m_ViewPortControl->setViewer(m_ChartViewer);
}

XYZoomScroll::~XYZoomScroll()
{
    delete m_ChartViewer->getChart();
    delete m_ViewPortControl->getChart();
}

//
// The ViewPortChanged event handler. This event occurs if the user scrolls or zooms in or
// out the chart by dragging or clicking on the chart. It can also be triggered by calling
// QChartViewer.updateViewPort.
//
void XYZoomScroll::onViewPortChanged()
{
    // In addition to updating the chart, we may also need to update other controls that
    // changes based on the view port.
    updateControls(m_ChartViewer);

    //
    // Update chart and image map if necessary
    //
    if (m_ChartViewer->needUpdateChart())
        drawChart(m_ChartViewer);
    if (m_ChartViewer->needUpdateImageMap())
        updateImageMap(m_ChartViewer);
}

//
// Update other controls that may be affected by the viewport.
//
void XYZoomScroll::updateControls(QChartViewer *viewer)
{
    //
    // Update the Zoom slider to reflect the current zoom level of the view port
    //
    double smallerSide = viewer->getViewPortWidth() > viewer->getViewPortHeight()
        ? viewer->getViewPortHeight() : viewer->getViewPortWidth();
    m_ZoomBar->setValue((int)(smallerSide * m_ZoomBar->maximum() + 0.5));
}

//
// Load the data
//
void XYZoomScroll::loadData()
{
    //
    // For simplicity, in this demo, we just use hard coded data.
    //
    double X0[] = {10, 15, 6, -12, 14, -8, 13, -3, 16, 12, 10.5, -7, 3, -10, -5, 2, 5};
    double Y0[] = {130, 150, 80, 110, -110, -105, -130, -15, -170, 125,  125, 60, 25, 150,
        150, 15, 120};
    double X1[] = {6, 7, -4, 3.5, 7, 8, -9, -10, -12, 11, 8, -3, -2, 8, 4, -15, 15};
    double Y1[] = {65, -40, -40, 45, -70, -80, 80, 10, -100, 105, 60, 50, 20, 170, -25,
        50, 75};
    double X2[] = {-10, -12, 11, 8, 6, 12, -4, 3.5, 7, 8, -9, 3, -13, 16, -7.5, -10, -15};
    double Y2[] = {65, -80, -40, 45, -70, -80, 80, 90, -100, 105, 60, -75, -150, -40, 120,
        -50, -30};

    dataX0.assign(X0, X0 + sizeof(X0) / sizeof(*X0));
    dataY0.assign(Y0, Y0 + sizeof(Y0) / sizeof(*Y0));
    dataX1.assign(X1, X1 + sizeof(X1) / sizeof(*X1));
    dataY1.assign(Y1, Y1 + sizeof(Y1) / sizeof(*Y1));
    dataX2.assign(X2, X2 + sizeof(X2) / sizeof(*X2));
    dataY2.assign(Y2, Y2 + sizeof(Y2) / sizeof(*Y2));
}

//
// Draw the chart and display it in the given viewer
//
void XYZoomScroll::drawChart(QChartViewer *viewer)
{
    // Create an XYChart object 500 x 480 pixels in size, with the same background color
    // as the container
    QColor bgColor = palette().color(backgroundRole()).rgb();
    XYChart *c = new XYChart(500, 480, (bgColor.red() << 16) + (bgColor.green() << 8) + bgColor.blue());

    // Set the plotarea at (50, 40) and of size 400 x 400 pixels. Use light grey (c0c0c0)
    // horizontal and vertical grid lines. Set 4 quadrant coloring, where the colors of 
    // the quadrants alternate between lighter and deeper grey (dddddd/eeeeee). 
    c->setPlotArea(50, 40, 400, 400, -1, -1, -1, 0xc0c0c0, 0xc0c0c0
        )->set4QBgColor(0xdddddd, 0xeeeeee, 0xdddddd, 0xeeeeee, 0x000000);

    // Enable clipping mode to clip the part of the data that is outside the plot area.
    c->setClipping();

    // Set 4 quadrant mode, with both x and y axes symetrical around the origin
    c->setAxisAtOrigin(Chart::XYAxisAtOrigin, Chart::XAxisSymmetric + Chart::YAxisSymmetric);

    // Add a legend box at (450, 40) (top right corner of the chart) with vertical layout
    // and 8 pts Arial Bold font. Set the background color to semi-transparent grey.
    LegendBox *legendBox = c->addLegend(450, 40, true, "arialbd.ttf", 8);
    legendBox->setAlignment(Chart::TopRight);
    legendBox->setBackground(0x40dddddd);

    // Add a titles to axes
    c->xAxis()->setTitle("Alpha Index");
    c->yAxis()->setTitle("Beta Index");

    // Set axes width to 2 pixels
    c->xAxis()->setWidth(2);
    c->yAxis()->setWidth(2);

    // The default ChartDirector settings has a denser y-axis grid spacing and less-dense
    // x-axis grid spacing. In this demo, we want the tick spacing to be symmetrical.
    // We use around 50 pixels between major ticks and 25 pixels between minor ticks.
    c->xAxis()->setTickDensity(50, 25);
    c->yAxis()->setTickDensity(50, 25);

    //
    // In this example, we represent the data by scatter points. If you want to represent
    // the data by somethings else (lines, bars, areas, floating boxes, etc), just modify
    // the code below to use the layer type of your choice. 
    //

    // Add scatter layer, using 11 pixels red (ff33333) X shape symbols
    c->addScatterLayer(vectorToArray(dataX0), vectorToArray(dataY0), "Group A", 
        Chart::Cross2Shape(), 11, 0xff3333);

    // Add scatter layer, using 11 pixels green (33ff33) circle symbols
    c->addScatterLayer(vectorToArray(dataX1), vectorToArray(dataY1), "Group B", 
        Chart::CircleShape, 11,  0x33ff33);

    // Add scatter layer, using 11 pixels blue (3333ff) triangle symbols
    c->addScatterLayer(vectorToArray(dataX2), vectorToArray(dataY2), "Group C", 
        Chart::TriangleSymbol, 11, 0x3333ff);

    //
    // In this example, we have not explicitly configured the full x and y range. In this case, 
    // the first time syncLinearAxisWithViewPort is called, ChartDirector will auto-scale the axis
    // and assume the resulting range is the full range. In subsequent calls, ChartDirector will 
    // set the axis range based on the view port and the full range.
    //
    viewer->syncLinearAxisWithViewPort("x", c->xAxis());
    viewer->syncLinearAxisWithViewPort("y", c->yAxis());
    
    // We need to update the track line too. If the mouse is moving on the chart (eg. if 
    // the user drags the mouse on the chart to scroll it), the track line will be updated
    // in the MouseMovePlotArea event. Otherwise, we need to update the track line here.
    if ((!viewer->isInMouseMoveEvent()) && viewer->isMouseOnPlotArea())
        crossHair(c, viewer->getPlotAreaMouseX(), viewer->getPlotAreaMouseY());

    // Set the chart image to the QChartViewer
    delete viewer->getChart();
    viewer->setChart(c);
}

//
// Draw the full thumbnail chart and display it in the given CViewPortControl
//
void XYZoomScroll::drawFullChart(QViewPortControl *vpc, QChartViewer *viewer)
{
    // Create an XYChart object 110 x 110 pixels in size
    XYChart *c = new XYChart(110, 110);

    // Set the plotarea to cover the entire chart. Disable grid lines by setting their colors
    // to transparent. Set 4 quadrant coloring, where the colors of the quadrants alternate
    // between lighter and deeper grey (dddddd/eeeeee).
    c->setPlotArea(0, 0, c->getWidth() - 1, c->getHeight() - 1, -1, -1, -1, Chart::Transparent,
        Chart::Transparent)->set4QBgColor(0xdddddd, 0xeeeeee, 0xdddddd, 0xeeeeee, 0x000000);

    // Set 4 quadrant mode, with both x and y axes symetrical around the origin
    c->setAxisAtOrigin(Chart::XYAxisAtOrigin, Chart::XAxisSymmetric + Chart::YAxisSymmetric);

    // The x and y axis scales reflect the full range of the view port
    c->xAxis()->setLinearScale(viewer->getValueAtViewPort("x", 0), viewer->getValueAtViewPort(
        "x", 1), Chart::NoValue);
    c->yAxis()->setLinearScale(viewer->getValueAtViewPort("y", 0), viewer->getValueAtViewPort(
        "y", 1), Chart::NoValue);

    // Add scatter layer, using 11 pixels red (ff33333) X shape symbols
    c->addScatterLayer(vectorToArray(dataX0), vectorToArray(dataY0), "", Chart::Cross2Shape(),
        3, 0xff3333, 0xff3333);

    // Add scatter layer, using 11 pixels green (33ff33) circle symbols
    c->addScatterLayer(vectorToArray(dataX1), vectorToArray(dataY1), "", Chart::CircleShape,
        3, 0x33ff33, 0x33ff33);

    // Add scatter layer, using 11 pixels blue (3333ff) triangle symbols
    c->addScatterLayer(vectorToArray(dataX2), vectorToArray(dataY2), "", Chart::TriangleSymbol,
        3, 0x3333ff, 0x3333ff);

    // Set the chart image to the WinChartViewer
    vpc->setChart(c);
}

//
// Update the image map
//
void XYZoomScroll::updateImageMap(QChartViewer *viewer)
{
    if (0 == viewer->getImageMapHandler())
    {
        // no existing image map - creates a new one
        viewer->setImageMap(viewer->getChart()->getHTMLImageMap("clickable", "",
            "title='[{dataSetName}] Alpha = {x}, Beta = {value}'"));
    }
}

//
// User clicks on the QChartViewer
//
void XYZoomScroll::onClickChart(QMouseEvent *)
{
    ImageMapHandler *handler = m_ChartViewer->getImageMapHandler();
    if (0 != handler)
    {
        // Query the ImageMapHandler to see if the mouse is on a clickable hot spot. We
        // consider the hot spot as clickable if its href ("path") parameter is not empty.
        const char *path = handler->getValue("path");
        if ((0 != path) && (0 != *path))
        {
            // In this sample code, we just show all hot spot parameters.
            HotSpotDialog hs;
            hs.setData(handler);
            hs.exec();
        }
    }
}

//
// The Pointer, Zoom In or Zoom out button is pressed
//
void XYZoomScroll::onMouseUsageChanged(int mouseUsage)
{
    m_ChartViewer->setMouseUsage(mouseUsage);
}

//
// The Save button is pressed
//
void XYZoomScroll::onSave(bool)
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
// User moves the Zoom slider control
//
void XYZoomScroll::onZoomBarChanged(int value)
{
    if (!m_ChartViewer->isInViewPortChangedEvent())
    {
        // Remember the center point
        double centerX = m_ChartViewer->getViewPortLeft() +
            m_ChartViewer->getViewPortWidth() / 2;
        double centerY = m_ChartViewer->getViewPortTop() +
            m_ChartViewer->getViewPortHeight() / 2;

        // Aspect ratio and zoom factor
        double aspectRatio = m_ChartViewer->getViewPortWidth() /
            m_ChartViewer->getViewPortHeight();
        double zoomTo = ((double)value) / m_ZoomBar->maximum();

        // Zoom by adjusting ViewPortWidth and ViewPortHeight while maintaining the aspect ratio
        m_ChartViewer->setViewPortWidth(zoomTo * ((aspectRatio < 1) ? 1 : aspectRatio));
        m_ChartViewer->setViewPortHeight(zoomTo * ((aspectRatio > 1) ? 1 : (1 / aspectRatio)));

        // Adjust ViewPortLeft and ViewPortTop to keep center point unchanged
        m_ChartViewer->setViewPortLeft(centerX - m_ChartViewer->getViewPortWidth() / 2);
        m_ChartViewer->setViewPortTop(centerY - m_ChartViewer->getViewPortHeight() / 2);

        // Update the chart image only, but no need to update the image map.
        m_ChartViewer->updateViewPort(true, false);
    }
}

//
// Draw track cursor when mouse is moving over plotarea, and update image map if necessary
//
void XYZoomScroll::onMouseMovePlotArea(QMouseEvent *)
{
    // Draw crosshair track cursor
    crossHair((XYChart *)m_ChartViewer->getChart(), m_ChartViewer->getPlotAreaMouseX(),
        m_ChartViewer->getPlotAreaMouseY());
    m_ChartViewer->updateDisplay();

    // Hide the track cursor when the mouse leaves the plot area
    m_ChartViewer->removeDynamicLayer("mouseLeavePlotArea");

    // Update image map if necessary. If the mouse is still dragging, the chart is still 
    // updating and not confirmed, so there is no need to set up the image map.
    if (!m_ChartViewer->isMouseDragging())
        updateImageMap(m_ChartViewer);
}

//
// Draw cross hair cursor with axis labels
//
void XYZoomScroll::crossHair(XYChart *c, int mouseX, int mouseY)
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

//
// Convert std::vector to a DoubleArray
//
DoubleArray XYZoomScroll::vectorToArray(std::vector<double> &v)
{
    return (v.size() == 0) ? DoubleArray() : DoubleArray(&(v[0]), v.size());
}
