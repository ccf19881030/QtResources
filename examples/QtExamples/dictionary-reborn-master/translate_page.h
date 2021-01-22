#ifndef TRANSLATEPAGE_H
#define TRANSLATEPAGE_H

#include <QWidget>
#include <QVBoxLayout>
#include <QPlainTextEdit>
#include <QKeyEvent>

#include "youdao_api.h"

class TranslatePage : public QWidget
{
    Q_OBJECT

public:
    TranslatePage(QWidget *parent = 0);

    QPlainTextEdit *original;

private:
    YoudaoAPI *api;
    QVBoxLayout *layout;
    QHBoxLayout *hLayout;
    QPlainTextEdit *translator;


protected:
    void keyPressEvent(QKeyEvent *);

private slots:
    void translateButtonClicked();
    void clearButtonClicked();
    void processingData(QString);
};

#endif // TRANSLATEPAGE_H
