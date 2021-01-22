#include "mymaichongapi.h"
#include "myhelper.h"

myMaiChongAPI::myMaiChongAPI(QString portName)
{
    this->portName=portName;
    isOpen=false;
}

bool myMaiChongAPI::Open()
{
    myCOMMaiChong=new Win_QextSerialPort(this->portName,QextSerialBase::EventDriven);

    bool IsOpen=myCOMMaiChong->open(QIODevice::ReadWrite);

    if (IsOpen)
    {
        myCOMMaiChong->flush();//清空串口缓冲区
        myCOMMaiChong->setBaudRate(BAUD9600);
        myCOMMaiChong->setDataBits(DATA_8);
        myCOMMaiChong->setParity(PAR_NONE);
        myCOMMaiChong->setStopBits(STOP_1);
        myCOMMaiChong->setFlowControl(FLOW_OFF);
        myCOMMaiChong->setTimeout(10);

        connect(myCOMMaiChong,SIGNAL(readyRead()),this,SLOT(ReadData()));
        isOpen=true;
    }

    return IsOpen;
}

void myMaiChongAPI::Close()
{
    myCOMMaiChong->close();
    disconnect(myCOMMaiChong,SIGNAL(readyRead()),this,SLOT(ReadData()));
    isOpen=false;
}

void myMaiChongAPI::WriteData(uchar toAddress, uchar length, uchar id)
{
    uchar temp[]={toAddress,fromAddress,length,id};
    uchar checkCode=myHelper::GetCheckCode(temp,length+3);
    char body[]={head,toAddress,fromAddress,length,id,checkCode};
    myCOMMaiChong->write(body,length+5);
}

void myMaiChongAPI::WriteData(uchar toAddress, uchar length,uchar id,uchar parameter[],uchar size)
{
    uchar temp[4+size];//固定原地址、目的地址、长度、命令标识
    temp[0]=toAddress;
    temp[1]=fromAddress;
    temp[2]=length;
    temp[3]=id;

    for (int i=0;i<size;i++)
    {
        temp[4+i]=parameter[i];
    }

    //计算校验码
    uchar checkCode=myHelper::GetCheckCode(temp,length+3);

    char body[6+size];
    body[0]=head;
    body[1]=toAddress;
    body[2]=fromAddress;
    body[3]=length;
    body[4]=id;
    body[5+size]=checkCode;

    for (int i=0;i<size;i++)
    {
        body[5+i]=parameter[i];
    }

    myCOMMaiChong->write(body,length+5);
}

void myMaiChongAPI::SetChuChang(uchar addr, uchar year, uchar month, uchar day)
{
    uchar temp[6];
    temp[0]=0x05;
    temp[1]=0xA0;
    temp[2]=year;
    temp[3]=month;
    temp[4]=day;
    temp[5]=0x00;

    this->WriteData(addr,0x07,0xE8,temp,6);
}

void myMaiChongAPI::SetWeiXiu(uchar addr, uchar year, uchar month, uchar day)
{
    uchar temp[6];
    temp[0]=0x05;
    temp[1]=0xA0;
    temp[2]=year;
    temp[3]=month;
    temp[4]=day;
    temp[5]=0x01;

    this->WriteData(addr,0x07,0xE8,temp,6);
}

void myMaiChongAPI::GetChuChangOrWeiXiu(uchar addr, uchar number)
{
    uchar temp[3];
    temp[0]=0x02;
    temp[1]=0xA1;
    temp[2]=number;

    this->WriteData(addr,0x04,0xE8,temp,3);
}

void myMaiChongAPI::ClearData(uchar addr)
{
    uchar temp[2];
    temp[0]=0x01;
    temp[1]=0xAF;

    this->WriteData(addr,0x03,0xE8,temp,2);
}

void myMaiChongAPI::ReadData()
{
    myHelper::Sleep(100);
    QByteArray data=myCOMMaiChong->readAll();

    if (!data.isEmpty())
    {
        int len=data.length();
        int index=0;

        while(index<len)
        {
            if (data[index]==0x16 && data[index+1]==0x01)
            {
                uchar tempData=myHelper::GetUChar(data[index+6]);
                uchar addr=myHelper::GetUChar(data[index+2]);//源地址

                switch (tempData) {
                case 0xA8://写记录应答
                {
                    uchar countNumber=myHelper::GetUChar(data[index+7]);
                    emit this->OnWriteReceiveData(addr,countNumber);
                }
                    break;
                case 0xA9://读记录应答
                {
                    uchar countNumber=myHelper::GetUChar(data[index+7]);
                    uchar number=myHelper::GetUChar(data[index+8]);
                    uchar year=myHelper::GetUChar(data[index+9]);
                    uchar month=myHelper::GetUChar(data[index+10]);
                    uchar day=myHelper::GetUChar(data[index+11]);
                    uchar type=myHelper::GetUChar(data[index+12]);
                    emit this->OnReadReceiveData(
                                addr,
                                countNumber,
                                number,
                                year,
                                month,
                                day,
                                type);
                }
                    break;
                }
            }
            index = index + data[index + 3] + 5;
        }
    }
}
