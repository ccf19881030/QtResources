#ifndef TABLEMODEL_H
#define TABLEMODEL_H
#include <QAbstractTableModel>
#include <QVariant>

class TableModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    TableModel(QStringList header=QStringList());
    int rowCount(const QModelIndex &parent=QModelIndex()) const;
    int columnCount(const QModelIndex &parent=QModelIndex()) const;
    QVariant data(const QModelIndex &index, int role=Qt::DisplayRole) const;
   // bool setData(const QModelIndex &index, const QVariant &value, int role=Qt::DisplayRole);
    QVariant headerData(int section, Qt::Orientation orientation=Qt::Horizontal, int role=Qt::DisplayRole) const;
//    QModelIndex index(int row, int column, const QModelIndex &parent=QModelIndex()) const;

    bool insertRows(int row, int count, const QModelIndex &parent=QModelIndex());
    //bool insertColumns(int column, int count, const QModelIndex &parent=QModelIndex());
    bool removeRows(int row, int count, const QModelIndex &parent=QModelIndex());
    //bool removeColumns(int column, int count, const QModelIndex &parent=QModelIndex());
    bool addRow(QStringList row);
private:
    QList<QStringList*> userData;
    QStringList header;
};

#endif // TABLEMODEL_H
