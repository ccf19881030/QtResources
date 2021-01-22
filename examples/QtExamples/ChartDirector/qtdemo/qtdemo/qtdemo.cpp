#include <QApplication>
#include <QHBoxLayout>
#include <QTreeWidget>
#include <QTreeWidgetItem>
#include <QScrollArea>
#include <QHeaderView>
#include "qchartviewer.h"
#include "qtdemo.h"
#include "democharts.h"
#include "hotspotdialog.h"


int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    QTDemo demo;
    demo.show();
    return app.exec();
}


QTDemo::QTDemo(QWidget *parent) :
    QDialog(parent)
{
    setWindowTitle("ChartDirector QT Demo");
    resize(850, 600);
    QFont defaultFont("Arial");
    defaultFont.setPixelSize(11);
    setFont(defaultFont);

    // Use horizontal layout to put the tree view on the left and the charts on the right
    QHBoxLayout *horizontalLayout = new QHBoxLayout(this);
    horizontalLayout->setMargin(4);
    horizontalLayout->setSpacing(4);

    // Tree view on the left
    QTreeWidget *treeWidget = new QTreeWidget(this);
    treeWidget->setMaximumSize(220, 16777215);
    treeWidget->setHeaderHidden(true);
    horizontalLayout->addWidget(treeWidget);

    // In addition to the visible column, we add an invisible column in the tree view to hold
    // an index to the demo modules.
    treeWidget->setColumnCount(2);
    treeWidget->hideColumn(1);

    // Loop through all the demo charts to populate the tree view
    QTreeWidgetItem *currentCategory = 0;
    for (DemoChart *d = demoCharts; 0 != d->name; ++d)
    {
        if (d->noOfCharts == 0)
            // The item is just a category heading
            treeWidget->addTopLevelItem(currentCategory
                                        = new QTreeWidgetItem(QStringList() << d->name));
        else
            // The item is a demo module. We add the index in the hidden column.
            currentCategory->addChild(new QTreeWidgetItem(
                    QStringList() << d->name << QString("%1").arg(d - demoCharts)));
    }

    treeWidget->expandAll();
    connect(treeWidget, SIGNAL(itemSelectionChanged()), SLOT(onSelectionChanged()));

    // A scroll area on the right side
    QScrollArea *scrollArea = new QScrollArea(this);
    scrollArea->setPalette(QColor(255, 255, 255));
    scrollArea->setWidgetResizable(true);
    horizontalLayout->addWidget(scrollArea);
    QWidget *scrollAreaContent = new QWidget();
    scrollArea->setWidget(scrollAreaContent);

    // Put the chart viewers in the scroll area
    for (int i = 0; i < noOfChartViewers; ++i)
    {
        chartViewers[i] = new QChartViewer(scrollAreaContent);
        chartViewers[i]->hide();
        connect(chartViewers[i], SIGNAL(clicked(QMouseEvent*)), SLOT(onChartClicked(QMouseEvent*)));
    }
}

//
// User selects an item from the tree view
//
void QTDemo::onSelectionChanged()
{
    // Get the item selected
    QTreeWidgetItem *item = ((QTreeWidget *)QObject::sender())->currentItem();

    // The hidden column should contain the index to the demo module. The index is 0 if the item
    // is just a category heading.
    int demoIndex = item->data(1, Qt::DisplayRole).toString().toInt();
    if (demoIndex > 0)
    {
        // Get the demo module
        DemoChart *d = demoCharts + demoIndex;

        // Each demo module can display a number of charts. We display all of them.
        for (int i = 0; i < d->noOfCharts; ++i)
        {
            const char *imageMap = 0;
            chartViewers[i]->setChart(d->createChart(i, &imageMap));
            chartViewers[i]->setImageMap(imageMap);
            delete chartViewers[i]->getChart();
        }

        // We hide unused chart viewers.
        for (int i = 0; i < noOfChartViewers; ++i)
            chartViewers[i]->setVisible(i < d->noOfCharts);
    }

    // Flow layout the charts
    flowLayoutCharts();
}

//
// Re-layout the charts upon container resize
//
void QTDemo::resizeEvent(QResizeEvent * /*event*/)
{
    flowLayoutCharts();
}

//
// Helper method to flow layout the charts
//
void QTDemo::flowLayoutCharts()
{
    const int margin = 5;

    // initial cursor position
    int cursorX = margin;
    int cursorY = margin;

    // initial page size
    int pageWidth = 0;
    int pageHeight = 0;

    // the width limit, beyond which wrapping will occur
    int wrapWidth = chartViewers[0]->parentWidget()->parentWidget()->width();

    for (int i = 0; i < noOfChartViewers; ++i)
    {
        // only layout visible charts
        if (!chartViewers[i]->isVisible())
            continue;

        int chartWidth =  chartViewers[i]->width();
        int chartHeight = chartViewers[i]->height();

        if (cursorX + margin + chartWidth > wrapWidth)
        {
            // no enough position in current line, so move to next line
            cursorX = margin;
            cursorY = pageHeight + margin;
        }

        // put chart in current line
        chartViewers[i]->setGeometry(cursorX, cursorY, chartWidth, chartHeight);

        // advance cursor
        cursorX += chartWidth + margin;

        if (pageWidth < cursorX)
            pageWidth = cursorX;
        if (pageHeight < cursorY + chartHeight)
            pageHeight = cursorY + chartHeight;
    }

    // resize the container to the proper size
    chartViewers[0]->parentWidget()->setFixedSize(pageWidth, pageHeight);
}

//
// User clicks on the QChartViewer
//
void QTDemo::onChartClicked(QMouseEvent * /*event*/)
{
    QChartViewer *viewer = (QChartViewer *)QObject::sender();
    ImageMapHandler *handler = viewer->getImageMapHandler();
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
