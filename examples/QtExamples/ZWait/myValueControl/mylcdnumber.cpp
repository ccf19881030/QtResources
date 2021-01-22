#include "mylcdnumber.h"

myLCDNumber::myLCDNumber(QWidget *parent) :
    QWidget(parent)
{
    this->initVariables();
}

void myLCDNumber::initVariables()
{
    m_min=0;
    m_nNum=0;
}

void myLCDNumber::paintEvent(QPaintEvent *)
{
    QPainter painter;
    painter.begin(this);
    painter.setRenderHints(QPainter::Antialiasing);
    drawVariables(&painter);
    drawBackground(&painter);
    drawNumber(&painter);

}

void myLCDNumber::drawVariables(QPainter *painter)
{
    m_center=rect().center();
    m_min=qMin(width(),height());
    m_rectWidth=height()/8;
}

void myLCDNumber::drawBackground(QPainter *painter)
{
    painter->save();

    QLinearGradient bgGradient(QPointF(0,0),QPointF(0,height()));
//    bgGradient.setColorAt(0.0,Qt::transparent);
    bgGradient.setColorAt(0.0,QColor(30,30,30));
    bgGradient.setColorAt(0.5,QColor(30,30,30));
    bgGradient.setColorAt(1.0,QColor(30,30,30));
//    bgGradient.setColorAt(1.0,Qt::transparent);
    painter->setPen(Qt::NoPen);
    painter->setBrush(bgGradient);
    painter->drawRect(rect());
    painter->restore();
}

