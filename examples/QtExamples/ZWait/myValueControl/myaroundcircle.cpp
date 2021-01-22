#include "myaroundcircle.h"

myAroundCircle::myAroundCircle(QWidget *parent) :
    QWidget(parent)
{
    m_updateTimer = new QTimer(this);
    m_updateTimer->setInterval(10);
    connect(m_updateTimer,SIGNAL(timeout()),this,SLOT(UpdateAngle()));
    m_updateTimer->start();

    m_angle = 0;
    m_outerRadius = 0;
    setWindowFlags(Qt::FramelessWindowHint);
    setAttribute(Qt::WA_TranslucentBackground);
}

void myAroundCircle::paintEvent(QPaintEvent *)
{
  QPainter painter(this);
  painter.setRenderHints(QPainter::Antialiasing|QPainter::HighQualityAntialiasing);
  drawUnderCircle(&painter);
  drawBMW(&painter);
}

void myAroundCircle::drawUnderCircle(QPainter *painter)
{
  painter->save();

  m_outerRadius = width() > height() ? (qreal)height()/2 : (qreal)width()/2;

  QPointF TopLeft(rect().center().x() - m_outerRadius,rect().center().y() - m_outerRadius);
  QPointF BottomRight(rect().center().x() + m_outerRadius,rect().center().y() + m_outerRadius);
  QRectF CircleRect(TopLeft,BottomRight);

  painter->setPen(Qt::NoPen);

  QRadialGradient CircleGradient(CircleRect.center(),m_outerRadius,CircleRect.center());
  CircleGradient.setColorAt(0.0,PYB_OUTER_CIRCLE_START_COLOR);
  CircleGradient.setColorAt(1.0,PYB_OUTER_CIRCLE_END_COLOR);
  painter->setBrush(CircleGradient);

  painter->drawEllipse(CircleRect);

  painter->restore();
}

void myAroundCircle::drawBMW(QPainter *painter)
{
  // move to center

//  painter->translate(rect().center());

  painter->save();
  // setup transform
  QTransform t;
  t.translate(rect().center().x(),rect().center().y());
  t.rotate(m_angle,Qt::ZAxis);
  painter->setTransform(t);

  qreal InnerRadius = m_outerRadius * PYB_RADIUS_FACTOR;
  QPointF tTopLeft( -InnerRadius,-InnerRadius);
  QPointF tBottomRight(InnerRadius,InnerRadius);
  QRectF  tRect(tTopLeft,tBottomRight);

  qreal dAngle = 90 * 16;
  qreal StartAngle = 0;

  painter->setPen(Qt::NoPen);
  for(int AngleIndex = 0; AngleIndex < 4;AngleIndex++)
  {
    if(AngleIndex%2)
    {

      QRadialGradient PieGradient(tRect.center(),m_outerRadius,tRect.center());
      PieGradient.setColorAt(0.0,PYB_BLUE_CIRCLE_START_COLOR);
      PieGradient.setColorAt(1.0,PYB_BLUE_CIRCLE_END_COLOR);
      painter->setBrush(PieGradient);

    }else{

      QRadialGradient PieGradient(tRect.center(),m_outerRadius,tRect.center());
      PieGradient.setColorAt(0.0,PYB_WHITE_CIRCLE_START_COLOR);
      PieGradient.setColorAt(1.0,PYB_WHITE_CIRCLE_END_COLOR);
      painter->setBrush(PieGradient);

    }
    painter->drawPie(tRect,StartAngle,dAngle);

    /// increment StartAngle
    StartAngle += dAngle;
  }

  painter->restore();

  //
}

void myAroundCircle::UpdateAngle()
{
  m_angle += 1;
  if(m_angle > 360)
  {
    m_angle = 0;
  }
  update();
}
