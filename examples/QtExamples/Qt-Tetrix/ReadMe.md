####俄罗斯方块简单实现
--------------------
http://git.oschina.net/liujiaxingemail/Tetrix/wikis/home

#####思路：

* [画小方块，2D效果](#one)。
* [方块模型，三维数组](#two)。
* [绘制方块，方向颜色](#three)。
* [方块移动，方向变换](#four)。
* [游戏边框，越界判断](#five)。
* [记录方块，满行判断](#six)。
* [界面布局，效果显示](#seven)。

#####实现（下内容只截取了部分重要的函数做说明，但是整体的思路是完整的。具体的请看代码，代码中也有注释。）：

##### <a id="one">画小方块，2D效果。</a>

1. 创建一个继承于QFrame的类TetrixBoard,创建方法
    ```C++
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
    ```
    * x,y为相对于TetrixBoard左上角（0,0）的位置，TetrixShape为枚举常量，只是用来在Color数组ColorTable中选取颜色。
    * 首先让出边框，并实用颜色填充。设置填充颜色为浅色笔画小方块的上面横线和左边竖线，深色画笔画右边竖线和底部横线。
    * 这样就可以画出一个宽为SquareWidht，高为SquareHeight的正方型，且看起来有2D效果。
    * 定义好常量之后，可以直接重写paintEvent(QPaintEvent *event)方法中实用，并可以直接实例化TetrixBoard看到效果。

	
	
##### <a id="two">方块模型，三维数组。</a>

1. 创建TetrixPiece类，定义一个静态的static const int coordsTable[8][4][4][4]三位数组，具体参照源码，没有复杂的变化与计算，一目了然。1表示有值，0表示无值，有值才画。
2. TetrixShape枚举一 一对应对于三维数组的8种形状，TetrixDirection为每个方块的四种形状
3. ```C++
    void TetrixPiece::setShape(TetrixShape tetrixShape,TetrixDirection tetrixDirection){
        for(int i = 0; i < 4; i++){
            for(int j = 0; j < 4; j++){
                coords[i][j] = coordsTable[tetrixShape][tetrixDirection][i][j];
            }
        }
    
        pieceShape = tetrixShape;
        pieceDirection = tetrixDirection;
    
    }
    
    void TetrixPiece::setRandomShape(){
        setShape(TetrixShape( qrand() % 7 + 1),TetrixDirection(qrand() % 4));
    }
   ```

    * 当前模型数组int coords[4][4]，根据形状、方向给其赋值。
    * 使用qrand() % 7 可以获取0-6的随机数，piectShape、pieceDirection记录当前属性值。

##### <a id="three">绘制方块，方向颜色。</a>

1. 在TetrixBoard中创建TetrixPiece对象，并在TetrixBoard的初始化函数中，给TeitixPiece初始化赋值
2. ```C++
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
   ```

    * currentPiece为初始化的TetirxPiece
    * value(x,y)函数用来取值如果为1则画方块，如果为0则不画。
    * currentPiece.x()与currentPiece.y()分别表示模型中的左边的空列和顶部的空行，在该步骤中可以忽略。如果不减去的画，在移动时会发现无法将方块移动到边缘。
    * curX、curY标示的是当前方块的位置，GameBoardBoarder常量主要是边框，在此步骤中，改值可以忽略掉。currentPiece.shape()只为选取颜色而存在。
    * 写到此处就可以画出一个无法移动的完整的方块了。
    
##### <a id="four">方块移动，方向变换。</a>
 
1. 方块的移动，就是改变当前位置curX、curY并且调用update()->paintEvent()重新绘制。而方向的改变只是当前模型的变化。
2.  ```C++
    bool TetrixBoard::tryMove(const TetrixPiece &newPiece, int newX, int newY){
        currentPiece = newPiece;
        curX = newX;
        curY = newY;
        update();
        return true;
    }
   ```

    * 在此步骤下该方法只需要这么多，相对于源码去除的地方只是边界的判断。
    
2. 事件处理

   ```C++
    void TetrixBoard::keyPressEvent(QKeyEvent *event){
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
    ```
    * currentPiece.rotateLeft(),currentPiece.rotateRight()这两个方法就是用来改变当前方块的方向
    * 旋转的实现方式先设置好形状和方向，然后在三维数组中找到需要的二维数组模型。

##### <a id="five">游戏边框，越界判断。</a>

1. 对于边界判断

    ```C++
    bool TetrixBoard::tryMove(const TetrixPiece &newPiece, int newX, int newY){
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
    ```
    * BoardHeight、BoardWidth分别是整个游戏的行高和列宽。简单点说就是方块的可移动范围都是在TetrixShape coordsBoard[BoardWidth][BoardHeight];这样一个二维数组中变化。
    * 在coordsBoard是否有值的判断
    
    ```C++
        TetrixShape &shapeAt(int x, int y){return coordsBoard[x][y];}
    ```
    * 该方法主要是根据x,y看coordsboard中是否有值，有值则表示无法移动，返回false
    * 而此处调用时的计算，主要是由于currentPiece.x(),currentPiece.y()返回真实的模型位置。

##### <a id="six">记录方块，满行判断。</a>
* 在无法移动之后，则调用方法
    ```C++
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
    ```

    * dropDown的处理主要是用于瞬间落下的效果，按空格键可触发。
    * pieceDroped则是将当前无法移动的每个小放宽赋值到界面数组中

* 得分计算
    ```C++
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
    ```

    * 第一个外层的for循环是行，里面的是列，首先判断该行是否全部为空，如果不是则将其全部赋值为NOShape。
    * 在消除后要将消除上方的方块全部往下移动一行。
    * numFullLines只是记录当前消除的行数，根据numFullLines计算出分数，然后在每25分一关的记录。
    * emit scoreChanged(score);  emit levelChanged(level);是实用信号槽来改变界面上的值。

##### <a id="seven">界面布局，效果显示</a>
* 在写完逻辑代码后，就需要有个主窗体了，这个可以随意使用QMainWindow或者QWidget。
* 省略了很多方法，但是主要的思路就是这些，主要是理解整个思路，然后按照自己的理解开发。
* 界面的逻辑比较单一，主要就是布局好，然后连上信号槽就Ok了。组件我都去除边框，并且固定了大小。希望一起交流。