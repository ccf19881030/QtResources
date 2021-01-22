#include<QApplication>
#include"Calculator.h"
#include<QTextCodec>
#include<qtranslator.h>
#include<QSettings>
int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    app.setOrganizationName("Trolltech");
    app.setApplicationName("Calculator");
    //QTextCodec::setCodecForTr(QTextCodec::codecForLocale());
    QTranslator qt_translator,app_translator;
    qt_translator.load("qt_zh_CN");
    app_translator.load("Chinese");
    QSettings settings;
    bool isEnglish=settings.value("language",0).toBool();  //设置应用程序的语言
    if(isEnglish==false)
    {
        app.installTranslator(&qt_translator);
        app.installTranslator(&app_translator);
    }
    Calculator *calculator=new Calculator;
    calculator->show();
    return app.exec();
}
