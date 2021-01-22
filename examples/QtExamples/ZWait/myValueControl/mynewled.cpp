#include "mynewled.h"

#define DRAW_LED(NumberObj)     if(NumberObj->hasThisPair(hIndex,vIndex)) \
                                { \
                                    goto DoPainting; \
                                }else{ \
                                    goto DoNothing; \
                                }

#define ADD_COOR(Obj,X,Y) Obj->addPair(X,Y);

myNewLed::myNewLed(QWidget *parent) :
    QWidget(parent)
{
    this->initVariables();
}

void myNewLed::initVariables()
{

    this->myledColor1=QColor(55,142,234);
    this->myledColor2=QColor(48,125,207);

    m_nNum = 0;

    zero = new NumberObj();
    one = new NumberObj();
    two = new NumberObj();
    three = new NumberObj();
    four = new NumberObj();
    five = new NumberObj();
    six = new NumberObj();
    seven = new NumberObj();
    eight = new NumberObj();
    nine = new NumberObj();

    /// stuff zero
    ADD_COOR(zero,2,1);
    ADD_COOR(zero,3,1);
    ADD_COOR(zero,4,1);
    ADD_COOR(zero,5,1);
    ADD_COOR(zero,6,1);
    ADD_COOR(zero,2,2);
    ADD_COOR(zero,2,3);
    ADD_COOR(zero,2,4);
    ADD_COOR(zero,2,5);
    ADD_COOR(zero,2,6);
    ADD_COOR(zero,2,7);
    ADD_COOR(zero,3,7);
    ADD_COOR(zero,4,7);
    ADD_COOR(zero,5,7);
    ADD_COOR(zero,6,7);
    ADD_COOR(zero,6,2);
    ADD_COOR(zero,6,3);
    ADD_COOR(zero,6,4);
    ADD_COOR(zero,6,5);
    ADD_COOR(zero,6,6);


    /// stuff one
//    ADD_COOR(one,2,3);
    ADD_COOR(one,3,2);
    ADD_COOR(one,4,1);
    ADD_COOR(one,4,2);
    ADD_COOR(one,4,3);
    ADD_COOR(one,4,7);
    ADD_COOR(one,4,4);
    ADD_COOR(one,4,5);
    ADD_COOR(one,4,6);
//    ADD_COOR(one,2,7);
    ADD_COOR(one,3,7);
//    ADD_COOR(one,6,7);
    ADD_COOR(one,5,7);

    /// stuff two
    ADD_COOR(two,2,1);
    ADD_COOR(two,3,1);
    ADD_COOR(two,4,1);
    ADD_COOR(two,5,1);
    ADD_COOR(two,6,1);
    ADD_COOR(two,6,2);
    ADD_COOR(two,6,3);
    ADD_COOR(two,6,4);
    ADD_COOR(two,2,5);
    ADD_COOR(two,2,6);
    ADD_COOR(two,2,7);
    ADD_COOR(two,3,7);
    ADD_COOR(two,4,7);
    ADD_COOR(two,5,7);
    ADD_COOR(two,6,7);
    ADD_COOR(two,5,4);
    ADD_COOR(two,4,4);
    ADD_COOR(two,3,4);
    ADD_COOR(two,2,4);

    /// stuff three
    ADD_COOR(three,2,1);
    ADD_COOR(three,3,1);
    ADD_COOR(three,4,1);
    ADD_COOR(three,5,1);
    ADD_COOR(three,6,1);
    ADD_COOR(three,6,2);
    ADD_COOR(three,6,3);
    ADD_COOR(three,6,4);
    ADD_COOR(three,6,5);
    ADD_COOR(three,6,6);
    ADD_COOR(three,2,7);
    ADD_COOR(three,3,7);
    ADD_COOR(three,4,7);
    ADD_COOR(three,5,7);
    ADD_COOR(three,6,7);
    ADD_COOR(three,2,4);
    ADD_COOR(three,3,4);
    ADD_COOR(three,4,4);
    ADD_COOR(three,5,4);


    /// stuff four
    ADD_COOR(four,4,1);
    ADD_COOR(four,3,2);
    ADD_COOR(four,2,3);
    ADD_COOR(four,2,4);
    ADD_COOR(four,3,4);
    ADD_COOR(four,4,4);
    ADD_COOR(four,5,4);
    ADD_COOR(four,6,4);
    ADD_COOR(four,4,2);
    ADD_COOR(four,4,3);
    ADD_COOR(four,4,4);
    ADD_COOR(four,4,5);
    ADD_COOR(four,4,6);
    ADD_COOR(four,4,7);
    ADD_COOR(four,1,4);

    /// stuff five
    ADD_COOR(five,6,1);
    ADD_COOR(five,5,1);
    ADD_COOR(five,4,1);
    ADD_COOR(five,3,1);
    ADD_COOR(five,2,1);
    ADD_COOR(five,2,2);
    ADD_COOR(five,2,3);
    ADD_COOR(five,2,4);
    ADD_COOR(five,3,4);
    ADD_COOR(five,4,4);
    ADD_COOR(five,5,4);
    ADD_COOR(five,6,4);
    ADD_COOR(five,6,6);
    ADD_COOR(five,6,7);
    ADD_COOR(five,5,7);
    ADD_COOR(five,4,7);
    ADD_COOR(five,3,7);
    ADD_COOR(five,2,7);
    ADD_COOR(five,6,5);


    /// stuff six
    ADD_COOR(six,6,1);
    ADD_COOR(six,5,1);
    ADD_COOR(six,4,1);
    ADD_COOR(six,3,1);
    ADD_COOR(six,2,1);
    ADD_COOR(six,2,2);
    ADD_COOR(six,2,3);
    ADD_COOR(six,2,4);
    ADD_COOR(six,3,4);
    ADD_COOR(six,4,4);
    ADD_COOR(six,5,4);
    ADD_COOR(six,6,4);
    ADD_COOR(six,6,6);
    ADD_COOR(six,6,7);
    ADD_COOR(six,5,7);
    ADD_COOR(six,4,7);
    ADD_COOR(six,3,7);
    ADD_COOR(six,2,7);
    ADD_COOR(six,6,5);
    ADD_COOR(six,2,5);
    ADD_COOR(six,2,2);
    ADD_COOR(six,2,6);


    /// stuff seven
    ADD_COOR(seven,2,1);
    ADD_COOR(seven,3,1);
    ADD_COOR(seven,4,1);
    ADD_COOR(seven,5,1);
    ADD_COOR(seven,6,1);
    ADD_COOR(seven,6,2);
    ADD_COOR(seven,5,3);
    ADD_COOR(seven,4,4);
    ADD_COOR(seven,3,5);
    ADD_COOR(seven,2,6);
    ADD_COOR(seven,2,7);

    /// stuff eight
    ADD_COOR(eight,6,1);
    ADD_COOR(eight,5,1);
    ADD_COOR(eight,4,1);
    ADD_COOR(eight,3,1);
    ADD_COOR(eight,2,1);
    ADD_COOR(eight,2,2);
    ADD_COOR(eight,2,3);
    ADD_COOR(eight,2,4);
    ADD_COOR(eight,3,4);
    ADD_COOR(eight,4,4);
    ADD_COOR(eight,5,4);
    ADD_COOR(eight,6,4);
    ADD_COOR(eight,6,6);
    ADD_COOR(eight,6,7);
    ADD_COOR(eight,5,7);
    ADD_COOR(eight,4,7);
    ADD_COOR(eight,3,7);
    ADD_COOR(eight,2,7);
    ADD_COOR(eight,6,5);
    ADD_COOR(eight,2,2);
    ADD_COOR(eight,6,2);
    ADD_COOR(eight,6,3);
    ADD_COOR(eight,2,5);
    ADD_COOR(eight,2,6);

    /// stuff nine
    ADD_COOR(nine,6,1);
    ADD_COOR(nine,5,1);
    ADD_COOR(nine,4,1);
    ADD_COOR(nine,3,1);
    ADD_COOR(nine,2,1);
    ADD_COOR(nine,2,2);
    ADD_COOR(nine,2,3);
    ADD_COOR(nine,2,4);
    ADD_COOR(nine,3,4);
    ADD_COOR(nine,4,4);
    ADD_COOR(nine,5,4);
    ADD_COOR(nine,6,4);
    ADD_COOR(nine,6,6);
    ADD_COOR(nine,6,7);
    ADD_COOR(nine,5,7);
    ADD_COOR(nine,4,7);
    ADD_COOR(nine,3,7);
    ADD_COOR(nine,2,7);
    ADD_COOR(nine,6,5);
    ADD_COOR(nine,2,2);
    ADD_COOR(nine,6,2);
    ADD_COOR(nine,6,3);

}

