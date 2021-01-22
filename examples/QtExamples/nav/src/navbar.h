#ifndef NAVBAR_H
#define NAVBAR_H

#include <QStackedWidget>
#include <QToolBar>
#include <QList>
#include <QActionGroup>
#include <QMenu>
#include <QByteArray>
#include "navbarpage.h"
#include "navbarheader.h"
#include "navbarsplitter.h"
#include "navbarpagelistwidget.h"


class NavBarToolBar: public QToolBar
{
    Q_OBJECT

public:
    explicit NavBarToolBar(QWidget *parent = 0);
};

class NavBar : public QFrame
{
    Q_OBJECT
    Q_PROPERTY(int   count              READ count)
    Q_PROPERTY(int   currentIndex       READ currentIndex       WRITE setCurrentIndex NOTIFY currentChanged)
    Q_PROPERTY(int   rowHeight          READ rowHeight          WRITE setRowHeight)
    Q_PROPERTY(bool  collapsed          READ isCollapsed        WRITE setCollapsed    NOTIFY stateChanged)
    Q_PROPERTY(bool  autoPopup          READ autoPopup          WRITE setAutoPopup)
    Q_PROPERTY(bool  showCollapseButton READ showCollapseButton WRITE setShowCollapseButton)
    Q_PROPERTY(bool  showHeader         READ showHeader         WRITE setShowHeader)
    Q_PROPERTY(bool  showOptionsMenu    READ showOptionsMenu    WRITE setShowOptionsMenu)
    Q_PROPERTY(int   visibleRows        READ visibleRows        WRITE setVisibleRows  NOTIFY visibleRowsChanged)
    Q_PROPERTY(QSize smallIconSize      READ smallIconSize      WRITE setSmallIconSize)
    Q_PROPERTY(QSize largeIconSize      READ largeIconSize      WRITE setLargeIconSize)

public:
    enum { NavBarMarker = 0x4e426172 };

    explicit NavBar(QWidget *parent = 0, Qt::WindowFlags f = 0);
    ~NavBar();

    int      addPage(QWidget *page);
    int      addPage(QWidget *page, const QString &text);
    int      addPage(QWidget *page, const QString &text, const QIcon &icon);
    int      insertPage(int index, QWidget *page);
    int      insertPage(int index, QWidget *page, const QString &text);
    int      insertPage(int index, QWidget *page, const QString &text, const QIcon &icon);

    void     removePage(int index);

    void     setPageText(int index, const QString &text);
    QString  pageText(int index) const;

    void     setPageIcon(int index, const QIcon &icon);
    QIcon    pageIcon(int index) const;

    void     setPageEnabled(int index, bool enabled);
    bool     isPageEnabled(int index);

    void     setPageVisible(int index, bool visible);
    bool     isPageVisible(int index);

    int      currentIndex() const;
    QWidget *currentWidget() const;
    QWidget *widget(int index) const;
    int      indexOf(QWidget *widget) const;
    int      count() const;

    void     setSmallIconSize(const QSize &size);
    QSize    smallIconSize() const;

    void     setLargeIconSize(const QSize &size);
    QSize    largeIconSize() const;

    int      rowHeight() const;
    bool     isCollapsed() const;
    bool     autoPopup() const;
    bool     showCollapseButton() const;
    bool     showHeader() const;
    bool     showOptionsMenu() const;
    int      visibleRows() const;

    QByteArray saveState(int version = 0) const;
    bool       restoreState(const QByteArray & state, int version = 0);

    QSize    sizeHint() const;

    static QString loadStyle(const QString &filename);

signals:
    void currentChanged(int index);
    void visibleRowsChanged(int rows);
    void stateChanged(bool collapsed);

public slots:
    void setCurrentIndex(int index);
    void setCurrentWidget(QWidget *widget);
    void setRowHeight(int height);
    void setCollapsed(bool collapse);
    void setAutoPopup(bool enable);
    void setShowCollapseButton(bool show);
    void setShowHeader(bool show);
    void setShowOptionsMenu(bool show);
    void setVisibleRows(int rows);
    int  showOptionsDialog();

protected:
    void resizeEvent(QResizeEvent *e);
    void changeEvent(QEvent *e);

private slots:
    void onClickPageButton(QAction *action);
    void onButtonVisibilityChanged(int visCount);
    void changePageVisibility(QAction *action);
    void showContentsPopup();

private:
    void resizeContent(const QSize &size, int rowheight);
    void reorderStackedWidget();
    void recalcPageList(bool reorder);
    void refillToolBar(int visCount);
    void refillPagesMenu();
    void moveContentsToPopup(bool popup);
    void setHeaderText(const QString &text);

    QList<NavBarPage> visiblePages();

    NavBarHeader         *header;
    QStackedWidget       *stackedWidget;
    NavBarSplitter       *splitter;
    NavBarPageListWidget *pageListWidget;
    NavBarToolBar        *pageToolBar;
    QActionGroup         *actionGroup;
    QMenu                *pagesMenu;
    QFrame               *contentsPopup;
    NavBarTitleButton    *pageTitleButton;
    QAction              *actionOptions;
    QList<NavBarPage>     pages;
    QStringList           pageOrder;

    bool  collapsedState;
    bool  autoPopupMode;
    int   expandedWidth;
    bool  optMenuVisible;
    bool  headerVisible;
    int   headerHeight;
    int   collapsedWidth;
    QSize pageIconSize;
    int   uniquePageCount;
    bool  proceedCollapse;

    friend class NavBarPageListWidget;
};

#endif // NAVBAR_H
