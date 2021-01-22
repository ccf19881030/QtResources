#ifndef TICKER_H
#define TICKER_H

#include <QMainWindow>
#include <QPainter>

namespace Ui {
class Ticker;
}

class Ticker : public QMainWindow
{
    Q_OBJECT
    Q_PROPERTY(QString text READ text WRITE setText)

public:
    explicit Ticker(QWidget *parent = 0);
    ~Ticker();

    void setText(const QString &newText);
    QString text() const { return myText; }
    QSize sizeHint() const;

protected:
    void paintEvent(QPaintEvent *event);
    void timerEvent(QTimerEvent *event);
    void showEvent(QShowEvent *event);
    void hideEvent(QHideEvent *event);

private:
    Ui::Ticker *ui;
    QString myText;
    int offset;
    int myTimerId;
};

#endif // TICKER_H
