#include "frmroundplot.h"
#include "ui_frmroundplot.h"

frmRoundPlot::frmRoundPlot(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::frmRoundPlot)
{
    ui->setupUi(this);
    this->initForm();
    on_pushButton_clicked();
}

frmRoundPlot::~frmRoundPlot()
{
    delete ui;
}

void frmRoundPlot::initForm()
{
    ui->widget2->setUsedColor(QColor(41, 137, 219));
    ui->widget2->setFreeColor(QColor(50, 50, 50));
    ui->widget2->setRangeTextColor(QColor(103, 103, 103));
    ui->widget2->setValueTextColor(QColor(250, 250, 250));
    ui->widget2->setValueBgColor(QColor(45, 169, 222));
    ui->widget2->setOutBgColor(QColor(202, 225, 255));
    ui->widget2->setCenterBgColor(QColor(67, 205, 128), QColor(60, 179, 113));
}

void frmRoundPlot::on_pushButton_clicked()
{	
    QString unit = ui->txtUnit->text();
    double minValue = ui->txtMinValue->text().toDouble();
    double maxValue = ui->txtMaxValue->text().toDouble();
    double value = ui->txtValue->text().toDouble();

    ui->widget1->setUnit(unit);
    ui->widget1->setRange(minValue, maxValue);
    ui->widget1->setValue(value);

    ui->widget2->setUnit(unit);
    ui->widget2->setRange(minValue, maxValue);
    ui->widget2->setValue(value);
}
