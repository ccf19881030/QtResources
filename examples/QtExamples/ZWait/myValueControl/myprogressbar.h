#ifndef MYPROGRESSBAR_H
#define MYPROGRESSBAR_H

#define RECT_WIDTH 20
#define LEFT_SPACE 3
#define TOP_SPACE 2
#define RECT_SPACE 3
#define LARGE_ANGLE 20
#define SMALL_ANGLE 30

#include <QWidget>
#include <QtGui>

class myProgressBar : public QWidget
{
    Q_OBJECT
public:
    explicit myProgressBar(QWidget *parent = 0);

protected:
    void paintEvent(QPaintEvent *);
    QSize sizeHint() const
    {
        return QSize(300,70);
    }

private:
    void drawBackground(QPainter* painter);
    void drawRects(QPainter* painter);

private:
    int m_nCurrentIndex;
    int m_nRectCount;
    QTimer* updateTimer;
    bool m_bReverse;

private:
    void initVariables();

private slots:
    void UpdateGraph();

public slots:
    void start();
    void stop();
    void setInterval(int msec);

};

#endif // MYPROGRESSBAR_H
