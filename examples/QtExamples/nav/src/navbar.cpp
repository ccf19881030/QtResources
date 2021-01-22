#include <QDebug>
#include <QWidget>
#include <QStackedWidget>
#include <QToolBar>
#include <QList>
#include <QAction>
#include <QActionGroup>
#include <QResizeEvent>
#include <QAction>
#include <QList>
#include <QFile>
#include <QTextStream>
#include <QGridLayout>
#include <QSizeGrip>
#include <QWidgetAction>
#include "navbar.h"
#include "navbaroptionsdialog.h"


/**
 * @class NavBar
 * @brief Outlook-like navigation bar.
 *
 * @image html navbar.png
 * The NavBar class provides a stack of pages where only one page is visible at a time,
 * and page list in lower part of widget, which can be fully or partially folded into toolbar at the bottom.
 * @par Example:
 * @code
   NavBar *navBar = new NavBar(this);
   navBar->setStyleSheet(NavBar::loadStyle(":/styles/office2003gray.css"));
   navBar->addPage(new QLabel("Page 1 contents"), "Page 1", QIcon(":/images/mail.png"));
   navBar->addPage(new QLabel("Page 2 contents"), "Page 2", QIcon(":/images/calendar.png"));
   @endcode
 */
/**
 * @fn NavBar::currentChanged
 * This signal is emitted when the current item is changed.
 * @param index Index of selected page
 */
/**
 * @fn NavBar::visibleRowsChanged
 * This signal is emitted when number of visible rows in navigation bar page list changed, e.g. when splitter is moved.
 * @param rows Number of visible rows
 */
/**
 * @fn NavBar::stateChanged
 * This signal is emitted when navigation bar collapsed or expanded.
 * @param collapsed True if collapsed
 */


/**
 * Constructs new NavBar
 * @param parent Parent widget
 * @param f WindowFlags, passed to QFrame constructor
 */
NavBar::NavBar(QWidget *parent, Qt::WindowFlags f):
    QFrame(parent, f)
{
    collapsedState  = false;
    autoPopupMode   = false;
    headerVisible   = true;
    optMenuVisible  = true;
    headerHeight    = 26;
    collapsedWidth  = 33;
    pageIconSize    = QSize(24, 24);
    uniquePageCount = 0;
    proceedCollapse = false;

    setFrameStyle(QFrame::Panel | QFrame::Sunken);

    header = new NavBarHeader(this);
    header->setFrameStyle(QFrame::Panel | QFrame::Raised);
    header->setMinimumHeight(headerHeight);
    stackedWidget = new QStackedWidget(this);
    pageListWidget = new NavBarPageListWidget(this);
    pageToolBar = new NavBarToolBar(this);
    pageToolBar->setMinimumHeight(pageListWidget->rowHeight());

    splitter = new NavBarSplitter(this);
    splitter->setOrientation(Qt::Vertical);
    splitter->addWidget(stackedWidget);
    splitter->addWidget(pageListWidget);
    splitter->setStretchFactor(0, 1);
    splitter->setStretchFactor(1, 0);
    splitter->setCollapsible(0, false);

    resizeContent(size(), rowHeight());

    actionGroup = new QActionGroup(this);
    actionGroup->setExclusive(true);

    pagesMenu = new QMenu(this);
    actionOptions = new QAction(this);
    actionOptions->setText(tr("Options..."));

    contentsPopup = new QFrame(this, Qt::Popup);
    contentsPopup->setObjectName("navBarPopup"); //for stylesheets
    contentsPopup->setFrameStyle(QFrame::Panel | QFrame::Plain);
    contentsPopup->resize(0, 0);
    contentsPopup->setVisible(false);
    QGridLayout *l = new QGridLayout;
    l->setSpacing(0);
    l->setContentsMargins(0, 0, 0, 0);
    l->addWidget(new QSizeGrip(contentsPopup), 2, 0, Qt::AlignRight);
    contentsPopup->setLayout(l);

    pageTitleButton = new NavBarTitleButton(this);
    pageTitleButton->setVisible(false);

    connect(actionGroup,     SIGNAL(triggered(QAction*)),          SLOT(onClickPageButton(QAction*)));
    connect(pageListWidget,  SIGNAL(buttonVisibilityChanged(int)), SLOT(onButtonVisibilityChanged(int)));
    connect(pagesMenu,       SIGNAL(triggered(QAction*)),          SLOT(changePageVisibility(QAction*)));
    connect(pageTitleButton, SIGNAL(clicked()),                    SLOT(showContentsPopup()));
    connect(header,          SIGNAL(buttonClicked(bool)),          SLOT(setCollapsed(bool)));
}

