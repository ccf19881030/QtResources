#ifndef USER_CLOSE_H
#define USER_CLOSE_H

#include <QDialog>
#include "connect.h"
#include <QAbstractButton>

namespace Ui {
class user_close;
}

class user_close : public QDialog
{
    Q_OBJECT
    
public:
    explicit user_close(QWidget *parent = 0);
    ~user_close();
    void save_close();
    
private slots:
    void on_close_music_clicked();
    void read_server();
    void on_yesorno_clicked(QAbstractButton *button);

public:
    Ui::user_close *ui;
    QTcpSocket *tcpsocket;
    quint16 blocksize;
    Recv_MSG message;                                   //接收信息
};

#endif // USER_CLOSE_H
