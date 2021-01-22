#ifndef WIDGET_H
#define WIDGET_H

#include <QDialog>
//#include <QSound>

namespace Ui {
class Widget;
}

class Widget : public QDialog
{
    Q_OBJECT
    
public:
    explicit Widget(QDialog *parent = 0);
    ~Widget();
    //QSound *sound;

public slots:
    void on_Exit_clicked();
    void on_log_worker_clicked();
    void on_init_worker_clicked();

private:
    Ui::Widget *ui;    
};

#endif // WIDGET_H
