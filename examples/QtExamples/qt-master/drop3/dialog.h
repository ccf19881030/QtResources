#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QListWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>

namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = 0);
    ~Dialog();

public slots:
    void AToB_clicked();
    void BToA_clicked();

private:
    void moveCurrentItem(QListWidget *source,
                         QListWidget *target);

private:
    Ui::Dialog *ui;
private:
    QListWidget *listA;
    QListWidget *listB;
    QPushButton *buttonAToB;
    QPushButton *buttonBToA;
};

#endif // DIALOG_H
