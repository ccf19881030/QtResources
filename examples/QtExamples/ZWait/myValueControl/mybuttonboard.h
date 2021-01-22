#ifndef MYBUTTONBOARD_H
#define MYBUTTONBOARD_H

#define DECLARE_PRIVATE(CLASS) class CLASS##Private;

#ifdef PYBB_BUTTON_NORMAL_START_COLOR
#undef PYBB_BUTTON_NORMAL_START_COLOR
#endif
#define PYBB_BUTTON_NORMAL_START_COLOR QColor(245,245,245)

#ifdef PYBB_BUTTON_NORMAL_END_COLOR
#undef PYBB_BUTTON_NORMAL_END_COLOR
#endif
#define PYBB_BUTTON_NORMAL_END_COLOR QColor(221,221,221)

#ifdef PYBB_BUTTON_HIGHLIGHT_START_COLOR
#undef PYBB_BUTTON_HIGHLIGHT_START_COLOR
#endif
#define PYBB_BUTTON_HIGHLIGHT_START_COLOR PYBB_BUTTON_HIGHLIGHT_END_COLOR.lighter()

#ifdef PYBB_BUTTON_HIGHLIGHT_END_COLOR
#undef PYBB_BUTTON_HIGHLIGHT_END_COLOR
#endif
#define PYBB_BUTTON_HIGHLIGHT_END_COLOR QColor(98,138,21)

#ifdef PYBB_SPACE
#undef PYBB_SPACE
#endif
#define PYBB_SPACE 5

#ifdef PYBB_BUTTON_WIDTH
#undef PYBB_BUTTON_WIDTH
#endif
#define PYBB_BUTTON_WIDTH 30

#ifdef PYBB_BUTTON_START_COLOR
#undef PYBB_BUTTON_START_COLOR
#endif
#define PYBB_BUTTON_START_COLOR PYBB_BUTTON_END_COLOR.lighter()

#ifdef PYBB_BUTTON_END_COLOR
#undef PYBB_BUTTON_END_COLOR
#endif
#define PYBB_BUTTON_END_COLOR QColor(221,221,221)

#ifdef PYBB_BG_START_COLOR
#undef PYBB_BG_START_COLOR
#endif
#define PYBB_BG_START_COLOR QColor(212,212,212)

#ifdef PYBB_BG_END_COLOR
#undef PYBB_BG_END_COLOR
#endif
#define PYBB_BG_END_COLOR QColor(198,198,198)

/// BUTTON Macro

#ifdef PYBB_BUTTON_RECT_RADIUS
#undef PYBB_BUTTON_RECT_RADIUS
#endif
#define PYBB_BUTTON_RECT_RADIUS 5

#ifdef PYBB_BUTTON_HOVER_OPACITY
#undef PYBB_BUTTON_HOVER_OPACITY
#endif
#define PYBB_BUTTON_HOVER_OPACITY 0.6

#ifdef PYBB_SELECT_BUTTON_START_COLOR
#undef PYBB_SELECT_BUTTON_START_COLOR
#endif
#define PYBB_SELECT_BUTTON_START_COLOR PYBB_BUTTON_END_COLOR.lighter()

#ifdef PYBB_SELECT_BUTTON_END_COLOR
#undef PYBB_SELECT_BUTTON_END_COLOR
#endif
#define PYBB_SELECT_BUTTON_END_COLOR QColor(76,199,255)

#ifdef PYBB_BUTTON_TEXT_ALIGNMENT
#undef PYBB_BUTTON_TEXT_ALIGNMENT
#endif
#define PYBB_BUTTON_TEXT_ALIGNMENT Qt::AlignVCenter|Qt::AlignHCenter

#ifdef PYBB_HOVER_TEXT_COLOR
#undef PYBB_HOVER_TEXT_COLOR
#endif
#define PYBB_HOVER_TEXT_COLOR Qt::black

#ifdef PYBB_SELECT_TEXT_COLOR
#undef PYBB_SELECT_TEXT_COLOR
#endif
#define PYBB_SELECT_TEXT_COLOR Qt::white

#ifdef PYBB_NORMAL_TEXT_COLOR
#undef PYBB_NORMAL_TEXT_COLOR
#endif
#define PYBB_NORMAL_TEXT_COLOR Qt::black

#ifdef PYBB_EXTRA_SPACE
#undef PYBB_EXTRA_SPACE
#endif
#define PYBB_EXTRA_SPACE 7

#ifdef PYBB_BUTTON_HEIGHT
#undef PYBB_BUTTON_HEIGHT
#endif
#define PYBB_BUTTON_HEIGHT 25

#include <QWidget>
#include <QMouseEvent>
#include <QPainter>
#include <QPaintEvent>
#include <QVBoxLayout>
#include <QScrollArea>

class PYButtonBoardPrivate : public QWidget
{
Q_OBJECT
public:
    PYButtonBoardPrivate(QWidget* parent = 0);
    ~PYButtonBoardPrivate();

public:
    /// public interfaces
    void addButton(const QString& str);

    void setButtons(const QStringList& strList);


protected:
    virtual void paintEvent(QPaintEvent *);

    QSize sizeHint() const
    {
        return QSize(500,200);
    }

    virtual void mouseMoveEvent(QMouseEvent *);

    virtual void mousePressEvent(QMouseEvent *);

    virtual void leaveEvent(QEvent *);
private:
    /// painting functions
    void drawBg(QPainter* painter);

    void drawButtons(QPainter* painter);

    void drawHoverAndSelectButton(QPainter* painter);
private:
    QStringList m_ButtonList;
    QVector<QPair<QRectF,QString> > m_RectTextPairVec;

    qreal m_MaxButtonLength;
    qreal m_ButtonWidth;

    QRectF m_HoverRect;
    QRectF m_SelectRect;


    QString m_strHoverText;
    QString m_strSelectText;

Q_SIGNALS:
    void sig_ButtonClicked(const QString& str);
};


class myButtonBoard : public QWidget
{
    Q_OBJECT
public:
    explicit myButtonBoard(QWidget *parent = 0);

signals:
    void sig_ButtonClicked(const QString& str);

public:
    void addButton(const QString& str);
    void setButtons(const QStringList& strList);

protected:
    QSize sizeHint() const
    {
        return QSize(500,200);
    }

private:
    PYButtonBoardPrivate* d;
    QScrollArea* dContainer;
    QVBoxLayout* mainLayout;

private:
    void createWidgets();
    void initSettings();
    void initMessages();

};

#endif // MYBUTTONBOARD_H
