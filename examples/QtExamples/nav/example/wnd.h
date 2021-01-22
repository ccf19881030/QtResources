#ifndef WND_H
#define WND_H

#include <QWidget>
#include <QListWidget>
#include <QComboBox>
#include <QCheckBox>
#include <QPushButton>
#include <QCloseEvent>
#include "navbar.h"

class Wnd : public QWidget
{
    Q_OBJECT
    
public:
    Wnd(QWidget *parent = 0);
    ~Wnd();

private slots:
    void addPage();
    void insertPage();
    void removePage();
    void changeStylesheet(int index);
    void navBarCurrentChanged(int index);
    void navBarVisibleRowsChanged(int rows);
    void navBarStateChanged(bool collapsed);

protected:
    void closeEvent(QCloseEvent *e);

    NavBar *navBar;
    QListWidget *signalWidget;
    QComboBox *styleBox;
    QCheckBox *showHeaderBox;
    QCheckBox *showColBtnBox;
    QCheckBox *showOptMenuBox;
    QCheckBox *autoPopupBox;
    QPushButton *addPageButton;
    QPushButton *removePageButton;
    QPushButton *insertPageButton;
};

#endif // WND_H
