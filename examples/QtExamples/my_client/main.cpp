#include "widget.h"
#include <QApplication>
//本程序由小小为制作，只是简单实现多线程通信，有很多不足之处希望大神见谅，
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget w;
    w.show();

    return a.exec();
}
