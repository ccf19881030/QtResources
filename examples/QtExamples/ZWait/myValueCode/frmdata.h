#ifndef FRMDATA_H
#define FRMDATA_H

#include <QWidget>
#include "mydatahelper.h"

namespace Ui {
    class frmData;
}

class frmData : public QWidget
{
    Q_OBJECT

public:
    explicit frmData(QWidget *parent = 0);
    ~frmData();

private:
    Ui::frmData *ui;
    myDataHelper *myData;

private slots:
    void on_btn4_clicked();
    void on_btnOpen_clicked();
    void on_btn3_clicked();
    void on_btn2_clicked();
    void on_btn1_clicked();

    void ChangeEnable(bool b);
};

#endif // FRMDATA_H
