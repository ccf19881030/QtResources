#ifndef MYLCDNUMBER_H
#define MYLCDNUMBER_H

#define LCDNUMBER_SPACE 2

#include <QWidget>
#include <QPaintEvent>
#include <QPainter>

class myLCDNumber : public QWidget
{
    Q_OBJECT
public:
    explicit myLCDNumber(QWidget *parent = 0);

signals:

public slots:
    void setNumber(int num);

protected:

    QSize sizeHint() const
    {
        return QSize(20,30);
    }

    QSize minimumSizeHint() const
    {
        return QSize(10,15);
    }
    void paintEvent(QPaintEvent *);

private:
    void drawVariables(QPainter* painter);
    void drawBackground(QPainter* painter);
    void drawNumber(QPainter* painter);

private:
    int m_nNum;
    qreal m_min;
    qreal m_rectWidth;
    QPointF m_center;
    void initVariables();

};

#endif // MYLCDNUMBER_H
