#include "frmmain.h"
#include <QApplication>
#include <QTranslator>
#include "myhelper.h"
#include "myapp.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    myHelper::SetUTF8Code();
    myHelper::SetPlastiqueStyle();

    //加载中文字符
    QTranslator translator;
    translator.load(":/qt_zh_CN.qm");
    a.installTranslator(&translator);

    myApp::ReadConfig();

    frmMain w;
    w.show();
    
    return a.exec();
}
