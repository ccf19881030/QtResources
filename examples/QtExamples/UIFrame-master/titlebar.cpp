#include "titlebar.h"
#include <QPainter>

TitleBar::TitleBar(QWidget *parent)
    : QWidget(parent)
{
    layout = new QHBoxLayout(this);
    optionButton = new QPushButton;
    minimizeButton = new QPushButton;
    closeButton = new QPushButton;

    bgColor = "#1EA19D";

    optionButton->setObjectName("OptionButton");
    optionButton->setFocusPolicy(Qt::NoFocus);
    optionButton->setFixedSize(27, 23);
    optionButton->setCursor(Qt::PointingHandCursor);

    minimizeButton->setObjectName("MinimizeButton");
    minimizeButton->setFocusPolicy(Qt::NoFocus);
    minimizeButton->setFixedSize(27, 23);
    minimizeButton->setCursor(Qt::PointingHandCursor);

    closeButton->setObjectName("CloseButton");
    closeButton->setFocusPolicy(Qt::NoFocus);
    closeButton->setFixedSize(27, 23);
    closeButton->setCursor(Qt::PointingHandCursor);

    layout->addStretch();
    layout->addWidget(optionButton);
    layout->addWidget(minimizeButton);
    layout->addWidget(closeButton);
    layout->addSpacing(5);

    layout->setSpacing(0);
    layout->setContentsMargins(0, 0, 0, 0);

    setFixedHeight(36);

    connect(minimizeButton, &QPushButton::clicked, this, &TitleBar::MinimizeButtonClicked);
    connect(closeButton, &QPushButton::clicked, this, &TitleBar::CloseButtonClicked);
}

void TitleBar::setBackgroundColor(const QString &color)
{
    bgColor = color;

    update();
}

void TitleBar::paintEvent(QPaintEvent *e)
{
    Q_UNUSED(e)

    QPainter painter(this);
    painter.setPen(Qt::NoPen);
    painter.setBrush(QColor(bgColor));

    painter.drawRect(rect());
}
