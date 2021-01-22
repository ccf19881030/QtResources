#ifndef LEFTWIDGET_H
#define LEFTWIDGET_H

#include <QWidget>
#include <QVBoxLayout>

class LeftWidget : public QWidget
{
    Q_OBJECT

public:
    LeftWidget(QWidget *parent = 0);

protected:
    void paintEvent(QPaintEvent *);
    void mousePressEvent(QMouseEvent *);

private:
    QList<QString> tabNames;
    int currentIndex;

signals:
    void currentIndexChanged(int index);
};

#endif // LEFTWIDGET_H
