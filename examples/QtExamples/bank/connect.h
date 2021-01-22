#ifndef CONNECT_H
#define CONNECT_H

#include <QDialog>
#include <QtNetwork>
#include <QAbstractSocket>
#include <QTcpSocket>
#include <QString>

#define SERV_PORT           6666        //端口号
#define ERROR               99          //错误
#define WORKER_INIT         100         //注册
#define INIT_SUCCESS        101         //注册成功
#define WORKER_LOG          102         //登录
#define LOG_SUCCESS         103         //登录成功
#define LOG_EXIST           104         //已登录
#define EXIT                105         //退出
#define USER_INIT           106         //开户
#define USER_CLOSE          107         //销户
#define CLOSER_SUCCESS      108         //销户成功
#define USER_SAVEMONEY      109         //存款
#define SAVEMONEY_SUCCESS   110         //存款成功
#define USER_GETMONEY       111         //取款
#define GETMONEY_SUCCESS    112         //取款成功
#define OVER_MONEY          113         //余额不足
#define USER_TRANMONEY      114         //转账
#define TRANMONEY_SUCCESS   115         //转账成功
#define NO_TRANPEOPLE       116         //接收方未注册
#define USER_LOOKMONEY      117         //查看余额
#define LOOKMONEY_SUCCESS   118         //查看余额成功
#define USER_CHANGE         119         //修改密码
#define CHANGE_SUCCESS      120         //修改密码成功
#define USER_ACCOUNT_DETAIL 121         //账户明细
#define ACCOUNT_SUCCESS     122         //查看账户明细成功
#define LOOK_RECORD         123         //查看交易记录
#define LOOKRECORD_SUCCESS  124         //查看交易记录成功

const QString IP = "127.0.0.1";

typedef struct Send
{
    int     cmd;                    //命令
    int     work_num;               //职工工号
    QString work_id;                //职工身份证号码
    QString work_name;              //职工姓名
    QString work_passward;          //职工登录密码
    QString user_name;              //用户姓名
    int     user_num;               //用户账号
    QString user_id;                //用户身份证
    QString user_passward;          //用户密码
    QString first_money;            //开户金额（存取款）
    QString recv_people;            //转账接收方
    QString new_passward;           //修改后的新密码
    QString record;                 //交易记录
}Send_MSG;

typedef struct Recv
{
    int     cmd;                    //命令
    int     work_num;               //职工工号
    QString work_id;                //职工身份证号码
    QString work_name;              //职工姓名
    QString work_passward;          //职工登录密码
    QString user_name;              //用户姓名
    int     user_num;               //用户账号
    QString money;                  //余额
    QString recv_people;            //转账接收方
    QString record;                 //交易记录
}Recv_MSG;


inline QDataStream& operator<<(QDataStream& out, Send_MSG &send_msg)
{
    out<<send_msg.cmd;
    out<<send_msg.work_num;
    out<<send_msg.work_id;
    out<<send_msg.work_name;
    out<<send_msg.work_passward;
    out<<send_msg.first_money;
    out<<send_msg.user_id;
    out<<send_msg.user_name;
    out<<send_msg.user_num;
    out<<send_msg.user_passward;
    out<<send_msg.recv_people;
    out<<send_msg.new_passward;
    out<<send_msg.record;
    return out;
}

inline QDataStream& operator>>(QDataStream& in, Send_MSG &send_msg)
{
    in>>send_msg.cmd;
    in>>send_msg.work_num;
    in>>send_msg.work_id;
    in>>send_msg.work_name;
    in>>send_msg.work_passward;
    in>>send_msg.first_money;
    in>>send_msg.user_id;
    in>>send_msg.user_name;
    in>>send_msg.user_num;
    in>>send_msg.user_passward;
    in>>send_msg.recv_people;
    in>>send_msg.new_passward;
    in>>send_msg.record;
    return in;
}

inline QDataStream& operator <<(QDataStream& out, Recv_MSG &recv_msg)
{
    out<<recv_msg.cmd;
    out<<recv_msg.work_num;
    out<<recv_msg.work_id;
    out<<recv_msg.work_name;
    out<<recv_msg.work_passward;
    out<<recv_msg.money;
    out<<recv_msg.user_name;
    out<<recv_msg.user_num;
    out<<recv_msg.recv_people;
    out<<recv_msg.record;
    return out;
}

inline QDataStream& operator>>(QDataStream& in, Recv_MSG &recv_msg)
{
    in>>recv_msg.cmd;
    in>>recv_msg.work_num;
    in>>recv_msg.work_id;
    in>>recv_msg.work_name;
    in>>recv_msg.work_passward;
    in>>recv_msg.money;
    in>>recv_msg.user_name;
    in>>recv_msg.user_num;
    in>>recv_msg.recv_people;
    in>>recv_msg.record;
    return in;
}

#endif // CONNECT_H
