#ifndef MAGIC_FISH_H
#define MAGIC_FISH_H

#include <QWidget>
#include <QTimer>

class MagicFish : public QWidget
{
public:
    explicit MagicFish(QWidget *parent = 0);

    void setFishR(int value);
    void setSpeed(int value);
    void setCurrentAngle(float angle);
    void setFinAnimation(bool start);

    QPointF getHeadPos() const;

    int getFishR() const;
    float getAngle();

    void setWave(float value);

public slots:
    void updateValue();

protected:
    void paintEvent(QPaintEvent *e);
    void resizeEvent(QResizeEvent *e);

private:
    QPointF calcPoint(const QPointF &pos, float length, float angle);
    void paintMyPoint(QPainter &painter, const QPointF pos);

    void paintMyFishFins(QPainter &painter, const QPointF &pos, bool is_left, float father_angle);
    void paintMyBody(QPainter &painter, const QPointF &pos, float seg_r, float MP, float father_angle);
    void paintMyBody2(QPainter &painter, const QPointF &pos, float seg_r, float MP, float father_angle);
    void paintMyTail(QPainter &painter, const QPointF &pos, float length, float max_w, float angle);

private:
    float body_height;
    float fish_r; // fish head r
    float fin_length;
    int head_alpha;
    int body_alpha;
    int fin_alpha;
    float main_angle;
    int current_value;
    int speed;
    float wave;

    QTimer *timer;
    bool start_fin;
    bool paint_point;

    QPointF head_pos;
};

#endif // MAGIC_FISH_H
