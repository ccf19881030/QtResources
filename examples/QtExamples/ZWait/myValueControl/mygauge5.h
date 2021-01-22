#ifndef MYGAUGE5_H
#define MYGAUGE5_H

#include <QWidget>
#include <QtGui>

class myGauge5 : public QWidget
{
    Q_OBJECT
public:
    explicit myGauge5(QWidget *parent = 0);

protected:
    void paintEvent(QPaintEvent *);

    QSize sizeHint() const
    {
        return QSize(200,200);
    }

    QSize minimumSizeHint() const
    {
        return QSize(150,150);
    }

private:
    void drawOuterCircle(QPainter* painter);
    void drawInnerCircle(QPainter* painter);
    void drawColorPies(QPainter* painter);
    void drawCoverLines(QPainter* painter);
    void drawCoverCircle(QPainter* painter);
    void drawMarkAndText(QPainter* painter);
    void drawIndicator(QPainter* painter);
    void drawTextRect(QPainter* painter);
    void resetVariables(QPainter* painter);


private:
    qreal m_value;
    qreal m_outerRadius;
    qreal m_innerRadius;
    qreal m_colorPieRadius;
    qreal m_coverCircleRadius;
    qreal m_currentValue;
    qreal m_longHand;
    qreal m_okHand;
    qreal m_shortHand;
    qreal m_space;
    bool m_bReverse;
    QTimer* updateTimer;
    QPointF m_center;
    QRectF m_pieRect;

private slots:
    void UpdateGraph();

public slots:
    void setValue(qreal value);

};

#endif // MYGAUGE5_H
