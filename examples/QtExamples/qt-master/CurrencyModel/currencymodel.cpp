#include "currencymodel.h"
#include "ui_currencymodel.h"

CurrencyModel::CurrencyModel(QWidget *parent) :
    QAbstractTableModel(parent),
    ui(new Ui::CurrencyModel)
{
}

CurrencyModel::~CurrencyModel()
{
    delete ui;
}

void CurrencyModel::setCurrencyMap(const QMap<QString, double> &map)
{
    currencyMap = map;
}

int CurrencyModel::rowCount(const QModelIndex &parent) const
{
    return currencyMap.count();
}
int CurrencyModel::columnCount(const QModelIndex &parent) const
{
    return currencyMap.count();
}

//role为角色，不同的角色执行不同的动作,通过索引index来进行数据的读取
QVariant CurrencyModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid()) {
        return QVariant();
    }

    //返回于数字匹配的对其模式
    if (role == Qt::TextAlignmentRole) {
        return int(Qt::AlignRight | Qt::AlignVCenter);
    } else if (role == Qt::DisplayRole) {   //否则，返回数据
        QString rowCurrency = currencyAt(index.row());
        QString columnCurrency = currencyAt(index.column());

        //0不能被除
        if (currencyMap.value(rowCurrency) == 0.0) {
            return "####";
        }

        double amount = currencyMap.value(columnCurrency)
                / currencyMap.value(rowCurrency);

        return QString("%1").arg(amount, 0, 'f', 4);
    }

    return QVariant();
}

//用于对其边框的头列和头行
QVariant CurrencyModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role != Qt::DisplayRole) {
        return QVariant();
    }

    return currencyAt(section);
}

QString CurrencyModel::currencyAt(int offset) const
{
    return (currencyMap.begin() + offset).key();
}
