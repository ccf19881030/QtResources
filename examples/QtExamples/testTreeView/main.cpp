#include <QApplication>
#include "mainwindow.h"
#include "TreeView.h"
#include <QTextCodec>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    //QTextCodec::setCodecForTr(QTextCodec::codecForName(QTextCodec::codecForLocale()->name()));
    //QTextCodec::setCodecForLocale(QTextCodec::codecForName(QTextCodec::codecForLocale()->name()));
   // QTextCodec::setCodecForCStrings(QTextCodec::codecForName(QTextCodec::codecForLocale()->name()));

    MainWindow w;
    w.show();
//    TreeView view;
//    view.iterateOverItems();
//    view.show();
    
    return a.exec();
}
