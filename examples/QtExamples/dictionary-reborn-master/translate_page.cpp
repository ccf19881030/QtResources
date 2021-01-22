#include "translate_page.h"
#include <QLabel>
#include <QPushButton>

TranslatePage::TranslatePage(QWidget *parent)
    : QWidget(parent),
      api(new YoudaoAPI(this))
{
    layout = new QVBoxLayout(this);
    hLayout = new QHBoxLayout;
    original = new QPlainTextEdit;
    translator = new QPlainTextEdit;

    QLabel *tips1 = new QLabel("原文");
    QLabel *tips2 = new QLabel("译文");

    tips1->setObjectName("TrLabel");
    tips2->setObjectName("TrLabel");
    original->setObjectName("TranslateEdit1");
    translator->setObjectName("TranslateEdit2");

    QPushButton *clearBtn = new QPushButton("清空");
    QPushButton *trBtn = new QPushButton("翻译");
    clearBtn->setFixedHeight(35);
    trBtn->setFixedHeight(35);
    hLayout->addWidget(clearBtn);
    hLayout->addWidget(trBtn);
    trBtn->setFixedHeight(35);
    trBtn->setObjectName("Button");


    translator->setReadOnly(true);

    layout->setMargin(25);
    layout->addWidget(tips1);
    layout->addWidget(original);
    layout->addSpacing(10);
    layout->addLayout(hLayout);
    layout->addSpacing(10);
    layout->addWidget(tips2);
    layout->addWidget(translator);

    connect(trBtn, SIGNAL(clicked()), this, SLOT(translateButtonClicked()));
    connect(clearBtn, SIGNAL(clicked()), this, SLOT(clearButtonClicked()));
    connect(api, SIGNAL(translatorFinished(QString)), this, SLOT(processingData(QString)));
}

void TranslatePage::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Return && (event->modifiers() & Qt::ControlModifier))
            translateButtonClicked();
}

void TranslatePage::translateButtonClicked()
{
    original->setFocus();

    if (!original->toPlainText().isEmpty()) {
        api->translator(original->toPlainText());
    }else {

    }
}

void TranslatePage::clearButtonClicked()
{
    original->setFocus();
    original->setPlainText("");
    translator->setPlainText("");
}

void TranslatePage::processingData(QString text)
{
    translator->setPlainText(text);
}
