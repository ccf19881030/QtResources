#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

namespace Ui {
class Widget;
}
class tcpsocket;
class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

private slots:
    void on_pushButton_clicked();
    void readData();
    void on_pushButton_2_clicked();

private:
    tcpsocket *socket;
    Ui::Widget *ui;
};

#endif // WIDGET_H