NavBar::~NavBar()
{
}

/**
 * @property NavBar::count
 * Number of pages in navigation bar.
 * @access int count() const
 */
int NavBar::count() const
{
    return stackedWidget->count();
}

/**
 * @property NavBar::currentIndex
 * This property holds the index of the current page.
 * @access int currentIndex() const\n void setCurrentIndex(int)
 * @signals currentChanged(int)
 */
int NavBar::currentIndex() const
{
    return stackedWidget->currentIndex();
}

/**
 * Returns a pointer to the current widget, or 0 if there is no such page.
 * @return Current widget
 */
QWidget *NavBar::currentWidget() const
{
    return stackedWidget->currentWidget();
}

/**
 * Returns the index of widget, or -1 if the page does not exist.
 * @param widget Widget
 * @return Widget's index
 */
int NavBar::indexOf(QWidget *widget) const
{
    return stackedWidget->indexOf(widget);
}

/**
 * @property NavBar::showHeader
 * This property controls visibility of NavBar header.
 * @access bool showHeader() const\n void setShowHeader(bool)
 */
bool NavBar::showHeader() const
{
    return headerVisible;
}

/**
 * @property NavBar::showOptionsMenu
 * This property controls visibility of options menu button in NavBar toolbar.
 * @access bool showOptionsMenu() const\n void setShowOptionsMenu(bool)
 */
bool NavBar::showOptionsMenu() const
{
    return optMenuVisible;
}

/**
 * Toggles visibility of navbar header
 * @param show Show or hide
 */
void NavBar::setShowHeader(bool show)
{
    if(show != headerVisible)
    {
        headerVisible = show;
        header->setVisible(show);
        resizeContent(size(), rowHeight());
    }
}

/**
 * Toggles visibility of options menu button in NavBar toolbar.
 * @param show Show or hide
 */
void NavBar::setShowOptionsMenu(bool show)
{
    if(show != optMenuVisible)
    {
        optMenuVisible = show;
        refillToolBar(visibleRows());
    }
}

/**
 * @property NavBar::rowHeight
 * This property holds height of a row in a page list.
 * @access int rowHeight() const\n void setRowHeight(int)
 */
int NavBar::rowHeight() const
{
    return pageListWidget->rowHeight();
}

/**
 * @property NavBar::collapsed
 * Sets navigation bar collapsed state on/off
 * @access bool isCollaped() const\n void setCollapsed(bool)
 * @signals stateChanged(bool)
 */
bool NavBar::isCollapsed() const
{
    return collapsedState;
}

/**
 * @property NavBar::autoPopup
 * If turned on, navigation bar popup window will appear on page select (when collapsed).
 * @access bool autoPopup() const\n void setAutoPopup(bool)
 */
bool NavBar::autoPopup() const
{
    return autoPopupMode;
}

/**
 * @property NavBar::showCollapseButton
 * Show or hide navigation bar collapse button
 * @access bool showCollapseButton() const\n void setShowCollapseButton(bool)
 */
bool NavBar::showCollapseButton() const
{
    return header->button->isVisible();
}

/**
 * Set height of a row in a page list.
 * @param height Row height
 */
void NavBar::setRowHeight(int height)
{
    if(height < 3)
        height = 3;

    int rows = visibleRows();

    collapsedWidth = height + 1;
    pageListWidget->setRowHeight(height);
    pageToolBar->setMinimumHeight(height);
    splitter->setIncrement(height);

    if(collapsedState)
    {
        resize(collapsedWidth, this->height());
        setMaximumWidth(collapsedWidth);
    }
    else
        resizeContent(size(), height);

    setVisibleRows(rows);
}

