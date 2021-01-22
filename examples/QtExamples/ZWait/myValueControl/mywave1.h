#ifndef MYWAVE1_H
#define MYWAVE1_H

#define PYI_HEAD_HEIGHT 1
#define PYI_BAR_START_COLOR QColor(88,177,245)
#define PYI_BAR_END_COLOR QColor(74,149,206)
#define PYI_HEAD_Y_INCREMENT 1
#define PYI_VALUE_DECREMENT 1
#define PYI_EXTRA_SPACE 2
#define PYI_MAX_WIDTH 15

#define DEBUG_VAR(VAR) qDebug() << __FILE__ << ":" << __LINE__ << ":" << __FUNCTION__ << #VAR << ":" <<  VAR;


#include <QWidget>
#include <QtGui>

class myWave1 : public QWidget
{
    Q_OBJECT
public:
    explicit myWave1(QWidget *parent = 0);
    void setRange(int min,int max);

    void setValue(int value);

    int minimum() const;

    int maximum() const;

    int value() const;

protected:
    void paintEvent(QPaintEvent *);

    QSize sizeHint() const
    {
        return QSize(20,200);
    }

private:

    void drawBackground(QPainter* painter);

    void drawBar(QPainter* painter);

    void drawHead(QPainter* painter);


private:
    int m_nMin;
    int m_nMax;
    int m_nValue;
    int m_nCurrentValue;

    qreal m_headY;
    qreal m_barY;

    QTimer* m_shrinkTimer;
    QTimer* m_dropTimer;
    QTimer* m_toolTimer;

    QRectF m_BarRect;

private:
    void initVariables();

private slots:
    void DoShrinkBar();
    void DoDropHead();

};

#endif // MYWAVE1_H
