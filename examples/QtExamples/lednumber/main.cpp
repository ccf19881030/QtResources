#include "frmlednumber.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    frmLedNumber w;
    w.show();

    return a.exec();
}
