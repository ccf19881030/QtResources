#include "magic_fish.h"
#include <QtMath>
#include <QPainter>
#include <QDebug>

MagicFish::MagicFish(QWidget *parent)
    : QWidget(parent),
      fish_r(30),
      fin_length(30 * 1.3),
      body_height(30 * 3.2),
      head_alpha(200),
      body_alpha(225),
      fin_alpha(120),
      main_angle(0.0),
      current_value(0),
      speed(30),
      start_fin(false),
      paint_point(false),
      wave(1.0)
{
    this->timer = new QTimer(this);
    this->timer->setInterval(100);
    connect(timer, &QTimer::timeout, this, &MagicFish::updateValue);
    this->timer->start();
    this->setWindowFlags(Qt::WindowStaysOnTopHint | Qt::FramelessWindowHint);
}

void MagicFish::updateValue()
{
    this->current_value = (this->current_value + this->speed) % 54000;
    this->update();
}

void MagicFish::paintEvent(QPaintEvent *e)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    QPointF middle_pos = QPointF(this->width() / 2, this->height() / 2);
    this->head_pos = this->calcPoint(middle_pos, this->body_height / 2.0, this->main_angle);
    this->paintMyPoint(painter, this->head_pos);
    this->paintMyPoint(painter, middle_pos);
    painter.setPen(Qt::NoPen);
    painter.setBrush(QBrush(QColor(20, 203, 232, 50)));
    painter.setBrush(QBrush(QColor(244, 92, 71, this->head_alpha)));
    painter.drawEllipse(this->head_pos, this->fish_r, this->fish_r);

    float angle = this->main_angle + qSin(qDegreesToRadians(this->current_value * 1.2 * wave)) * 2;
    QPointF end_pos = this->calcPoint(this->head_pos, this->body_height, angle - 180);
    QPointF pos1 = calcPoint(this->head_pos, this->fish_r, angle - 80);
    QPointF pos2 = calcPoint(end_pos, this->fish_r * 0.7, angle - 90);
    QPointF pos3 = calcPoint(end_pos, this->fish_r * 0.7, angle + 90);
    QPointF pos4 = calcPoint(this->head_pos, this->fish_r, angle + 80);

    QPointF central_left = this->calcPoint(this->head_pos, this->body_height * 0.56, angle - 130);
    QPointF central_right = this->calcPoint(this->head_pos, this->body_height * 0.56, angle + 130);
    QPainterPath path;
    path.moveTo(pos1);
    path.quadTo(central_left, pos2);
    path.lineTo(pos3);
    path.quadTo(central_right, pos4);
    path.lineTo(pos1);

    painter.setBrush(QBrush(QColor(244, 92, 71, this->body_alpha)));
    painter.drawPath(path);

    this->paintMyBody(painter, end_pos, this->fish_r * 0.7, 0.6, angle);
    QPointF left_fin_pos = this->calcPoint(head_pos, this->fish_r * 0.9, angle + 110);
    this->paintMyFishFins(painter, left_fin_pos, true, angle);
    QPointF right_fin_pos = this->calcPoint(head_pos, this->fish_r * 0.9, angle - 110);
    this->paintMyFishFins(painter, right_fin_pos, false, angle);

    QWidget::paintEvent(e);
}

void MagicFish::resizeEvent(QResizeEvent *e)
{
    QWidget::resizeEvent(e);
    this->fish_r = qMin(this->width(), this->height()) / 10.0;
    this->fin_length = this->fish_r * 1.3;
    this->body_height = this->fish_r * 3.2;
}

QPointF MagicFish::calcPoint(const QPointF &pos, float length, float angle)
{
    float delta_x = qCos(qDegreesToRadians(angle)) * length;
    float delta_y = qSin(qDegreesToRadians(angle - 180)) * length;
    return QPointF(pos + QPointF(delta_x, delta_y));
}

void MagicFish::paintMyPoint(QPainter &painter, const QPointF pos)
{
    if(paint_point)
    {
        painter.save();
        painter.setPen(QPen(Qt::black, 3));
        painter.setBrush(QBrush(Qt::black));
        painter.drawPoint(pos);
        painter.restore();
    }
}

void MagicFish::paintMyFishFins(QPainter &painter, const QPointF &pos, bool is_left, float father_angle)
{
    float contral_angle = 115;
    float fin_angle = this->start_fin ? qSin(qDegreesToRadians(this->current_value * 16.1 * wave)) * 12.0 : 2;
    QPainterPath path;
    path.moveTo(pos);
    QPointF end_pos = this->calcPoint(pos, this->fin_length, is_left ?
                                                             father_angle + fin_angle + 180 :
                                                             father_angle - fin_angle - 180);
    QPointF control_pos = this->calcPoint(pos, this->fin_length * 1.8, is_left ?
                                              father_angle + contral_angle + fin_angle :
                                              father_angle - contral_angle - fin_angle);


    path.quadTo(control_pos, end_pos);
    path.lineTo(pos);

    painter.save();
    painter.setBrush(QBrush(QColor(244, 92, 71, this->fin_alpha)));
    painter.drawPath(path);
    painter.restore();
}

