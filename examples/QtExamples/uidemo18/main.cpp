#include "qapplication.h"
#include "appinit.h"
#include "uidemo18.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setFont(QFont("Microsoft Yahei", 10));
    AppInit::Instance()->start();

    UIDemo18 w;
    w.show();

    return a.exec();
}
