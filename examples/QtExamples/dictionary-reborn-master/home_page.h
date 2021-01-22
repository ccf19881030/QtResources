#ifndef HOMEPAGE_H
#define HOMEPAGE_H

#include <QWidget>
#include <QVBoxLayout>
#include <QStackedLayout>
#include <QLineEdit>
#include "everyday_page.h"
#include "dict_page.h"

class HomePage : public QWidget
{
    Q_OBJECT

public:
    HomePage(QWidget *parent = 0);

private:
    QVBoxLayout *layout;
    QHBoxLayout *topLayout;
    QStackedLayout *switchLayout;

    QLineEdit *queryEditor;

    EverydayPage *everydayPage;
    DictPage *dictPage;

private slots:
    void queryWord();
};

#endif // HOMEPAGE_H
