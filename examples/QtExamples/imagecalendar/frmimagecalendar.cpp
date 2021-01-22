#include "frmimagecalendar.h"
#include "ui_frmimagecalendar.h"

frmImageCalendar::frmImageCalendar(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::frmImageCalendar)
{
    ui->setupUi(this);
}

frmImageCalendar::~frmImageCalendar()
{
    delete ui;
}
