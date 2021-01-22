#include "dict_page.h"

DictPage::DictPage(QWidget *parent)
    : QWidget(parent),
      api(new YoudaoAPI(this))
{
    layout = new QVBoxLayout(this);
    pronLayout = new QHBoxLayout();

    nameLabel = new QLabel("");
    pronLabel1 = new QLabel("");
    pronLabel2 = new QLabel("");
    infoLabel = new QPlainTextEdit();    

    infoLabel->setReadOnly(true);
    nameLabel->setWordWrap(true);

    nameLabel->setStyleSheet("font-size: 22px; color:#2CA7F8;");
    pronLabel1->setStyleSheet("font-size: 13px");
    pronLabel2->setStyleSheet("font-size: 13px");
    infoLabel->setStyleSheet("font-size: 17px");

    pronLayout->addSpacing(30);
    pronLayout->addWidget(pronLabel1);
    pronLayout->addWidget(pronLabel2);
    pronLayout->addSpacing(30);

    QHBoxLayout *wordLayout = new QHBoxLayout();
    QHBoxLayout *infoLayout = new QHBoxLayout();

    wordLayout->addSpacing(30);
    wordLayout->addWidget(nameLabel);
    wordLayout->addSpacing(30);

    infoLayout->addSpacing(30);
    infoLayout->addWidget(infoLabel);
    infoLayout->addSpacing(30);

    layout->addSpacing(20);
    layout->addLayout(wordLayout);
    layout->addLayout(pronLayout);
    layout->addSpacing(10);
    layout->addLayout(infoLayout);
    layout->addStretch();

    connect(api, SIGNAL(searchWordFinished(QString, QString, QString, QString)), this, SLOT(processingData(QString, QString, QString, QString)));

    pronLabel1->setVisible(false);
    pronLabel2->setVisible(false);
}

void DictPage::start(const QString &word)
{
    if (!word.isEmpty()) {
        api->searchWord(word);
    }
}

void DictPage::processingData(QString name, QString uk_phonetic, QString us_phonetic, QString text)
{
    if (uk_phonetic.isEmpty() && us_phonetic.isEmpty()) {
        pronLabel1->setVisible(false);
        pronLabel2->setVisible(false);
    }else {
        pronLabel1->setVisible(true);
        pronLabel2->setVisible(true);

        pronLabel1->setText(QString("英[%1]").arg(uk_phonetic));
        pronLabel2->setText(QString("美[%1]").arg(us_phonetic));
    }

    nameLabel->setText(name);
    infoLabel->setPlainText(text);
}
