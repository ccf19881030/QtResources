#ifndef MAGIC_POOL_H
#define MAGIC_POOL_H

#include <QWidget>
#include "magic_fish.h"
#include <QPushButton>
#include <QPropertyAnimation>
#include <QEasingCurve>

class MagicPool : public QWidget
{
public:
    explicit MagicPool(QWidget *parent = 0);

public slots:
    void slotUpdateValue();
    void slotUpdateMove();

protected:
    void mousePressEvent(QMouseEvent *e);
    void paintEvent(QPaintEvent *e);

private:
    float calcIncludedAngle(const QPointF &center, const QPointF &head, const QPointF &touch);
    QPointF calcPoint(const QPointF &pos, float length, float angle);
    float getLength(const QPointF &pos1, const QPointF &pos2);

private:
    bool start_circle;
    QTimer *circle_timer;
    QTimer *move_timer;
    int circle_r;
    QPoint pos;

    MagicFish *fish;
    QPushButton *btn;

    QPainterPath path;
    float move_step;
};

#endif // MAGIC_POOL_H
