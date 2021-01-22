#include <QtWidgets>
#include <QTextCodec>
#include "widget.h"
#include <QDebug>
#include "connect.h"
#include "worker_init.h"
#include "worker_log.h"

QTcpSocket *tcpsocket;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    //QTextCodec::setCodecForTr(QTextCodec::codecForLocale());
    //QTextCodec::setCodecForCStrings(QTextCodec::codecForLocale());
    Widget w;
    w.show();
    
    return a.exec();
}