void myLCDNumber::drawNumber(QPainter *painter)
{
    painter->save();
    painter->setPen(Qt::NoPen);


    qreal space=m_rectWidth/2;

    QPointF top_leftPot(LCDNUMBER_SPACE+space,LCDNUMBER_SPACE+space);
    QPointF top_topLeftPot(top_leftPot.x()+space,LCDNUMBER_SPACE);
    QPointF top_topRightPot(width()-LCDNUMBER_SPACE-m_rectWidth,LCDNUMBER_SPACE);
    QPointF top_rightPot(width()-LCDNUMBER_SPACE-space,LCDNUMBER_SPACE+space);
    QPointF top_bottomRightPot(top_topRightPot.x(),LCDNUMBER_SPACE+m_rectWidth);
    QPointF top_bottomLeftPot(top_topLeftPot.x(),LCDNUMBER_SPACE+m_rectWidth);

    QVector<QPointF> topRectVec;
    topRectVec.push_back(top_leftPot);
    topRectVec.push_back(top_topLeftPot);
    topRectVec.push_back(top_topRightPot);
    topRectVec.push_back(top_rightPot);
    topRectVec.push_back(top_bottomRightPot);
    topRectVec.push_back(top_bottomLeftPot);
    topRectVec.push_back(top_leftPot);

    QLinearGradient topGradient(top_topLeftPot,top_bottomLeftPot);
    topGradient.setColorAt(0.0,Qt::transparent);
    topGradient.setColorAt(0.2,QColor(40,150,40));
    topGradient.setColorAt(0.5,QColor(30,230,30));
    topGradient.setColorAt(0.8,QColor(40,150,40));
    topGradient.setColorAt(1.0,Qt::transparent);

    qreal polygon_height=(height()-3*LCDNUMBER_SPACE-3*m_rectWidth)/2;

    QPointF tl_topPot(LCDNUMBER_SPACE+space,LCDNUMBER_SPACE*2+space);
    QPointF tl_topLeftPot(LCDNUMBER_SPACE,tl_topPot.y()+space);
    QPointF tl_bottomLeftPot(tl_topLeftPot.x(),tl_topLeftPot.y()+polygon_height);
    QPointF tl_bottomPot(tl_topPot.x(),tl_topPot.y()+m_rectWidth+polygon_height);
    QPointF tl_bottomRightPot(tl_bottomPot.x()+space,tl_bottomPot.y()-space);
    QPointF tl_topRightPot(tl_bottomRightPot.x(),tl_bottomRightPot.y()-polygon_height);

    QVector<QPointF> tlPotVec;
    tlPotVec.push_back(tl_topPot);
    tlPotVec.push_back(tl_topLeftPot);
    tlPotVec.push_back(tl_bottomLeftPot);
    tlPotVec.push_back(tl_bottomPot);
    tlPotVec.push_back(tl_bottomRightPot);
    tlPotVec.push_back(tl_topRightPot);
    tlPotVec.push_back(tl_topPot);

    QLinearGradient tlGradient(tl_topLeftPot,tl_topRightPot);
    tlGradient.setColorAt(0.0,Qt::transparent);
    tlGradient.setColorAt(0.2,QColor(40,150,40));
    tlGradient.setColorAt(0.5,QColor(30,230,30));
    tlGradient.setColorAt(0.8,QColor(40,150,40));
    tlGradient.setColorAt(1.0,Qt::transparent);

    QPointF bl_topPot(LCDNUMBER_SPACE+space,tl_bottomPot.y()+LCDNUMBER_SPACE);
    QPointF bl_topLeftPot(bl_topPot.x()-space,bl_topPot.y()+space);
    QPointF bl_bottomLeftPot(bl_topLeftPot.x(),bl_topLeftPot.y()+polygon_height);
    QPointF bl_bottomPot(bl_bottomLeftPot.x()+space,bl_bottomLeftPot.y()+space);
    QPointF bl_bottomRightPot(bl_bottomPot.x()+space,bl_bottomPot.y()-space);
    QPointF bl_topRightPot(bl_bottomRightPot.x(),bl_bottomRightPot.y()-polygon_height);

    QVector<QPointF> blPotVec;
    blPotVec.push_back(bl_topPot);
    blPotVec.push_back(bl_topLeftPot);
    blPotVec.push_back(bl_bottomLeftPot);
    blPotVec.push_back(bl_bottomPot);
    blPotVec.push_back(bl_bottomRightPot);
    blPotVec.push_back(bl_topRightPot);
    blPotVec.push_back(bl_topPot);

    QLinearGradient blGradient(bl_topLeftPot,bl_topRightPot);
    blGradient.setColorAt(0.0,Qt::transparent);
    blGradient.setColorAt(0.2,QColor(40,150,40));
    blGradient.setColorAt(0.5,QColor(30,230,30));
    blGradient.setColorAt(0.8,QColor(40,150,40));
    blGradient.setColorAt(1.0,Qt::transparent);

    QPointF m_leftPot(LCDNUMBER_SPACE*2+space,tl_bottomPot.y()+LCDNUMBER_SPACE/2);
    QPointF m_topLeftPot(m_leftPot.x()+space,m_leftPot.y()-space);
    QPointF m_topRightPot(top_rightPot.x()-space,m_leftPot.y()-space);
    QPointF m_rightPot(m_topRightPot.x()+space,m_topRightPot.y()+space);
    QPointF m_bottomRightPot(m_topRightPot.x(),m_rightPot.y()+space);
    QPointF m_bottomLeftPot(m_topLeftPot.x(),m_bottomRightPot.y());

    QVector<QPointF> mPotVec;
    mPotVec.push_back(m_leftPot);
    mPotVec.push_back(m_topLeftPot);
    mPotVec.push_back(m_topRightPot);
    mPotVec.push_back(m_rightPot);
    mPotVec.push_back(m_bottomRightPot);
    mPotVec.push_back(m_bottomLeftPot);
    mPotVec.push_back(m_leftPot);

    QLinearGradient mGradient(m_topLeftPot,m_bottomLeftPot);
    mGradient.setColorAt(0.0,Qt::transparent);
    mGradient.setColorAt(0.2,QColor(40,150,40));
    mGradient.setColorAt(0.5,QColor(30,230,30));
    mGradient.setColorAt(0.8,QColor(40,150,40));
    mGradient.setColorAt(1.0,Qt::transparent);

    QPointF bottom_leftPot(bl_bottomPot.x()+LCDNUMBER_SPACE,bl_bottomPot.y()+LCDNUMBER_SPACE/2);
    QPointF bottom_topLeftPot(bottom_leftPot.x()+space,bottom_leftPot.y()-space);
    QPointF bottom_topRightPot(top_topRightPot.x(),bottom_topLeftPot.y());
    QPointF bottom_rightPot(top_rightPot.x(),bottom_topRightPot.y()+space);
    QPointF bottom_bottomRightPot(bottom_rightPot.x()-space,bottom_rightPot.y()+space);
    QPointF bottom_bottomLeftPot(bottom_topLeftPot.x(),bottom_bottomRightPot.y());

    QVector<QPointF> bottomPotVec;
    bottomPotVec.push_back(bottom_leftPot);
    bottomPotVec.push_back(bottom_topLeftPot);
    bottomPotVec.push_back(bottom_topRightPot);
    bottomPotVec.push_back(bottom_rightPot);
    bottomPotVec.push_back(bottom_bottomRightPot);
    bottomPotVec.push_back(bottom_bottomLeftPot);
    bottomPotVec.push_back(bottom_leftPot);

    QLinearGradient bottomGradient(bottom_topLeftPot,bottom_bottomLeftPot);
    bottomGradient.setColorAt(0.0,Qt::transparent);
    bottomGradient.setColorAt(0.2,QColor(40,150,40));
    bottomGradient.setColorAt(0.5,QColor(30,230,30));
    bottomGradient.setColorAt(0.8,QColor(40,150,40));
    bottomGradient.setColorAt(1.0,Qt::transparent);

    QPointF tr_topPot(top_rightPot.x()+LCDNUMBER_SPACE,top_rightPot.y()+LCDNUMBER_SPACE/2);
    QPointF tr_topLeftPot(tr_topPot.x()-space,tr_topPot.y()+space);
    QPointF tr_bottomLeftPot(tr_topLeftPot.x(),tr_topLeftPot.y()+polygon_height);
    QPointF tr_bottomPot(tr_bottomLeftPot.x()+space,tr_bottomLeftPot.y()+space);
    QPointF tr_bottomRightPot(tr_bottomPot.x()+space,tr_bottomPot.y()-space);
    QPointF tr_topRightPot(tr_topPot.x()+space,tr_topPot.y()+space);

    QVector<QPointF> trPotVec;
    trPotVec.push_back(tr_topPot);
    trPotVec.push_back(tr_topLeftPot);
    trPotVec.push_back(tr_bottomLeftPot);
    trPotVec.push_back(tr_bottomPot);
    trPotVec.push_back(tr_bottomRightPot);
    trPotVec.push_back(tr_topRightPot);
    trPotVec.push_back(tr_topPot);

    QLinearGradient trGradient(tr_topLeftPot,tr_topRightPot);
    trGradient.setColorAt(0.0,Qt::transparent);
    trGradient.setColorAt(0.2,QColor(40,150,40));
    trGradient.setColorAt(0.5,QColor(30,230,30));
    trGradient.setColorAt(0.8,QColor(40,150,40));
    trGradient.setColorAt(1.0,Qt::transparent);

    QPointF br_topPot(m_rightPot.x()+LCDNUMBER_SPACE,m_rightPot.y()+LCDNUMBER_SPACE/2);
    QPointF br_topLeftPot(br_topPot.x()-space,br_topPot.y()+space);
    QPointF br_bottomLeftPot(br_topLeftPot.x(),br_topLeftPot.y()+polygon_height);
    QPointF br_bottomPot(br_bottomLeftPot.x()+space,br_bottomLeftPot.y()+space);
    QPointF br_bottomRightPot(br_bottomPot.x()+space,br_bottomPot.y()-space);
    QPointF br_topRightPot(br_topPot.x()+space,br_topPot.y()+space);

    QVector<QPointF> brPotVec;
    brPotVec.push_back(br_topPot);
    brPotVec.push_back(br_topLeftPot);
    brPotVec.push_back(br_bottomLeftPot);
    brPotVec.push_back(br_bottomPot);
    brPotVec.push_back(br_bottomRightPot);
    brPotVec.push_back(br_topRightPot);
    brPotVec.push_back(br_topPot);

    QLinearGradient brGradient(br_topLeftPot,br_topRightPot);
    brGradient.setColorAt(0.0,Qt::transparent);
    brGradient.setColorAt(0.2,QColor(40,150,40));
    brGradient.setColorAt(0.5,QColor(30,230,30));
    brGradient.setColorAt(0.8,QColor(40,150,40));
    brGradient.setColorAt(1.0,Qt::transparent);

    switch(m_nNum)
    {
    case 0:
        // top
        painter->setBrush(topGradient);
        painter->drawPolygon(QPolygonF(topRectVec));

        // top left
        painter->setBrush(tlGradient);
        painter->drawPolygon(QPolygonF(tlPotVec));

        // bottom left
        painter->setBrush(blGradient);
        painter->drawPolygon(QPolygonF(blPotVec));

        //middle
        mGradient.setColorAt(0.0,Qt::transparent);
        mGradient.setColorAt(0.2,QColor(30,30,30));
        mGradient.setColorAt(0.5,QColor(50,50,50));
        mGradient.setColorAt(0.8,QColor(30,30,30));
        mGradient.setColorAt(1.0,Qt::transparent);

        painter->setBrush(mGradient);
        painter->drawPolygon(QPolygonF(mPotVec));

        //bottom
        painter->setBrush(bottomGradient);
        painter->drawPolygon(QPolygonF(bottomPotVec));

        //top right
        painter->setBrush(trGradient);
        painter->drawPolygon(QPolygonF(trPotVec));

        // bottom right
        painter->setBrush(brGradient);
        painter->drawPolygon(QPolygonF(brPotVec));

        break;
    case 1:
        // top
        topGradient.setColorAt(0.0,Qt::transparent);
        topGradient.setColorAt(0.2,QColor(30,30,30));
        topGradient.setColorAt(0.5,QColor(50,50,50));
        topGradient.setColorAt(0.8,QColor(30,30,30));
        topGradient.setColorAt(1.0,Qt::transparent);

        painter->setBrush(topGradient);
        painter->drawPolygon(QPolygonF(topRectVec));

        // top left
        tlGradient.setColorAt(0.0,Qt::transparent);
        tlGradient.setColorAt(0.2,QColor(30,30,30));
        tlGradient.setColorAt(0.5,QColor(50,50,50));
        tlGradient.setColorAt(0.8,QColor(30,30,30));
        tlGradient.setColorAt(1.0,Qt::transparent);

        painter->setBrush(tlGradient);
        painter->drawPolygon(QPolygonF(tlPotVec));

        // bottom left
        blGradient.setColorAt(0.0,Qt::transparent);
        blGradient.setColorAt(0.2,QColor(30,30,30));
        blGradient.setColorAt(0.5,QColor(50,50,50));
        blGradient.setColorAt(0.8,QColor(30,30,30));
        blGradient.setColorAt(1.0,Qt::transparent);

        painter->setBrush(blGradient);
        painter->drawPolygon(QPolygonF(blPotVec));

        //middle
        mGradient.setColorAt(0.0,Qt::transparent);
        mGradient.setColorAt(0.2,QColor(30,30,30));
        mGradient.setColorAt(0.5,QColor(50,50,50));
        mGradient.setColorAt(0.8,QColor(30,30,30));
        mGradient.setColorAt(1.0,Qt::transparent);

        painter->setBrush(mGradient);
        painter->drawPolygon(QPolygonF(mPotVec));

        //bottom
        bottomGradient.setColorAt(0.0,Qt::transparent);
        bottomGradient.setColorAt(0.2,QColor(30,30,30));
        bottomGradient.setColorAt(0.5,QColor(50,50,50));
        bottomGradient.setColorAt(0.8,QColor(30,30,30));
        bottomGradient.setColorAt(1.0,Qt::transparent);

        painter->setBrush(bottomGradient);
        painter->drawPolygon(QPolygonF(bottomPotVec));

        //top right
        painter->setBrush(trGradient);
        painter->drawPolygon(QPolygonF(trPotVec));

        // bottom right
        painter->setBrush(brGradient);
        painter->drawPolygon(QPolygonF(brPotVec));



        break;
    case 2:
        // top
        painter->setBrush(topGradient);
        painter->drawPolygon(QPolygonF(topRectVec));

        // top left
        tlGradient.setColorAt(0.0,Qt::transparent);
        tlGradient.setColorAt(0.2,QColor(30,30,30));
        tlGradient.setColorAt(0.5,QColor(50,50,50));
        tlGradient.setColorAt(0.8,QColor(30,30,30));
        tlGradient.setColorAt(1.0,Qt::transparent);


        painter->setBrush(tlGradient);
        painter->drawPolygon(QPolygonF(tlPotVec));

        // bottom left
        painter->setBrush(blGradient);
        painter->drawPolygon(QPolygonF(blPotVec));

        //middle
        painter->setBrush(mGradient);
        painter->drawPolygon(QPolygonF(mPotVec));

        //bottom
        painter->setBrush(bottomGradient);
        painter->drawPolygon(QPolygonF(bottomPotVec));

        //top right
        painter->setBrush(trGradient);
        painter->drawPolygon(QPolygonF(trPotVec));

        // bottom right
        brGradient.setColorAt(0.0,Qt::transparent);
        brGradient.setColorAt(0.2,QColor(30,30,30));
        brGradient.setColorAt(0.5,QColor(50,50,50));
        brGradient.setColorAt(0.8,QColor(30,30,30));
        brGradient.setColorAt(1.0,Qt::transparent);


        painter->setBrush(brGradient);
        painter->drawPolygon(QPolygonF(brPotVec));



        break;
    case 3:
        // top
        painter->setBrush(topGradient);
        painter->drawPolygon(QPolygonF(topRectVec));

        // top left
        tlGradient.setColorAt(0.0,Qt::transparent);
        tlGradient.setColorAt(0.2,QColor(30,30,30));
        tlGradient.setColorAt(0.5,QColor(50,50,50));
        tlGradient.setColorAt(0.8,QColor(30,30,30));
        tlGradient.setColorAt(1.0,Qt::transparent);

        painter->setBrush(tlGradient);
        painter->drawPolygon(QPolygonF(tlPotVec));

        // bottom left
        blGradient.setColorAt(0.0,Qt::transparent);
        blGradient.setColorAt(0.2,QColor(30,30,30));
        blGradient.setColorAt(0.5,QColor(50,50,50));
        blGradient.setColorAt(0.8,QColor(30,30,30));
        blGradient.setColorAt(1.0,Qt::transparent);

        painter->setBrush(blGradient);
        painter->drawPolygon(QPolygonF(blPotVec));

        //middle

        painter->setBrush(mGradient);
        painter->drawPolygon(QPolygonF(mPotVec));

        //bottom
        painter->setBrush(bottomGradient);
        painter->drawPolygon(QPolygonF(bottomPotVec));

        //top right
        painter->setBrush(trGradient);
        painter->drawPolygon(QPolygonF(trPotVec));

        // bottom right
        painter->setBrush(brGradient);
        painter->drawPolygon(QPolygonF(brPotVec));



        break;
    case 4:
        // top
        topGradient.setColorAt(0.0,Qt::transparent);
        topGradient.setColorAt(0.2,QColor(30,30,30));
        topGradient.setColorAt(0.5,QColor(50,50,50));
        topGradient.setColorAt(0.8,QColor(30,30,30));
        topGradient.setColorAt(1.0,Qt::transparent);


        painter->setBrush(topGradient);
        painter->drawPolygon(QPolygonF(topRectVec));

        // top left
        painter->setBrush(tlGradient);
        painter->drawPolygon(QPolygonF(tlPotVec));

        // bottom left
        blGradient.setColorAt(0.0,Qt::transparent);
        blGradient.setColorAt(0.2,QColor(30,30,30));
        blGradient.setColorAt(0.5,QColor(50,50,50));
        blGradient.setColorAt(0.8,QColor(30,30,30));
        blGradient.setColorAt(1.0,Qt::transparent);


        painter->setBrush(blGradient);
        painter->drawPolygon(QPolygonF(blPotVec));

        //middle

        painter->setBrush(mGradient);
        painter->drawPolygon(QPolygonF(mPotVec));

        //bottom
        bottomGradient.setColorAt(0.0,Qt::transparent);
        bottomGradient.setColorAt(0.2,QColor(30,30,30));
        bottomGradient.setColorAt(0.5,QColor(50,50,50));
        bottomGradient.setColorAt(0.8,QColor(30,30,30));
        bottomGradient.setColorAt(1.0,Qt::transparent);


        painter->setBrush(bottomGradient);
        painter->drawPolygon(QPolygonF(bottomPotVec));

        //top right
        painter->setBrush(trGradient);
        painter->drawPolygon(QPolygonF(trPotVec));

        // bottom right
        painter->setBrush(brGradient);
        painter->drawPolygon(QPolygonF(brPotVec));


        break;
    case 5:
        // top
        painter->setBrush(topGradient);
        painter->drawPolygon(QPolygonF(topRectVec));

        // top left
        painter->setBrush(tlGradient);
        painter->drawPolygon(QPolygonF(tlPotVec));

        // bottom left
        blGradient.setColorAt(0.0,Qt::transparent);
        blGradient.setColorAt(0.2,QColor(30,30,30));
        blGradient.setColorAt(0.5,QColor(50,50,50));
        blGradient.setColorAt(0.8,QColor(30,30,30));
        blGradient.setColorAt(1.0,Qt::transparent);


        painter->setBrush(blGradient);
        painter->drawPolygon(QPolygonF(blPotVec));

        //middle
        painter->setBrush(mGradient);
        painter->drawPolygon(QPolygonF(mPotVec));

        //bottom
        painter->setBrush(bottomGradient);
        painter->drawPolygon(QPolygonF(bottomPotVec));

        //top right
        trGradient.setColorAt(0.0,Qt::transparent);
        trGradient.setColorAt(0.2,QColor(30,30,30));
        trGradient.setColorAt(0.5,QColor(50,50,50));
        trGradient.setColorAt(0.8,QColor(30,30,30));
        trGradient.setColorAt(1.0,Qt::transparent);


        painter->setBrush(trGradient);
        painter->drawPolygon(QPolygonF(trPotVec));

        // bottom right
        painter->setBrush(brGradient);
        painter->drawPolygon(QPolygonF(brPotVec));


        break;
    case 6:
        // top
        painter->setBrush(topGradient);
        painter->drawPolygon(QPolygonF(topRectVec));

        // top left
        painter->setBrush(tlGradient);
        painter->drawPolygon(QPolygonF(tlPotVec));

        // bottom left
        painter->setBrush(blGradient);
        painter->drawPolygon(QPolygonF(blPotVec));

        //middle

        painter->setBrush(mGradient);
        painter->drawPolygon(QPolygonF(mPotVec));

        //bottom
        painter->setBrush(bottomGradient);
        painter->drawPolygon(QPolygonF(bottomPotVec));

        //top right
        trGradient.setColorAt(0.0,Qt::transparent);
        trGradient.setColorAt(0.2,QColor(30,30,30));
        trGradient.setColorAt(0.5,QColor(50,50,50));
        trGradient.setColorAt(0.8,QColor(30,30,30));
        trGradient.setColorAt(1.0,Qt::transparent);

        painter->setBrush(trGradient);
        painter->drawPolygon(QPolygonF(trPotVec));

        // bottom right
        painter->setBrush(brGradient);
        painter->drawPolygon(QPolygonF(brPotVec));


        break;
    case 7:
        // top
        painter->setBrush(topGradient);
        painter->drawPolygon(QPolygonF(topRectVec));

        // top left
        tlGradient.setColorAt(0.0,Qt::transparent);
        tlGradient.setColorAt(0.2,QColor(30,30,30));
        tlGradient.setColorAt(0.5,QColor(50,50,50));
        tlGradient.setColorAt(0.8,QColor(30,30,30));
        tlGradient.setColorAt(1.0,Qt::transparent);


        painter->setBrush(tlGradient);
        painter->drawPolygon(QPolygonF(tlPotVec));

        // bottom left
        blGradient.setColorAt(0.0,Qt::transparent);
        blGradient.setColorAt(0.2,QColor(30,30,30));
        blGradient.setColorAt(0.5,QColor(50,50,50));
        blGradient.setColorAt(0.8,QColor(30,30,30));
        blGradient.setColorAt(1.0,Qt::transparent);


        painter->setBrush(blGradient);
        painter->drawPolygon(QPolygonF(blPotVec));

        //middle
        mGradient.setColorAt(0.0,Qt::transparent);
        mGradient.setColorAt(0.2,QColor(30,30,30));
        mGradient.setColorAt(0.5,QColor(50,50,50));
        mGradient.setColorAt(0.8,QColor(30,30,30));
        mGradient.setColorAt(1.0,Qt::transparent);

        painter->setBrush(mGradient);
        painter->drawPolygon(QPolygonF(mPotVec));

        //bottom
        bottomGradient.setColorAt(0.0,Qt::transparent);
        bottomGradient.setColorAt(0.2,QColor(30,30,30));
        bottomGradient.setColorAt(0.5,QColor(50,50,50));
        bottomGradient.setColorAt(0.8,QColor(30,30,30));
        bottomGradient.setColorAt(1.0,Qt::transparent);


        painter->setBrush(bottomGradient);
        painter->drawPolygon(QPolygonF(bottomPotVec));

        //top right
        painter->setBrush(trGradient);
        painter->drawPolygon(QPolygonF(trPotVec));

        // bottom right
        painter->setBrush(brGradient);
        painter->drawPolygon(QPolygonF(brPotVec));


        break;
    case 8:
        // top
        painter->setBrush(topGradient);
        painter->drawPolygon(QPolygonF(topRectVec));

        // top left
        painter->setBrush(tlGradient);
        painter->drawPolygon(QPolygonF(tlPotVec));

        // bottom left
        painter->setBrush(blGradient);
        painter->drawPolygon(QPolygonF(blPotVec));

        //middle

        painter->setBrush(mGradient);
        painter->drawPolygon(QPolygonF(mPotVec));

        //bottom
        painter->setBrush(bottomGradient);
        painter->drawPolygon(QPolygonF(bottomPotVec));

        //top right
        painter->setBrush(trGradient);
        painter->drawPolygon(QPolygonF(trPotVec));

        // bottom right
        painter->setBrush(brGradient);
        painter->drawPolygon(QPolygonF(brPotVec));


        break;
    case 9:
        // top
        painter->setBrush(topGradient);
        painter->drawPolygon(QPolygonF(topRectVec));

        // top left
        painter->setBrush(tlGradient);
        painter->drawPolygon(QPolygonF(tlPotVec));

        // bottom left
        blGradient.setColorAt(0.0,Qt::transparent);
        blGradient.setColorAt(0.2,QColor(30,30,30));
        blGradient.setColorAt(0.5,QColor(50,50,50));
        blGradient.setColorAt(0.8,QColor(30,30,30));
        blGradient.setColorAt(1.0,Qt::transparent);

        painter->setBrush(blGradient);
        painter->drawPolygon(QPolygonF(blPotVec));

        //middle

        painter->setBrush(mGradient);
        painter->drawPolygon(QPolygonF(mPotVec));

        //bottom
        painter->setBrush(bottomGradient);
        painter->drawPolygon(QPolygonF(bottomPotVec));

        //top right
        painter->setBrush(trGradient);
        painter->drawPolygon(QPolygonF(trPotVec));

        // bottom right
        painter->setBrush(brGradient);
        painter->drawPolygon(QPolygonF(brPotVec));
        break;
    }
    painter->restore();
}

void myLCDNumber::setNumber(int num)
{
    m_nNum=num;
    update();
}