/**
 * Toggles navigation bar collapsed state.
 * @param collapse Collapsed/Normal
 */
void NavBar::setCollapsed(bool collapse)
{
    if(collapse == collapsedState)
        return;

    proceedCollapse = true;
    collapsedState = collapse;

    if(collapse)
    {
        for(int i = 0; i < pages.size(); i++)
        {
            pages[i].button->setToolButtonStyle(Qt::ToolButtonIconOnly);
            pages[i].button->setToolTip(pages[i].text());
        }

        moveContentsToPopup(true);

        splitter->insertWidget(0, pageTitleButton);
        pageTitleButton->setVisible(true);
        splitter->setStretchFactor(0, 1);
        splitter->setStretchFactor(1, 0);
        splitter->setCollapsible(0, false);

        expandedWidth = width();
        resize(collapsedWidth, height());
        setMaximumWidth(collapsedWidth);
    }
    else
    {
        contentsPopup->setVisible(false);

        for(int i = 0; i < pages.size(); i++)
        {
            pages[i].button->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
            pages[i].button->setToolTip("");
        }

        setMaximumWidth(QWIDGETSIZE_MAX);
        resize(expandedWidth, height());

        pageTitleButton->setParent(this);
        pageTitleButton->setVisible(false);

        moveContentsToPopup(false);
    }

    header->button->setText(QString::fromUtf8(collapse ? "\xC2\xBB" : "\xC2\xAB"));

    splitter->setVisible(false);
    splitter->setVisible(true);
    resizeContent(size(), rowHeight());
    proceedCollapse = false;

    emit stateChanged(collapse);
}

/**
 * If turned on, navigation bar popup window will appear on page select (when collapsed).
 * @param enable Enable/Disable
 */
void NavBar::setAutoPopup(bool enable)
{
    autoPopupMode = enable;
}

/**
 * Show or hide navigation bar collapse button
 * @param show
 */
void NavBar::setShowCollapseButton(bool show)
{
    header->button->setVisible(show);
}

/**
 * @property NavBar::visibleRows
 * This property holds number of currently visible rows.
 * It's value changed when splitter is moved.
 * @access int visibleRows() const\n void setVisibleRows(int)
 * @signals visibleRowsChanged(int)
 */
int NavBar::visibleRows() const
{
    return pageListWidget->height() / rowHeight();
}

/**
 * Set number of currently visible rows.
 * @param rows Number of rows
 */
void NavBar::setVisibleRows(int rows)
{
    if(rows < 0)
        rows = 0;
    if(rows > visiblePages().size())
        rows = visiblePages().size();

    int listHeight = rows * rowHeight();
    int pageHeight = splitter->height() - listHeight;
    QList<int> sizes;
    sizes.append(pageHeight);
    sizes.append(listHeight);
    splitter->setSizes(sizes);
}

void NavBar::resizeEvent(QResizeEvent *e)
{
    resizeContent(e->size(), rowHeight());
    QFrame::resizeEvent(e);
}

void NavBar::changeEvent(QEvent *e)
{
    if(e->type() == QEvent::StyleChange)
        contentsPopup->setStyleSheet(styleSheet());

    QFrame::changeEvent(e);
}

void NavBar::resizeContent(const QSize &size, int rowheight)
{
    int left, top, right, bottom;
    getContentsMargins(&left, &top, &right, &bottom);

    if(headerVisible && (!collapsedState))
    {
        header->setGeometry(left, top, size.width()-right-left, headerHeight);
        splitter->setGeometry(left, top + headerHeight, size.width()-right-left, size.height()-(rowheight+top+bottom+headerHeight));
    }
    else
        splitter->setGeometry(left, top, size.width()-right-left, size.height()-(rowheight+top+bottom));

    pageToolBar->setGeometry(left, size.height()-(rowheight+bottom), size.width()-left-right, rowheight);
}

void NavBar::reorderStackedWidget()
{
    QList<QWidget *> widgets;
    QWidget *current = stackedWidget->currentWidget();

    for(int i = 0; i < stackedWidget->count(); i++)
        widgets.append(stackedWidget->widget(i));

    for(int i = 0; i < stackedWidget->count(); i++)
        stackedWidget->removeWidget(stackedWidget->widget(0));

    for(int i = 0; i < pages.size(); i++)
        stackedWidget->addWidget(widgets[pages[i].action->data().toInt()]);

    stackedWidget->setCurrentWidget(current);
}

