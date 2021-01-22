#include "hexspinbox.h"
#include <QApplication>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Hexspinbox w;
    w.show();

    //用来显示最初的值
    qDebug() << w.value();

    //通过信号来输出值
    QObject::connect(&w, SIGNAL(valueChanged(int)),
            &w, SLOT(debug(int)));

    return a.exec();
}
