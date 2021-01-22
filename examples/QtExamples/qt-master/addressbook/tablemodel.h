#ifndef TABLEMODEL_H
#define TABLEMODEL_H

#include <QAbstractTableModel>
#include <QList>
#include <QPair>

/*********************
 * QAbstractTableModel为抽象类，用于实现table表格
 * 此程序中实现了N行两列的表格，用于存储姓名和地址
 * *************************/
class TableModel : public QAbstractTableModel
{
    Q_OBJECT

public:
    TableModel(QObject *parent = 0);
    TableModel(QList<QPair<QString, QString> > listofPairs, QObject *parent = 0);

    int rowCount(const QModelIndex &parent) const;
    int columnCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;
    Qt::ItemFlags flags(const QModelIndex &index) const;
    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole);
    bool insertRows(int position, int rows, const QModelIndex &index = QModelIndex());
    bool removeRows(int position, int rows, const QModelIndex &index = QModelIndex());
    QList<QPair<QString, QString> > getList();

private:
    //用于存储一个N行2列的表格内容(2列分别为姓名和地址)
    QList<QPair<QString, QString> > listOfPairs;
};

#endif // TABLEMODEL_H
