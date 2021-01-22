#ifndef FRMMESSAGEBOX_H
#define FRMMESSAGEBOX_H

#include <QDialog>

namespace Ui
{
    class frmMessageBox;
}

class frmMessageBox : public QDialog
{
    Q_OBJECT

public:
    explicit frmMessageBox(QWidget *parent = 0);
    ~frmMessageBox();

    void SetMessage(QString msg, int type);

private slots:
    void on_btnOk_clicked();

private:
    Ui::frmMessageBox *ui;

private:
    void InitStyle();

};

#endif // FRMMESSAGEBOX_H
