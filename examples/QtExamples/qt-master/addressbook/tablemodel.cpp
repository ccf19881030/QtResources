#include "tablemodel.h"

TableModel::TableModel(QObject *parent)
    : QAbstractTableModel(parent)
{
}

TableModel::TableModel(QList<QPair<QString, QString> > pairs, QObject *parent)
    : QAbstractTableModel(parent)
{
    listOfPairs = pairs;
}

//Q_UNUSED宏定义的作用为：避免不适用parent而编译情况下产生告警
int TableModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return listOfPairs.size();
}

int TableModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return 2;
}

//返回名字或者地址（要读取的数据的行号和列号均存储在QModelIndex中）
QVariant TableModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    //读取的数据应该在有效范围内，而listOfPairs代表所储存的数据
    if (index.row() >= listOfPairs.size() || index.row() < 0)
        return QVariant();

    if (role == Qt::DisplayRole) {
        QPair<QString, QString> pair = listOfPairs.at(index.row());

        //如果为第一列，则返回name，否则返回address
        if (index.column() == 0)
            return pair.first;
        else if (index.column() == 1)
            return pair.second;
    }
    return QVariant();
}

//用于实现表头信息：姓名和地址
QVariant TableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role != Qt::DisplayRole)
        return QVariant();

    if (orientation == Qt::Horizontal) {
        switch (section) {
            case 0:
                return tr("Name");

            case 1:
                return tr("Address");

            default:
                return QVariant();
        }
    }
    return QVariant();
}

//在指定的position行上插入rows行
bool TableModel::insertRows(int position, int rows, const QModelIndex &index)
{
    Q_UNUSED(index);
    //beginInsertRows的作用是开始一个插入行的操作（类似初始化操作，具体请参考QT助手）
    beginInsertRows(QModelIndex(), position, position + rows - 1);

    for (int row = 0; row < rows; ++row) {
        QPair<QString, QString> pair(" ", " ");
        listOfPairs.insert(position, pair); //在listOfPairs中初始化rows行
    }

    endInsertRows();
    return true;
}

//删除从第position行开始的rows行
bool TableModel::removeRows(int position, int rows, const QModelIndex &index)
{
    Q_UNUSED(index);
    beginRemoveRows(QModelIndex(), position, position + rows - 1);

    for (int row = 0; row < rows; ++row) {
        listOfPairs.removeAt(position);
    }

    endRemoveRows();
    return true;
}

//修改特定某行某列的数据（行号和列号由QModelIndex导出）
bool TableModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (index.isValid() && role == Qt::EditRole) {
        int row = index.row();

        //找到要修改的行数据--这里p是副本
        QPair<QString, QString> p = listOfPairs.value(row);

        if (index.column() == 0)
            p.first = value.toString();
        else if (index.column() == 1)
            p.second = value.toString();
        else
            return false;

        listOfPairs.replace(row, p);
        //引发信号：数据已经被修改
        emit(dataChanged(index, index));

        return true;
    }

    return false;
}

//返回项目标志（用于表明table是可编辑的--在此程序中没有用到，为了后期的扩展）
Qt::ItemFlags TableModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return Qt::ItemIsEnabled;

    return QAbstractTableModel::flags(index) | Qt::ItemIsEditable;
}

QList< QPair<QString, QString> > TableModel::getList()
{
    return listOfPairs;
}
