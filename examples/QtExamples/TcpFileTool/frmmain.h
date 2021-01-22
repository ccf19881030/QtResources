#ifndef FRMMAIN_H
#define FRMMAIN_H

#include <QDialog>
#include "api/sendfileclient.h"
#include "api/receivefileserver.h"

namespace Ui
{
class frmMain;
}

class frmMain : public QDialog
{
    Q_OBJECT

public:
    explicit frmMain(QWidget *parent = 0);
    ~frmMain();

protected:
    bool eventFilter(QObject *obj, QEvent *event);

private:
    Ui::frmMain *ui;
    bool max;           //是否处于最大化状态
    QRect location;     //鼠标移动窗体后的坐标位置

    int sendBytes;
    qint64 sendBlockNumber;
    qint64 sendMaxBytes;

    int receiveBytes;
    qint64 receiveBlockNumber;
    qint64 receiveMaxBytes;

    ReceiveFileServer *receive;

private slots:
    void InitStyle();   //初始化无边框窗体
    void ChangeStyle(); //改变样式
    void InitForm();    //初始化窗体数据
    void InitConfig();  //加载配置文件
    void SaveConfig();  //保存配置文件

private slots:
    void on_btnMenu_Max_clicked();
    void on_btnSend_clicked();
    void on_btnSelect_clicked();
    void on_btnListen_clicked();

    void updateSendPBar(qint64 size);
    void updateSendStatus(QString msg);
    void setSendPBar(qint64 size);
    void sendFinsh();

    void updateReceivePBar(qint64 size);
    void updateReceiveStatus(QString msg);
    void setReceivePBar(qint64 size);
    void receiveFinsh();
    void receiveFileName(QString name);

};

#endif // FRMMAIN_H
