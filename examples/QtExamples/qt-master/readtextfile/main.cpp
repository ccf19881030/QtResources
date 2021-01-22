#include "widget.h"
#include <QApplication>
#include <QFile>
#include <iostream>
#include <QTextStream>
#include <string>
#include <QDebug>
using namespace std;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QFile inFile("input.txt");
    QFile outFile("output.txt");
    QTextStream inFileStream(&inFile);
    QTextStream outFileStream(&outFile);

    if (!inFile.open(QIODevice::ReadWrite)) {
        cerr << "cannot open file:" << endl;
        return 1;
    }
    inFileStream << "hello\nworld\ni\nlove\nthis\nworld\nand";
    inFileStream.seek(0);
    if ( !outFile.open(QIODevice::ReadWrite)) {
        cerr << "cannot open file:" << endl;
        return 1;
    }

    while (!inFileStream.atEnd()) {
        outFileStream << inFileStream.readLine() << endl;
    }
    outFileStream.seek(0);
    while (!outFileStream.atEnd()) {
        qDebug() << outFileStream.readLine();
    }
    inFile.close();
    outFile.close();

    return a.exec();
}
