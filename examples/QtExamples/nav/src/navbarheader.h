#ifndef NAVBARHEADER_H
#define NAVBARHEADER_H

#include <QLabel>
#include <QToolButton>
#include <QPushButton>
#include <QResizeEvent>
#include <QPaintEvent>


class NavBarHeader: public QLabel
{
    Q_OBJECT

public:
    explicit NavBarHeader(QWidget *parent = 0, Qt::WindowFlags f = 0);
    explicit NavBarHeader(const QString & text, QWidget *parent = 0, Qt::WindowFlags f = 0);

    QToolButton *button;

signals:
    void buttonClicked(bool checked = false);

protected:
    void resizeEvent(QResizeEvent *e);

private:
    void createButton();
};

class NavBarTitleButton: public QPushButton
{
    Q_OBJECT

public:
    explicit NavBarTitleButton(QWidget *parent = 0);

    QSize sizeHint() const;
    QSize minimumSizeHint() const;

protected:
    void paintEvent(QPaintEvent *e);
};

#endif // NAVBARHEADER_H
