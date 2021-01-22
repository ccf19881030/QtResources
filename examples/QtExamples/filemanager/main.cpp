#include <QtWidgets>
#include <QFileDialog>
#include <QTranslator>
#include <QTextCodec>
#include "fileview.h"

int main(int argc, char *argv[])
{

    QApplication a(argc, argv);

    QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));
     //QTextCodec::setCodecForTr(QTextCodec::codecForName("UTF-8"));
    //QTextCodec::setCodecForCStrings(QTextCodec::codecForName("UTF-8"));
    QTranslator translator(0);
    translator.load("filemanager_zh",".");
    a.installTranslator(&translator);

    QTranslator qttranslator(0);
    qttranslator.load("qt_zh_CN",".");
    a.installTranslator(&qttranslator);

    QTranslator fileinfotranslator(0);
    fileinfotranslator.load("qfile_zh",".");
    a.installTranslator(&fileinfotranslator);


    fileview w;

    QFont font;
    font.setPointSize(12);
    font.setFamily(("wenquanyi"));

    a.setFont(font);


    w.show();


    return a.exec();
}
