#ifndef MYMAICHONGAPI_H
#define MYMAICHONGAPI_H

#define head 0x16 //帧头
#define fromAddress 0x01 //原地址

#include "win_qextserialport.h"
#include <QObject>

/*脉冲主机出厂维修操作类
 *作者：刘典武
 *时间：2013-9-24
 */
class myMaiChongAPI : public QObject
{
    Q_OBJECT
public:
    explicit myMaiChongAPI(QString portName);

    //串口是否通信成功
    bool IsOpen()const{return isOpen;}

    //打开与关闭串口
    bool Open();
    void Close();

    //设置出厂记录
    void SetChuChang(uchar addr,uchar year,uchar month,uchar day);

    //设置维修记录
    void SetWeiXiu(uchar addr,uchar year,uchar month,uchar day);

    //获取出厂记录和维修记录
    void GetChuChangOrWeiXiu(uchar addr,uchar number);

    //擦除出厂记录
    void ClearData(uchar addr);

private:
    Win_QextSerialPort *myCOMMaiChong;
    QString portName;
    bool isOpen;

    void WriteData(uchar toAddress,uchar length,uchar id);
    void WriteData(uchar toAddress, uchar length,uchar id,uchar parameter[],uchar size);

private slots:
    void ReadData();
    
signals:
    //写记录应答
    void OnWriteReceiveData(uchar addr,uchar countNumber);

    //读记录应答
    void OnReadReceiveData(uchar addr,
                           uchar countNumber,
                           uchar number,
                           uchar year,
                           uchar month,
                           uchar day,
                           uchar type);
    
public slots:
    
};

#endif // MYMAICHONGAPI_H
