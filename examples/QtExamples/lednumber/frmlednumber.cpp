#include "frmlednumber.h"
#include "ui_frmlednumber.h"
#include "qdatetime.h"
#include "qtimer.h"

frmLedNumber::frmLedNumber(QWidget *parent) :
	QWidget(parent),
	ui(new Ui::frmLedNumber)
{
	ui->setupUi(this);
	this->initForm();
}

frmLedNumber::~frmLedNumber()
{
    delete ui;
}

void frmLedNumber::initForm()
{
    //初始化随机数种子
    QTime t = QTime::currentTime();
    qsrand(t.msec() + t.second() * 1000);

    QTimer *timer = new QTimer(this);
    timer->setInterval(1000);
    connect(timer, SIGNAL(timeout()), this, SLOT(updateValue()));
    timer->start();
    updateValue();
}

void frmLedNumber::updateValue()
{
    ui->widget1->setNumber(qrand() % 10);
    ui->widget2->setNumber(qrand() % 10);
}
