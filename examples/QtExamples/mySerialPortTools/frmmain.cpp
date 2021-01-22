#include "frmmain.h"
#include "ui_frmmain.h"
#include "myhelper.h"

frmMain::frmMain(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::frmMain)
{
    ui->setupUi(this);
    myHelper::FormInCenter(this);
    this->InitForm();
}

frmMain::~frmMain()
{    
    delete ui;
}

//监听回车键
bool frmMain::eventFilter(QObject *obj, QEvent *event)
{
    if (obj==ui->txtSend)
    {
        if (event->type()==QEvent::KeyPress)
        {
            QKeyEvent *keyEvent=static_cast<QKeyEvent *>(event);
            if (keyEvent->key()==Qt::Key_Return || keyEvent->key()==Qt::Key_Enter)
            {
                WriteMyCom();
                return true;
            }
        }
    }

    return QObject::eventFilter(obj,event);
}

void frmMain::InitForm()
{    
    ReceiveCount=0;
    SendCount=0;
    IsShow=true;
    IsAutoClear=false;
    IsHexSend=true;
    IsHexReceive=true;
    IsDebug=false;

    QStringList comList;//串口号
    QStringList baudList;//波特率
    QStringList parityList;//校验位
    QStringList dataBitsList;//数据位
    QStringList stopBitsList;//停止位

#ifdef Q_OS_WIN//如果是windows系统
    comList<<"COM1"<<"COM2"<<"COM3"<<"COM4"<<"COM5"<<"COM6"
          <<"COM7"<<"COM8"<<"COM9"<<"COM10"<<"COM11"<<"COM12"
         <<"COM13"<<"COM14"<<"COM15";
#else//如果是unix或者其他系统
    comList<<"ttyUSB0"<<"ttyUSB1"<<"ttyUSB2"<<"ttyUSB3"<<"ttyUSB4"<<"ttyUSB5"
          <<"ttyS0"<<"ttyS1"<<"ttyS2"<<"ttyS3"<<"ttyS4"<<"ttyS5"<<"ttyS6"
         <<"ttyS7"<<"ttyS8"<<"ttyS9";
#endif

    ui->cboxPortName->addItems(comList);
    ui->cboxPortName->setCurrentIndex(0);

    baudList<<"50"<<"75"<<"100"<<"134"<<"150"<<"200"<<"300"
           <<"600"<<"1200"<<"1800"<<"2400"<<"4800"<<"9600"
          <<"14400"<<"19200"<<"38400"<<"56000"<<"57600"
         <<"76800"<<"115200"<<"128000"<<"256000";

    ui->cboxBaudRate->addItems(baudList);
    ui->cboxBaudRate->setCurrentIndex(12);

    parityList<<"无"<<"奇"<<"偶";

#ifdef Q_OS_WIN//如果是windows系统
    parityList<<"标志";
#endif

    parityList<<"空格";

    ui->cboxParity->addItems(parityList);
    ui->cboxParity->setCurrentIndex(0);

    dataBitsList<<"5"<<"6"<<"7"<<"8";
    ui->cboxDataBit->addItems(dataBitsList);
    ui->cboxDataBit->setCurrentIndex(3);

    stopBitsList<<"1";

#ifdef Q_OS_WIN//如果是windows系统
    stopBitsList<<"1.5";
#endif

    stopBitsList<<"2";

    ui->cboxStopBit->addItems(stopBitsList);
    ui->cboxStopBit->setCurrentIndex(0);

    //读取数据(采用定时器读取数据，不采用事件，方便移植到linux)
    myReadTimer=new QTimer(this);
    myReadTimer->setInterval(300);
    connect(myReadTimer,SIGNAL(timeout()),this,SLOT(ReadMyCom()));

    //发送数据
    mySendTimer=new QTimer(this);
    mySendTimer->setInterval(5000);
    connect(mySendTimer,SIGNAL(timeout()),this,SLOT(WriteMyCom()));

    //保存数据
    mySaveTimer=new QTimer(this);
    mySaveTimer->setInterval(5000);
    connect(mySaveTimer,SIGNAL(timeout()),this,SLOT(SaveMyCom()));

    //显示日期时间
    myTimer=new QTimer(this);
    myTimer->start(1000);
    connect(myTimer,SIGNAL(timeout()),this,SLOT(SetTime()));

    QDate dateNow=QDate::currentDate();
    ui->labDate->setText(QString("日期:%1").arg(dateNow.toString("yyyy年MM月dd日 dddd")));

    for (int i=1;i<=60;i++)
    {
        ui->cboxSend->addItem(QString::number(i)+"秒");
        ui->cboxSave->addItem(QString::number(i)+"秒");
    }

    ui->cboxSave->setCurrentIndex(4);
    ui->cboxSend->setCurrentIndex(4);

    ui->cboxSend->setEnabled(false);
    ui->cboxSave->setEnabled(false);

    this->ChangeEnable(false);
    this->ReadConfigData();//读取发送数据加载到下拉框
    this->ReadSendData();//读取数据转发文件

    ui->txtSend->installEventFilter(this);//安装监听器监听发送数据框回车响应
}

