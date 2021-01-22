#ifndef FRMMAIN_H
#define FRMMAIN_H

#include <QWidget>
#include "mymaichongapi.h"

namespace Ui {
class frmMain;
}

class frmMain : public QWidget
{
    Q_OBJECT
    
public:
    explicit frmMain(QWidget *parent = 0);
    ~frmMain();

protected:
    void closeEvent(QCloseEvent *);
    
private slots:
    void on_btnOpen_clicked();

    //写记录应答
    void OnWriteReceive(uchar addr,uchar countNumber);

    //读记录应答
    void OnReadReceive(uchar addr,
                           uchar countNumber,
                           uchar number,
                           uchar year,
                           uchar month,
                           uchar day,
                           uchar type);

    void on_btnClear_clicked();

    void on_btnRead_clicked();

    void on_btnWriteChuChang_clicked();

    void on_btnWriteWeiXiu_clicked();

    void on_btnClearData_clicked();

    void on_btnClearChuChang_clicked();

    void on_btnClearWeiXiu_clicked();

private:
    Ui::frmMain *ui;
    myMaiChongAPI *MaiChong;    

    void InitForm();    
};

#endif // FRMMAIN_H
