#ifndef USER_SAVE_MONEY_H
#define USER_SAVE_MONEY_H

#include <QDialog>
#include "connect.h"
#include <QAbstractButton>

namespace Ui {
class user_save_money;
}

class user_save_money : public QDialog
{
    Q_OBJECT
    
public:
    explicit user_save_money(QWidget *parent = 0);
    ~user_save_money();
    void save_data();
    
private slots:
    void on_close_music_clicked();
    void read_server();
    void on_yesorno_clicked(QAbstractButton *button);

public:
    Ui::user_save_money *ui;
    QTcpSocket *tcpsocket;
    quint16 blocksize;
    Recv_MSG message;                                   //接收信息
    Send_MSG str;
};

#endif // USER_SAVE_MONEY_H
