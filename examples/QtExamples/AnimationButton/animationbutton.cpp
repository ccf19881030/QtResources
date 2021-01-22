#include "animationbutton.h"
#include "qpainter.h"
#include "qpropertyanimation.h"
#include "qdebug.h"

AnimationButton::AnimationButton(QWidget *parent) : QWidget(parent)
{
	enter = true;
	leave = false;
	pixWidth = 0;
	pixHeight = 0;
	oldWidth = 0;
	oldHeight = 0;

	enterAnimation = new QPropertyAnimation(this, "");
	enterAnimation->setStartValue(0);
	enterAnimation->setEndValue(5);
	enterAnimation->setDuration(200);
	connect(enterAnimation, SIGNAL(valueChanged(QVariant)), this, SLOT(enterImageChanged(QVariant)));

	leaveAnimation = new QPropertyAnimation(this, "");
	leaveAnimation->setStartValue(0);
	leaveAnimation->setEndValue(5);
	leaveAnimation->setDuration(200);
	connect(leaveAnimation, SIGNAL(valueChanged(QVariant)), this, SLOT(leaveImageChanged(QVariant)));
}

AnimationButton::~AnimationButton()
{
	delete enterAnimation;
	delete leaveAnimation;
}

void AnimationButton::enterEvent(QEvent *)
{
	enter = true;
	leave = false;
	pixWidth = pixWidth - 25;
	pixHeight = pixHeight - 25;
	enterAnimation->start();
}

void AnimationButton::leaveEvent(QEvent *)
{
	enter = false;
	leave = true;
	pixWidth = oldWidth;
	pixHeight = oldHeight;
	leaveAnimation->start();
}

void AnimationButton::paintEvent(QPaintEvent *)
{
	if (image.isEmpty()) {
		return;
	}

	QPainter painter(this);
	painter.setRenderHint(QPainter::Antialiasing);

	QPixmap pix(image);
    pix = pix.scaled(targetWidth, targetHeight, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);

	if (enter || leave) {
		int pixX = rect().center().x() - targetWidth / 2;
		int pixY = rect().center().y() - targetHeight / 2 - 10;
		QPoint point(pixX, pixY);
		painter.drawPixmap(point, pix);
		painter.drawText(QRectF(0, height() - 20, width(), 20), Qt::AlignCenter, text);
	}
}

void AnimationButton::enterImageChanged(QVariant index)
{
	int i = index.toInt();
	targetWidth = pixWidth + i * 5;
	targetHeight = pixHeight + i * 5;
	update();
}

void AnimationButton::leaveImageChanged(QVariant index)
{
	int i = index.toInt();
	targetWidth = pixWidth - i * 5;
	targetHeight = pixWidth - i * 5;
	update();
}

void AnimationButton::setImage(QString image)
{
	this->image = image;
	QPixmap pix(image);
	pixWidth = pix.width();
	pixHeight = pix.height();
	oldWidth = pixWidth;
	oldHeight = pixHeight;
	targetWidth = pixWidth - 25;
	targetHeight = pixHeight - 25;
	update();
}

void AnimationButton::setText(QString text)
{
	this->text = text;
	update();
}

