#ifndef WORKER_LOG_H
#define WORKER_LOG_H

#include <QDialog>
#include <QString>
#include <QAbstractButton>
#include "ui_logging.h"
#include "connect.h"
#include "deal_user.h"

namespace Ui {
class Form;
}

class work_log : public QDialog
{
    Q_OBJECT
public:
    Ui::Form work_ui;
    QTcpSocket *tcpsocket;
    quint16 blocksize;
    Recv_MSG message;
public:
    work_log(QWidget * parent = 0)
    {
        blocksize = 0;
        work_ui.setupUi(this);
    }
private slots:
    void on_Yesorno_clicked(QAbstractButton *button);
    void on_close_music_clicked();
    void read_server();
};

#endif // WORKER_LOG_H
