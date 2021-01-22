#ifndef FRMMAIN_H
#define FRMMAIN_H

#include <QWidget>
#include <QtGui>


namespace Ui {
    class frmMain;
}

class frmMain : public QWidget
{
    Q_OBJECT

public:
    explicit frmMain(QWidget *parent = 0);
    ~frmMain();

private:
    Ui::frmMain *ui;   

private slots:
    void on_btn36_clicked();
    void on_btn35_clicked();
    void on_btn34_clicked();
    void on_btn33_clicked();
    void on_btn32_clicked();
    void on_btn31_clicked();
    void on_btn24_clicked();
    void on_btn23_clicked();
    void on_btn22_clicked();
    void on_btn21_clicked();
    void on_btn8_clicked();
    void on_btn7_clicked();
    void on_btn6_clicked();
    void on_btn5_clicked();
    void on_btn4_clicked();
    void on_btn3_clicked();
    void on_btn2_clicked();
    void on_btn1_clicked();    
};

#endif // FRMMAIN_H
