/***************************************************************
 *Copyright(c) 2014-2015 Company By LiQi
 *All rights reserved.
 *文件名称：数据库备份文件
 *简要描述：提供用户备份数据库功能
 *
 *当前版本：V1.0
 *作者：Kelvin Li
 *创作日期：2014/12
 *说明：酒店管理系统数据库备份
 *版权归creazylq所有，转载请注明出处并保持作品完整性
 *Email：creazylq@163.com
******************************************************************/
#include "backupdatanasedialog.h"
#include "ui_backupdatanasedialog.h"

#include "app/myhelper.h"
#include "app/myapp.h"
#include <QProcess>
#include <QFileDialog>
#include <QMessageBox>
#include <QDebug>

BackupDatanaseDialog::BackupDatanaseDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::BackupDatanaseDialog)
{
    ui->setupUi(this);
    this->InitForm();
}

BackupDatanaseDialog::~BackupDatanaseDialog()
{
    delete ui;
}

void BackupDatanaseDialog::InitForm()
{
    ui->labelBackInfo->setText(tr(" "));//初始化备份提示信息
    ui->pbnOk->setToolTip(tr("确认备份"));

    ui->progressBar->setRange(0,5000 - 1);
    ui->progressBar->setValue(0);
}

/*
 *函数功能：备份数据库
*/
void BackupDatanaseDialog::on_pbnOk_clicked()
{
    QString pathname = ui->lineEdit->text();
    QString Cmd = QString("mysqldump.exe --add-drop-table -u%1 -p%2 hotel").arg("root","123456");
    QString Path = QString("%1").arg(pathname);
    QProcess *poc=new QProcess;
    poc->setStandardOutputFile(Path);
    poc->start(Cmd);

    for(int i = 0;i<5000;i++)
    {
        ui->labelBackInfo->setText(tr("正在备份……"));
        for(int j = 0;j<2000;j++)
        {
            ui->progressBar->setValue(i);
        }
        ui->labelBackInfo->setText(tr("备份完成"));

        ui->pbnOk->setToolTip(tr("已经备份完成"));
    }

    QString currentname = Myapp::CurrentUserName;
    qDebug() <<"备份数据库:"<<currentname;
    myHelper::MyLoginBlog("logblog","备份数据库","备份全部数据",currentname);

}

/*
 *获取当前要备份数据库的目录
*/
void BackupDatanaseDialog::on_pbnSearch_clicked()
{
    QString defaultname = "back_hotel.sql";
    //选择路径
    QString filename = QFileDialog::getSaveFileName(this,tr("保存数据库"),"",
                                                    tr("*sql;; *txt;;"));
    if(filename.isEmpty())
    {
        filename = defaultname;
    }
    ui->lineEdit->setText(filename);

}

void BackupDatanaseDialog::on_lineEdit_textChanged(const QString &arg1)
{
    ui->progressBar->setValue(0);
    ui->pbnOk->setToolTip(tr(""));
}
