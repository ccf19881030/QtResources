#ifndef DEAL_USER_H
#define DEAL_USER_H

#include <QDialog>
#include <QtNetwork>
#include "connect.h"
//#include <QSound>

namespace Ui {
class deal_user;
}

class deal_user : public QDialog
{
    Q_OBJECT
    
public:
    explicit deal_user(QWidget *parent = 0);
    ~deal_user();
    QTcpSocket *tcpsocket;
    quint16 blocksize;
    Recv_MSG message;
    //QSound *sound;

private slots:
    void on_close_music_clicked();

    void on_Exit_clicked();

    void on_init_user_clicked();

    void on_close_account_clicked();

    void on_bank_save_clicked();

    void on_get_money_clicked();

    void on_tran_accounts_clicked();

    void on_look_money_clicked();

    void on_change_passward_clicked();

    void on_account_detail_clicked();

    void on_tran_record_clicked();

public:
    Ui::deal_user *ui;
};

#endif // DEAL_USER_H
