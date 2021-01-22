#include <QCoreApplication>
#include <QList>
#include <iostream>
#include <vector>
using namespace std;

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QList<double> list;
    list.push_back(1);
    list.push_back(2);
    list.push_back(3);
    list.push_back(4);
    list.push_front(-1);
    list.push_front(-2);
    list.push_front(-3);
    list.push_front(-4);

    //java风格
    QListIterator<double> i(list);
    //不用qDebug，因为其会自动换行
    //向后迭代输出
    while (i.hasNext()) {
        cout << i.next() << " ";
    }
    cout << endl;
    //向前迭代输出
    i = list;
    i.toBack();
    while (i.hasPrevious()) {
        cout << i.previous() << " ";
    }
    cout << endl;

    //STL风格
    //向后迭代输出
    vector<double> dvec(list.begin(), list.end());
    vector<double>::iterator beg = dvec.begin();
    for (; beg != dvec.end(); beg++) {
        cout << *beg << " ";
    }
    cout << endl;
    //向前迭代输出
    vector<double>::reverse_iterator rbeg = dvec.rbegin();
    for (; rbeg != dvec.rend(); rbeg++) {
        cout << *rbeg << " ";
    }
    cout << endl;

    return a.exec();
}
