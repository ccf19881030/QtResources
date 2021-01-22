#include "frmbarruler.h"
#include "ui_frmbarruler.h"
#include "qdatetime.h"
#include "qtimer.h"

frmBarRuler::frmBarRuler(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::frmBarRuler)
{
    ui->setupUi(this);
    this->initForm();
}

frmBarRuler::~frmBarRuler()
{
    delete ui;
}

void frmBarRuler::initForm()
{
    //初始化随机数种子
    QTime t = QTime::currentTime();
    qsrand(t.msec() + t.second() * 1000);

    QTimer *timer = new QTimer(this);
    timer->setInterval(2000);
    connect(timer, SIGNAL(timeout()), this, SLOT(updateValue()));
    timer->start();
    updateValue();
}

void frmBarRuler::updateValue()
{
    ui->widget1->setValue(qrand() % 100);
    ui->widget2->setValue(qrand() % 100);
    ui->widget3->setValue(qrand() % 100);
    ui->widget4->setValue(qrand() % 100);
}
