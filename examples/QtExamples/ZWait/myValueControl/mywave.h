#ifndef MYWAVE_H
#define MYWAVE_H

#define PYW_BG_START_COLOR QColor(187,187,187)
#define PYW_BG_END_COLOR QColor(67,67,67)

#define PYW_CURVE_COLOR QColor(69,131,189)
#define PYW_PEN_WIDTH 2
#define PYW_LEFT_SPACE 10
#define PYW_TOP_SPACE 10
#define PYW_UPDATE_INTERVAL 20
#define PYW_VALUE_INCREMENT 1
#define PYW_RANGE 100

#define ANTIALIASING_ON true

#include <QWidget>
#include <QtGui>

class myWave : public QWidget
{
    Q_OBJECT
public:
    explicit myWave(QWidget *parent = 0);

public:
    /// public interfaces
    void setChannelCount(int cnt);

    void setChannelData(const QVector<int> DataVec);

protected:
    void paintEvent(QPaintEvent *);

    QSize sizeHint() const
    {
        return QSize(500,120);
    }

    void resizeEvent(QResizeEvent *);

private:
    void drawBg(QPainter* painter);

    void drawWave(QPainter* painter);


private:
    QTimer* m_updateTimer;

private slots:
    void UpdateData();

private:
    void initVariables();

private:
    int m_nChannelCount;

    QVector<int> m_CurrDataVec;
    QVector<int> m_DataVec;

    qreal m_xIncrement;

};

#endif // MYWAVE_H
