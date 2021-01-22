#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include <QMainWindow>
#include <QHBoxLayout>
#include "left_widget.h"
#include "right_widget.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    QWidget *mainWidget;
    QHBoxLayout *layout;
    LeftWidget *leftWidget;
    RightWidget *rightWidget;
};

#endif // MAIN_WINDOW_H
