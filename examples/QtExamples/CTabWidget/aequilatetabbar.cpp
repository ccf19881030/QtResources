
#include "aequilatetabbar.h"

AequilateTabBar::AequilateTabBar(QWidget *parent) :
    QTabBar(parent),height(35)
{

}

QSize AequilateTabBar::tabSizeHint ( int index ) const
{
    if(index != count()-1)
    {
       return QSize(width()/count(), height );
    }
    else
    {
       return QSize(width()-width()/count()*(count()-1), height );
    }
}

void AequilateTabBar::setTabWidth( int value)
{
    setFixedWidth(value-2);
}

void AequilateTabBar::setTabHeight( int value )
{
	height = value;
}


