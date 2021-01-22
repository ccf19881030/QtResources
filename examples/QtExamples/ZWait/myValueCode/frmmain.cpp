#include "frmmain.h"
#include "ui_frmmain.h"
#include "myStaticClass.h"

frmMain::frmMain(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::frmMain)
{
    ui->setupUi(this);

    FormHelper::FormInCenter(this);
    FormHelper::FormNotResize(this);
    FormHelper::FormOnTop(this);
    FormHelper::FormOpacity(this,0.9);
    FormHelper::FormOnlyCloseButton(this);

    this->setWindowIcon(QIcon(":/img/1.ico"));
}

frmMain::~frmMain()
{
    delete ui;
}

void frmMain::on_btn1_clicked()
{
    MyMessageBox::ChMessageOnlyOk(MyHelper::GetLongDateTime());
}

void frmMain::on_btn2_clicked()
{
    QStringList ss=MyHelper::GetFileNames("*.exe");
    foreach(QString s,ss)
    {
        ui->txt->append(s);
    }
}

void frmMain::on_btn3_clicked()
{
    MyHelper::OpenUrlOrExe("notepad.exe");
}

void frmMain::on_btn4_clicked()
{
    MyHelper::OpenUrlOrExe("calc");
}

void frmMain::on_btn5_clicked()
{
    QStringList filter;
    filter<<"*.exe"<<"*.txt"<<"*.dll";
    QStringList ss=MyHelper::GetFolderFileNames(filter);
    foreach(QString s,ss)
    {
        ui->txt->append(s);
    }
}

void frmMain::on_btn6_clicked()
{
    ui->txt->append(MyHelper::GetCurrentPath());
}

void frmMain::on_btn7_clicked()
{
    ui->txt->append(tr("现在是:%1").arg(MyHelper::GetLongDateTime()));
    MyHelper::DelayTime(3000);
    ui->txt->append(tr("现在是:%1").arg(MyHelper::GetLongDateTime()));
}

void frmMain::on_btn8_clicked()
{
    ui->txt->append(tr("2012年是闰年:%1").arg(MyHelper::IsLeapYear("2012")));
}

void frmMain::on_btn21_clicked()
{
    FileHelper::CreateFile(MyHelper::GetCurrentPath()+"/temp.txt");
}

void frmMain::on_btn22_clicked()
{
    ui->txt->append(tr("文件是否存在:%1").arg(FileHelper::FileExists(MyHelper::GetCurrentPath()+"/temp.txt")));
}

void frmMain::on_btn23_clicked()
{
    FileHelper::CreateFolder(MyHelper::GetCurrentPath()+"/temp");
}

void frmMain::on_btn24_clicked()
{
    ui->txt->append(tr("文件夹是否存在:%1").arg(FileHelper::FolderExists(MyHelper::GetCurrentPath()+"/temp")));
}

void frmMain::on_btn31_clicked()
{
    FormHelper::FormOpacity(this,0.5);
}

void frmMain::on_btn32_clicked()
{
    FormHelper::FormOpacity(this,1);
}

void frmMain::on_btn33_clicked()
{
    FormHelper::FormOnTop(this);
}

void frmMain::on_btn34_clicked()
{
    FormHelper::FormOnBottom(this);
}

void frmMain::on_btn35_clicked()
{
    FormHelper::SetMyStyle(this);
}

void frmMain::on_btn36_clicked()
{
    QSize deskSize=FormHelper::GetDesktopSize();
    ui->txt->append(tr("分辨率:%1 x %2").arg(deskSize.width()).arg(deskSize.height()));
}
