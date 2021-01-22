#include "frminputbox.h"
#include "ui_frminputbox.h"
#include "api/myhelper.h"

frmInputBox::frmInputBox(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::frmInputBox)
{
    ui->setupUi(this);
    this->InitStyle();
    myHelper::FormInCenter(this);
}

frmInputBox::~frmInputBox()
{
    delete ui;
}

void frmInputBox::InitStyle()
{
    if (App::UseStyle) {
        this->setProperty("Form", true);
        this->setProperty("CanMove", true);
        this->setWindowFlags(Qt::FramelessWindowHint | Qt::WindowSystemMenuHint | Qt::WindowMinMaxButtonsHint);
        IconHelper::Instance()->SetIcoMain(ui->lab_Ico, App::FontSize + 2);
        IconHelper::Instance()->SetIcoClose(ui->btnMenu_Close);
        connect(ui->btnMenu_Close, SIGNAL(clicked()), this, SLOT(close()));
        this->setFixedSize(280, 150);
    } else {
        this->setWindowFlags(Qt::WindowCloseButtonHint);
        this->resize(size().width(), size().height() - ui->widget_title->size().height());
        ui->widget_title->setVisible(false);
        this->setFixedSize(280, 120);
    }

    this->setWindowTitle(ui->lab_Title->text());
    connect(ui->btnCancel, SIGNAL(clicked()), this, SLOT(close()));
}

void frmInputBox::SetParameter(QString title, int type, QString defaultValue, bool pwd)
{
    ui->labInfo->setText(title);
    if (type == 0) {
        ui->cboxValue->setVisible(false);
        ui->txtValue->setPlaceholderText(defaultValue);
        if (pwd) {
            ui->txtValue->setEchoMode(QLineEdit::Password);
        }
    } else if (type == 1) {
        ui->txtValue->setVisible(false);
        ui->cboxValue->addItems(defaultValue.split("|"));
    }
}

void frmInputBox::on_btnOk_clicked()
{
    if (ui->txtValue->isVisible()) {
        value = ui->txtValue->text();
    } else if (ui->cboxValue->isVisible()) {
        value = ui->cboxValue->currentText();
    }

    done(1);
    this->close();
}
