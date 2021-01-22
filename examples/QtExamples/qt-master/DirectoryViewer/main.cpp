#include "directoryviewer.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    DirectoryViewer w;
    w.show();

    return a.exec();
}
