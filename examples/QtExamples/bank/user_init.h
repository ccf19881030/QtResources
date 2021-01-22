#ifndef USER_INIT_H
#define USER_INIT_H

#include <QDialog>
#include "connect.h"
#include <QAbstractButton>

namespace Ui {
class user_init;
}

class user_init : public QDialog
{
    Q_OBJECT
    
public:
    explicit user_init(QWidget *parent = 0);
    ~user_init();
    void SaveUserInit();
    
private slots:
    void on_close_music_clicked();
    void on_yesorno_clicked(QAbstractButton *button);
    void read_server();

public:
    Ui::user_init *ui;
    QTcpSocket *tcpsocket;
    quint16 blocksize;
    Recv_MSG message;                                   //接收信息
};

#endif // USER_INIT_H
