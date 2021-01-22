#ifndef USER_TRANRECORD_H
#define USER_TRANRECORD_H

#include <QDialog>
#include "connect.h"
#include <QAbstractButton>

namespace Ui {
class user_tranRecord;
}

class user_tranRecord : public QDialog
{
    Q_OBJECT
    
public:
    explicit user_tranRecord(QWidget *parent = 0);
    ~user_tranRecord();
    
private slots:
    void on_close_music_clicked();
    void read_server();
    void on_Yesorno_clicked(QAbstractButton *button);

public:
    Ui::user_tranRecord *ui;
    QTcpSocket *tcpsocket;
    quint16 blocksize;
    Recv_MSG message;                                   //接收信息
    Send_MSG str;
};

#endif // USER_TRANRECORD_H
