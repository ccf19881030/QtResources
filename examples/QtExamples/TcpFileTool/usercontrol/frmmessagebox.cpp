#include "frmmessagebox.h"
#include "ui_frmmessagebox.h"
#include "api/myhelper.h"

frmMessageBox::frmMessageBox(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::frmMessageBox)
{
    ui->setupUi(this);
    this->InitStyle();
    myHelper::FormInCenter(this);
}

frmMessageBox::~frmMessageBox()
{
    delete ui;
}

void frmMessageBox::InitStyle()
{
    if (App::UseStyle) {
        this->setProperty("Form", true);
        this->setProperty("CanMove", true);
        this->setWindowFlags(Qt::FramelessWindowHint | Qt::WindowSystemMenuHint | Qt::WindowMinMaxButtonsHint);
        IconHelper::Instance()->SetIcoMain(ui->lab_Ico, App::FontSize + 2);
        IconHelper::Instance()->SetIcoClose(ui->btnMenu_Close);
        connect(ui->btnMenu_Close, SIGNAL(clicked()), this, SLOT(close()));
    } else {
        this->setWindowFlags(Qt::WindowCloseButtonHint);
        this->resize(size().width(), size().height() - ui->widget_title->size().height());
        ui->widget_title->setVisible(false);
    }

    this->setWindowTitle(ui->lab_Title->text());
    connect(ui->btnCancel, SIGNAL(clicked()), this, SLOT(close()));
}

void frmMessageBox::SetMessage(QString msg, int type)
{
    if (type == 0) {
        ui->labIcoMain->setStyleSheet("border-image: url(:/image/msg_info.png);");
        ui->btnCancel->setVisible(false);
        ui->lab_Title->setText("提示");
    } else if (type == 1) {
        ui->labIcoMain->setStyleSheet("border-image: url(:/image/msg_question.png);");
        ui->lab_Title->setText("询问");
    } else if (type == 2) {
        ui->labIcoMain->setStyleSheet("border-image: url(:/image/msg_error.png);");
        ui->btnCancel->setVisible(false);
        ui->lab_Title->setText("错误");
    }

    ui->labInfo->setText(msg);
    this->setWindowTitle(ui->lab_Title->text());
}

void frmMessageBox::on_btnOk_clicked()
{
    done(1);
    this->close();
}
