#include "frmcurvechart.h"
#include "ui_frmcurvechart.h"
#include "qdatetime.h"
#include "qtimer.h"

frmCurveChart::frmCurveChart(QWidget *parent) :
	QWidget(parent),
	ui(new Ui::frmCurveChart)
{
	ui->setupUi(this);
	this->initForm();
}

frmCurveChart::~frmCurveChart()
{
	delete ui;
}

void frmCurveChart::initForm()
{
	QTime t = QTime::currentTime();
	qsrand(t.msec() + t.second() * 1000);

	timer = new QTimer(this);
	timer->setInterval(200);
	connect(timer, SIGNAL(timeout()), this, SLOT(addData()));
}

void frmCurveChart::addData()
{
	ui->widget1->addData(qrand() % 100);
	ui->widget2->addData(qrand() % 100);
}

void frmCurveChart::on_ckShowHLine_stateChanged(int arg1)
{
	bool show = (arg1 != 0);
	ui->widget1->setShowHLine(show);
	ui->widget2->setShowHLine(show);
}

void frmCurveChart::on_ckShowPoint_stateChanged(int arg1)
{
	bool show = (arg1 != 0);
	ui->widget1->setShowPoint(show);
	ui->widget2->setShowPoint(show);
}

void frmCurveChart::on_ckShowPointBg_stateChanged(int arg1)
{
	bool show = (arg1 != 0);
	ui->widget1->setShowPointBg(show);
	ui->widget2->setShowPointBg(show);
}

void frmCurveChart::on_btnSetData_clicked()
{
	if (ui->btnAddData->text() == "停止模拟") {
		on_btnAddData_clicked();
	}

	on_btnClearData_clicked();

	QVector<double> data;

	for (int i = 0; i < 10; i++) {
		data.push_front(i * 10);
	}

	ui->widget2->setData(data);
}

void frmCurveChart::on_btnAddData_clicked()
{
	if (ui->btnAddData->text() == "模拟数据") {
		timer->start();
		ui->btnAddData->setText("停止模拟");
	} else {
		timer->stop();
		ui->btnAddData->setText("模拟数据");
	}
}

void frmCurveChart::on_btnClearData_clicked()
{
	ui->widget1->clearData();
	ui->widget2->clearData();
}
