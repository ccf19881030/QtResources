#include "frmcpumemorylabel.h"
#include "ui_frmcpumemorylabel.h"

frmCpuMemoryLabel::frmCpuMemoryLabel(QWidget *parent) :
	QWidget(parent),
	ui(new Ui::frmCpuMemoryLabel)
{
	ui->setupUi(this);
	this->initForm();
}

frmCpuMemoryLabel::~frmCpuMemoryLabel()
{
	delete ui;
}

void frmCpuMemoryLabel::initForm()
{
	setFont(QFont("Microsoft Yahei", 13));

	QString qss1 = QString("QLabel{background-color:rgb(0,0,0);color:rgb(%1);}").arg("100,184,255");
	QString qss2 = QString("QLabel{background-color:rgb(0,0,0);color:rgb(%1);}").arg("255,107,107");
	QString qss3 = QString("QLabel{background-color:rgb(0,0,0);color:rgb(%1);}").arg("24,189,155");

	ui->label1->setStyleSheet(qss1);
	ui->label2->setStyleSheet(qss2);
	ui->label3->setStyleSheet(qss3);

	connect(ui->label1, SIGNAL(textChanged(QString)), ui->label2, SLOT(setText(QString)));
	connect(ui->label1, SIGNAL(textChanged(QString)), ui->label3, SLOT(setText(QString)));
	ui->label1->start(1500);
}
