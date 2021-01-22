#ifndef ABOUTPAGE_H
#define ABOUTPAGE_H

#include <QWidget>
#include <QVBoxLayout>

class AboutPage : public QWidget
{
    Q_OBJECT

public:
    AboutPage(QWidget *parent = 0);

private:
    QVBoxLayout *layout;
};

#endif // ABOUTPAGE_H
