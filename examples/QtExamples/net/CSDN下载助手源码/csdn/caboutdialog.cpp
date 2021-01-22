#include "caboutdialog.h"
#include "ui_caboutdialog.h"
#include <QMessageBox>
#include <QDesktopServices>
#include <QUrl>

CAboutDialog::CAboutDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CAboutDialog)
{
    ui->setupUi(this);

#if (QT_VERSION <= QT_VERSION_CHECK(5,0,0))
    setWindowFlags(Qt::Dialog | Qt::WindowSystemMenuHint);
#else
    setWindowFlags(Qt::WindowCloseButtonHint);
#endif

}

CAboutDialog::~CAboutDialog()
{
    delete ui;
}

void CAboutDialog::on_pBtnAboutQt_clicked()
{
    QMessageBox::aboutQt(this, QString("关于QT"));
}

void CAboutDialog::on_pBtnAuthor_clicked()
{
    QDesktopServices::openUrl(QUrl("http://blog.csdn.net/wu5151"));
}
