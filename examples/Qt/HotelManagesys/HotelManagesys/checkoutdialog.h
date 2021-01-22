#ifndef CHECKOUTDIALOG_H
#define CHECKOUTDIALOG_H

#include <QDialog>

namespace Ui {
class CheckOutDialog;
}

class CheckOutDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit CheckOutDialog(QWidget *parent = 0);
    ~CheckOutDialog();
    
private:
    Ui::CheckOutDialog *ui;
};

#endif // CHECKOUTDIALOG_H
