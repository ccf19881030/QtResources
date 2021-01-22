#ifndef MYNEWLED_H
#define MYNEWLED_H

#define PYL_LEFT_SPACE 10
#define PYL_TOP_SPACE 10

#define PYL_WIDGET_SPACE 2
#define PYL_RECT_RADIUS 3

#define PYL_H_COUNT 9
#define PYL_V_COUNT 9

#define PYL_BG_COLOR QColor(45,45,45)
#define PYL_NON_START_COLOR QColor(119,119,119)
#define PYL_NON_END_COLOR QColor(89,89,89)

#define PYL_SCHEME1
#ifdef PYL_SCHEME1
#define PYL_QUI_START_COLOR QColor(55,142,234)
#define PYL_QUI_END_COLOR QColor(48,125,207)
#endif

#ifdef PYL_SCHEME2
#define PYL_QUI_START_COLOR QColor(228,93,255)
#define PYL_QUI_END_COLOR QColor(195,79,218)
#endif

#ifdef PYL_SCHEME3
#define PYL_QUI_START_COLOR QColor(162,255,41)
#define PYL_QUI_END_COLOR QColor(138,217,35)
#endif

#include <QDebug>


#ifdef DEBUG_VAR
#undef DEBUG_VAR
#endif
#define DEBUG_VAR(VAR) qDebug() << __FILE__ << ":" << __LINE__ << ":" << __FUNCTION__ << #VAR << ":" <<  VAR;


#include <QWidget>
#include <QtGui>

class NumberObj : public QObject
{
Q_OBJECT
public:
    NumberObj(){}

    void addPair(int hCoor,int vCoor)
    {
        DEBUG_VAR(hCoor);
        DEBUG_VAR(vCoor);
        m_CoorPairVec.push_back(qMakePair(hCoor,vCoor));
        DEBUG_VAR(m_CoorPairVec.count());
    }

    void clear()
    {
        m_CoorPairVec.clear();
    }

    int pairCount() const
    {
        return m_CoorPairVec.count();
    }

    bool hasThisPair(int hCoor,int vCoor)
    {
        int PairCnt = m_CoorPairVec.count();
        for(int PairIndex = 0;PairIndex < PairCnt ; PairIndex++)
        {
            if(m_CoorPairVec.at(PairIndex).first == hCoor &&
               m_CoorPairVec.at(PairIndex).second == vCoor)
            {
                return true;
            }
        }
        return false;
    }

private:
    QVector< QPair<int,int> > m_CoorPairVec;
};


class myNewLed : public QWidget
{
    Q_OBJECT
public:
    explicit myNewLed(QWidget *parent = 0);

public:
    void setNumber(int num);
    void SetmyLedColor(QColor c1,QColor c2);

protected:
    void paintEvent(QPaintEvent *);

    QSize sizeHint() const
    {
        return QSize(300,300);
    }

private:
    void drawBg(QPainter* painter);
    void drawLed(QPainter* painter);

    QColor myledColor1;
    QColor myledColor2;

private:
    void initVariables();

    NumberObj* zero,*one,*two,*three,*four,*five,*six,*seven,*eight,*nine;
    int m_nNum;

};

#endif // MYNEWLED_H
