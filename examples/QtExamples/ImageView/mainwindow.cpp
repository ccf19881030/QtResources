#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    resize(1024,600);

    m_ImagePreview = new ImagePreview(this);
    m_ImagePreview->setGeometry(0,0,1024,600);
}

MainWindow::~MainWindow()
{
    delete ui;
}
