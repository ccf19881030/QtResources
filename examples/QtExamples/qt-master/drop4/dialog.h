#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include "projectlistwidget.h"

namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = 0);
    ~Dialog();

private:
    Ui::Dialog *ui;
private:
    QListWidget *listA;
    QListWidget *listB;
    QPushButton *buttonAToB;
    QPushButton *buttonBToA;
};

#endif // DIALOG_H
