#ifndef MYAROUNDCIRCLE_H
#define MYAROUNDCIRCLE_H

#define PYB_RADIUS_FACTOR 0.8

#define PYB_OUTER_CIRCLE_START_COLOR QColor(65,65,65)
#define PYB_OUTER_CIRCLE_END_COLOR QColor(89,89,89)

#define PYB_BLUE_CIRCLE_START_COLOR QColor(0,133,203)
#define PYB_BLUE_CIRCLE_END_COLOR QColor(0,118,177)

#define PYB_WHITE_CIRCLE_START_COLOR QColor(255,255,255)
#define PYB_WHITE_CIRCLE_END_COLOR QColor(233,233,233)

#include <QWidget>
#include <QtGui>

class myAroundCircle : public QWidget
{
    Q_OBJECT
public:
    explicit myAroundCircle(QWidget *parent = 0);

protected:
    void paintEvent(QPaintEvent *);

    QSize sizeHint() const
    {
      return QSize(300,300);
    }

private:
    void drawUnderCircle(QPainter* painter);

    void drawBMW(QPainter* painter);


private:
    QTimer* m_updateTimer;

    qreal   m_angle;
    qreal   m_outerRadius;

private slots:
    void UpdateAngle();

};

#endif // MYAROUNDCIRCLE_H
