#include "widget.h"
#include <QApplication>
#include <QImage>
#include <QMap>
#include <QFile>
#include <iostream>
#include <QDebug>
#include <string>
using namespace std;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    quint32 value;
    QImage image("C:/Users/fzyz_sb/Desktop/readfile/2.png"), outImage;
    QMap<QString, QString> map, outMap;
    map["red"] = "RED";
    map["green"] = "GREEN";
    map["blue"] = "BLUE";

    QFile file("facts.dat");
    if (!file.open(QIODevice::WriteOnly)) {
        cerr << "cannot open file for writing:"
             << qPrintable(file.errorString()) << endl;
        return 1;
    }
    //写入二进制文件
    QDataStream out(&file);
    out.setVersion(QDataStream::Qt_5_3);
    out << quint32(0x12345678) << image << map;
    file.close();

    QFile outFile("facts.dat");
    if (!outFile.open(QIODevice::ReadOnly)) {
        cerr << "cannot open file for reading:"
             << qPrintable(outFile.errorString()) << endl;
        return 1;
    }
    //读取二进制文件
    QDataStream in(&outFile);
    in.setVersion(QDataStream::Qt_5_3);
    in >> value >> outImage >> outMap;

    qDebug() << "value is:" << value;
    qDebug() << outMap["blue"] << " " << outMap["red"] << " " << outMap["green"] << endl;

    return a.exec();
}
