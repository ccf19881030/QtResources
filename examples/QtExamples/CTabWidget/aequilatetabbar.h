#ifndef AEQUILATETABBAR_H
#define AEQUILATETABBAR_H
#include <QTabBar>

class AequilateTabBar : public QTabBar
{
    Q_OBJECT

public:

    explicit AequilateTabBar(QWidget *parent = 0);
    QSize tabSizeHint ( int index ) const;
    void setTabWidth( int value);
	void setTabHeight(int value);
private:
	int height;
};

#endif // AEQUILATETABBAR_H
