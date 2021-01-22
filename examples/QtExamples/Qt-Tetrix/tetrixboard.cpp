#include "tetrixboard.h"
#include "tetrixpiece.h"

#include <QPainter>
#include <QDebug>
#include <QKeyEvent>
#include <QTimerEvent>
#include <QPixmap>
#include <QPainter>
#include <QLabel>
#include <QPointer>
#include <QSize>

//颜色的数序与定义的形状顺序一直
static const QRgb colorTable[8] = {
    0x000000, 0xCC6666, 0x66CC66, 0x6666CC,
    0xCCCC66, 0xCC66CC, 0x66CCCC, 0xDAAA00
};

TetrixBoard::TetrixBoard(QWidget *parent) :
    QFrame(parent)
{
    setFrameStyle(QFrame::NoFrame);
    setFocusPolicy(Qt::StrongFocus);
    clearBoard();
    isPaused = false;
    isStarted = false;
    nextPiece.setRandomShape();
}


void TetrixBoard::start(){
    if(isPaused){
        return;
    }
    isStarted = true;
    clearBoard();
    newPiece();

    level = 1;
    score = 0;

    emit levelChanged(level);
    emit scoreChanged(score);

    timer.start(1000/level,this);
}

void TetrixBoard::setNextPieceLabel(QLabel *label){
    nextPieceLabel = label;
}

void TetrixBoard::showNextPiece(){
    if(!nextPieceLabel){
        return;
    }

    QPixmap pixmap(nextPiece.getWidth() * SquareWidth , nextPiece.getHeight() * SquareHeight);
    QPainter painter(&pixmap);
    painter.fillRect(pixmap.rect(),nextPieceLabel->palette().background());
    for(int i = 0; i < 4; i++){
        for(int j = 0; j < 4; j++){
            if(nextPiece.value(i,j) == 0){
                continue;
            }
            int x = (j - nextPiece.x()) * SquareWidth;
            int y = (i - nextPiece.y())  * SquareHeight;
            drawSquare(painter,x,y,nextPiece.shape());
        }
    }
    nextPieceLabel->setPixmap(pixmap);
}

void TetrixBoard::paintEvent(QPaintEvent *event){

    QFrame::paintEvent(event);
    QPainter painter(this);
    painter.setPen(Qt::gray);
    //游戏边框
    painter.drawRect(GameBoardBorder - 1,GameBoardBorder - 1,SquareWidth * BoardWidth + 1,SquareHeight * BoardHeight + 1);

    //画出已经存在的形状
    for(int i = 0; i < BoardHeight; i++){
        for(int j = 0; j < BoardWidth; j++){
            TetrixShape shape = shapeAt(j,i);
            if(shape != NOShape){
                int x = GameBoardBorder + j * SquareWidth;
                int y = GameBoardBorder + i * SquareHeight;
                drawSquare(painter, x, y,shape);
            }
        }
    }

    //画出当前的形状
    for(int i = 0; i < 4; i++){
        for(int j = 0; j < 4; j++){
            if(currentPiece.value(i,j) == 0){
                continue;
            }
            int x = (j - currentPiece.x() + curX) * SquareWidth + GameBoardBorder;
            int y = (i - currentPiece.y() + curY) * SquareHeight + GameBoardBorder;
            drawSquare(painter,x,y,currentPiece.shape());
        }
    }
    //暂停
    if(isPaused){
        painter.setPen(QColor(Qt::green).light());
        painter.drawText(contentsRect(),Qt::AlignCenter,tr("Pause"));
        return;
    }

 }

void TetrixBoard::keyPressEvent(QKeyEvent *event){
    if(!isStarted || isPaused || currentPiece.shape() == NOShape){
        return;
    }
    switch(event->key()){
    case Qt::Key_Left:
        tryMove(currentPiece,curX - 1,curY);
        break;
    case Qt::Key_Right:
        tryMove(currentPiece,curX + 1,curY);
        break;
    case Qt::Key_Down:
        if(!tryMove(currentPiece,curX,curY+1)){
            pieceDroped();
        }
        break;
    case Qt::Key_J:
        tryMove(currentPiece.rotateLeft(),curX,curY);
        break;
    case Qt::Key_Up:
        tryMove(currentPiece.rotateRight(),curX,curY);
        break;
    case Qt::Key_Space:
        dropDown();
        break;
    default:
        //事件传递
        QFrame::keyPressEvent(event);
    }
}

