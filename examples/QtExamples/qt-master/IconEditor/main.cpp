#include "iconeditor.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    IconEditor w;
    w.show();

    return a.exec();
}
