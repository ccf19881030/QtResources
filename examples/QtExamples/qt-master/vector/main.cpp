#include <QCoreApplication>
#include <QVector>
#include <QDebug>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QVector<double> vect;

    //通过[]操作符--知道大小情况下
    vect.resize(3);
    vect[0] = 1.0;
    vect[1] = 2.0;
    vect[2] = 3.0;

    //通过append--不知道大小情况下
    vect.append(4.0);
    vect.append(5.0);
    vect.append(6.0);

    //通过<<操作符
    vect << 7.0 << 8.0 << 9.0;

    for (int i = 0; i < vect.size(); ++i) {
        qDebug() << vect[i];
    }


    return a.exec();
}
