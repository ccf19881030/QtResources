#include "window.h"
#include <QApplication>
#include <QStandardItemModel>
#include <QTime>

void addMail(QAbstractItemModel *model, const QString &subject,
             const QString &sender, const QDateTime &date)
{
    model->insertRow(0);
    //这里是在model的第0行0，1，2列插入数据--则会将数据插入到sourceGroupBox中去
    model->setData(model->index(0, 0), subject);
    model->setData(model->index(0, 1), sender);
    model->setData(model->index(0, 2), date);
}

QAbstractItemModel *createMailModel(QObject *parent)
{
    QStandardItemModel *model = new QStandardItemModel(0, 3, parent);

    model->setHeaderData(0, Qt::Horizontal, QObject::tr("Subject"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Sender"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Date"));

    addMail(model, "Happy New Year!", "Grace K. <grace@software-inc.com>",
            QDateTime(QDate(2006, 12, 31), QTime(17, 03)));
    addMail(model, "Radically new concept", "Grace K. <grace@software-inc.com>",
            QDateTime(QDate(2006, 12, 22), QTime(9, 44)));
    addMail(model, "Accounts", "pascale@nospam.com",
            QDateTime(QDate(2006, 12, 31), QTime(12, 50)));
    addMail(model, "Expenses", "Joe Bloggs <joe@bloggs.com>",
            QDateTime(QDate(2006, 12, 25), QTime(11, 39)));
    addMail(model, "Re: Expenses", "Andy <andy@nospam.com>",
            QDateTime(QDate(2007, 01, 02), QTime(16, 05)));
    addMail(model, "Re: Accounts", "Joe Bloggs <joe@bloggs.com>",
            QDateTime(QDate(2007, 01, 03), QTime(14, 18)));
    addMail(model, "Re: Accounts", "Andy <andy@nospam.com>",
            QDateTime(QDate(2007, 01, 03), QTime(14, 26)));
    addMail(model, "Sports", "Linda Smith <linda.smith@nospam.com>",
            QDateTime(QDate(2007, 01, 05), QTime(11, 33)));
    addMail(model, "AW: Sports", "Rolf Newschweinstein <rolfn@nospam.com>",
            QDateTime(QDate(2007, 01, 05), QTime(12, 00)));
    addMail(model, "RE: Sports", "Petra Schmidt <petras@nospam.com>",
            QDateTime(QDate(2007, 01, 05), QTime(12, 01)));

    return model;
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Window window;
    //将模式装载进视图中
    window.setSourceModel(createMailModel(&window));
    window.show();

    return a.exec();
}
