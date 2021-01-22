#include "frmmain.h"
#include <QApplication>
#include <QTranslator>
#include "myhelper.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    //设置字符编码和外观样式
    myHelper::SetUTF8Code();
    myHelper::SetStyle();

    //加载中文字符
    QTranslator translator;
    translator.load(":/qt_zh_CN.qm");
    a.installTranslator(&translator);

    frmMain w;
    w.show();

    return a.exec();
}
