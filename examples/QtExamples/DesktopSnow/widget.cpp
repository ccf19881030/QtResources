#include "widget.h"
#include "ui_widget.h"
#include <QDesktopWidget>
#include <QPalette>
#include <QBrush>

#include <time.h>

#ifdef Q_OS_LINUX
#include <X11/extensions/shape.h>
#endif
#ifdef Q_OS_WIN
#include <windows.h>
#endif

Widget::Widget(QWidget *parent) :
	QWidget(parent),
	ui(new Ui::Widget)
{
	ui->setupUi(this);
	setGeometry(0, 0, qApp->desktop()->width(), qApp->desktop()->height());
	setWindowFlags(windowFlags()
				   |Qt::FramelessWindowHint //去边框
				   |Qt::X11BypassWindowManagerHint //linux下脱离任务管理器
				   |Qt::WindowStaysOnBottomHint //最低层显示
				   |Qt::Tool //不在任务栏显示
					);
	setAttribute(Qt::WA_TranslucentBackground);
	setWindowState(Qt::WindowNoState //不激活
				   |Qt::WindowFullScreen //全屏
				   );
	setFocusPolicy(Qt::NoFocus);
	setWindowOpacity(WINDOW_OPACITY);


	int i=0;
	pixmapList[i++].load(":/snowIcons/11.png");
	pixmapList[i++].load(":/snowIcons/03.png");
	pixmapList[i++].load(":/snowIcons/06.png");
	pixmapList[i++].load(":/snowIcons/08.png");
	pixmapList[i++].load(":/snowIcons/10.png");
	pixmapList[i++].load(":/snowIcons/12.png");
	pixmapList[i++].load(":/snowIcons/13.png");
	pixmapList[i++].load(":/snowIcons/16.png");
	pixmapList[i++].load(":/snowIcons/17.png");
	pixmapList[i++].load(":/snowIcons/18.png");
	pixmapList[i++].load(":/snowIcons/19.png");

	for(i = 0; i < MAX_PICS; i++)
	{
		picLabel[i] = new QLabel(this);
		picLabel[i]->setGeometry(-128, -128, 64, 64);
	}
	startTimer(150);
}

Widget::~Widget()
{
	delete ui;
}

void Widget::timerEvent(QTimerEvent *e)
{
	const int timeinit = 10;
	static int timeCount = timeinit;
	static int initLabel = MAX_PICS;
	if(--timeCount <= 0)
	{
		qsrand(::time(NULL));
		timeCount = timeinit;
		if(initLabel > 0)
		{
			--initLabel;
			picLabel[initLabel]->move(0, -picLabel[initLabel]->height());
		}
	}
	FlashSnow();
}

void Widget::SetLabelBG(const QPixmap &pixmap, QLabel *label)
{
	if(!label || pixmap.isNull()) return;
	QPixmap map = pixmap.scaled(label->size());
	if(map.isNull()) return;
	label->setPixmap(map);
}

void Widget::FlashSnow()
{
	int i;
	for(i = 0; i < MAX_PICS; i++)
	{
		if(picLabel[i] == NULL) continue;
		if(picLabel[i]->y() == -picLabel[i]->height())
		{
			//resize label
			int size = (qrand()%64)+16;
			picLabel[i]->resize(size, size);

			//init place
			int x = (qrand()%this->width());
			picLabel[i]->move(x, 10-picLabel[i]->height());

			//repaint label's backgroud
			int imgId = (qrand()%MAX_PIXMAP);
			SetLabelBG(pixmapList[imgId], picLabel[i]);
		}
		else
		{
			//snow flow down
			WidgetFlowDown(picLabel[i]);
		}
	}
}

void Widget::WidgetFlowDown(QWidget *widget, bool bRandom)
{
	if(!widget) return;
	int downY = widget->y()+5;
	if(bRandom)
	{
		downY = widget->y()+qrand()%(this->height() - widget->y());
	}
	if(downY > (this->height())) downY = -widget->height();
	widget->move(widget->x(), downY);
}
