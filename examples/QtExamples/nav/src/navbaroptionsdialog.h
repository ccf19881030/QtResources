#ifndef NAVBAROPTIONSDLG_H
#define NAVBAROPTIONSDLG_H

#include "navbarpage.h"
#include "ui_navbaroptionsdialog.h"

class NavBarOptionsDialog : public QDialog, private Ui::NavBarOptionsDialog
{
    Q_OBJECT

public:
    explicit NavBarOptionsDialog(QWidget *parent = 0);

    void setPageList(const QList<NavBarPage> &plist);
    QList<NavBarPage> pageList();

    void setDefaultPageOrder(const QStringList &order);

private slots:
    void movePageUp();
    void movePageDown();
    void resetPages();
    void onCurrentRowChanged(int row);

private:
    void fillListWidget();

    QList<NavBarPage> pages;
    QStringList       pageOrder;
};

#endif // NAVBAROPTIONSDLG_H