void NavBar::recalcPageList(bool reorder)
{
    if(reorder)
        reorderStackedWidget();

    for(int i = 0; i < pages.size(); i++)
        pages[i].action->setData(i);

    pageListWidget->setMaximumHeight(visiblePages().size() * rowHeight());
    pageListWidget->layoutButtons(pageListWidget->width());
}

/**
 * @property NavBar::smallIconSize
 * This property holds size of icons in the bottom toolbar.
 * @access int smallIconSize() const\n void setSmallIconSize(int)
 */
QSize NavBar::smallIconSize() const
{
    return pageToolBar->iconSize();
}

/**
 * Sets size of icons in the page list.
 * @param size Icon size
 */
void NavBar::setSmallIconSize(const QSize &size)
{
    pageToolBar->setIconSize(size);
    pageToolBar->setMinimumHeight(pageListWidget->rowHeight());
}

/**
 * @property NavBar::largeIconSize
 * This property holds size of icons in the page list.
 * @access int smallIconSize() const\n void setSmallIconSize(int)
 */
QSize NavBar::largeIconSize() const
{
    return pageIconSize;
}

/**
 * Sets size of icons in the bottom toolbar.
 * @param size Icon size
 */
void NavBar::setLargeIconSize(const QSize &size)
{
    pageIconSize = size;

    for(int i = 0; i < pages.size(); i++)
        pages[i].button->setIconSize(size);
}

/**
 * Adds widget as new page to navigation bar
 * @param page Widget to be added as new page
 * @return The new page's index
 */
int NavBar::addPage(QWidget *page)
{
    return addPage(page, "");
}

/**
 * Adds widget as new page to navigation bar
 * @param page Widget to be added as new page
 * @param text Page text
 * @return The new page's index
 */
int NavBar::addPage(QWidget *page, const QString &text)
{
    return addPage(page, text, QIcon());
}

/**
 * Adds widget as new page to navigation bar
 * @param page Widget to be added as new page
 * @param text Page text
 * @param icon Page icon
 * @return The new page's index
 */
int NavBar::addPage(QWidget *page, const QString &text, const QIcon &icon)
{
    return insertPage(-1, page, text, icon);
}

/**
 * Inserts new page at given position, or at the bottom of the navigation bar if index is out of range.
 * @param index Page position
 * @param page Widget
 * @return The new page's index
 */
int NavBar::insertPage(int index, QWidget *page)
{
    return insertPage(index, page, "");
}

/**
 * Inserts new page at given position, or at the bottom of the navigation bar if index is out of range.
 * @param index Page position
 * @param page Widget
 * @param text Page text
 * @return The new page's index
 */
int NavBar::insertPage(int index, QWidget *page, const QString &text)
{
    return insertPage(index, page, text, QIcon());
}

/**
 * Inserts new page at given position, or at the bottom of the navigation bar if index is out of range.
 * @param index Page position
 * @param page Widget
 * @param text Page text
 * @param icon Page icon
 * @return The new page's index
 */
int NavBar::insertPage(int index, QWidget *page, const QString &text, const QIcon &icon)
{
    NavBarPage p;

    p.action = new QAction(this);
    p.action->setObjectName(QString("page-%1").arg(uniquePageCount));
    p.action->setCheckable(true);
    p.action->setText(text);
    p.action->setIcon(icon);

    p.button = new NavBarButton(pageListWidget);
    p.button->setDefaultAction(p.action);
    p.button->setToolButtonStyle(collapsedState ? Qt::ToolButtonIconOnly : Qt::ToolButtonTextBesideIcon);
    p.button->setToolTip("");
    p.button->setAutoRaise(true);
    p.button->setIconSize(pageIconSize);
    p.button->setGeometry(0, visiblePages().size() * rowHeight(), pageListWidget->width(), rowHeight()); //TODO: move to NavBarPageListWidget
    p.button->setVisible(true);

    int oldIdx = stackedWidget->currentIndex();

    int idx;
    if(index < 0) // add page
    {
        p.action->setData(pages.size());
        idx = stackedWidget->addWidget(page);
        pages.append(p);
        pageOrder.append(p.name());
    }
    else // insert page
    {
        idx = stackedWidget->insertWidget(index, page);
        pages.insert(index, p);
        pageOrder.insert(index, p.name());
    }

    uniquePageCount++;

    pages[stackedWidget->currentIndex()].action->setChecked(true);
    actionGroup->addAction(p.action);
    setHeaderText(pages[stackedWidget->currentIndex()].text());
    recalcPageList(false);
    refillToolBar(visibleRows());
    refillPagesMenu();

    int newIdx = stackedWidget->currentIndex();

    if(oldIdx != newIdx)
        emit currentChanged(newIdx);

    return idx;
}

