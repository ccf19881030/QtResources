#ifndef MYPHOTOVIEW_H
#define MYPHOTOVIEW_H

#ifndef PYNUM_H
#define PYNUM_H

#define PYN_HOLD_DURATION 1000
#define PYN_TIMER_INTERVAL 20
#define PYN_OPACITY_INCREMENT 0.05
#define PYN_FIN_OPACITY 0.6
#define PYN_WIDTH_FACTOR 2.5

#define PYN_MAX_HEIGHT 30
#define PYN_RECT_RADIUS 6

#define PYN_BG_START_COLOR QColor(46,132,243)
#define PYN_BG_END_COLOR QColor(39,110,203)

#define PYN_TEXT_COLOR Qt::white

#define PYP_TOP_SPACE 20
#define PYP_LEFT_SPACE 15
#define PYP_BUTTON_WIDTH 70
#define PYP_BUTTON_SIZE QSize(PYP_BUTTON_WIDTH,PYP_BUTTON_WIDTH)

#define PYP_BG_START_COLOR QColor(89,89,89)
#define PYP_BG_END_COLOR   QColor(56,56,56)
#define PYP_IMAGE_SUFFIX   QStringList() << "*.png" << "*.jpg" << "*.gif" << "*.jpeg" << "*.bmp"

#define PYP_IMAGE_MOTION_PATTERN_FADE
#ifdef PYP_IMAGE_MOTION_PATTERN_FADE
#define PYP_IMAGE_FADE_TIMER_INTERVAL 40
#define PYP_IMAGE_OPACITY_INCREMENT 0.05
#endif



#include <QtWidgets>
#include <QtGui>

class PYNum : public QWidget
{
    Q_OBJECT
public:
    PYNum(QWidget* parent = 0);

public slots:
    void setTotal(int totalNum);

    void setValue(int value);


protected:
    void paintEvent(QPaintEvent *);

    void showEvent(QShowEvent *);

    QSize sizeHint() const
    {
        return QSize(100,PYN_MAX_HEIGHT);
    }

private:
    void drawBg(QPainter* painter);

    void drawText(QPainter* painter);


private:
    int m_nTotal,m_nValue;

    QTimer* m_fadeTimer;
    QTimer* m_holdTimer;
    QTimer* m_hideTimer;

    qreal m_opacity;

private slots:
    void DoFading();
    void DoHiding();
};

#endif // PYNUM_H

class myPhotoView : public QWidget
{
    Q_OBJECT
public:
    explicit myPhotoView(QWidget *parent = 0);

public slots:
    void load(const QString& strFolder);

    void showNext();

    void showPrevious();

protected:
    virtual void paintEvent(QPaintEvent *);


    QSize sizeHint() const
    {
        return QSize(400,400);
    }

    virtual void showEvent(QShowEvent *);

    virtual void resizeEvent(QResizeEvent *);
private:
    void drawBg(QPainter* painter);

    void drawImage(QPainter* painter);


private:
    void initVariables();
    void calcGeo();


private:
    QString m_strFolder;

    int m_nTotal;
    int m_nCurrIndex;

    QToolButton* prevButton;
    QToolButton* nextButton;

    QVector<QImage*> m_ImageVec;
    QImage* m_currImage;

    PYNum* num;

#ifdef PYP_IMAGE_MOTION_PATTERN_FADE
    qreal m_imageOpacity;
    QTimer* m_imageFadeTimer;
#endif

private slots:

#ifdef PYP_IMAGE_FADE_TIMER_INTERVAL
    void DoImageFading();
#endif


signals:
    void sig_setValue(int value);
    void sig_setTotal(int total);

};

#endif // MYPHOTOVIEW_H
