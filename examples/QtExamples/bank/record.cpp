#include "record.h"
#include "ui_record.h"
#include "widget.h"
#include "deal_user.h"
#include "user_tranrecord.h"

extern QString ReCord;

record::record(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::record)
{
    ui->setupUi(this);
    this->ui->label->setText(ReCord);
}

record::~record()
{
    delete ui;
}

void record::on_close_music_clicked()
{
    Widget w;
    //w.sound->stop();
}

void record::on_exit_clicked()
{
    this->close();
    deal_user D;
    D.show();
    D.exec();
}
