#ifndef LIGHTBUTTON_H
#define LIGHTBUTTON_H

/**
 * 高亮发光按钮控件 作者:feiyangqingyun(QQ:517216493) 2016-10-16
 * 1:可设置文本,居中显示
 * 2:可设置文本颜色
 * 3:可设置外边框渐变颜色
 * 4:可设置里边框渐变颜色
 * 5:可设置背景色
 * 6:可直接调用内置的设置 绿色/红色/黄色/黑色/蓝色 等公有槽函数
 * 7:可设置是否在容器中可移动,当成一个对象使用
 */

#include <QWidget>

#ifdef quc
#if (QT_VERSION < QT_VERSION_CHECK(5,7,0))
#include <QtDesigner/QDesignerExportWidget>
#else
#include <QtUiPlugin/QDesignerExportWidget>
#endif

class QDESIGNER_WIDGET_EXPORT LightButton : public QWidget
#else
class LightButton : public QWidget
#endif

{
	Q_OBJECT
	Q_PROPERTY(QString text READ getText WRITE setText)
	Q_PROPERTY(QColor textColor READ getTextColor WRITE setTextColor)

	Q_PROPERTY(QColor borderOutColorStart READ getBorderOutColorStart WRITE setBorderOutColorStart)
	Q_PROPERTY(QColor borderOutColorEnd READ getBorderOutColorEnd WRITE setBorderOutColorEnd)
	Q_PROPERTY(QColor borderInColorStart READ getBorderInColorStart WRITE setBorderInColorStart)
	Q_PROPERTY(QColor borderInColorEnd READ getBorderInColorEnd WRITE setBorderInColorEnd)
	Q_PROPERTY(QColor bgColor READ getBgColor WRITE setBgColor)

	Q_PROPERTY(bool canMove READ getCanMove WRITE setCanMove)
	Q_PROPERTY(bool showOverlay READ getShowOverlay WRITE setShowOverlay)
	Q_PROPERTY(QColor overlayColor READ getOverlayColor WRITE setOverlayColor)

public:
	explicit LightButton(QWidget *parent = 0);

protected:
	bool eventFilter(QObject *, QEvent *);
	void paintEvent(QPaintEvent *);
	void drawBorderOut(QPainter *painter);
	void drawBorderIn(QPainter *painter);
	void drawBg(QPainter *painter);
	void drawText(QPainter *painter);
	void drawOverlay(QPainter *painter);

private:
	QString text;                   //文本
	QColor textColor;               //文字颜色

	QColor borderOutColorStart;     //外边框渐变开始颜色
	QColor borderOutColorEnd;       //外边框渐变结束颜色
	QColor borderInColorStart;      //里边框渐变开始颜色
	QColor borderInColorEnd;        //里边框渐变结束颜色
	QColor bgColor;                 //背景颜色

	bool canMove;                   //是否能够移动
	bool showOverlay;               //是否显示遮罩层
	QColor overlayColor;            //遮罩层颜色

public:
	QString getText()               const;
	QColor getTextColor()           const;

	QColor getBorderOutColorStart() const;
	QColor getBorderOutColorEnd()   const;
	QColor getBorderInColorStart()  const;
	QColor getBorderInColorEnd()    const;
	QColor getBgColor()             const;

	bool getCanMove()               const;
	bool getShowOverlay()           const;
	QColor getOverlayColor()        const;

	QSize sizeHint()                const;
	QSize minimumSizeHint()         const;

public Q_SLOTS:
	//设置文本
    void setText(const QString &text);
	//设置文本颜色
    void setTextColor(const QColor &textColor);

	//设置外边框渐变颜色
    void setBorderOutColorStart(const QColor &borderOutColorStart);
    void setBorderOutColorEnd(const QColor &borderOutColorEnd);

	//设置里边框渐变颜色
    void setBorderInColorStart(const QColor &borderInColorStart);
    void setBorderInColorEnd(const QColor &borderInColorEnd);

	//设置背景色
    void setBgColor(const QColor &bgColor);

	//设置是否可移动
	void setCanMove(bool canMove);
	//设置是否显示遮罩层
	void setShowOverlay(bool showOverlay);
	//设置遮罩层颜色
    void setOverlayColor(const QColor &overlayColor);

	//设置为绿色
	void setGreen();
	//设置为红色
	void setRed();
	//设置为黄色
	void setYellow();
	//设置为黑色
	void setBlack();
	//设置为灰色
	void setGray();
	//设置为蓝色
	void setBlue();
	//设置为淡蓝色
	void setLightBlue();
	//设置为淡红色
	void setLightRed();
	//设置为淡绿色
	void setLightGreen();
};

#endif //LIGHTBUTTON_H
