#include "frmnettool.h"
#include <QApplication>
#include "myhelper.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setWindowIcon(QIcon(":/main.ico"));
    myHelper::setCode();
    frmNetTool w;    
    w.show();

    return a.exec();
}
