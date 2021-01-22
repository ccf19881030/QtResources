#include "ticker.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Ticker ticker;
    ticker.setWindowTitle(QObject::tr("Ticker"));
    ticker.setText(QObject::tr("How long it lasted was impossible to "
                                   "say ++ "));
    ticker.show();

    return a.exec();
}
