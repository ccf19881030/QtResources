#ifndef BACKUPDATANASEDIALOG_H
#define BACKUPDATANASEDIALOG_H

#include <QDialog>

namespace Ui {
class BackupDatanaseDialog;
}

class BackupDatanaseDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit BackupDatanaseDialog(QWidget *parent = 0);
    ~BackupDatanaseDialog();

    void InitForm();
    
private slots:

    void on_pbnOk_clicked();

    void on_pbnSearch_clicked();

    void on_lineEdit_textChanged(const QString &arg1);

private:
    Ui::BackupDatanaseDialog *ui;
};

#endif // BACKUPDATANASEDIALOG_H
