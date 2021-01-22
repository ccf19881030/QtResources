#include "checkoutdialog.h"
#include "ui_checkoutdialog.h"

CheckOutDialog::CheckOutDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CheckOutDialog)
{
    ui->setupUi(this);
}

CheckOutDialog::~CheckOutDialog()
{
    delete ui;
}
