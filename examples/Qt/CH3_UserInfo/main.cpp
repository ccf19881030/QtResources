#include "userinfo.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    UserInfo w;
    w.show();

    return a.exec();
}
