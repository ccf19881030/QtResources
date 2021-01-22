#include "wnd.h"
#include <QApplication>


int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    Q_INIT_RESOURCE(navbar);

    Wnd wnd;
    wnd.show();
    
    return app.exec();
}
