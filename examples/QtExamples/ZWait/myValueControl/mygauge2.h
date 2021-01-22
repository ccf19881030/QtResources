#ifndef MYGAUGE2_H
#define MYGAUGE2_H

#define LONG1 10
#define OK1 7
#define SHORT1 5
#define SPACE1 3
#define ANGLE1 10

#include <QWidget>
#include <QtGui>

class myGauge2 : public QWidget
{
    Q_OBJECT
public:
    explicit myGauge2(QWidget *parent = 0);

public slots:
    void setValue(qreal value);
    void setAnimating(bool enable)
    {
        m_bAnimating=enable;
        update();
    }

public:
    bool isAnimating() const
    {
        return m_bAnimating;
    }

protected:
    void paintEvent(QPaintEvent *);

    QSize sizeHint() const
    {
        return QSize(300,300);
    }

    QSize minimumSizeHint() const
    {
        return QSize(200,200);
    }

private:
    void drawOuterCircle(QPainter* painter);
    void drawInnerCircle(QPainter* painter);
    void drawMark(QPainter* painter);
    void drawCoverCircle(QPainter* painter);
    void drawColorPie(QPainter* painter);
    void drawIndicator(QPainter* painter);
    void drawCoverBall(QPainter* painter);
    void resetVariables(QPainter* painter);
    void drawTextRect(QPainter* painter);

private:
    qreal m_outerRadius;
    qreal m_innerRadius;
    qreal m_coverCircleRadius;
    qreal m_colorCircleRadius;
    qreal m_coverBallRadius;
    QPointF m_center;
    QRectF m_colorCircleRect;
    qreal m_value;
    QTimer* updateTimer;
    bool m_bReverse;
    qreal m_currentValue;
    QTimer* singleTimer;
    bool m_bAnimating;

private:
    void initVariables();

private slots:
    void UpdateGraph();
};

#endif // MYGAUGE2_H