/**
 * Removes widget from the NavBar. i.e., widget is not deleted but simply removed from the navigation bar, causing it to be hidden.
 * @param index Index of widget to be removed
 */
void NavBar::removePage(int index)
{
    if((index < 0) || (index > (pages.size()-1)))
        return;

    int rows = visibleRows();

    stackedWidget->removeWidget(stackedWidget->widget(index));
    actionGroup->removeAction(pages[index].action);
    delete pages[index].button;
    delete pages[index].action;
    pages.removeAt(index);
    pageOrder.removeAt(index);
    recalcPageList(false);

    if(!pages.isEmpty())
    {
        setHeaderText(pages[stackedWidget->currentIndex()].text());
        pages[stackedWidget->currentIndex()].action->setChecked(true);
    }
    else
        setHeaderText("");

    if(rows > visiblePages().size())
        setVisibleRows(visiblePages().size());

    refillToolBar(visibleRows());
    refillPagesMenu();
}

/**
 * Returns the text of the page at given position, or an empty string if index is out of range.
 * @param index Page index
 * @return Page text
 */
QString NavBar::pageText(int index) const
{
    return pages[index].text();
}

/**
 * Returns true if the page at given position is enabled; otherwise returns false.
 * @param index Page index
 * @return Enabled or disabled
 */
bool NavBar::isPageEnabled(int index)
{
    return pages[index].isEnabled();
}

/**
 * If visible is true then the page at given position is visible; otherwise the page at position index is invisible.
 * @param index Page index
 * @param enabled Enable or disable
 */
void NavBar::setPageVisible(int index, bool visible)
{
    int rows = visibleRows();

    pages[index].setVisible(visible);
    recalcPageList(false);
    refillToolBar(visibleRows());

    if(rows > visiblePages().size())
        setVisibleRows(visiblePages().size());
}

/**
 * Returns true if the page at given position is visible; otherwise returns false.
 * @param index Page index
 * @return Visible or not
 */
bool NavBar::isPageVisible(int index)
{
    return pages[index].isVisible();
}

/**
 * If enabled is true then the page at given position is enabled; otherwise the page at position index is disabled.
 * @param index Page index
 * @param enabled Enable or disable
 */
void NavBar::setPageEnabled(int index, bool enabled)
{
    pages[index].setEnabled(enabled);
}

/**
 * Returns the icon of the page at given position, or a null icon if index is out of range.
 * @param index Page index
 * @return Page icon
 */
QIcon NavBar::pageIcon(int index) const
{
    return pages[index].icon();
}

/**
 * Sets the text of the page at given position.
 * @param index Page index
 * @param text New text
 */
void NavBar::setPageText(int index, const QString &text)
{
    pages[index].setText(text);
}

/**
 * Sets the icon of the page at given position.
 * @param index Page index
 * @param icon New icon
 */
void NavBar::setPageIcon(int index, const QIcon &icon)
{
    pages[index].setIcon(icon);
}

/**
 * Returns the widget at given index, or 0 if there is no such widget.
 * @param index Widget index
 * @return Widget
 */
QWidget *NavBar::widget(int index) const
{
    return stackedWidget->widget(index);
}

QSize NavBar::sizeHint() const
{
    return QSize(180, 300);
}

/**
 * Changes active page.
 * @param index Page index
 */
