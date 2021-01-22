#include "frmmain.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    qApp->setFont(QFont("Microsoft YaHei",12));
    frmMain w;
    w.show();

    return a.exec();
}
