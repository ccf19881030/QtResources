#include <QApplication>
#include <stdlib.h>
#include <QDebug>
#include <QTime>
#include "tetrixwindow.h"
#include "tetrixboard.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    TetrixWindow window;
    window.show();

//    TetrixBoard board;
//    board.resize(380,620);
//    board.start();
//    board.show();

    //初始化随机数种子
    qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));

    return app.exec();
}
