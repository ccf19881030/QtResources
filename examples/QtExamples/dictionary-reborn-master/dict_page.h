#ifndef DICTPAGE_H
#define DICTPAGE_H

#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QPlainTextEdit>
#include "youdao_api.h"

class DictPage : public QWidget
{
    Q_OBJECT

public:
    DictPage(QWidget *parent = 0);

    void queryWord(const QString &word);
    void changeTheme(const QString &theme);

    QVBoxLayout *layout;
    QHBoxLayout *pronLayout;

    QLabel *nameLabel;
    QLabel *pronLabel1;
    QLabel *pronLabel2;
    QPlainTextEdit *infoLabel;

    void start(const QString &word);

private:
    YoudaoAPI *api;

private slots:
    void processingData(QString, QString, QString, QString);
};

#endif // DICTPAGE_H