void myNewLed::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing);
    drawBg(&painter);
    drawLed(&painter);
}

void myNewLed::drawBg(QPainter *painter)
{
    painter->save();
    painter->setPen(Qt::NoPen);
    painter->setBrush(PYL_BG_COLOR);
    painter->drawRect(rect());
    painter->restore();
}

void myNewLed::SetmyLedColor(QColor c1, QColor c2)
{
    this->myledColor1=c1;
    this->myledColor2=c2;
}

void myNewLed::drawLed(QPainter *painter)
{
    qreal initX = PYL_LEFT_SPACE;
    qreal initY = PYL_TOP_SPACE;
    qreal LedWidth = (width() - 2 * PYL_LEFT_SPACE - (PYL_H_COUNT-1)*PYL_WIDGET_SPACE)/PYL_H_COUNT;
    qreal LedHeight = (height() - 2* PYL_TOP_SPACE -(PYL_V_COUNT-1)*PYL_WIDGET_SPACE)/PYL_V_COUNT;

    painter->save();
    painter->setPen(Qt::NoPen);
    for(int hIndex = 0;hIndex < PYL_H_COUNT;hIndex++)
    {
        for(int vIndex = 0;vIndex < PYL_V_COUNT;vIndex++)
        {
            QPointF LedTopLeft(initX,initY);
            QPointF LedBottomRight(initX + LedWidth,initY + LedHeight);
            QRectF LedRect(LedTopLeft,LedBottomRight);

            QLinearGradient LedGradient(LedRect.topLeft(),LedRect.bottomLeft());
            LedGradient.setColorAt(0.0,PYL_NON_START_COLOR);
            LedGradient.setColorAt(1.0,PYL_NON_END_COLOR);
            painter->setBrush(LedGradient);

            painter->drawRoundedRect(LedRect,PYL_RECT_RADIUS,PYL_RECT_RADIUS);

            /// increment initX
            initX += LedWidth + PYL_WIDGET_SPACE;
        }

        /// increment initY
        initY += LedHeight + PYL_WIDGET_SPACE;
        initX = PYL_LEFT_SPACE;
    }

    painter->restore();

    // draw highlight led
    initX = PYL_LEFT_SPACE;
    initY = PYL_TOP_SPACE;
    qreal LedX = 0;
    qreal LedY = 0;

    painter->save();
    painter->setPen(Qt::NoPen);

    for(int hIndex = 0;hIndex < PYL_H_COUNT;hIndex++)
    {
        for(int vIndex = 0;vIndex < PYL_V_COUNT;vIndex++)
        {
            switch(m_nNum)
            {
            case 0:
                DRAW_LED(zero);
            case 1:
                DRAW_LED(one);
            case 2:
                DRAW_LED(two);
            case 3:
                DRAW_LED(three);
            case 4:
                DRAW_LED(four);
            case 5:
                DRAW_LED(five);
            case 6:
                DRAW_LED(six);
            case 7:
                DRAW_LED(seven);
            case 8:
                DRAW_LED(eight);
            case 9:
                DRAW_LED(nine);


            }

DoPainting:
            LedX = initX + hIndex * LedWidth + (hIndex)*PYL_WIDGET_SPACE;
            LedY = initY + vIndex * LedHeight + (vIndex)* PYL_WIDGET_SPACE;
            {
                QPointF LedTopLeft(LedX,LedY);
                QPointF LedBottomRight(LedX + LedWidth,LedY + LedHeight);
                QRectF LedRect(LedTopLeft,LedBottomRight);

                QLinearGradient LedGradient(LedRect.topLeft(),LedRect.bottomLeft());
//                LedGradient.setColorAt(0.0,PYL_QUI_START_COLOR);
//                LedGradient.setColorAt(1.0,PYL_QUI_END_COLOR);

                LedGradient.setColorAt(0.0,this->myledColor1);
                LedGradient.setColorAt(1.0,this->myledColor2);

                painter->setBrush(LedGradient);
                painter->drawRoundedRect(LedRect,PYL_RECT_RADIUS,PYL_RECT_RADIUS);
            }

DoNothing:
           ;
        }
    }

    painter->restore();

}

void myNewLed::setNumber(int num)
{
    m_nNum = num;
    update();
}
