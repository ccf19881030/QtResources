#include "magic_pool.h"
#include <QPainter>
#include <QMouseEvent>
#include <QDebug>
#include <QtMath>

MagicPool::MagicPool(QWidget *parent)
    : QWidget(parent),
      start_circle(false),
      circle_r(4),
      move_step(0.0)
{
    this->circle_timer = new QTimer(this);
    this->circle_timer->setInterval(20);
    connect(this->circle_timer, &QTimer::timeout, this, &MagicPool::slotUpdateValue);

    this->move_timer = new QTimer(this);
    this->move_timer->setInterval(20);
    connect(this->move_timer, &QTimer::timeout, this, &MagicPool::slotUpdateMove);
    this->setFixedSize(500, 400);
    this->fish = new MagicFish(this);
    this->fish->setFixedSize(50, 50);
}

void MagicPool::slotUpdateValue()
{
    this->circle_r += 2;
    if(this->circle_r >= 40)
    {
        this->circle_r = 4;
        this->start_circle = false;
        this->circle_timer->stop();
    }
    this->update();
}

void MagicPool::slotUpdateMove()
{
    float tmp = 0.00;
    if(this->move_step >= 0.85)
    {
        tmp = qSin(qDegreesToRadians(this->move_step * 180)) * 0.02;
        this->fish->setFinAnimation(false);
        this->fish->setWave(1.0);
    }
    else
    {
        tmp = 0.015 + qCos(qDegreesToRadians(this->move_step * 90)) * 0.02;
        this->fish->setWave(1.0 / (this->move_step + 0.1));
    }
    this->move_step += tmp;
    if(this->move_step >= 1.0 || (1 - this->move_step) <= 0.003)
    {
        this->move_step = 0.0;
        this->path = QPainterPath();
        this->move_timer->stop();
    }
    else
    {
        QPointF p = this->path.pointAtPercent(this->move_step);
        this->fish->setCurrentAngle(this->path.angleAtPercent(this->move_step));
        this->fish->move(p.x(), p.y());
        this->update();
    }
}

void MagicPool::mousePressEvent(QMouseEvent *e)
{
    this->start_circle = true;
    this->pos = e->pos();
    this->circle_r = 4;
    this->move_step = 0.0;

    QPointF fish_middle = this->fish->geometry().center();
    QPointF fish_head = this->fish->geometry().topLeft() + this->fish->getHeadPos();
    float angle = this->calcIncludedAngle(fish_middle, fish_head, this->pos);
    float delta = this->calcIncludedAngle(fish_middle, fish_middle + QPointF(1, 0), fish_head);
    QPointF c = this->calcPoint(fish_middle, 17 * this->fish->getFishR(), angle / 2 + delta);
    QPointF p(this->fish->width() / 2, this->fish->height() / 2);
    this->path = QPainterPath();
    this->path.moveTo(this->fish->geometry().topLeft());
    this->path.cubicTo(fish_head - p, c - p, this->pos - p);

    this->circle_timer->start();
    this->move_timer->start();
    this->fish->setFinAnimation(true);
    this->fish->setWave(2.5);
}

void MagicPool::paintEvent(QPaintEvent *e)
{
    QWidget::paintEvent(e);
    if(this->start_circle)
    {
        QPainter painter(this);
        painter.setRenderHint(QPainter::Antialiasing);
        painter.setPen(QPen(QColor(20, 203, 232, 50), 3));
        painter.drawEllipse(this->pos, this->circle_r, this->circle_r);
    }
}

float MagicPool::calcIncludedAngle(const QPointF &center, const QPointF &head, const QPointF &touch)
{
    float abc = (head.x() - center.x()) * (touch.x() - center.x()) +
                (head.y() - center.y()) * (touch.y() - center.y());
    float cos_abc = (abc) / qSqrt((head.x() - center.x()) * (head.x() - center.x()) + (head.y() - center.y()) * (head.y() - center.y())) /
                            qSqrt((touch.x() - center.x()) * (touch.x() - center.x()) + (touch.y() - center.y()) * (touch.y() - center.y()));
    float tmp_angle = qRadiansToDegrees(qAcos(cos_abc));
    float direction = (center.x() - touch.x()) * (head.y() - touch.y()) -
                      (center.y() - touch.y()) * (head.x() - touch.x());
    if(direction == 0)
    {
        if(abc >= 0)
        {
            return 0;
        }
        else
        {
            return 180;
        }
    }
    else
    {
        if(direction > 0)
        {
            return -tmp_angle;
        }
        else
        {
            return tmp_angle;
        }
    }
}

QPointF MagicPool::calcPoint(const QPointF &pos, float length, float angle)
{
    float delta_x = qCos(qDegreesToRadians(angle)) * length;
    float delta_y = qSin(qDegreesToRadians(angle - 180)) * length;
    return QPointF(pos + QPointF(delta_x, delta_y));
}

float MagicPool::getLength(const QPointF &pos1, const QPointF &pos2)
{
    return qSqrt((pos1.x() - pos2.x()) * (pos1.x() - pos2.x())
                 + (pos1.y() - pos2.y()) * (pos1.y() - pos2.y()));
}

