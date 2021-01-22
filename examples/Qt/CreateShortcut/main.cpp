#include "createshortcut.h"
#include <QApplication>

int main(int argc, char *argv[]){
    QApplication a(argc, argv);
    createShortcut w;
    w.show();

    return a.exec();
}
