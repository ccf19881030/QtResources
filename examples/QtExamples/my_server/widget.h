#ifndef WIDGET_H
#define WIDGET_H
#include "mytcpserver.h"
#include <QWidget>
namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();
private slots:
    void on_pushButton_clicked();
    void updataData(QByteArray byte);
    void on_pushButton_2_clicked();
signals:
    void sendData(QByteArray byte);
private:
    mytcpserver *tcpserver;
    Ui::Widget *ui;
};

#endif // WIDGET_H
