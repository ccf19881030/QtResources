#ifndef MAINDIALOG_H
#define MAINDIALOG_H

#include "qicmp.h"
#include <QDialog>
#include <QTime>
#include <QStandardItemModel>
#include <QHostInfo>
#include "ui_detail.h"
namespace Ui {
class MainDialog;
}

class MainDialog : public QDialog
{
    Q_OBJECT

public:
    explicit MainDialog(QWidget *parent = 0);
    ~MainDialog();
    void initSpinBox();
    void initView();
    QString getLocalhost();
    QVector<int> splitIpAddr(QString ipAddr);
    QString constructIpAddr(QVector<int>ipSplits);
    QStringList getIpRange();
private slots:
    void on_pushButton_clicked();
    void updateView(int timeout,QString destIp,QString status);
    void on_pushButton_2_clicked();
    void on_pushButton_3_clicked();
    void on_spinBox_4_valueChanged(int arg1);
    void on_pushButton_4_clicked();
    void updateTime();
    void threadFinished();
    void printResults(QModelIndex);
    void on_pushButton_5_clicked();
    void showDetails(QHostInfo info);

private:
    Ui::MainDialog       *ui;
    QStandardItemModel   *model;
    QTimer               *timer;
    QList<QIcmp*>        threadList;
    bool                 isStop;
    QModelIndex          modelIndex;
    Ui_Dialog            ui_dialog;
    int                  secs;
};

#endif // MAINDIALOG_H
