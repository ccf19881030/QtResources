#ifndef QDRAGRECT_H
#define QDRAGRECT_H

#include <QFrame>
#include <QMouseEvent>

//
// A Utility Widget to represent a draggable rectangle
//
class QDragRect : public QFrame
{
    Q_OBJECT
public:
    explicit QDragRect(QWidget *parent = 0) : QFrame(parent)
    {
    }
signals:
    void mouseDrag(QPoint fromPoint, QPoint toPoint);
protected :
    virtual void mousePressEvent(QMouseEvent *event)
    {
        if (event->button() == Qt::LeftButton)
            fromPoint = event->pos();
    }
    virtual void mouseMoveEvent(QMouseEvent *event)
    {
        if (event->buttons() & Qt::LeftButton)
            emit mouseDrag(fromPoint, event->pos());
    }
private :
    QPoint fromPoint;
};

#endif // QDRAGRECT_H
