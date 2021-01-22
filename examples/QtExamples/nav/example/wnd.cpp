#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QLabel>
#include <QInputDialog>
#include <QSettings>
#include "wnd.h"

Wnd::Wnd(QWidget *parent)
    : QWidget(parent)
{
    //Creating NavBar

    navBar = new NavBar;
    navBar->setStyleSheet(NavBar::loadStyle(":/styles/office2003gray.css"));

    navBar->addPage(new QLabel("This is page 1"), "Page 1", QIcon(":/images/mail_yellow.png"));
    navBar->addPage(new QLabel("This is page 2"), "Page 2", QIcon(":/images/calendar.png"));
    navBar->addPage(new QLabel("This is page 3"), "Page 3", QIcon(":/images/client_account_template.png"));
    navBar->addPage(new QLabel("This is page 4"), "Page 4", QIcon(":/images/date_task.png"));
    navBar->addPage(new QLabel("This is page 5"), "Page 5", QIcon(":/images/note.png"));

    navBar->setVisibleRows(3);

    connect(navBar, SIGNAL(currentChanged(int)),     SLOT(navBarCurrentChanged(int)));
    connect(navBar, SIGNAL(visibleRowsChanged(int)), SLOT(navBarVisibleRowsChanged(int)));
    connect(navBar, SIGNAL(stateChanged(bool)),      SLOT(navBarStateChanged(bool)));

    //Creating other stuff

    addPageButton = new QPushButton;
    addPageButton->setText("Add page");
    addPageButton->setIcon(QIcon(":/images/page_white_add.png"));
    connect(addPageButton, SIGNAL(clicked()), SLOT(addPage()));

    insertPageButton = new QPushButton;
    insertPageButton->setText("Insert page");
    insertPageButton->setIcon(QIcon(":/images/page_white_put.png"));
    connect(insertPageButton, SIGNAL(clicked()), SLOT(insertPage()));

    removePageButton = new QPushButton;
    removePageButton->setText("Remove page");
    removePageButton->setIcon(QIcon(":/images/page_white_delete.png"));
    connect(removePageButton, SIGNAL(clicked()), SLOT(removePage()));

    showHeaderBox = new QCheckBox;
    showHeaderBox->setText("Show header");
    showHeaderBox->setChecked(true);
    connect(showHeaderBox, SIGNAL(toggled(bool)), navBar, SLOT(setShowHeader(bool)));

    showColBtnBox = new QCheckBox;
    showColBtnBox->setText("Show collapse button");
    showColBtnBox->setChecked(true);
    connect(showColBtnBox, SIGNAL(toggled(bool)), navBar, SLOT(setShowCollapseButton(bool)));

    showOptMenuBox = new QCheckBox;
    showOptMenuBox->setText("Show options menu button");
    showOptMenuBox->setChecked(true);
    connect(showOptMenuBox, SIGNAL(toggled(bool)), navBar, SLOT(setShowOptionsMenu(bool)));

    autoPopupBox = new QCheckBox;
    autoPopupBox->setText("Auto popup in collapsed mode");
    autoPopupBox->setChecked(false);
    connect(autoPopupBox, SIGNAL(toggled(bool)), navBar, SLOT(setAutoPopup(bool)));

    styleBox = new QComboBox;
    styleBox->addItem("Office 2003 Gray",   ":/styles/office2003gray.css");
    styleBox->addItem("Office 2003 Blue",   ":/styles/office2003blue.css");
    styleBox->addItem("Office 2003 Silver", ":/styles/office2003silver.css");
    styleBox->addItem("Office 2003 Green",  ":/styles/office2003green.css");
    styleBox->addItem("Office 2007 Blue",   ":/styles/office2007blue.css");
    styleBox->addItem("Office 2007 Black",  ":/styles/office2007black.css");
    styleBox->addItem("Office 2007 Silver", ":/styles/office2007silver.css");
    styleBox->addItem("None",               "");
    connect(styleBox, SIGNAL(currentIndexChanged(int)), SLOT(changeStylesheet(int)));

    signalWidget = new QListWidget;

    //Laying out widgets

    QVBoxLayout *vLayout = new QVBoxLayout;
    QHBoxLayout *hLayout = new QHBoxLayout;
    QHBoxLayout *bLayout = new QHBoxLayout;
    QGridLayout *cLayout = new QGridLayout;
    bLayout->addWidget(addPageButton);
    bLayout->addWidget(insertPageButton);
    bLayout->addWidget(removePageButton);
    vLayout->addLayout(bLayout);
    vLayout->addWidget(styleBox);
    cLayout->addWidget(showHeaderBox,  0, 0);
    cLayout->addWidget(showColBtnBox,  1, 0);
    cLayout->addWidget(showOptMenuBox, 0, 1);
    cLayout->addWidget(autoPopupBox,   1, 1);
    vLayout->addLayout(cLayout);
    vLayout->addWidget(signalWidget);
    hLayout->addWidget(navBar);
    hLayout->addLayout(vLayout);
    setLayout(hLayout);

    //Restoring NavBar state

    QSettings settings("Mitrich Software", "NavBar example");
    if(!navBar->restoreState(settings.value("navBarState").toByteArray()))
        qDebug("Cannot restore state. Saved pages doesn't match pages, present in navigation bar.");
}

Wnd::~Wnd()
{    
}

void Wnd::addPage()
{
    bool ok;
    QString text = QInputDialog::getText(this, "Add new page",
                                         "Page text:", QLineEdit::Normal,
                                         "New Page", &ok);
    if (ok && !text.isEmpty())
        navBar->addPage(new QLabel(QString("This is %1").arg(text)), text, QIcon(":/images/page_white.png"));
}

void Wnd::insertPage()
{
    bool ok;
    QString text = QInputDialog::getText(this, "Insert new page",
                                         "Page text:", QLineEdit::Normal,
                                         "New Page", &ok);
    if (ok && !text.isEmpty())
        navBar->insertPage(navBar->currentIndex(), new QLabel(QString("This is %1").arg(text)), text, QIcon(":/images/page_white.png"));
}

void Wnd::removePage()
{
    navBar->removePage(navBar->currentIndex());
}

void Wnd::changeStylesheet(int index)
{
    navBar->setStyleSheet(NavBar::loadStyle(styleBox->itemData(index).toString()));
}

void Wnd::navBarCurrentChanged(int index)
{
    signalWidget->addItem(QString("currentChanged(%1)").arg(index));
    signalWidget->scrollToBottom();
}

void Wnd::navBarVisibleRowsChanged(int rows)
{
    signalWidget->addItem(QString("visibleRowsChanged(%1)").arg(rows));
    signalWidget->scrollToBottom();
}

void Wnd::navBarStateChanged(bool collapsed)
{
    signalWidget->addItem(QString("stateChanged(%1)").arg(collapsed));
    signalWidget->scrollToBottom();
}

void Wnd::closeEvent(QCloseEvent *e)
{
    //Saving NavBar state

    QSettings settings("Mitrich Software", "NavBar example");
    settings.setValue("navBarState", navBar->saveState());

    QWidget::closeEvent(e);
}
