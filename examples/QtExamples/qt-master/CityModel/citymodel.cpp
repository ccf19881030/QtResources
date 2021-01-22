#include "citymodel.h"
#include "ui_citymodel.h"

CityModel::CityModel(QObject *parent) :
    QAbstractTableModel(parent),
    ui(new Ui::CityModel)
{
}

void CityModel::setCities(const QStringList &cityNames)
{
    cities = cityNames;
    //用于存储城市之间的距离
    distances.resize(cities.count() * (cities.count() - 1) / 2);
    distances.fill(0);
}

int CityModel::rowCount(const QModelIndex & /* parent */) const
{
    return cities.count();
}

int CityModel::columnCount(const QModelIndex & /* parent */) const
{
    return cities.count();
}

QVariant CityModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    //当为对其模式的时候，则对其table表
    if (role == Qt::TextAlignmentRole) {
        return int(Qt::AlignRight | Qt::AlignVCenter);
    } else if (role == Qt::DisplayRole) {
        //为同一个城市，则距离为0
        if (index.row() == index.column())
            return 0;
        //得到不同城市之间的距离
        int offset = offsetOf(index.row(), index.column());
        return distances[offset];
    }
    return QVariant();
}

//用户编辑一项的时候，会触发setData
bool CityModel::setData(const QModelIndex &index,
                        const QVariant &value, int role)
{
    if (index.isValid() && index.row() != index.column()
            && role == Qt::EditRole) {
        int offset = offsetOf(index.row(), index.column());
        distances[offset] = value.toInt();

        //createIndex()函数用于产生一个模型索引。我们需要使用它获得主对角线另外一侧和当前
        //正在被设置的项所对应项的模型索引，参数顺序是行号在列好之前，所以我们得颠倒一下顺序：column，row
        QModelIndex transposedIndex = createIndex(index.column(),
                                                  index.row());
        //修改整个区域(index,index)来刷新界面
        emit dataChanged(index, index);
        emit dataChanged(transposedIndex, transposedIndex);
        return true;
    }
    return false;
}

QVariant CityModel::headerData(int section,
                               Qt::Orientation /* orientation */,
                               int role) const
{
    if (role == Qt::DisplayRole)
        return cities[section];
    return QVariant();
}

Qt::ItemFlags CityModel::flags(const QModelIndex &index) const
{
    //只有不是同一个城市，才能编辑其距离
    Qt::ItemFlags flags = QAbstractItemModel::flags(index);
    if (index.row() != index.column())
        flags |= Qt::ItemIsEditable;
    return flags;
}

int CityModel::offsetOf(int row, int column) const
{
    if (row < column)
        qSwap(row, column);
    //二维数组的索引下标
    return (row * (row - 1) / 2) + column;
}