void frmMain::ReadSendData()
{
    QString fileName="SendData.txt";
    QFile file(fileName);
    if (!file.exists()){return;}//如果文件不存在则返回

    file.open(QFile::ReadOnly | QIODevice::Text);
    QTextStream in(&file);
    QString line;

    do { line=in.readLine();if (line!="") { SendDataList.append(line); }}
    while(!line.isNull());

    file.close();
}

void frmMain::ChangeEnable(bool b)
{
    ui->cboxBaudRate->setEnabled(!b);
    ui->cboxDataBit->setEnabled(!b);
    ui->cboxParity->setEnabled(!b);
    ui->cboxPortName->setEnabled(!b);
    ui->cboxStopBit->setEnabled(!b);

    ui->gbox2->setEnabled(b);
    ui->gbox3->setEnabled(b);
    ui->gbox5->setEnabled(b);
    ui->gbox6->setEnabled(b);
    ui->btnOpen->setEnabled(true);
}

void frmMain::SetTime()
{
    QTime timeNow=QTime::currentTime();
    ui->labTime->setText(QString("时间:%1").arg(timeNow.toString()));
}

void frmMain::ReadMyCom()
{
    //这个判断尤为重要,否则的话直接延时再接收数据,空闲时和会出现高内存占用
    if (myCom->bytesAvailable()<=0){return;}

    myHelper::Sleep(100);//延时100毫秒保证接收到的是一条完整的数据,而不是脱节的
    QByteArray buffer=myCom->readAll();

    if (IsShow)
    {
        if (IsHexReceive)
        {
            QString tempDataHex=myHelper::ByteArrayToHexStr(buffer);
            ui->txtDataHex->append(QString("接收:%1 时间:%2")
                                   .arg(tempDataHex)
                                   .arg(QTime::currentTime().toString("HH:mm:ss")));

            if (IsDebug)//2013-8-6增加接收数据后转发数据，模拟设备
            {
                foreach(QString tempData,SendDataList)
                {
                    QStringList temp=tempData.split(';');
                    if (tempDataHex==temp[0])
                    {
                        //这里没有跳出循环，有可能一条数据会对应多条数据需要转发
                        myCom->write(myHelper::HexStrToByteArray(temp[1]));
                    }
                }
            }
        }
        else
        {
            QString tempDataNormal=QString(buffer);
            ui->txtDataHex->append(QString("接收:%1 时间:%2")
                                   .arg(tempDataNormal)
                                   .arg(QTime::currentTime().toString("HH:mm:ss")));

            if (IsDebug)//2013-8-6增加接收数据后转发数据，模拟设备
            {
                foreach(QString tempData,SendDataList)
                {
                    QStringList temp=tempData.split(';');
                    if (tempDataNormal==temp[0])
                    {
                        //这里没有跳出循环，有可能一条数据会对应多条数据需要转发
                        myCom->write(temp[1].toLatin1());
                    }
                }
            }
        }

        ReceiveCount=ReceiveCount+buffer.size();
        ui->labReceive->setText(QString("接收:%1 字节").arg(ReceiveCount));
    }
}

void frmMain::WriteMyCom()
{
    QString str=ui->txtSend->currentText();
    if (str==""){ui->txtSend->setFocus();return;}//发送数据为空
    if (!myCom->isOpen()) { return; }//串口没有打开

    QByteArray outData=str.toLatin1();
    int size=outData.size();

    if (IsHexSend)//转化为16进制发送
    {
        outData=myHelper::HexStrToByteArray(str);
        size=outData.size();
        myCom->write(outData);
    }
    else
    {
        size=outData.size();
        myCom->write(outData);
    }

    ui->txtDataHex->append(QString("发送:%1 时间:%2")
                           .arg(str)
                           .arg(QTime::currentTime().toString("HH:mm:ss")));

    SendCount=SendCount+size;
    ui->labSend->setText(QString("发送:%1 字节").arg(SendCount));

    if (IsAutoClear)
    {
        ui->txtSend->setCurrentIndex(-1);
        ui->txtSend->setFocus();
    }
}

void frmMain::SaveMyCom()
{
    QString tempData=ui->txtDataHex->toPlainText();
    if (tempData==""){return;}//如果没有内容则不保存

    QDateTime now=QDateTime::currentDateTime();
    QString name=now.toString("yyyyMMddHHmmss");
    QString fileName=name+".txt";

    QFile file(fileName);
    file.open(QFile::WriteOnly | QIODevice::Text);
    QTextStream out(&file);
    out<<tempData;
    file.close();
}

