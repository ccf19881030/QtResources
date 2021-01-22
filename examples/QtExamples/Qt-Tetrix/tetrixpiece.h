#ifndef TETRIXPIECE_H
#define TETRIXPIECE_H

//改形状的顺序与coordsTable所对应的形状一致
enum TetrixShape {NOShape,IShape,OShape,TShape,LShape,JShape,SShape,ZShape};
//朝向 coordsTable 从上之下的朝向均为顺时针
enum TetrixDirection {UP,RIGHT,DOWN,LEFT};
//Size
enum TetrixSize{SquareHeight = 20 , SquareWidth = 20};

class TetrixPiece
{
public:
    //初始化
    TetrixPiece(){setShape(NOShape);}
    //设置Shape
    void setShape(TetrixShape tetrixShape,TetrixDirection tetrixDirection = UP);
    void setRandomShape();
    TetrixShape shape(){return pieceShape;}
    TetrixDirection direction(){return pieceDirection;}
    //顺时针旋转
    TetrixPiece rotateRight() const;
    //逆时针选择
    TetrixPiece rotateLeft() const;
    int value(int x, int y) const {return coords[x][y];}
    int getHeight() const;
    int getWidth() const;
    int x() const;
    int y() const;


private:
    TetrixShape pieceShape;
    TetrixDirection pieceDirection;
    //当前形状
    int coords[4][4];
};

#endif // TETRIXPIECE_H
