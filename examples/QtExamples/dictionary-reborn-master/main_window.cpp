#include "main_window.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    mainWidget = new QWidget();
    layout = new QHBoxLayout();
    leftWidget = new LeftWidget();
    rightWidget = new RightWidget();

    layout->addWidget(leftWidget);
    layout->addWidget(rightWidget);

    layout->setMargin(0);
    layout->setSpacing(0);

    mainWidget->setLayout(layout);

    setCentralWidget(mainWidget);

    connect(leftWidget, &LeftWidget::currentIndexChanged, this, [=](int index){
        rightWidget->layout->setCurrentIndex(index);
    });
}

MainWindow::~MainWindow()
{

}
