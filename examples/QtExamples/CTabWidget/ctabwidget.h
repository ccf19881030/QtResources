#ifndef CTABWIDGET_H
#define CTABWIDGET_H   
#include <QTabWidget>   
#include "aequilatetabbar.h"
class CTabWidget :public QTabWidget  
{  
	Q_OBJECT  
public:  
	enum animation_Direction{
		animationTop,
		animationRight,
		animationBottom,
		animationLeft,
		animationTopLeft,
		animationTopRight,
		animationBottomRight,
		animationBottomLeft,
		animationCenter
	};

	CTabWidget(QWidget* =0);  
    ~CTabWidget();
    void	resizeEvent ( QResizeEvent * );
     void   setTabBarHeight(int value);



private slots:
    void deleteWidget(int index);
	void switchScreen(int index);
	
private:
	void cloudAntimation(animation_Direction direction);
	

private:
	QPixmap pixmap;
	int preindex;
    AequilateTabBar *bar;
};  
#endif // CTABWIDGET_H
