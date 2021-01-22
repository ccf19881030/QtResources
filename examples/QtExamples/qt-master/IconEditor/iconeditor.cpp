#include "iconeditor.h"
#include "ui_iconeditor.h"

IconEditor::IconEditor(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::IconEditor)
{
    ui->setupUi(this);
    //保留原窗口内容，防止重绘
    setAttribute(Qt::WA_StaticContents);
    //已经设置了窗口的最小大小(窗口可拉伸)
    setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);

    //画笔的颜色设置为黑色
    curColor = Qt::black;
    //缩放因子设置为8，即每个像素会显示成一个8*8的正方形
    zoom = 8;

    //图标数据初始化为16*16的像素大小和32位的ARGB颜色格式
    image = QImage(16, 16, QImage::Format_ARGB32);
    //类似于RGB(0,0,0)的数据格式
    image.fill(qRgba(0, 0, 0, 0));
}

IconEditor::~IconEditor()
{
    delete ui;
}

QSize IconEditor::sizeHint() const
{
    //缩放因子*像素大小 = 窗口部件的理想大小
    QSize size = zoom * image.size();
    //如果缩放因子大于3，则增加一个额外的像素，用来容纳网格线
    if (zoom >= 3) {
        size += QSize(1, 1);
    }
    return size;
}

void IconEditor::setpenColor(const QColor &newColor)
{
    curColor = newColor;
}

//编辑图像
void IconEditor::seticonImage(const QImage &newImage)
{
    if (newImage != image) {
        image = newImage.convertToFormat(QImage::Format_ARGB32);
        //update会强制使用新的图像重绘窗口部件
        update();
        //通知窗口布局，窗口部件的大小已经改变了
        updateGeometry();
    }
}

//设置图像的缩放因子
void IconEditor::setzoomFactor(int newZoom)
{
    if (newZoom < 1) {
        newZoom = 1;
    }
    if (newZoom != zoom) {
        zoom = newZoom;
        update();
        updateGeometry();
    }
}

void IconEditor::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    //缩放因子大于3的情况下，重新画网格
    if (zoom >= 3) {
        //窗口部件的调色板palette
        painter.setPen(palette().foreground().color());
        for (int i = 0; i <= image.width(); ++i) {
            painter.drawLine(zoom * i, 0,
                             zoom * i, zoom * image.height());
        }
        for (int j = 0; j <= image.height(); ++j) {
            painter.drawLine(0, zoom * j,
                             zoom * image.width(), zoom * j);
        }
    }

    for (int i = 0; i < image.width(); ++i) {
        for (int j = 0; j < image.height(); ++j) {
            //返回像素坐标
            QRect rect = pixelRect(i, j);
            //绘制窗口颜色为白色
            if (!event->region().intersected(rect).isEmpty()) {
                QColor color = QColor::fromRgba(image.pixel(i, j));
                if (color.alpha() < 255) {
                    painter.fillRect(rect, Qt::white);
                }
                painter.fillRect(rect, color);
            }
        }
    }
}

QRect IconEditor::pixelRect(int i, int j) const
{
    if (zoom >= 3) {
        return QRect(zoom * i + 1, zoom * j + 1, zoom - 1, zoom - 1);
    } else {
        return QRect(zoom * i, zoom * j, zoom, zoom);
    }
}
void IconEditor::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        //把鼠标选中的像素设置成当前画笔的颜色
        setImagePixel(event->pos(), true);
    } else if (event->button() == Qt::RightButton) {
        //通过传递false，来清空这个像素
        setImagePixel(event->pos(), false);
    }
}

void IconEditor::mouseMoveEvent(QMouseEvent *event)
{
    if (event->button() & Qt::LeftButton) {
        //鼠标选中后连续的设置像素
        setImagePixel(event->pos(), true);
    } else if (event->button() & Qt::RightButton) {
        //鼠标选中后连续的清空像素
        setImagePixel(event->pos(), false);
    }
}

void IconEditor::setImagePixel(const QPoint &pos, bool opaque)
{
    //这里必须除以zoom，因为image.rect()是返回格子范围16*16,而pos则为像素的范围，存在缩放因子，所以扩大了zoom倍
    int i = pos.x() / zoom;
    int j = pos.y() / zoom;

    if (image.rect().contains(i, j)) {
        if (opaque) {
            //设定一个像素
            image.setPixel(i, j, penColor().rgba());
        } else {
            //清除一个像素
            image.setPixel(i, j, qRgba(0, 0, 0, 0));
        }
        update(pixelRect(i, j));
    }
}
