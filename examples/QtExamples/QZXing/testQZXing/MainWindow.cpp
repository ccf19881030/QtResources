#include "MainWindow.h"
#include "ui_MainWindow.h"
#include "../QZXingLib/QZXing/QZXing.h"

#include <QTextCodec>
#include <QFileDialog>
#include <QMessageBox>

CMainWindow::CMainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::CMainWindow)
{
    ui->setupUi(this);
    setWindowTitle("Create By liuyuanan");
}

void CMainWindow::on_pushButton_clicked()
{
    m_fileName = QFileDialog::getOpenFileName(this,
                                              tr("二维码打开文件"),
                                              "./",
                                              tr("任何文件(*.*)"
                                              ";;文本文件(*.png)")
                                              );

    if(m_fileName.isEmpty() == false)
    {
        ui->lineEdit->setText(m_fileName);
        QImage img;        //加载图像
        if(!(img.load(m_fileName)))
        {
            QMessageBox::information(this,
                                     tr("打开图像失败"),
                                     tr("打开图像失败!"));
            return;
        }
        img=img.scaled(ui->label->width(),ui->label->height(),Qt::KeepAspectRatio);
        ui->label->setPixmap(QPixmap::fromImage(img));

        QZXing decoder(QZXing::DecoderFormat_None);
        QString qrmsg = decoder.decodeImage(img);
        ui->textEdit->setText(tr(">> %1").arg(qrmsg));
    }
}

CMainWindow::~CMainWindow()
{
    delete ui;
}
