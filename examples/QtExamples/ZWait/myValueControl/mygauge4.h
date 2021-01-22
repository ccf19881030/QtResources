#ifndef MYGAUGE4_H
#define MYGAUGE4_H

#define INCREMENT2 66
#define LONG2 8
#define OK2 5
#define SHORT2 3
#define TOP_SPACE2 10
#define SPACE2 20

#include <QWidget>
#include <QtGui>
#include <QObject>

class LinearGradient : public QObject
{
    Q_OBJECT
public:
    explicit LinearGradient(QObject *parent = 0);

public:
    static QLinearGradient GetGradient(const QPointF& startPos,const QPointF& endPos,const QColor& clr);

};


class myGauge4 : public QWidget
{
    Q_OBJECT
public:
    explicit myGauge4(QWidget *parent = 0);

    void SetmyLineColor(QColor c);

protected:
    void paintEvent(QPaintEvent *);
    QSize sizeHint() const
    {
        return QSize(300,120);
    }


private:
    void drawTopBottomRects(QPainter* painter);
    void drawMark(QPainter *painter);
    void drawIndicator(QPainter* painter);

private:
    LinearGradient lg;
    qreal m_rectHeight;
    QRectF m_topRect;
    QRectF m_bottomRect;
    QRectF m_middleRect;
    qreal m_markLength;
    qreal m_topY;
    qreal m_startX;
    qreal m_length;
    qreal m_increment;
    qreal m_bottomY;
    bool  m_bReverse;
    qreal m_value;
    qreal m_currentValue;
    QTimer* updateTimer;
    QColor mylinecolor;

private slots:
    void UpdateGraph();

public slots:
    void setValue(qreal value);

};

#endif // MYGAUGE4_H
