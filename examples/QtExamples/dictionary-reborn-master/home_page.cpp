#include "home_page.h"

HomePage::HomePage(QWidget *parent)
    : QWidget(parent)
{
    layout = new QVBoxLayout(this);
    topLayout = new QHBoxLayout();
    switchLayout = new QStackedLayout();
    queryEditor = new QLineEdit();
    everydayPage = new EverydayPage();
    dictPage = new DictPage();

    queryEditor->setFixedHeight(35);

    switchLayout->addWidget(everydayPage);
    switchLayout->addWidget(dictPage);

    topLayout->addSpacing(20);
    topLayout->addWidget(queryEditor);
    topLayout->addSpacing(20);

    layout->addSpacing(5);
    layout->addLayout(topLayout);
    layout->addLayout(switchLayout);

    connect(queryEditor, &QLineEdit::textChanged, this, &HomePage::queryWord);
    connect(queryEditor, &QLineEdit::returnPressed, this, &HomePage::queryWord);
}

void HomePage::queryWord()
{
    queryEditor->setFocus();

    if (queryEditor->text().isEmpty()) {
        switchLayout->setCurrentIndex(0);

        return;
    }

    dictPage->start(queryEditor->text());
    switchLayout->setCurrentIndex(1);
}
