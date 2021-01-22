#include <QApplication>
#include <QVBoxLayout>
#include <QRect>
#include "realtimesweep.h"
#include "chartdir.h"
#include <math.h>
#include <vector>
#include <sstream>

using namespace std;


int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    RealTimeSweep demo;
    demo.show();
    return app.exec();
}

RealTimeSweep::RealTimeSweep(QWidget *parent) :
    QDialog(parent, Qt::WindowCloseButtonHint | Qt::WindowMinimizeButtonHint | Qt::WindowMaximizeButtonHint)
{
    //
    // Set up the GUI
    //

    resize(720, 360);
    setWindowTitle("Real-Time Sweep Chart");

    // Use QVBoxLayout so that the content can resize automatically to fit the window.
    QVBoxLayout *layout = new QVBoxLayout();
    layout->setMargin(0);
    layout->setSpacing(0);

    // Title
    QLabel *title = new QLabel("Real-Time Sweep Chart", this);
    title->setFixedHeight(30);
    title->setAlignment(Qt::AlignCenter);
    title->setStyleSheet("* {font-family:arial;font-size:24px;background-color:#FFF;}");
    layout->addWidget(title);

    // Instead of adding the QChartViewer to the window directly, we add a QFrame to
    // the window, and then add the QChartViewer to the QFrame. This allows the chart
    // to be resized. (The QVBoxLayout would not allow the QChartViewer to be resized,
    // but it would allow the QFrame to resize.)
    QFrame *frame = new QFrame(this);
    layout->addWidget(frame);

    // Chart Viewer
    m_ChartViewer = new QChartViewer(frame);
    connect(m_ChartViewer, SIGNAL(viewPortChanged()), SLOT(onViewPortChanged()));

    // Apply the layout to the window
    setLayout(layout);

    //
    // Initialize member variables
    //
    m_currentIndex = 0;

    // Start the random data generator
    dataSource = new RandomWave(OnData, this);
    dataSource->start();

    // Set up the chart update timer
    m_ChartUpdateTimer = new QTimer(this);
    connect(m_ChartUpdateTimer, SIGNAL(timeout()), SLOT(onChartUpdateTimer()));

    // The chart update rate is set to 100ms
    m_ChartUpdateTimer->start(100);
}

RealTimeSweep::~RealTimeSweep()
{
    delete m_ChartViewer->getChart();
    delete dataSource;
}

//
// Handles realtime data from RandomWalk. The RandomWalk will call this method from its own thread.
// This is a static method.
//
void RealTimeSweep::OnData(void *self, double elapsedTime, double series0, double series1)
{
    // Copy the data into a structure and store it in the queue.
    DataPacket packet;
    packet.elapsedTime = elapsedTime;
    packet.series0 = series0;
    packet.series1 = series1;

    ((RealTimeSweep *)self)->buffer.put(packet);
}

//
// Get data from the queue, update the viewport and update the chart display if necessary.
//
void RealTimeSweep::onChartUpdateTimer()
{
    // Get new data from the queue and append them to the data arrays
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

        // Remove data older than the time range to leave space for new data. The data removed must
        // be at least equal to the packet count.
        int originalIndex = m_currentIndex;
        if (m_currentIndex > 0)
        {
            m_currentIndex -= (int)(Chart::bSearch(DoubleArray(m_timeStamps, m_currentIndex),
                m_timeStamps[m_currentIndex - 1] - timeRange));
        }
        if (m_currentIndex > sampleSize - count)
            m_currentIndex = sampleSize - count;

        for (int i = 0; i < m_currentIndex; ++i)
        {
            int srcIndex = i + originalIndex - m_currentIndex;
            m_timeStamps[i] = m_timeStamps[srcIndex];
            m_channel1[i] = m_channel1[srcIndex];
            m_channel2[i] = m_channel2[srcIndex];
        }
    }

    // Append the data from the queue to the data arrays
    for (int n = 0; n < count; ++n)
    {
        m_timeStamps[m_currentIndex] = packets[n].elapsedTime;
        m_channel1[m_currentIndex] = packets[n].series0;
        m_channel2[m_currentIndex] = packets[n].series1;
        ++m_currentIndex;
    }

    m_ChartViewer->updateViewPort(true, false);
}

//
// Update the chart if the window size is changed
//
void RealTimeSweep::resizeEvent(QResizeEvent *e)
{
    QDialog::resizeEvent(e);
    m_ChartViewer->updateViewPort(true, false);
}

//
// View port changed event
//
void RealTimeSweep::onViewPortChanged()
{
    // Update the chart if necessary
    if (m_ChartViewer->needUpdateChart())
        drawChart(m_ChartViewer);
}

