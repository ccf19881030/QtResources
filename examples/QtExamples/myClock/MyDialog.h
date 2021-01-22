#ifndef MYDIALOG_H
#define MYDIALOG_H
#include <QDialog>
#include <QCloseEvent>

class MyDialog : public QDialog
{
public:
    MyDialog(QWidget * parent=0);
private:
    void closeEvent(QCloseEvent *);
};

#endif // MYDIALOG_H
