#include <QApplication>
#include <QButtonGroup>
#include <QIcon>
#include <QPushButton>
#include <QComboBox>
#include "realtimetrack.h"
#include "chartdir.h"
#include <math.h>
#include <vector>
#include <sstream>

using namespace std;


int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    app.setStyleSheet("* {font-family:arial;font-size:11px}");
    RealtimeTrack demo;
    demo.show();
    return app.exec();
}


static const int DataInterval = 250;

RealtimeTrack::RealtimeTrack(QWidget *parent) :
    QDialog(parent)
{
    //
    // Set up the GUI
    //

    setFixedSize(740, 285);
    setWindowTitle("Realtime Chart with Track Line");

    // The frame on the left side
    QFrame *frame = new QFrame(this);
    frame->setGeometry(4, 4, 120, 277);
    frame->setFrameShape(QFrame::StyledPanel);

    // Run push button
    QPushButton *runPB = new QPushButton(QIcon(":/play.png"), "Run", frame);
    runPB->setGeometry(4, 8, 112, 28);
    runPB->setStyleSheet("QPushButton { text-align:left; padding:5px}");
    runPB->setCheckable(true);

    // Freeze push button
    QPushButton *freezePB = new QPushButton(QIcon(":/pause.png"), "Freeze", frame);
    freezePB->setGeometry(4, 36, 112, 28);
    freezePB->setStyleSheet("QPushButton { text-align:left; padding:5px}");
    freezePB->setCheckable(true);

    // The Run/Freeze buttons form a button group
    QButtonGroup *runFreezeControl = new QButtonGroup(frame);
    runFreezeControl->addButton(runPB, 1);
    runFreezeControl->addButton(freezePB, 0);
    connect(runFreezeControl, SIGNAL(buttonPressed(int)), SLOT(onRunFreezeChanged(int)));

    // Update Period drop down list box
    (new QLabel("Update Period (ms)", frame))->setGeometry(6, 80, 108, 16);
    QComboBox *updatePeriod = new QComboBox(frame);
    updatePeriod->setGeometry(6, 96, 108, 21);
    updatePeriod->addItems(QStringList() << "250" << "500" << "750" << "1000" << "1250" << "1500"
                           << "1750" << "2000");
    connect(updatePeriod, SIGNAL(currentIndexChanged(QString)),
            SLOT(onUpdatePeriodChanged(QString)));

    // Alpha Value display
    (new QLabel("Alpha", frame))->setGeometry(6, 200, 48, 21);
    m_ValueA = new QLabel(frame);
    m_ValueA->setGeometry(55, 200, 59, 21);
    m_ValueA->setFrameShape(QFrame::StyledPanel);

    // Beta Value display
    (new QLabel("Beta", frame))->setGeometry(6, 223, 48, 21);
    m_ValueB = new QLabel(frame);
    m_ValueB->setGeometry(55, 223, 59, 21);
    m_ValueB->setFrameShape(QFrame::StyledPanel);

    // Gamma Value display
    (new QLabel("Gamma", frame))->setGeometry(6, 246, 48, 21);
    m_ValueC = new QLabel(frame);
    m_ValueC->setGeometry(55, 246, 59, 21);
    m_ValueC->setFrameShape(QFrame::StyledPanel);

    // Chart Viewer
    m_ChartViewer = new QChartViewer(this);
    m_ChartViewer->setGeometry(132, 8, 600, 270);
    connect(m_ChartViewer, SIGNAL(viewPortChanged()), SLOT(drawChart()));
    connect(m_ChartViewer, SIGNAL(mouseMovePlotArea(QMouseEvent*)),
        SLOT(onMouseMovePlotArea(QMouseEvent*)));

    // Clear data arrays to Chart::NoValue
    for (int i = 0; i < sampleSize; ++i)
        m_timeStamps[i] = m_dataSeriesA[i] = m_dataSeriesB[i] = m_dataSeriesC[i] = Chart::NoValue;
    m_currentIndex = 0;

    // Set m_nextDataTime to the current time. It is used by the real time random number
    // generator so it knows what timestamp should be used for the next data point.
    m_nextDataTime = QDateTime::currentDateTime();

    // Set up the data acquisition mechanism. In this demo, we just use a timer to get a
    // sample every 250ms.
    QTimer *dataRateTimer = new QTimer(this);
    dataRateTimer->start(DataInterval);
    connect(dataRateTimer, SIGNAL(timeout()), SLOT(getData()));

    // Set up the chart update timer
    m_ChartUpdateTimer = new QTimer(this);
    connect(m_ChartUpdateTimer, SIGNAL(timeout()), SLOT(updateChart()));

    // Can start now
    updatePeriod->setCurrentIndex(3);
    runPB->click();
}

