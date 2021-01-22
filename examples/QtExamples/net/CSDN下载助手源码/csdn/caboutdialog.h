/*
 *      文件名: caboutdialog.h
 *
 *      功能: 关于助手   界面
 *
 *      作者: wu5151
 *      博客地址: http://blog.csdn.net/wu5151
 */

#ifndef CABOUTDIALOG_H
#define CABOUTDIALOG_H

#include <QDialog>

namespace Ui {
class CAboutDialog;
}

class CAboutDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit CAboutDialog(QWidget *parent = 0);
    ~CAboutDialog();
    
private slots:
    void on_pBtnAboutQt_clicked();

    void on_pBtnAuthor_clicked();

private:
    Ui::CAboutDialog *ui;
};

#endif // CABOUTDIALOG_H
