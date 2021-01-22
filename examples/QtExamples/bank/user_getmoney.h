#ifndef USER_GETMONEY_H
#define USER_GETMONEY_H

#include <QDialog>
#include "connect.h"
#include <QAbstractButton>

namespace Ui {
class user_getmoney;
}

class user_getmoney : public QDialog
{
    Q_OBJECT
    
public:
    explicit user_getmoney(QWidget *parent = 0);
    ~user_getmoney();
    void save_data();
    
private slots:
    void on_close_music_clicked();
    void read_server();
    void on_yesorno_clicked(QAbstractButton *button);

public:
    Ui::user_getmoney *ui;
    QTcpSocket *tcpsocket;
    quint16 blocksize;
    Recv_MSG message;                                   //接收信息
    Send_MSG str;
};

#endif // USER_GETMONEY_H
