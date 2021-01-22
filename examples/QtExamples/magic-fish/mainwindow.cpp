#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "magic_pool.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    MagicPool *pool = new MagicPool;
    this->setCentralWidget(pool);
}

MainWindow::~MainWindow()
{
    delete ui;
}

