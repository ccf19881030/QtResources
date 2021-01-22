#ifndef ICONEDITOR_H
#define ICONEDITOR_H

#include <QWidget>
#include <QPainter>
#include <QImage>
#include <QPaintEvent>
#include <QRegion>
#include <QMouseEvent>

namespace Ui {
class IconEditor;
}

class IconEditor : public QWidget
{
    Q_OBJECT
    //使用Q_PROPERTY声明三个自定义属性，而每个属性均有一个数据类型QColor，一个读函数penColor和一个写函数setpenColor
    Q_PROPERTY(QColor penColor READ penColor WRITE setpenColor)
    Q_PROPERTY(QImage iconImage READ iconImage WRITE seticonImage)
    Q_PROPERTY(int zoomFactor READ zoomFactor WRITE setzoomFactor)

public:
    explicit IconEditor(QWidget *parent = 0);
    ~IconEditor();

    void setpenColor(const QColor &newColor);
    QColor penColor() const { return curColor; }
    void setzoomFactor(int newZoom);
    int zoomFactor() const { return zoom; }
    void seticonImage(const QImage &newImage);
    QImage iconImage() const { return image; }
    QSize sizeHint() const;

protected:
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void paintEvent(QPaintEvent *event);
private:
    void setImagePixel(const QPoint &pos, bool opaque);
    QRect pixelRect(int i, int j) const;

    Ui::IconEditor *ui;
    //三个私有变量保存着属性的值
    QColor curColor;
    QImage image;
    int zoom;
};

#endif // ICONEDITOR_H
