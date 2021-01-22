#ifndef USER_LOOKMONEY_H
#define USER_LOOKMONEY_H

#include <QDialog>
#include "connect.h"
#include <QAbstractButton>

namespace Ui {
class user_lookmoney;
}

class user_lookmoney : public QDialog
{
    Q_OBJECT
    
public:
    explicit user_lookmoney(QWidget *parent = 0);
    ~user_lookmoney();
    
private slots:
    void on_close_music_clicked();
    void read_server();
    void on_yesorno_clicked(QAbstractButton *button);

public:
    Ui::user_lookmoney *ui;
    QTcpSocket *tcpsocket;
    quint16 blocksize;
    Recv_MSG message;                                   //接收信息
    Send_MSG str;
};

#endif // USER_LOOKMONEY_H
