
#include "ctabwidget.h"

#include <QLabel>
#include <QtGui>

CTabWidget::CTabWidget(QWidget *parent):QTabWidget(parent),preindex(0)
{  
    bar = new AequilateTabBar(this);
    setTabBar( bar );
    connect(this, SIGNAL(currentChanged(int)), this, SLOT(switchScreen(int)));
    connect(this, SIGNAL(tabCloseRequested(int)), this, SLOT(deleteWidget(int)));

}

CTabWidget::~CTabWidget()
{

}

void CTabWidget::deleteWidget(int index)
{

  disconnect(this, SIGNAL(currentChanged(int)), this, SLOT(switchScreen(int)));
  QWidget *widget = this->widget(index);
  QPixmap tempPixmap(widget->size());
  pixmap = tempPixmap;
  widget->render(&pixmap);


  QWidget* tabItem = this->widget(index);
  removeTab(index);
  delete tabItem;


  if(this->count() != 0)
   {
      cloudAntimation(animationTopRight);
      preindex = this->currentIndex();
   }

  connect(this, SIGNAL(currentChanged(int)), this, SLOT(switchScreen(int))); 


}

void CTabWidget::switchScreen(int index)
{	
	int n = 0 ;
	if (preindex == this->currentIndex() || preindex >= this->count())
	{
		return;
	}
	else if(preindex > this->currentIndex())
	{
		n = 2;
	}
	else if (preindex < this->currentIndex())
	{
		n = 6;
	}

	QPixmap tempPixmap(this->widget(preindex)->size());
	pixmap = tempPixmap;
	this->widget(preindex)->render(&pixmap);


	switch (n) {
	case 0:
		cloudAntimation(animationTop);
		break;
	case 1:
		cloudAntimation(animationTopRight);
		break;
	case 2:
		cloudAntimation(animationRight);
		break;
	case 3:
		cloudAntimation(animationBottomRight);
		break;
	case 4:
		cloudAntimation(animationBottom);
		break;
	case 5:
		cloudAntimation(animationBottomLeft);
		break;
	case 6:
		cloudAntimation(animationLeft);
		break;
	case 7:
		cloudAntimation(animationTopLeft);
		break;
	case 8:
		cloudAntimation(animationCenter);
		break;
	default:
		break;
	}
	preindex = index;
}

void CTabWidget::cloudAntimation(animation_Direction direction)
{
	QLabel* circle = new QLabel(this->currentWidget());
	//QPixmap pixmap(this->widget(preindex)->size());
	//this->widget(preindex)->render(&pixmap);
	circle->setPixmap(pixmap);
	circle->show();
	circle->resize(this->currentWidget()->size());

	

	QPropertyAnimation *animation = new QPropertyAnimation(circle, "geometry");
	animation->setDuration(1000);
	animation->setStartValue(circle->geometry());
	animation->setEasingCurve(QEasingCurve::OutCubic);

	switch (direction) {
	case animationTop:
		animation->setEndValue(QRect(circle->x(), circle->y() - 10, circle->width(), 0));
		break;
	case animationTopRight:
		animation->setEndValue(QRect(circle->width(), 0, 0, 0));
		break;
	case animationRight:

		animation->setEndValue(QRect(circle->width() + 3, 0, circle->width(), circle->height()));
		break;
	case animationBottomRight:
		animation->setEndValue(QRect(circle->width(), circle->height(), 0, 0));
		break;
	case animationBottom:
		animation->setEndValue(QRect(0, circle->height() + 10, circle->width(), 0));
		break;
	case animationBottomLeft:
		animation->setEndValue(QRect(0, circle->height(), 0, 0));
		break;
	case animationLeft:

		animation->setEndValue(QRect(-3-circle->width(), 0, circle->width(), circle->height()));
		break;
	case animationTopLeft:
		animation->setEndValue(QRect(0, 0, 0, 0));
		break;
	case animationCenter:
		animation->setEndValue(QRect(circle->width()/2, circle->height()/2, 0, 0));
		break;
	default:
		break;
	}
	


    connect(animation,SIGNAL(finished()), circle, SLOT(deleteLater()));

    connect(animation,SIGNAL(finished()), animation, SLOT(deleteLater()));

    animation->start();
}

void CTabWidget::resizeEvent ( QResizeEvent  *e)
{
   QTabWidget::resizeEvent ( e );
   bar->setTabWidth(width());
}

void CTabWidget::setTabBarHeight(int value)
{
    bar->setTabHeight(value);
}