RealtimeTrack::~RealtimeTrack()
{
    delete m_ChartViewer->getChart();   
}
        
//
// A utility to shift a new data value into a data array
//
static void shiftData(double *data, int len, double newValue)
{
    memmove(data, data + 1, sizeof(*data) * (len - 1));
    data[len - 1] = newValue;
}

//
// Shift new data values into the real time data series
//
void RealtimeTrack::getData()
{
    // The current time
    QDateTime now = QDateTime::currentDateTime();

    // This is our formula for the random number generator
    do
    {
        // We need the currentTime in millisecond resolution
        double currentTime = Chart::chartTime2(m_nextDataTime.toTime_t())
                             + m_nextDataTime.time().msec() / 1000.0;

        // Get a data sample
        double p = currentTime * 4;
        double dataA = 20 + cos(p * 129241) * 10 + 1 / (cos(p) * cos(p) + 0.01);
        double dataB = 150 + 100 * sin(p / 27.7) * sin(p / 10.1);
        double dataC = 150 + 100 * cos(p / 6.7) * cos(p / 11.9);

        // After obtaining the new values, we need to update the data arrays.
        if (m_currentIndex < sampleSize)
        {
            // Store the new values in the current index position, and increment the index.
            m_dataSeriesA[m_currentIndex] = dataA;
            m_dataSeriesB[m_currentIndex] = dataB;
            m_dataSeriesC[m_currentIndex] = dataC;
            m_timeStamps[m_currentIndex] = currentTime;
            ++m_currentIndex;
        }
        else
        {
            // The data arrays are full. Shift the arrays and store the values at the end.
            shiftData(m_dataSeriesA, sampleSize, dataA);
            shiftData(m_dataSeriesB, sampleSize, dataB);
            shiftData(m_dataSeriesC, sampleSize, dataC);
            shiftData(m_timeStamps, sampleSize, currentTime);
        }

        m_nextDataTime = m_nextDataTime.addMSecs(DataInterval);
    }
    while (m_nextDataTime < now);

    //
    // We provide some visual feedback to the latest numbers generated, so you can see the
    // data being generated.
    //
    m_ValueA->setText(QString::number(m_dataSeriesA[m_currentIndex - 1], 'f', 2));
    m_ValueB->setText(QString::number(m_dataSeriesB[m_currentIndex - 1], 'f', 2));
    m_ValueC->setText(QString::number(m_dataSeriesC[m_currentIndex - 1], 'f', 2));
}

//
// The Run or Freeze button is pressed
//
void RealtimeTrack::onRunFreezeChanged(int run)
{
    if (run)
        m_ChartUpdateTimer->start();
    else
        m_ChartUpdateTimer->stop();
}

//
// User changes the chart update period
//
void RealtimeTrack::onUpdatePeriodChanged(QString text)
{
    m_ChartUpdateTimer->start(text.toInt());
}

//
// Update the chart. Instead of drawing the chart directly, we call updateViewPort, which
// will trigger a ViewPortChanged signal. We update the chart in the signal handler
// "drawChart". This can take advantage of the built-in rate control in QChartViewer to
// ensure a smooth user interface, even for extremely high update rate. (See the
// documentation on QChartViewer.setUpdateInterval).
//
void RealtimeTrack::updateChart()
{
    m_ChartViewer->updateViewPort(true, false);
}

