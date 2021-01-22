#ifndef QCHARTVIEWER_H
#define QCHARTVIEWER_H

#include <QLabel>
#include "chartdir.h"

#ifdef CD_NAMESPACE
namespace CD_NAMESPACE
{
#endif

namespace Chart
{
    //
    // Mouse usage mode constants
    //
    enum
    {
        MouseUsageDefault = 0,
        MouseUsageScroll = 1,
        MouseUsageZoomIn = 3,
        MouseUsageZoomOut = 4
    };
}

#ifdef CD_NAMESPACE
}
#endif

//
// Forward declarations
//
class QMouseEvent;

class QChartViewer : public QLabel, public ViewPortManager
{
Q_OBJECT
public:
    explicit QChartViewer(QWidget *parent = 0);
    ~QChartViewer();

    //
    // QChartViewer properties
    //

    virtual void setChart(BaseChart *c);
    virtual BaseChart *getChart();

    virtual void setImageMap(const char *imageMap);
    virtual ImageMapHandler *getImageMapHandler();

    virtual void setDefaultToolTip(QString text);

    virtual void setSelectionBorderWidth(int width);
    virtual int getSelectionBorderWidth();

    virtual void setSelectionBorderColor(QColor c);
    virtual QColor getSelectionBorderColor();

    virtual void setMouseUsage(int mouseUsage);
    virtual int getMouseUsage();

    virtual void setZoomDirection(int direction);
    virtual int getZoomDirection();

    virtual void setScrollDirection(int direction);
    virtual int getScrollDirection();

    virtual void setZoomInRatio(double ratio);
    virtual double getZoomInRatio();

    virtual void setZoomOutRatio(double ratio);
    virtual double getZoomOutRatio();

    virtual void setMouseWheelZoomRatio(double ratio);
    virtual double getMouseWheelZoomRatio();

    virtual void setMinimumDrag(int offset);
    virtual int getMinimumDrag();

    virtual void setUpdateInterval(int interval);
    virtual int getUpdateInterval();

    virtual bool needUpdateChart();
    virtual bool needUpdateImageMap();

    virtual bool isMouseOnPlotArea();
    virtual bool isInMouseMoveEvent();
    virtual bool isInViewPortChangedEvent();
    virtual bool isMouseDragging();

    //
    // QChartViewer methods
    //

    // Trigger the ViewPortChanged event
    virtual void updateViewPort(bool needUpdateChart, bool needUpdateImageMap);

    // Request CChartViewer to redisplay the chart
    virtual void updateDisplay();

    // Handles mouse wheel zooming
    virtual bool onMouseWheelZoom(int x, int y, int zDelta);

    // Set the message used to remove the dynamic layer
    virtual void removeDynamicLayer(const char *msg);

    // Get the mouse coordinates
    virtual int getChartMouseX();
    virtual int getChartMouseY();

    // Get the mouse coordinates bounded to the plot area
    virtual int getPlotAreaMouseX();
    virtual int getPlotAreaMouseY();

protected:
    //
    // QChartViewer event handlers
    //

    virtual void mouseMoveEvent(QMouseEvent *event);
    virtual void onDelayedMouseMove();
    virtual void mousePressEvent(QMouseEvent *event);
    virtual void mouseReleaseEvent(QMouseEvent *event);
    virtual void leaveEvent(QEvent *event);
    virtual void wheelEvent(QWheelEvent *event);
    virtual void timerEvent (QTimerEvent *event);
    virtual void onSetCursor();

private:
    //
    // QChartViewer configurable properties
    //

    BaseChart *m_currentChart;          // Current BaseChart object
    ImageMapHandler *m_hotSpotTester;   // ImageMapHander representing the image map
    QString m_defaultToolTip;           // Default tool tip text
    QColor m_selectBoxLineColor;        // Selectiom box border color
    int m_selectBoxLineWidth;           // Selectiom box border width
    int m_mouseUsage;                   // Mouse usage mode
    int m_zoomDirection;                // Zoom direction
    int m_scrollDirection;              // Scroll direction
    double m_zoomInRatio;               // Click zoom in ratio
    double m_zoomOutRatio;              // Click zoom out ratio
    double m_mouseWheelZoomRatio;       // Mouse wheel zoom ratio
    int m_minDragAmount;                // Minimum drag amount
    int m_updateInterval;               // Minimum interval between chart updates
    bool m_needUpdateChart;             // Has pending chart update request
    bool m_needUpdateImageMap;          // Has pending image map udpate request

    //
    // Keep track of mouse states
    //

    int m_currentHotSpot;               // The hot spot under the mouse cursor.
    bool m_isClickable;                 // Mouse is over a clickable hot spot.
    bool m_isOnPlotArea;                // Mouse is over the plot area.
    bool m_isPlotAreaMouseDown;         // Mouse left button is down in the plot area.
    bool m_isDragScrolling;             // Is current dragging scrolling the chart.
    bool m_isMouseTracking;             // Is tracking mouse leave event
    bool m_isInMouseMove;               // Is in mouse moeve event handler

