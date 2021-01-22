#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "titlebar.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

protected:
    void mousePressEvent(QMouseEvent *);
    void mouseReleaseEvent(QMouseEvent *);
    void mouseMoveEvent(QMouseEvent *);

private:
    bool isPress;
    QPoint windowPos;
    QPoint mousePos;

    TitleBar *titleBar;
};

#endif // MAINWINDOW_H
