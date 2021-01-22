#ifndef MYBATTERY_H
#define MYBATTERY_H

#include <QWidget>
#include <QtGui>

class myBattery : public QWidget
{
    Q_OBJECT
public:
    explicit myBattery(QWidget *parent = 0);

protected:
    void paintEvent(QPaintEvent *);
    QSize sizeHint() const
    {
        return QSize(200,120);
    }


private:
    void drawFrame(QPainter* painter);
    void drawBattery(QPainter* painter);

private:
    QTimer* updateTimer;
    bool    m_bReverse;
    qreal   m_headWidth;
    qreal   m_value;
    qreal   m_currentValue;
    QRectF  m_batteryRect;

signals:
    void valueChanged(qreal value);

private slots:
    void UpdateGraph();

public slots:
    void setValue(qreal value);

};

#endif // MYBATTERY_H
