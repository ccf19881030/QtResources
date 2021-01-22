#ifndef WORKER_INIT_H
#define WORKER_INIT_H

#include <QDialog>
#include <QString>
#include <QAbstractButton>
#include <QtNetwork>
#include "ui_init_worker.h"
#include "connect.h"

namespace Ui {
class Dialog;
}

class work_init : public QDialog
{
    Q_OBJECT
public:
    Ui::Dialog Init_ui;
    QTcpSocket *tcpsocket;
    quint16 blocksize;
    Recv_MSG message;                                   //接收信息
public:
    work_init(QWidget * parent = 0)
    {
        blocksize = 0;
        Init_ui.setupUi(this);
    }

private slots:
    void on_yesorno_clicked(QAbstractButton *button);
    void on_close_music_clicked();
    void read_server();
};

#endif // WORKER_INIT_H
