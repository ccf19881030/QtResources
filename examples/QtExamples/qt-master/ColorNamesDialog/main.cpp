#include "colornamesdialog.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ColorNamesDialog w;
    w.show();

    return a.exec();
}