void NavBar::setCurrentIndex(int index)
{
    if((index < 0) || (index > (pages.size()-1)))
        return;

    stackedWidget->setCurrentIndex(index);
    setHeaderText(pages[index].text());
    pages[index].action->setChecked(true);
    emit currentChanged(index);
}

/**
 * Makes widget the current widget. The widget must be an item in this navbar.
 * @param widget Pointer to widget
 */
void NavBar::setCurrentWidget(QWidget *widget)
{
    if(pages.isEmpty())
        return;

    stackedWidget->setCurrentWidget(widget);
    int index = stackedWidget->currentIndex();
    setHeaderText(pages[index].text());
    pages[index].action->setChecked(true);
    emit currentChanged(index);
}

/**
 * Shows navigation bar options dialog, allowing user to change page order and visibility.
 * @return DialogCode result.
 */
int NavBar::showOptionsDialog()
{
    NavBarOptionsDialog optionsDlg(this);
    optionsDlg.setPageList(pages);
    optionsDlg.setDefaultPageOrder(pageOrder);

    int ret = optionsDlg.exec();

    if(ret == QDialog::Accepted)
    {
        pages = optionsDlg.pageList();
        recalcPageList(true);
        refillToolBar(visibleRows());
        refillPagesMenu();
    }

    return ret;
}

void NavBar::onClickPageButton(QAction *action)
{
    int current = stackedWidget->currentIndex();
    int index = action->data().toInt();

    if(index != current)
    {
        stackedWidget->setCurrentIndex(index);
        setHeaderText(action->text());
        emit currentChanged(index);
    }

    if(autoPopupMode && collapsedState)
        showContentsPopup();
}

void NavBar::refillToolBar(int visCount)
{
    pageToolBar->clear();
    QWidget *spacerWidget = new QWidget(this);
    spacerWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    spacerWidget->setVisible(true);
    pageToolBar->addWidget(spacerWidget);

    for(int i = 0; i < visiblePages().size(); i++)
        if(i > visCount-1)
            pageToolBar->addAction(visiblePages()[i].action);

    if(optMenuVisible)
    {
        QToolButton *menuBtn = new QToolButton;
        menuBtn->setMaximumWidth(16);
        menuBtn->setAutoRaise(true);
        menuBtn->setPopupMode(QToolButton::InstantPopup);
        menuBtn->setMenu(pagesMenu);
        pageToolBar->addWidget(menuBtn);
    }
}

void NavBar::refillPagesMenu()
{
    pagesMenu->clear();
    pagesMenu->addAction(actionOptions);
    pagesMenu->addSeparator();

    for(int i = 0; i < pages.size(); i++)
    {
        QAction *changeVis = pagesMenu->addAction(pages[i].text());
        changeVis->setCheckable(true);
        changeVis->setChecked(pages[i].isVisible());
        changeVis->setData(i);
    }
}

void NavBar::moveContentsToPopup(bool popup)
{
    if(popup)
    {
        qobject_cast<QGridLayout *>(contentsPopup->layout())->addWidget(header, 0, 0);
        qobject_cast<QGridLayout *>(contentsPopup->layout())->addWidget(stackedWidget, 1, 0);
    }
    else
    {
        contentsPopup->layout()->removeWidget(stackedWidget);
        contentsPopup->layout()->removeWidget(header);

        splitter->insertWidget(0, stackedWidget);
        stackedWidget->setVisible(true);
        header->setParent(this, Qt::Widget);
        header->setVisible(headerVisible);
    }
}

void NavBar::setHeaderText(const QString &text)
{
    header->setText(text);
    pageTitleButton->setText(text);
}

QList<NavBarPage> NavBar::visiblePages()
{
    QList<NavBarPage> l;

    for(int i = 0; i < pages.size(); i++)
        if(pages[i].isVisible())
            l.append(pages[i]);

    return l;
}

void NavBar::onButtonVisibilityChanged(int visCount)
{
    refillToolBar(visCount);

    if(!proceedCollapse)
        emit visibleRowsChanged(visCount); //TODO: do not emit this, when rowHeight is changed.
}

