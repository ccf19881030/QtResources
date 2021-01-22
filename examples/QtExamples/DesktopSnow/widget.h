#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QLabel>
#include <QPixmap>

#define WINDOW_OPACITY		0.5
#define MAX_PIXMAP			11
#define MAX_PICS			30

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
	Q_OBJECT
	
public:
	explicit Widget(QWidget *parent = 0);
	~Widget();

	static void SetLabelBG(const QPixmap &pixmap, QLabel *label);
	
protected:
	void WidgetFlowDown(QWidget *widget, bool bRandom = false);

protected slots:
	void timerEvent(QTimerEvent *e);
	void FlashSnow();

private:
	Ui::Widget *ui;
	QLabel* picLabel[MAX_PICS];
	QPixmap pixmapList[MAX_PIXMAP];
};

#endif // WIDGET_H