//
// Draw chart
//
void RealTimeSweep::drawChart(QChartViewer *viewer)
{
    //================================================================================
    // Configure overall chart appearance.
    //================================================================================

    // Create an XYChart object extending to the container boundary, with a minimum of 300 x 150
    XYChart *c = new XYChart(std::max(300, viewer->parentWidget()->width()),
                             std::max(150, viewer->parentWidget()->height()));

    // Set the plotarea at (0, 0) with width 1 pixel less than chart width, and height 20 pixels
    // less than chart height. Use a vertical gradient from light blue (f0f6ff) to sky blue (a0c0ff)
    // as background. Set border to transparent and grid lines to white (ffffff).
    c->setPlotArea(0, 0, c->getWidth() - 1, c->getHeight() - 20, c->linearGradientColor(0, 0, 0,
        c->getHeight() - 20, 0xf0f6ff, 0xa0c0ff), -1, Chart::Transparent, 0xffffff, 0xffffff);

    // In our code, we can overdraw the line slightly, so we clip it to the plot area.
    c->setClipping();

    // Add a legend box at the right side using horizontal layout. Use 10pt Arial Bold as font.
    // Set the background and border color to Transparent and use line style legend key.
    LegendBox *b = c->addLegend(c->getWidth() - 1, 10, false, "arialbd.ttf", 10);
    b->setBackground(Chart::Transparent);
    b->setAlignment(Chart::Right);
    b->setLineStyleKey();

    // Set the x and y axis stems to transparent and the label font to 10pt Arial
    c->xAxis()->setColors(Chart::Transparent);
    c->yAxis()->setColors(Chart::Transparent);
    c->xAxis()->setLabelStyle("arial.ttf", 10);
    c->yAxis()->setLabelStyle("arial.ttf", 10, 0x336699);

    // Configure the y-axis label to be inside the plot area and above the horizontal grid lines
    c->yAxis()->setLabelGap(-1);
    c->yAxis()->setMargin(20);
    c->yAxis()->setLabelAlignment(1);

    // Configure the x-axis labels to be to the left of the vertical grid lines
    c->xAxis()->setLabelAlignment(1);

    //================================================================================
    // Add data to chart
    //================================================================================

    // We only need data form the latest time range.
    double startTime = m_timeStamps[m_currentIndex - 1] - timeRange;
    int startIndex = (int)ceil(Chart::bSearch(DoubleArray(m_timeStamps, m_currentIndex), startTime) - 0.1);

    // For a sweep chart, if the data overflow the right border (which should be a multiple
    // of the time range), it will wrap back to the left.
    double wrapTime = floor(startTime / timeRange + 1) * timeRange;
    double wrapIndex = Chart::bSearch(DoubleArray(m_timeStamps, m_currentIndex), wrapTime);

    //
    // First, draw the part of the line from the start time to the wrap time.
    //

    LineLayer *layerA = c->addLineLayer();
    layerA->setLineWidth(2);
    layerA->setFastLineMode();

    int lenA = (int)ceil(wrapIndex) - startIndex + 1;

    // The x-coordinates needs to be normalized to 0 - time_range.
    layerA->setXData(ArrayMath(DoubleArray(m_timeStamps + startIndex, lenA)).sub(
        wrapTime - timeRange).result());

    layerA->addDataSet(DoubleArray(m_channel1 + startIndex, lenA), 0xff0000, "Channel 1");
    layerA->addDataSet(DoubleArray(m_channel2 + startIndex, lenA), 0x00cc00, "Channel 2");

    //
    // Second, draw the part of the line from the wrap time to the latest time.
    //

    LineLayer *layerB = c->addLineLayer();
    layerB->setLineWidth(2);
    layerB->setFastLineMode();

    int wrapStart = (int)floor(wrapIndex);
    int lenB = m_currentIndex - wrapStart;

    // The x-coordinates need to be adjusted to 0 - time_range.
    layerB->setXData(ArrayMath(DoubleArray(m_timeStamps + wrapStart, lenB))
        .sub(wrapTime).result());

    layerB->addDataSet(DoubleArray(m_channel1 + wrapStart, lenB), 0xff0000, "Channel 1");
    layerB->addDataSet(DoubleArray(m_channel2 + wrapStart, lenB), 0x00cc00, "Channel 2");

    // Disable legend for the second part to avoid duplication with the first part.
    layerB->setLegend(Chart::NoLegend);

    //
    // Finally, we add symbols and labels for the vertical sweep line.
    //

    // The layerB contains the latest data. Add a vertical line at the latest position.
    Mark *m = c->xAxis()->addMark(layerB->getXPosition(lenB - 1), -1);
    m->setMarkColor(0x0000ff, Chart::Transparent, Chart::Transparent);
    m->setDrawOnTop(false);

    // Add symbols for each data series at the latest position
    for (int i = 0; i < layerB->getDataSetCount(); ++i)
    {
        // Add the symbol
        DataSet *dataSet = layerB->getDataSetByZ(i);
        double lastX = layerB->getXPosition(lenB - 1);
        double lastY = dataSet->getPosition(lenB - 1);
        Layer *labelLayer = c->addScatterLayer(DoubleArray(&lastX, 1), DoubleArray(&lastY, 1),
            "", Chart::CircleSymbol, 9, dataSet->getDataColor(), Chart::SameAsMainColor);
        labelLayer->moveFront();

        // Add the label
        char labelFormat[1024];
        sprintf(labelFormat, "<*font,bgColor=%x*> {value|P4} <*/font*>", dataSet->getDataColor());
        labelLayer->setDataLabelFormat(labelFormat);

        // The label style
        TextBox *t = labelLayer->setDataLabelStyle("arialbd.ttf", 10, 0xffffff);
        bool isOnLeft = lastX <= timeRange / 2;
        t->setAlignment(isOnLeft ? Chart::Left : Chart::Right);
        t->setMargin(isOnLeft ? 5 : 0, isOnLeft ? 0 : 5, 0, 0);
    }

    //================================================================================
    // Configure axis scale and labelling
    //================================================================================

    c->xAxis()->setLinearScale(0, timeRange);

    // For the automatic axis labels, set the minimum spacing to 75/40 pixels for the x/y axis.
    c->xAxis()->setTickDensity(75);
    c->yAxis()->setTickDensity(40);

    // Set the auto-scale margin to 0.05, and the zero affinity to 0.6
    c->yAxis()->setAutoScale(0.05, 0.05, 0.6);

    //================================================================================
    // Output the chart
    //================================================================================

    // Set the chart image to the CChartViewer
    delete viewer->getChart();
    viewer->setChart(c);
}
