#ifndef FRMNAVLISTVIEW_H
#define FRMNAVLISTVIEW_H

#include <QWidget>
#include <QModelIndex>

namespace Ui {
class frmNavListView;
}

class frmNavListView : public QWidget
{
    Q_OBJECT

public:
    explicit frmNavListView(QWidget *parent = 0);
    ~frmNavListView();

private slots:
    void initForm();

private:
    Ui::frmNavListView *ui;
};

#endif // FRMNAVLISTVIEW_H
