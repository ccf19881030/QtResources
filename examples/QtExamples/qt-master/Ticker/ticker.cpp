#include "ticker.h"
#include "ui_ticker.h"

Ticker::Ticker(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Ticker)
{
    ui->setupUi(this);
    offset = 0;
    myTimerId = 0;
}

Ticker::~Ticker()
{
    delete ui;
}

void Ticker::setText(const QString &newText)
{
    myText = newText;
    //强制执行一个重绘操作
    update();
    //通知对Ticker窗口部件负责的任意布局管理器，提示该窗口部件的大小发生了变化
    updateGeometry();
}

QSize Ticker::sizeHint() const
{
    //返回窗口所需的空间大小
    return fontMetrics().size(0, text());
}

void Ticker::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);

    int textWidth = fontMetrics().width(text());
    if (textWidth < 1) return;

    int x = -offset;
    while (x < width()) {
        painter.drawText(x, 0, textWidth, height(),
                         Qt::AlignLeft | Qt::AlignVCenter, text());
        x += textWidth;
    }
}

void Ticker::showEvent(QShowEvent *event)
{
    //每30ms产生一个定时器事件
    myTimerId = startTimer(30);
}

void Ticker::timerEvent(QTimerEvent *event)
{
    //通过offset的增加来实现窗口的滚动
    if (event->timerId() == myTimerId) {
        ++offset;
        if (offset >= fontMetrics().width(text())) offset = 0;
        scroll(-1, 0);
    } else {
        QWidget::timerEvent(event);
    }
}

void Ticker::hideEvent(QHideEvent *event)
{
    killTimer(myTimerId);
    myTimerId = 0;
}
