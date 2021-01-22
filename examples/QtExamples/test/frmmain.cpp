#include "frmmain.h"
#include "ui_frmmain.h"
#include "qmessagebox.h"

frmMain::frmMain(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::frmMain)
{
    ui->setupUi(this);
}

frmMain::~frmMain()
{
    delete ui;
}

void frmMain::on_btnAdd_clicked()
{
    QPushButton *btn=new QPushButton;
    btn->setFocusPolicy(Qt::NoFocus);
    btn->setText(ui->txtName->text());
    btn->setProperty("btnType",ui->cboxType->currentIndex());
    ui->groupBox->layout()->addWidget(btn);
    connect(btn,SIGNAL(clicked()),this,SLOT(on_btn_clicked()));
}

void frmMain::on_btn_clicked()
{
    QPushButton *btn=(QPushButton*)sender();
    QMessageBox::information(this,"hello",btn->text());
}
