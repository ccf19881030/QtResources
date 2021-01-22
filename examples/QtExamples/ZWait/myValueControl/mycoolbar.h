#ifndef MYCOOLBAR_H
#define MYCOOLBAR_H

#include <QWidget>
#include <QtGui>

const int BAR_HEIGHT=25;
const int INDICATOR_RADIUS=qRound(1.0*BAR_HEIGHT/2)+1;
const int RECT_RADIUS =10;
const int LEFT_WIDTH=20;
const int RIGHT_WIDTH=LEFT_WIDTH;

class myCoolBar : public QWidget
{
    Q_OBJECT
public:
    explicit myCoolBar(QWidget *parent = 0);
    void setRange(int min,int max);
    void setValue(int value);

protected:
    void paintEvent(QPaintEvent *);
    QSize sizeHint() const
    {
        return QSize(300,30);
    }

    QSize minimumSizeHint() const
    {
        return QSize(200,30);
    }
    void mousePressEvent(QMouseEvent *);
    void mouseMoveEvent(QMouseEvent *);
    void mouseReleaseEvent(QMouseEvent *);
    void resizeEvent(QResizeEvent *);

private:
    void drawBackground(QPainter* painter);
    void drawBar(QPainter* painter);
    void drawIndicator(QPainter* painter);
    void drawFilledRegion(QPainter* painter);


private:
    qreal m_indicatorPos;
    int m_Max;
    int m_Min;
    int m_value;
    qreal m_increment;
    qreal m_indicatorY;
    qreal m_indicatorX;
    QRectF m_barRect;
    QRectF m_indicatorRect;
    QRectF m_leftRect;
    QPointF m_lastPot;
    bool m_pressed;
    bool m_valid;
    bool m_firstRun;
    QTimer* updateTimer;

private:
    void initVariables();

signals:
    void valueChanged(int value);

public slots:

};

#endif // MYCOOLBAR_H