void MagicFish::paintMyBody(QPainter &painter, const QPointF &pos, float seg_r, float MP, float father_angle)
{
    float angle = father_angle + qCos(qDegreesToRadians(this->current_value * 1.5 * wave)) * 15;
    float length = seg_r * (MP + 1);
    QPointF end_pos = this->calcPoint(pos, length, angle - 180);

    QPointF pos1 = this->calcPoint(pos, seg_r, angle - 90);
    QPointF pos2 = this->calcPoint(end_pos, seg_r * MP, angle - 90);
    QPointF pos3 = this->calcPoint(end_pos, seg_r * MP, angle + 90);
    QPointF pos4 = this->calcPoint(pos, seg_r, angle + 90);

    painter.save();
    painter.setBrush(QBrush(QColor(244, 92, 71, this->head_alpha)));
    painter.drawEllipse(pos, seg_r, seg_r);
    painter.drawEllipse(end_pos, seg_r * MP, seg_r * MP);

    QPainterPath path;
    path.moveTo(pos1);
    path.lineTo(pos2);
    path.lineTo(pos3);
    path.lineTo(pos4);
    painter.drawPath(path);
    painter.restore();
    this->paintMyBody2(painter, end_pos, seg_r * 0.6, 0.4, angle);
}

void MagicFish::paintMyBody2(QPainter &painter, const QPointF &pos, float seg_r, float MP, float father_angle)
{
    float angle = father_angle + qSin(qDegreesToRadians(this->current_value * 1.7 * wave)) * 35;
    float length = seg_r * (MP + 2.7);
    QPointF end_pos = this->calcPoint(pos, length, angle - 180);

    QPointF pos1 = this->calcPoint(pos, seg_r, angle - 90);
    QPointF pos2 = this->calcPoint(end_pos, seg_r * MP, angle - 90);
    QPointF pos3 = this->calcPoint(end_pos, seg_r * MP, angle + 90);
    QPointF pos4 = this->calcPoint(pos, seg_r, angle + 90);

    this->paintMyTail(painter, pos, length, seg_r, angle);

    painter.save();
    painter.setBrush(QBrush(QColor(244, 92, 71, this->head_alpha)));
    painter.drawEllipse(end_pos, seg_r * MP, seg_r * MP);

    QPainterPath path;
    path.moveTo(pos1);
    path.lineTo(pos2);
    path.lineTo(pos3);
    path.lineTo(pos4);
    painter.drawPath(path);
    painter.restore();
}

void MagicFish::paintMyTail(QPainter &painter, const QPointF &pos, float length, float max_w, float angle)
{
    float w = qAbs(qSin(qDegreesToRadians(this->current_value * 1.9 * wave)) * max_w + this->fish_r / 5.0 * 3.0);
    QPointF end_point1 = this->calcPoint(pos, length, angle - 180);
    QPointF end_point2 = this->calcPoint(pos, length - 10, angle -180);

    QPointF pos1 = this->calcPoint(end_point1, w, angle - 90);
    QPointF pos2 = this->calcPoint(end_point1, w, angle + 90);
    QPointF pos3 = this->calcPoint(end_point2, w - this->fish_r / 1.5, angle - 90);
    QPointF pos4 = this->calcPoint(end_point2, w - this->fish_r / 1.5, angle + 90);

    QPainterPath path;
    path.moveTo(pos);
    path.lineTo(pos3);
    path.lineTo(pos4);
    path.lineTo(pos);
    painter.save();
    painter.setBrush(QBrush(QColor(244, 92, 71, this->head_alpha)));
    painter.drawPath(path);

    path.closeSubpath();
    path.moveTo(pos);
    path.lineTo(pos1);
    path.lineTo(pos2);
    path.lineTo(pos);
    painter.drawPath(path);
    painter.restore();
}

void MagicFish::setWave(float value)
{
    wave = value;
}

int MagicFish::getFishR() const
{
    return fish_r;
}

float MagicFish::getAngle()
{
    return this->main_angle;
}

QPointF MagicFish::getHeadPos() const
{
    return head_pos;
}

void MagicFish::setSpeed(int value)
{
    this->speed = value;
}

void MagicFish::setCurrentAngle(float angle)
{
    this->main_angle = angle;
    this->update();
}

void MagicFish::setFinAnimation(bool start)
{
    this->start_fin = start;
}

void MagicFish::setFishR(int value)
{
    this->fish_r = value;
    this->fin_length = value * 1.3;
    this->body_height = value * 3.2;
    this->update();
}
