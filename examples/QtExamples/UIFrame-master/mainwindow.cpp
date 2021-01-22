#include "mainwindow.h"
#include <QMouseEvent>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    titleBar = new TitleBar();
    isPress = false;

    setWindowFlags(Qt::FramelessWindowHint);
    setMenuWidget(titleBar);

    connect(titleBar, &TitleBar::MinimizeButtonClicked, this, &MainWindow::showMinimized);
    connect(titleBar, &TitleBar::CloseButtonClicked, this, &MainWindow::close);
}

MainWindow::~MainWindow()
{

}

void MainWindow::mousePressEvent(QMouseEvent *e)
{
    if (e->button() == Qt::LeftButton) {
        windowPos = this->pos();
        mousePos = e->globalPos();

        isPress = true;
    }
}

void MainWindow::mouseReleaseEvent(QMouseEvent *e)
{
    if (e->button() == Qt::LeftButton)
        isPress = false;
}

void MainWindow::mouseMoveEvent(QMouseEvent *e)
{
    if (isPress)
        move(windowPos + (e->globalPos() - mousePos));
}
