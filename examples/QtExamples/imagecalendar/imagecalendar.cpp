#pragma execution_character_set("utf-8")

#include "imagecalendar.h"
#include "lunarcalendarinfo.h"
#include "qpainter.h"
#include "qtimer.h"
#include "qdatetime.h"
#include "qaction.h"
#include "qdebug.h"

ImageCalendar::ImageCalendar(QWidget *parent) : QWidget(parent)
{
	setFont(QFont("Microsoft Yahei", 9));

	QAction *action_yellow = new QAction("黄色风格", this);
	connect(action_yellow, SIGNAL(triggered(bool)), this, SLOT(changeStyle()));
	this->addAction(action_yellow);

	QAction *action_blue = new QAction("蓝色风格", this);
	connect(action_blue, SIGNAL(triggered(bool)), this, SLOT(changeStyle()));
	this->addAction(action_blue);

	QAction *action_brown = new QAction("褐色风格", this);
	connect(action_brown, SIGNAL(triggered(bool)), this, SLOT(changeStyle()));
	this->addAction(action_brown);

	QAction *action_gray = new QAction("灰色风格", this);
	connect(action_gray, SIGNAL(triggered(bool)), this, SLOT(changeStyle()));
	this->addAction(action_gray);

	QAction *action_purple = new QAction("紫色风格", this);
	connect(action_purple, SIGNAL(triggered(bool)), this, SLOT(changeStyle()));
	this->addAction(action_purple);

	QAction *action_red = new QAction("红色风格", this);
	connect(action_red, SIGNAL(triggered(bool)), this, SLOT(changeStyle()));
	this->addAction(action_red);

	this->setContextMenuPolicy(Qt::ActionsContextMenu);

	imageNames << "yellow" << "blue" << "brown" << "gray" << "purple" << "red";
    setCalendarStyle(CalendarStyle_Blue);
	currentDate = QDateTime::currentDateTime();
}

void ImageCalendar::paintEvent(QPaintEvent *)
{
	QString strYearMonth = currentDate.toString("yyyy年 MM月");
	QString strWeek = currentDate.toString("dddd");
	QString strDay = currentDate.toString("dd");
	QString strLunar = LunarCalendarInfo::Instance()->getLunarYearMonthDay(currentDate.date().year(), currentDate.date().month(), currentDate.date().day());

	//先将需要绘制的图形绘制到一张图片上,最后将图片绘制到屏幕
	QImage buffer(140, 158, QImage::Format_ARGB32_Premultiplied);
	//填充透明背景
	buffer.fill(Qt::transparent);

	//启用反锯齿及图片平滑过渡
	QPainter painter(&buffer);
	painter.setRenderHint(QPainter::Antialiasing, true);
	painter.setRenderHint(QPainter::TextAntialiasing, true);
	painter.setRenderHint(QPainter::SmoothPixmapTransform, true);

	//绘制背景
	painter.drawImage(0, 0, calendarBg);

	//设置文字颜色
	painter.setPen(QColor(250, 250, 250));

	//绘制年份月份
	painter.setFont(QFont("Microsoft Yahei", 9));
	painter.drawText(QRect(10, 26, 140 - 20, 20), Qt::AlignCenter, strYearMonth);

	//绘制星期
	painter.drawText(QRect(10, 106, 140 - 20, 20), Qt::AlignCenter, strWeek);

	//绘制农历年份及月份
	painter.setFont(QFont("Microsoft Yahei", 8));
	painter.drawText(QRect(10, 124, 140 - 20, 20), Qt::AlignCenter, strLunar);

	//绘制日
	painter.setFont(QFont("Arial", 45));
	painter.setPen(QColor(50, 50, 50));
	painter.drawText(QRect(12, 40, 140 - 20, 80), Qt::AlignCenter, strDay);
	painter.setPen(QColor(250, 250, 250));
	painter.drawText(QRect(10, 38, 140 - 20, 80), Qt::AlignCenter, strDay);

	painter.end();

	//居中绘制图片
	QPainter p(this);
	int pixX = rect().center().x() - buffer.width() / 2;
	int pixY = rect().center().y() - buffer.height() / 2;
	QPoint point(pixX, pixY);
	p.drawImage(point, buffer);
}

void ImageCalendar::changeStyle()
{
	QAction *action = (QAction *)sender();

	if (action->text() == "黄色风格") {
		setCalendarStyle(CalendarStyle_Yellow);
	} else if (action->text() == "蓝色风格") {
		setCalendarStyle(CalendarStyle_Blue);
	} else if (action->text() == "褐色风格") {
		setCalendarStyle(CalendarStyle_Brown);
	} else if (action->text() == "灰色风格") {
		setCalendarStyle(CalendarStyle_Gray);
	} else if (action->text() == "紫色风格") {
		setCalendarStyle(CalendarStyle_Purple);
	} else if (action->text() == "红色风格") {
		setCalendarStyle(CalendarStyle_Red);
	}
}

void ImageCalendar::changeDate()
{
	currentDate = QDateTime::currentDateTime();
    update();
}

ImageCalendar::CalendarStyle ImageCalendar::getCalendarStyle() const
{
	return this->calendarStyle;
}

QSize ImageCalendar::sizeHint() const
{
	return QSize(140, 158);
}

QSize ImageCalendar::minimumSizeHint() const
{
	return QSize(140, 158);
}

void ImageCalendar::setCalendarStyle(ImageCalendar::CalendarStyle calendarStyle)
{
    if (this->calendarStyle != calendarStyle){
        this->calendarStyle = calendarStyle;
        QString imageName = imageNames.at(calendarStyle);
        calendarBg = QImage(QString(":/image/Calendar_bg_%1.png").arg(imageName));
        update();
    }
}
