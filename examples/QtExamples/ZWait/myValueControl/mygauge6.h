#ifndef MYGAUGE6_H
#define MYGAUGE6_H

#include <QWidget>
#include <QtGui>

class myGauge6 : public QWidget
{
    Q_OBJECT
public:
    explicit myGauge6(QWidget *parent = 0);
    void SetGraphColor(QColor c);

public slots:
    void setValue(qreal value);
    void setRange(int min,int max);
    void setUseAntialiasing(bool use);
    void setAnimating(bool animate);

protected:
    void paintEvent(QPaintEvent *);

    QSize sizeHint() const
    {
        return QSize(200,350);
    }

    QSize minimumSizeHint() const
    {
        return QSize(120,70);
    }

private:
    void drawVariables(QPainter* painter);
    void drawBackground(QPainter* painter);
    void drawTextRect(QPainter* painter);
    void drawGauge(QPainter* painter);
    void drawMark(QPainter* painter);
    void drawUnderRect(QPainter* painter);


private:
    qreal   m_currentValue;
    qreal   m_value;
    qreal   m_leftSpace;
    qreal   m_topSpace;
    qreal   m_long;
    qreal   m_ok;
    qreal   m_short;
    qreal   m_markX;
    qreal   m_markY;
    qreal   m_markBottom;

    int     m_nMin;
    int     m_nMax;
    bool    m_bReverse;
    bool    m_bAnimate;
    bool    m_bUseAntialiasing;
    QTimer* updateTimer;
    QRectF  m_textRect;
    QRectF  m_underRect;
    QPointF m_gaugeTopLeftPot;
    QPointF m_gaugeBottomRightPot;
    QColor graphcolor;

private slots:
    void UpdateGraph();

};

#endif // MYGAUGE6_H
