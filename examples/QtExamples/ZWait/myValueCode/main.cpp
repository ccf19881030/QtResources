#include <QtWidgets>
#include "frmmain.h"
#include "frmdata.h"
#include "myStaticClass.h"


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    frmMain w;
    FormHelper::SetGB2312Code();
    FormHelper::SetPlastiqueStyle();
    w.show();

     return a.exec();
}
