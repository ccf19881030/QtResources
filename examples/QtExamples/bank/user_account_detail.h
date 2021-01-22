#ifndef USER_ACCOUNT_DETAIL_H
#define USER_ACCOUNT_DETAIL_H

#include <QDialog>
#include "connect.h"
#include <QAbstractButton>

namespace Ui {
class user_account_detail;
}

class user_account_detail : public QDialog
{
    Q_OBJECT
    
public:
    explicit user_account_detail(QWidget *parent = 0);
    ~user_account_detail();
    
private slots:
    void on_close_music_clicked();
    void read_server();
    void on_yesorno_clicked(QAbstractButton *button);

public:
    Ui::user_account_detail *ui;
    QTcpSocket *tcpsocket;
    quint16 blocksize;
    Recv_MSG message;                                   //接收信息
    Send_MSG str;
};

#endif // USER_ACCOUNT_DETAIL_H
