#include "cvalidatedialog.h"
#include "ui_cvalidatedialog.h"

CValidateDialog::CValidateDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CValidateDialog)
{
    ui->setupUi(this);

#if (QT_VERSION <= QT_VERSION_CHECK(5,0,0))
    setWindowFlags(Qt::Dialog | Qt::WindowSystemMenuHint);
#else
    setWindowFlags(Qt::WindowCloseButtonHint);
#endif

}

CValidateDialog::~CValidateDialog()
{
    delete ui;
}

void CValidateDialog::on_pushButton_clicked()
{
    m_ValidateCode = ui->lineEdit->text();
    done(1);
    this->close();
    ui->lineEdit->setText("");
}

QString CValidateDialog::getValidateCode()
{
    return m_ValidateCode;
}

void CValidateDialog::setPixmap(QPixmap pixmap)
{
    ui->label->setPixmap(pixmap);
}
