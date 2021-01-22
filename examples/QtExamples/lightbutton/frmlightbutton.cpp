#include "frmlightbutton.h"
#include "ui_frmlightbutton.h"
#include "qdatetime.h"
#include "qtimer.h"

frmLightButton::frmLightButton(QWidget *parent) :
	QWidget(parent),
	ui(new Ui::frmLightButton)
{
	ui->setupUi(this);
	this->initForm();
}

frmLightButton::~frmLightButton()
{
	delete ui;
}

void frmLightButton::initForm()
{
	type = 0;

	QTimer *timer = new QTimer(this);
	timer->setInterval(1000);
	connect(timer, SIGNAL(timeout()), this, SLOT(updateValue()));
	timer->start();
	updateValue();
}

void frmLightButton::updateValue()
{
	if (type == 0) {
		ui->widget1->setLightGreen();
		ui->widget2->setLightRed();
		ui->widget3->setLightBlue();
		type = 1;
	} else if (type == 1) {
		ui->widget1->setLightBlue();
		ui->widget2->setLightGreen();
		ui->widget3->setLightRed();
		type = 2;
	} else if (type == 2) {
		ui->widget1->setLightRed();
		ui->widget2->setLightBlue();
		ui->widget3->setLightGreen();
		type = 0;
	}
}
