#include <QDebug>
#include "navbaroptionsdialog.h"

NavBarOptionsDialog::NavBarOptionsDialog(QWidget *parent) :
    QDialog(parent)
{
    setupUi(this);

    connect(upButton,    SIGNAL(clicked()),  SLOT(movePageUp()));
    connect(downButton,  SIGNAL(clicked()),  SLOT(movePageDown()));
    connect(resetButton, SIGNAL(clicked()),  SLOT(resetPages()));
    connect(buttonBox,   SIGNAL(accepted()), SLOT(accept()));
    connect(buttonBox,   SIGNAL(rejected()), SLOT(reject()));

    connect(pageListWidget, SIGNAL(currentRowChanged(int)), SLOT(onCurrentRowChanged(int)));
}

void NavBarOptionsDialog::setPageList(const QList<NavBarPage> &plist)
{
    pages = plist;
    fillListWidget();
}

QList<NavBarPage> NavBarOptionsDialog::pageList()
{
    for(int i = 0; i < pages.size(); i++)
        pages[i].setVisible(pageListWidget->item(i)->checkState() == Qt::Checked);

    return pages;
}

void NavBarOptionsDialog::setDefaultPageOrder(const QStringList &order)
{
    pageOrder = order;
    resetButton->setEnabled(true);
}

void NavBarOptionsDialog::fillListWidget()
{
    pageListWidget->clear();

    for(int i = 0; i < pages.size(); i++)
    {
        QListWidgetItem *item = new QListWidgetItem(pages[i].text());
        item->setCheckState(pages[i].isVisible() ? Qt::Checked : Qt::Unchecked);
        pageListWidget->addItem(item);
    }
}

void NavBarOptionsDialog::movePageUp()
{
    int row = pageListWidget->currentRow();

    if(row > 0)
    {
        pages.swap(row, row-1);
        fillListWidget();
        pageListWidget->setCurrentRow(row-1);
    }
}

void NavBarOptionsDialog::movePageDown()
{
    int row = pageListWidget->currentRow();

    if(row < pages.size()-1)
    {
        pages.swap(row, row+1);
        fillListWidget();
        pageListWidget->setCurrentRow(row+1);
    }
}

void NavBarOptionsDialog::resetPages()
{
    pages = sortNavBarPageList(pages, pageOrder);
    fillListWidget();
}

void NavBarOptionsDialog::onCurrentRowChanged(int row)
{
    if(row < 0)
    {
        upButton->setEnabled(false);
        downButton->setEnabled(false);
        return;
    }

    if(row == 0)
        upButton->setEnabled(false);
    else
        upButton->setEnabled(true);

    if(row == pages.size()-1)
        downButton->setEnabled(false);
    else
        downButton->setEnabled(true);
}
