#include <QStylePainter>
#include <QStyleOptionButton>
#include <QFontMetrics>
#include "navbarheader.h"


/**
 * @class NavBarHeader
 * @brief Navigation bar header.
 *
 * Navigation bar header.
 */
/**
 * @fn NavBarHeader::buttonClicked
 * Emitted when header button is clicked.
 * @param checked Button check state (false by default)
 */
/**
 * @var NavBarHeader::button
 * Header button.
 */

/**
 * Constructs new NavBarHeader
 * @param parent Parent widget, passed to QLabel constructor
 * @param f WindowFlags, passed to QLabel constructor
 */
NavBarHeader::NavBarHeader(QWidget *parent, Qt::WindowFlags f):
    QLabel(parent, f)
{
    createButton();
}

/**
 * Constructs new NavBarHeader
 * @param text Header text
 * @param parent Parent widget, passed to QLabel constructor
 * @param f WindowFlags, passed to QLabel constructor
 */
NavBarHeader::NavBarHeader(const QString &text, QWidget *parent, Qt::WindowFlags f):
    QLabel(text, parent, f)
{
    createButton();
}

void NavBarHeader::resizeEvent(QResizeEvent *e)
{
    button->setGeometry(width()-23, 3, 20, 20);
    QLabel::resizeEvent(e);
}

void NavBarHeader::createButton()
{
    button = new QToolButton(this);
    button->setCheckable(true);
    button->setAutoRaise(true);
    button->setText(QString::fromUtf8("\xC2\xAB"));
    connect(button, SIGNAL(clicked(bool)), SIGNAL(buttonClicked(bool)));
}


NavBarTitleButton::NavBarTitleButton(QWidget *parent):
    QPushButton(parent)
{

}

QSize NavBarTitleButton::sizeHint() const
{
    return QSize(-1, -1);
}

QSize NavBarTitleButton::minimumSizeHint() const
{
    return QSize(-1, -1);
}

void NavBarTitleButton::paintEvent(QPaintEvent *e)
{
    Q_UNUSED(e);

    QStylePainter p(this);
    QStyleOptionButton opt;
    initStyleOption(&opt);

    p.drawControl(QStyle::CE_PushButtonBevel, opt);

    p.setFont(font());
    QFontMetrics fm(font());
    p.translate(width()/2 + fm.ascent()/2, height()/2 + fm.width(text())/2);
    p.rotate(270);
    p.drawText(0, 0, text());
}