    //
    // Dragging support
    //

    int m_plotAreaMouseDownXPos;        // The starting x coordinate of the mouse drag.
    int m_plotAreaMouseDownYPos;        // The starting y coordinate of the mouse drag.
    bool isDrag(int direction, QMouseEvent *event);   // Check if mouse is dragging
    void onPlotAreaMouseDrag(QMouseEvent *point);     // Process mouse dragging

    //
    // Selection rectangle
    //

    QLabel *m_LeftLine;                 // Left edge of selection rectangle
    QLabel *m_RightLine;                // Right edge of selection rectangle
    QLabel *m_TopLine;                  // Top edge of selection rectangle
    QLabel *m_BottomLine;               // Bottom edge of selection rectangle

    void initRect();                    // Initialize selection rectangle edges
    void drawRect(int x, int y, int width, int height);     // Draw selection rectangle
    void setRectVisible(bool b);        // Show/hide selection rectangle

    //
    // Chart update rate control
    //

    bool m_holdTimerActive;             // Delay chart update to limit update frequency
    int m_holdTimerId;                  // The id of the hold timer.
    bool m_isInViewPortChanged;         // Flag to avoid infinite update loops

    int m_delayUpdateChart;             // Delay chart update until the mouse event is completed
    BaseChart *m_delayedChart;
    void commitUpdateChart();           // Commit updating the chart.

    unsigned int m_lastMouseMove;       // The timestamp of the last mouse move event.
    QMouseEvent *m_delayedMouseEvent;	// The delayed mouse move event.
    int m_delayedMouseEventTimerId;     // The id of the delayed mouse move timer.
    void commitMouseMove(QMouseEvent *event);     // Raise the delayed mouse move event.

    bool m_delayImageMapUpdate;			// Delay image map update until mouse moves on plot area

    //
    // Track Cursor support
    //
    int m_currentMouseX;                // Get the mouse x-pixel coordinate
    int m_currentMouseY;                // Get the mouse y-pixel coordinate
    int m_isInMouseMovePlotArea;    	// flag to indicate if is in a mouse move plot area event.

    //
    // Dynamic Layer support
    //
    QString m_autoHideMsg;                      // The message that will trigger removing the dynamic layer.
    void applyAutoHide(const char *msg);        // Attempt to remove the dynamic layer with the given message.

signals:
    void viewPortChanged();                     // View port has changed
    void clicked(QMouseEvent *event);           // Mouse button clicked
    void mouseMove(QMouseEvent *event);         // Mouse moves over the widget
    void mouseWheel(QWheelEvent *event);        // Mouse wheel scrolled
    void mouseMoveChart(QMouseEvent *event);    // Mouse moves over the chart
    void mouseLeaveChart(QEvent *event);        // Mouse leaves the chart
    void mouseMovePlotArea(QMouseEvent *event); // Mouse moves over the extended plot area
    void mouseLeavePlotArea(QEvent *event);     // Mouse leaves the extended plot area

public slots:

};


class QViewPortControl : public QLabel, public ViewPortControlBase
{
Q_OBJECT
public:
    explicit QViewPortControl(QWidget *parent = 0);
    ~QViewPortControl();

    // Set the chart to be displayed in the control
    virtual void setChart(BaseChart *c);
    virtual BaseChart *getChart();

    // Associated QChartViewer
    virtual void setViewer(QChartViewer *viewer);
    virtual QChartViewer *getViewer();

    // Request the CViewPortControl to update its contents
    virtual void updateDisplay();

protected:
    //
    // QChartViewer event handlers
    //

    virtual void mouseMoveEvent(QMouseEvent *event);
    virtual void mousePressEvent(QMouseEvent *event);
    virtual void mouseReleaseEvent(QMouseEvent *event);
    virtual void wheelEvent(QWheelEvent *event);

private slots:
    virtual void onViewPortChanged();

private:
    QChartViewer *m_ChartViewer;            // Associated QChartViewer
    BaseChart *m_Chart;                     // BaseChart object displayed in the control

    int m_mouseDownX;                       // Current mouse x coordinates
    int m_mouseDownY;                       // Current mouse y coordinates
    bool isDrag(QMouseEvent *event);        // Check if mouse is dragging

    void paintDisplay();                    // Paint the display
    void syncState();                       // Synchronize the CViewPortControl with CChartViewer
    void updateCursor(int position);        // Update the mouse cursor
    void updateChartViewerIfNecessary();    // Update CChartViewer if viewport has changed

    double toImageX(int x);                 // Convert from mouse to image x-coordinate
    double toImageY(int y);                 // Convert from mouse to image y-coordinate
};


#endif // QCHARTVIEWER_H
