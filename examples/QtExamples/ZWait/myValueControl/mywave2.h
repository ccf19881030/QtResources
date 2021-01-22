#ifndef MYWAVE2_H
#define MYWAVE2_H

#define PYS_TOP_SPACE 1
#define PYS_LEFT_SPACE 0
#define PYS_TIMER_INTERVAL 10
#define PYS_WIDTH 3
#define PYS_INCREMENT_FACTOR 100

#define PYS_BG_START_COLOR QColor(178,178,178)
#define PYS_BG_END_COLOR QColor(60,60,60)

#define PYS_BAR_START_COLOR QColor(46,132,243)
#define PYS_BAR_END_COLOR QColor(39,110,203)

//#define PYS_BAR_START_COLOR QColor(157,157,235)
//#define PYS_BAR_END_COLOR QColor(85,85,127)

#define PYS_APPLY_LINEAR_GRADIENT(Rect,StartPot,EndPot,StartColor,EndColor)  QLinearGradient Rect##Gradient(StartPot,EndPot); \
   Rect##Gradient.setColorAt(0.0,StartColor); \
   Rect##Gradient.setColorAt(1.0,EndColor); \
   painter->setBrush(Rect##Gradient);

#ifdef DEBUG_VAR
#undef DEBUG_VAR
#endif
#include <QDebug>
#define DEBUG_VAR(Var) qDebug() << "["<<__FILE__ <<"]" << "Line:" << __LINE__  << __FUNCTION__ << #Var << "=" << Var;


#ifdef STOP_TIMER
#undef STOP_TIMER
#endif
#define STOP_TIMER(Timer) if(Timer->isActive()){ Timer->stop();}


#include <QWidget>
#include <QtGui>

class myWave2 : public QWidget
{
    Q_OBJECT
public:
    explicit myWave2(QWidget *parent = 0);

public:

    void setRange(int min,int max);

    void setMinimum(int min);

    void setMaximum(int max);

public slots:
    void setValue(int value);

protected:
    void paintEvent(QPaintEvent *);

    QSize sizeHint() const
    {
        return QSize(PYS_WIDTH,120);
    }

private:
    void drawBackground(QPainter* painter);
    void drawSpectrum(QPainter* painter);

private:
    void initVariables();

private:
    int m_nMin;
    int m_nMax;
    int m_nCurrentValue;
    int m_nValue;
    int m_nIncrement;

    bool m_bReverse;

    QTimer* m_updateTimer;

private slots:
    void UpdateValue();

};

#endif // MYWAVE2_H
