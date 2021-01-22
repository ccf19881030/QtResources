/*
 *      文件名: cvalidatedialog.h
 *
 *      功能: 验证码显示窗口。和接收用户输入的验证码内容
 *
 *      作者: wu5151
 *      博客地址: http://blog.csdn.net/wu5151
 */


#ifndef CVALIDATEDIALOG_H
#define CVALIDATEDIALOG_H

#include <QDialog>
#include <QString>

namespace Ui {
class CValidateDialog;
}

class CValidateDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit CValidateDialog(QWidget *parent = 0);
    ~CValidateDialog();

    // 设置显示的验证码内容
    void setPixmap(QPixmap pixmap);
    // 获取用户输入的验证码
    QString getValidateCode();

private slots:
    void on_pushButton_clicked();

private:
    Ui::CValidateDialog *ui;

    QString m_ValidateCode;
};

#endif // CVALIDATEDIALOG_H
