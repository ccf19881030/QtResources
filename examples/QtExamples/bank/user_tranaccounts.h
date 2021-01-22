#ifndef USER_TRANACCOUNTS_H
#define USER_TRANACCOUNTS_H

#include <QDialog>
#include "connect.h"
#include <QAbstractButton>

namespace Ui {
class user_tranaccounts;
}

class user_tranaccounts : public QDialog
{
    Q_OBJECT
    
public:
    explicit user_tranaccounts(QWidget *parent = 0);
    ~user_tranaccounts();
    void save_data();
    
private slots:
    void on_close_music_clicked();
    void read_server();
    void on_yesorno_clicked(QAbstractButton *button);

private:
    Ui::user_tranaccounts *ui;
    QTcpSocket *tcpsocket;
    quint16 blocksize;
    Recv_MSG message;                                   //接收信息
    Send_MSG str;
};

#endif // USER_TRANACCOUNTS_H