void TetrixBoard::timerEvent(QTimerEvent *event){
    if(timer.timerId() == event->timerId()){
        if(!tryMove(currentPiece,curX,curY+1)){
            pieceDroped();
        }
    }else{
        QFrame::timerEvent(event);
    }
}

void TetrixBoard::dropDown(){
    int newY = curY;
    while(newY < BoardHeight){
        if(!tryMove(currentPiece,curX,curY+1)){
            break;
        }
        ++newY;
    }
    pieceDroped();
}

void TetrixBoard::pieceDroped(){
    //无法移动，则根据当前位置将方块赋值到board
    for(int i = 0; i < 4; i++){
        for(int j = 0; j < 4; j++){
            if(currentPiece.value(i,j) == 0){
                continue;
            }
            shapeAt(j - currentPiece.x() + curX,i - currentPiece.y() + curY) = currentPiece.shape();
        }
    }
    removeFullLines();
    newPiece();
}

void TetrixBoard::removeFullLines(){

    int numFullLines = 0;

    for(int i = 0; i < BoardHeight; i++){
        bool isFullLine = true;
        for(int j = 0; j < BoardWidth; j++){
            if(shapeAt(j,i) == NOShape){
                isFullLine = false;
                break;
            }
        }
        if(isFullLine){
            //消除当前的满行
            ++ numFullLines;
            for(int j = 0; j < BoardWidth; j++){
                shapeAt(j,i) = NOShape;
            }
            //将上一行的数据向下移动一行
            for(int k = i; k > 0; k--){
                for(int j = 0; j < BoardWidth; j++){
                    shapeAt(j,k) = shapeAt(j,k - 1);
                }
            }
        }
    }

    //关卡分数计算
    if(numFullLines > 0){
        score += numFullLines;
        emit scoreChanged(score);
        if( score - (level - 1) * 25 >=  25){
            ++level;
            timer.start(1000/level,this);
            emit levelChanged(level);
        }
        update();
    }


}

void TetrixBoard::newPiece(){
    currentPiece = nextPiece;
    nextPiece.setRandomShape();
    showNextPiece();
    curX = BoardWidth / 2 - 1 ;
    curY = 0;

    //如果无法移动表示已经到达顶部
    if(!tryMove(currentPiece,curX,curY)){
        currentPiece.setShape(NOShape);
        timer.stop();
        isStarted = false;
    }
}

void TetrixBoard::clearBoard(){
    for(int i = 0; i < BoardHeight; i++){
        for(int j = 0; j < BoardWidth; j++){
            coordsBoard[j][i] = NOShape;
        }
    }
}

//暂停
void TetrixBoard::pause(){
    if(!isStarted){
        return;
    }
    isPaused = !isPaused;
    if(isPaused){
        timer.stop();
    }else{
        timer.start(1000/2,this);
    }
    update();
}

bool TetrixBoard::tryMove(const TetrixPiece &newPiece, int newX, int newY){
    //newPiece 由const 修饰，则只能访问实用const 修饰的成员函数或者方法
    //是否越界
    if((newPiece.getHeight() + newY) > BoardHeight){
        return false;
    }else if((newPiece.getWidth() + newX) > BoardWidth || newX < 0){
        return false;
    }else{
        for(int i = 0; i < 4; i++){
            for(int j = 0; j < 4; j++){
                //如果模型中的值为零，则跳过
                if(newPiece.value(i,j) == 0){
                    continue;
                }
                if(shapeAt(j - currentPiece.x() + newX , i - currentPiece.y() + newY) != NOShape){
                    return false;
                }
            }
        }
    }

    currentPiece = newPiece;
    curX = newX;
    curY = newY;
    update();
    return true;
}

void TetrixBoard::drawSquare(QPainter &painter, int x, int y, TetrixShape shape){
    QColor color = colorTable[(int)shape];
    //实用颜色填充方块
    painter.fillRect(x + 1 , y + 1 , SquareWidth - 2, SquareHeight -2,color);
    //设置颜色为浅色
    painter.setPen(color.light());
    painter.drawLine(x , y + SquareHeight - 1 ,x , y);
    painter.drawLine(x , y , x + SquareWidth - 1 , y);
    painter.setPen(color.dark());
    //x + 1 y + 1是由于已经存在浅色的线条 -1 表示将像素宽度为1的线条画在方块内部
    painter.drawLine(x + 1, y + SquareHeight - 1,x + SquareWidth - 1 , y + SquareHeight - 1);
    painter.drawLine(x + SquareWidth - 1 , y + SquareHeight -1 ,x + SquareWidth - 1, y + 1);

}