void NavBar::changePageVisibility(QAction *action)
{
    if(action == actionOptions)
        showOptionsDialog();
    else
        setPageVisible(action->data().toInt(), action->isChecked());
}

void NavBar::showContentsPopup()
{
    if(contentsPopup->size().isEmpty())
        contentsPopup->resize(expandedWidth, height());

    contentsPopup->move(mapToGlobal(QPoint(width(), 0)));
    contentsPopup->show();
}

/**
 * Saves the current state of navigation bar.
 * @param version Version number, which be stored as part of the data
 * @return State data
 */
QByteArray NavBar::saveState(int version) const
{
    QByteArray data;
    QDataStream stream(&data, QIODevice::WriteOnly);

    stream << NavBarMarker;
    stream << version;
    stream << visibleRows();
    stream << currentIndex();
    stream << pages.size();

    foreach(const NavBarPage &page, pages)
    {
        stream << page.name();
        stream << page.isVisible();
    }

    return data;
}

/**
 * Restores the state of navigation bar.
 * @param state State data
 * @param version Version number
 * @return True if successfull
 */
bool NavBar::restoreState(const QByteArray &state, int version)
{
    QByteArray data = state;
    QDataStream stream(&data, QIODevice::ReadOnly);

    int magic, ver, rows, cur, size;

    stream >> magic;
    stream >> ver;

    if((magic != NavBarMarker) || (ver != version))
        return false;

    stream >> rows;
    stream >> cur;
    stream >> size;

    if((rows > pages.size()) || (cur > pages.size()-1) || (size > pages.size()))
        return false;

    QStringList order;
    QList<bool> visibility;

    for(int i = 0; i < size; i++)
    {
        QString name;
        bool visible;

        stream >> name;
        stream >> visible;

        order.append(name);
        visibility.append(visible);
    }

    foreach(const QString &name, order)
    {
        bool found = false;

        for(int i = 0; i < pages.size(); i++)
            if(name == pages[i].name())
                found = true;

        if(!found)
            return false;
    }

    pages = sortNavBarPageList(pages, order);
    for(int i = 0; i < visibility.size(); i++)
        pages[i].setVisible(visibility[i]);

    recalcPageList(true);
    refillToolBar(visibleRows());
    refillPagesMenu();

    setVisibleRows(rows);
    setCurrentIndex(cur);

    return true;
}

QList<NavBarPage> sortNavBarPageList(const QList<NavBarPage> &pages, const QStringList &order)
{
    QList<NavBarPage> sortedPages;

    for(int i = 0; i < order.size(); i++)
    {
        int idx = -1;

        for(int j = 0; j < pages.size(); j++)
        {
            if(order[i] == pages[j].name())
            {
                idx = j;
                break;
            }
        }

        if(idx >= 0)
            sortedPages.append(pages[idx]);
    }

    return sortedPages;
}


/**
 * Helper function, which loads text file and returns it content as QString.
 * There are some style sheets, included in resources under <tt>:/styles/</tt> path:
 *   - office2003gray.css
 *   - office2003blue.css
 *   - office2003green.css
 *   - office2003silver.css
 *   - office2007blue.css
 *   - office2007black.css
 *   - office2007silver.css
 *
 * @par Example:
 * @code
   navBar->setStyleSheet(NavBar::loadStyle(":/styles/office2003gray.css"));
   @endcode
 *
 * @note If you want to use style sheets from navbar resource file, when navbar compiled as static library,
 * you should call <TT>Q_INIT_RESOURCE(navbar)</TT> in your application, see
 * <A HREF="http://qt-project.org/doc/qt-4.8/qdir.html#Q_INIT_RESOURCE">Q_INIT_RESOURCE</A>.
 *
 * @param filename Style sheet file name
 * @return Style sheet
 */
QString NavBar::loadStyle(const QString &filename)
{
    QFile stylefile(filename);
    if(stylefile.open(QFile::ReadOnly))
    {
        QTextStream stream(&stylefile);
        QString stylesheet = stream.readAll();
        return stylesheet;
    }
    else
        return "";
}


NavBarToolBar::NavBarToolBar(QWidget *parent):
    QToolBar(parent)
{
}