//
// Draw chart
//
void RealtimeTrack::drawChart()
{
    // Create an XYChart object 600 x 270 pixels in size, with light grey (f4f4f4) 
    // background, black (000000) border, 1 pixel raised effect, and with a rounded frame.
    XYChart *c = new XYChart(600, 270, 0xf4f4f4, 0x000000, 1);
    QColor bgColor = palette().color(backgroundRole()).rgb();
    c->setRoundedFrame((bgColor.red() << 16) + (bgColor.green() << 8) + bgColor.blue());

    // Set the plotarea at (55, 55) and of size 520 x 185 pixels. Use white (ffffff) 
    // background. Enable both horizontal and vertical grids by setting their colors to 
    // grey (cccccc). Set clipping mode to clip the data lines to the plot area.
    c->setPlotArea(55, 55, 520, 185, 0xffffff, -1, -1, 0xcccccc, 0xcccccc);
    c->setClipping();

    // Add a title to the chart using 15 pts Times New Roman Bold Italic font, with a light
    // grey (dddddd) background, black (000000) border, and a glass like raised effect.
    c->addTitle("Field Intensity at Observation Satellite", "timesbi.ttf", 15
        )->setBackground(0xdddddd, 0x000000, Chart::glassEffect());
            
    // Set the reference font size of the legend box
    c->getLegend()->setFontSize(8);

    // Configure the y-axis with a 10pts Arial Bold axis title
    c->yAxis()->setTitle("Intensity (V/m)", "arialbd.ttf", 10);

    // Configure the x-axis to auto-scale with at least 75 pixels between major tick and 
    // 15  pixels between minor ticks. This shows more minor grid lines on the chart.
    c->xAxis()->setTickDensity(75, 15);

    // Set the axes width to 2 pixels
    c->xAxis()->setWidth(2);
    c->yAxis()->setWidth(2);

    // Now we add the data to the chart. 
    double firstTime  = m_timeStamps[0];
    if (firstTime != Chart::NoValue)
    {
        // Set up the x-axis to show the time range in the data buffer
        c->xAxis()->setDateScale(firstTime, firstTime + DataInterval * sampleSize / 1000);
        
        // Set the x-axis label format
        c->xAxis()->setLabelFormat("{value|hh:nn:ss}");

        // Create a line layer to plot the lines
        LineLayer *layer = c->addLineLayer();

        // The x-coordinates are the timeStamps.
        layer->setXData(DoubleArray(m_timeStamps, sampleSize));

        // The 3 data series are used to draw 3 lines.
        layer->addDataSet(DoubleArray(m_dataSeriesA, sampleSize), 0xff0000, "Alpha");
        layer->addDataSet(DoubleArray(m_dataSeriesB, sampleSize), 0x00cc00, "Beta");
        layer->addDataSet(DoubleArray(m_dataSeriesC, sampleSize), 0x0000ff, "Gamma");
    }

    // Include track line with legend. If the mouse is on the plot area, show the track 
    // line with legend at the mouse position; otherwise, show them for the latest data
    // values (that is, at the rightmost position).
    trackLineLegend(c, m_ChartViewer->isMouseOnPlotArea() ? m_ChartViewer->getPlotAreaMouseX() :
        c->getPlotArea()->getRightX());

    // Set the chart image to the WinChartViewer
    delete m_ChartViewer->getChart();
    m_ChartViewer->setChart(c);
}

//
// Draw track cursor when mouse is moving over plotarea
//
void RealtimeTrack::onMouseMovePlotArea(QMouseEvent *)
{
    trackLineLegend((XYChart *)m_ChartViewer->getChart(), m_ChartViewer->getPlotAreaMouseX());
    m_ChartViewer->updateDisplay();
}

//
// Draw the track line with legend
//
void RealtimeTrack::trackLineLegend(XYChart *c, int mouseX)
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
        << c->xAxis()->getFormattedLabel(xValue, "hh:nn:ss") << "]<*/*>";
    for (int i = ((int)legendEntries.size()) - 1; i >= 0; --i)
        legendText << "        " << legendEntries[i];
    
    // Display the legend on the top of the plot area
    TTFText *t = d->text(legendText.str().c_str(), "arial.ttf", 8);
    t->draw(plotArea->getLeftX() + 5, plotArea->getTopY() - 3, 0x000000, Chart::BottomLeft);
    t->destroy();
}
