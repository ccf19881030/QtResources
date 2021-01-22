#ifndef MYGAUGE3_H
#define MYGAUGE3_H

#define LEFT_SPACE1 30
#define TOP_SPACE1 40

#include <QWidget>
#include <QtGui>

class myGauge3 : public QWidget
{
    Q_OBJECT
public:
    explicit myGauge3(QWidget *parent = 0);

    void SetmyTopColor(QColor c);

protected:
    void paintEvent(QPaintEvent *);

    QSize sizeHint() const
    {
        return QSize(400,150);
    }

    QSize minimumSizeHint() const
    {
        return QSize(300,120);
    }

    void mousePressEvent(QMouseEvent *);
    void mouseReleaseEvent(QMouseEvent *);
    void mouseMoveEvent(QMouseEvent *);
    void resizeEvent(QResizeEvent *);

private:
    void drawBackground(QPainter* painter);
    void drawRule(QPainter* painter);
    void drawHandle(QPainter* painter);
    void drawHorizontalLine(QPainter* painter);
    void drawVerticalLines(QPainter* painter);
    void resetVariables(QPainter* painter);
    void drawTip(QPainter* painter);

private:
    int m_nMin;
    int m_nMax;
    int m_length;
    qreal m_value;
    qreal m_longHand;
    qreal m_okHand;
    qreal m_shortHand;
    qreal m_handleWidth;
    qreal m_handleHeight;
    qreal m_indicatorLength;
    QPointF m_indicatorTopPot;
    QPointF m_indicatorLastPot;
    QPointF m_indicatorBottomLeftPot;
    QPointF m_indicatorBottomRightPot;
    QPointF m_lineLeftPot;
    QPointF m_lineRightPot;
    QRectF  m_handleRect;
    QPointF m_lastPos;
    QTimer* tipTimer;
    QTimer* eraseTimer;
    QRectF m_tipRect;
    qreal m_currentValue;

    bool m_bDrag;
    bool m_bShowTip;

    QColor myTopColor;

private:
    void initVariables();
    void initSettings();

private slots:
    void ShowTip();
    void HideTip();

signals:
    void valueChanged(qreal value);

public slots:
    void setRange(int min,int max);
    void setValue(qreal value);
};

#endif // MYGAUGE3_H
