#include "frmmain.h"
#include "ui_frmmain.h"
#include "myhelper.h"
#include "myapp.h"

frmMain::frmMain(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::frmMain)
{
    ui->setupUi(this);

    FormHelper::FormInCenter(this);
    FormHelper::FormNotResize(this);
    FormHelper::FormOnlyCloseButton(this);

    this->InitForm();
    this->on_btnOpen_clicked();
}

frmMain::~frmMain()
{
    delete ui;
}

void frmMain::closeEvent(QCloseEvent *)
{
    myApp::PortName=ui->cboxPortName->currentText();
    myApp::WriteConfig();
}

void frmMain::InitForm()
{
    QStringList portNames;
    portNames<<"COM1"<<"COM2"<<"COM3"<<"COM4"<<"COM5"
            <<"COM6"<<"COM7"<<"COM8"<<"COM9"<<"COM10";
    ui->cboxPortName->addItems(portNames);
    ui->cboxPortName->setCurrentIndex(ui->cboxPortName->findText(myApp::PortName));
    ui->txtChuChang->setText(QString::number(myApp::CountChuChang));
    ui->txtWeiXiu->setText(QString::number(myApp::CountWeiXiu));

    for (int i=16;i<255;i++)
    {
        ui->cboxAddr->addItem(QString::number(i));
    }

    for (int i=2013;i<=2020;i++)
    {
        ui->cboxYear->addItem(QString::number(i));
    }

    for (int i=1;i<=12;i++)
    {
        ui->cboxMonth->addItem(QString::number(i));
    }

    for (int i=1;i<=31;i++)
    {
        ui->cboxDay->addItem(QString::number(i));
    }

    QDate Now=QDate::currentDate();
    ui->cboxYear->setCurrentIndex(
                ui->cboxYear->findText(QString::number(Now.year())));
    ui->cboxMonth->setCurrentIndex(
                ui->cboxMonth->findText(QString::number(Now.month())));
    ui->cboxDay->setCurrentIndex(
                ui->cboxDay->findText(QString::number(Now.day())));

    ui->gbox2->setEnabled(false);
    ui->gbox3->setEnabled(false);
    ui->btnWriteChuChang->setEnabled(false);
    ui->btnWriteWeiXiu->setEnabled(false);
}

void frmMain::on_btnOpen_clicked()
{
    if (ui->btnOpen->text()=="打开(&O)")
    {
        MaiChong=new myMaiChongAPI(ui->cboxPortName->currentText());
        if (MaiChong->Open())
        {
            connect(MaiChong,SIGNAL(OnWriteReceiveData(uchar,uchar)),
                    this,SLOT(OnWriteReceive(uchar,uchar)));
            connect(MaiChong,SIGNAL(OnReadReceiveData(uchar,uchar,uchar,uchar,uchar,uchar,uchar)),
                    this,SLOT(OnReadReceive(uchar,uchar,uchar,uchar,uchar,uchar,uchar)));

            MaiChong->GetChuChangOrWeiXiu(0xFF,0x00);//首次读取出厂维修记录
            ui->gbox2->setEnabled(true);
            ui->gbox3->setEnabled(true);
            ui->btnOpen->setText("关闭(&C)");
        }
        else
        {
            myHelper::ShowMessageBoxError("串口打开失败！请检查串口是否正确！");
        }
    }
    else
    {
        MaiChong->Close();

        disconnect(MaiChong,SIGNAL(OnWriteReceiveData(uchar,uchar)),
                   this,SLOT(OnWriteReceive(uchar,uchar)));
        disconnect(MaiChong,SIGNAL(OnReadReceiveData(uchar,uchar,uchar,uchar,uchar,uchar,uchar)),
                   this,SLOT(OnReadReceive(uchar,uchar,uchar,uchar,uchar,uchar,uchar)));

        this->on_btnClear_clicked();
        ui->gbox2->setEnabled(false);
        ui->gbox3->setEnabled(false);
        ui->btnWriteChuChang->setEnabled(false);
        ui->btnWriteWeiXiu->setEnabled(false);
        ui->btnOpen->setText("打开(&O)");
    }
}

void frmMain::OnWriteReceive(uchar addr, uchar countNumber)
{
    QString temp=tr("设备地址:%1 记录总数:%2").arg(addr).arg(countNumber);
    ui->cboxAddr->setCurrentIndex(ui->cboxAddr->findText(QString::number(addr)));
    ui->txtReceive->append(temp);
}

