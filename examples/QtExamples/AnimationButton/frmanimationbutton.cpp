#include "frmanimationbutton.h"
#include "ui_frmanimationbutton.h"

frmAnimationButton::frmAnimationButton(QWidget *parent) :
	QWidget(parent),
	ui(new Ui::frmAnimationButton)
{
	ui->setupUi(this);

	QString qss = "color:#BECEC6;background:qlineargradient(spread:pad,x1:0,y1:0,x2:0,y2:1,stop:0 #1B3152,stop:1 #255C80);";
	this->setStyleSheet(qss);

	ui->widget1->setText("主页");
	ui->widget1->setImage(":/image/v-home-ico-home.png");

	ui->widget2->setText("通讯录");
	ui->widget2->setImage(":/image/v-home-ico-contact.png");

	ui->widget3->setText("图片");
	ui->widget3->setImage(":/image/v-home-ico-img.png");

	ui->widget4->setText("录音");
	ui->widget4->setImage(":/image/v-home-ico-record.png");
    ui->widget4->update();
}

frmAnimationButton::~frmAnimationButton()
{
	delete ui;
}
