#ifndef FRMNAVLISTVIEWFORM_H
#define FRMNAVLISTVIEWFORM_H

#include <QWidget>

namespace Ui {
class frmNavListViewForm;
}

class frmNavListViewForm : public QWidget
{
    Q_OBJECT

public:
    explicit frmNavListViewForm(QWidget *parent = 0);
    ~frmNavListViewForm();

private slots:
    void initForm();
    void on_listView_pressed();

private:
    Ui::frmNavListViewForm *ui;
};

#endif // FRMNAVLISTVIEWFORM_H