void frmMain::OnReadReceive(uchar addr, uchar countNumber, uchar number, uchar year, uchar month, uchar day, uchar type)
{    
    QString temp;
    if (type==0x00)
    {
        temp=tr("记录总数:%1 记录号:%2 出厂时间:20%3年%4月%5日").arg(countNumber).arg(number).arg(year).arg(month).arg(day);
    }
    else
    {
        temp=tr("记录总数:%1 记录号:%2 维修时间:20%3年%4月%5日").arg(countNumber).arg(number).arg(year).arg(month).arg(day);
    }

    if (countNumber==0x00)//如果记录总数为0，说明还没有出厂，则这个时候只能设置出厂
    {
        ui->btnWriteChuChang->setEnabled(true);
        ui->btnWriteWeiXiu->setEnabled(false);
        return;//不需要显示255的出厂记录
    }
    else//如果记录总数大于0，说明已经出厂，则这个时候只能维修
    {
        ui->btnWriteChuChang->setEnabled(false);
        ui->btnWriteWeiXiu->setEnabled(true);
    }

    ui->cboxAddr->setCurrentIndex(ui->cboxAddr->findText(QString::number(addr)));
    ui->txtReceive->append(temp);

    if (countNumber-1>number)
    {
        MaiChong->GetChuChangOrWeiXiu(0xFF,number+1);
    }
}

void frmMain::on_btnClear_clicked()
{
    ui->txtReceive->clear();
}

void frmMain::on_btnRead_clicked()
{
    if (!MaiChong->IsOpen()){return;}
    MaiChong->GetChuChangOrWeiXiu(0xFF,0x00);
}

void frmMain::on_btnWriteChuChang_clicked()
{
    if (!MaiChong->IsOpen()){return;}
    MaiChong->SetChuChang(0xFF,
                          ui->cboxYear->currentText().mid(2,2).toInt(),
                          ui->cboxMonth->currentText().toInt(),
                          ui->cboxDay->currentText().toInt());

    //重新读取出厂和维修记录信息
    myHelper::Sleep(100);
    this->on_btnRead_clicked();

    //计数累加
    myApp::CountChuChang++;
    ui->txtChuChang->setText(QString::number(myApp::CountChuChang));
}

void frmMain::on_btnWriteWeiXiu_clicked()
{
    if (!MaiChong->IsOpen()){return;}
    MaiChong->SetWeiXiu(0xFF,
                        ui->cboxYear->currentText().mid(2,2).toInt(),
                        ui->cboxMonth->currentText().toInt(),
                        ui->cboxDay->currentText().toInt());

    //重新读取出厂和维修记录信息
    myHelper::Sleep(100);
    this->on_btnRead_clicked();

    //计数累加
    myApp::CountWeiXiu++;
    ui->txtWeiXiu->setText(QString::number(myApp::CountWeiXiu));
}

void frmMain::on_btnClearData_clicked()
{
    if (!MaiChong->IsOpen()){return;}

    if (myApp::UsePwd)
    {
        QString pwd=myHelper::ShowInputBox(this,"请输入密码：");
        if (pwd.isEmpty()){return;}

        if (pwd==myApp::PassWord)
        {
            MaiChong->ClearData(0xFF);

            //重新读取出厂和维修记录信息
            myHelper::Sleep(100);
            this->on_btnRead_clicked();

            myHelper::ShowMessageBoxInfo("擦除记录成功！");
        }
        else
        {
            myHelper::ShowMessageBoxError("密码错误，请重新输入！");
        }
    }
    else
    {
        if (myHelper::ShowMessageBoxQuesion("确定要擦除记录吗？")==0)
        {
            MaiChong->ClearData(0xFF);

            //重新读取出厂和维修记录信息
            myHelper::Sleep(100);
            this->on_btnRead_clicked();

            myHelper::ShowMessageBoxInfo("擦除记录成功！");
        }
    }
}

void frmMain::on_btnClearChuChang_clicked()
{
    if (myHelper::ShowMessageBoxQuesion("确定要清空出厂总数吗？")==0)
    {
        myApp::CountChuChang=0;
        ui->txtChuChang->setText(QString::number(myApp::CountChuChang));
    }
}

void frmMain::on_btnClearWeiXiu_clicked()
{
    if (myHelper::ShowMessageBoxQuesion("确定要清空维修总数吗？")==0)
    {
        myApp::CountWeiXiu=0;
        ui->txtWeiXiu->setText(QString::number(myApp::CountWeiXiu));
    }
}
