#include "MyDialog.h"
#include <QDebug>

MyDialog::MyDialog(QWidget * parent):
    QDialog(parent)
{

}

void MyDialog::closeEvent(QCloseEvent *e)
{
    //qDebug()<<"----"<<e->type();
    e->ignore();
    this->hide();
}
