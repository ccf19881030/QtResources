#ifndef USER_CHANGEPASSWARD_H
#define USER_CHANGEPASSWARD_H

#include <QDialog>
#include "connect.h"
#include <QAbstractButton>

namespace Ui {
class user_changepassward;
}

class user_changepassward : public QDialog
{
    Q_OBJECT
    
public:
    explicit user_changepassward(QWidget *parent = 0);
    ~user_changepassward();
    
private slots:
    void on_close_music_clicked();
    void read_server();
    void on_yesorno_clicked(QAbstractButton *button);

public:
    Ui::user_changepassward *ui;
    QTcpSocket *tcpsocket;
    quint16 blocksize;
    Recv_MSG message;                                   //接收信息
    Send_MSG str;
};

#endif // USER_CHANGEPASSWARD_H