void frmMain::on_btnOpen_clicked()
{
    if (ui->btnOpen->text()=="打开串口")
    {
        QString portName=ui->cboxPortName->currentText();

#ifdef Q_OS_WIN//如果是windows系统
        myCom = new QextSerialPort(portName);
#else
        myCom = new QextSerialPort("/dev/" + portName);
#endif        

        if (myCom->open(QIODevice::ReadWrite))
        {
            //清空缓冲区
            myCom->flush();
            //设置波特率
            myCom->setBaudRate((BaudRateType)ui->cboxBaudRate->currentText().toInt());
            //设置数据位
            myCom->setDataBits((DataBitsType)ui->cboxDataBit->currentText().toInt());
            //设置校验位
            myCom->setParity((ParityType)ui->cboxParity->currentIndex());
            //设置停止位
            myCom->setStopBits((StopBitsType)ui->cboxStopBit->currentIndex());
            myCom->setFlowControl(FLOW_OFF);
            myCom->setTimeout(10);

            this->ChangeEnable(true);
            ui->btnOpen->setText("关闭串口");
            ui->labIsOpen->setText("串口状态：打开");
            this->myReadTimer->start();
        }
    }
    else
    {
        myCom->close();
        this->ChangeEnable(false);
        ui->btnOpen->setText("打开串口");
        ui->labIsOpen->setText("串口状态：关闭");
        this->myReadTimer->stop();

        //这样的话保证每次关闭串口后,自动发送和自动保存定时器不会空转
        ui->ckIsAutoSend->setChecked(false);
        ui->ckIsAutoSave->setChecked(false);
    }
}

void frmMain::on_ckHexSend_stateChanged(int arg1)
{
    IsHexSend=(arg1==0?false:true);
}

void frmMain::on_ckHexReceive_stateChanged(int arg1)
{
    IsHexReceive=(arg1==0?false:true);
}

void frmMain::on_ckIsAutoSend_stateChanged(int arg1)
{    
    bool IsAutoSend=(arg1==0?false:true);
    if (IsAutoSend)
    {
        this->mySendTimer->start();
    }
    else
    {
        this->mySendTimer->stop();
    }
    ui->cboxSend->setEnabled(IsAutoSend);
}

void frmMain::on_ckIsAutoSave_stateChanged(int arg1)
{
    bool IsAutoSave=(arg1==0?false:true);
    if (IsAutoSave)
    {
        this->mySaveTimer->start();
    }
    else
    {
        this->mySaveTimer->stop();
    }
    ui->cboxSave->setEnabled(IsAutoSave);
}

void frmMain::on_ckIsAutoClear_stateChanged(int arg1)
{
    IsAutoClear=(arg1==0?false:true);
}

void frmMain::on_ckIsDebug_stateChanged(int arg1)
{
    IsDebug=(arg1==0?false:true);
}

void frmMain::on_btnClearSend_clicked()
{
    SendCount=0;
    ui->labSend->setText("发送:0 字节");
}

void frmMain::on_btnClearReceive_clicked()
{
    ReceiveCount=0;
    ui->labReceive->setText("接收:0 字节");
}

void frmMain::on_cboxSend_currentIndexChanged(int index)
{
    mySendTimer->setInterval((index+1)*1000);
}

void frmMain::on_cboxSave_currentIndexChanged(int index)
{
    mySaveTimer->setInterval((index+1)*1000);
}

void frmMain::on_btnStopShow_clicked()
{
    if (ui->btnStopShow->text()=="停止显示")
    {
        IsShow=false;
        ui->btnStopShow->setText("开始显示");
    }
    else
    {
        IsShow=true;
        ui->btnStopShow->setText("停止显示");
    }
}

void frmMain::on_btnClearAll_clicked()
{    
    ui->txtDataHex->clear();
}

void frmMain::on_btnSend_clicked()
{
    this->WriteMyCom();
}

void frmMain::on_btnSave_clicked()
{
    this->SaveMyCom();
}

void frmMain::ReadConfigData()
{    
    QString fileName="ConfigData.txt";
    QFile file(fileName);
    if (!file.exists()){return;}

    ui->txtSend->clear();
    file.open(QFile::ReadOnly | QIODevice::Text);
    QTextStream in(&file);
    QString line;

    do{ line=in.readLine();if (line!="") {ui->txtSend->addItem(line);}}
    while(!line.isNull());

    file.close();
}

void frmMain::on_btnData_clicked()
{
    QString fileName="ConfigData.txt";
    QFile file(fileName);

    if (!file.exists()){ myHelper::ShowMessageBoxError("数据文件不存在！"); return;}

    if (ui->btnData->text()=="管理数据")
    {
        ui->txtDataHex->setReadOnly(false);
        ui->gbox2->setTitle("管理数据");
        ui->txtDataHex->clear();

        file.open(QFile::ReadOnly | QIODevice::Text);
        QTextStream in(&file);
        ui->txtDataHex->setText(in.readAll());
        file.close();

        ui->btnData->setText("保存数据");
    }
    else
    {
        ui->txtDataHex->setReadOnly(true);
        ui->gbox2->setTitle("接收数据");

        file.open(QFile::WriteOnly | QIODevice::Text);
        QTextStream out(&file);
        out<<ui->txtDataHex->toPlainText();
        file.close();

        ui->txtDataHex->clear();
        ui->btnData->setText("管理数据");

        this->ReadConfigData();
    }
}
