#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    textEdit = new QTextEdit;
    setCentralWidget(textEdit);
}

MainWindow::~MainWindow()
{
    delete ui;
}
