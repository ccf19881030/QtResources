#include "bankbook.h"
#include "ui_bankbook.h"
#include "user_account_detail.h"
#include "widget.h"
#include "deal_user.h"

extern QString Name;

bankbook::bankbook(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::bankbook)
{
    ui->setupUi(this);
    QString filename = QString("%1µÄ´æÕÛ.txt").arg(Name);
    QFile file(filename);
    if(!file.open(QIODevice::ReadWrite | QIODevice::Text))
    {
        qDebug()<<file.errorString();
    }
    QString book = file.readAll();
    this->ui->label->setText(book);
    file.close();
}

bankbook::~bankbook()
{
    delete ui;
}

void bankbook::on_close_music_clicked()
{
    Widget w;
    //w.sound->stop();
}

void bankbook::on_exit_clicked()
{
    this->close();
    deal_user D;
    D.show();
    D.exec();
}
