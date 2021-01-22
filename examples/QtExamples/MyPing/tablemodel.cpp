#include "tablemodel.h"
#include <QDebug>
#define qd qDebug()<<

TableModel::TableModel( QStringList header)
{
    this->header=header;
    //insertRows(0,255);
}

int TableModel::rowCount(const QModelIndex &parent) const
{
    return userData.count();
}

int TableModel::columnCount(const QModelIndex &parent) const
{
   // qd "columnCount()"<<header.count();
    if(header.count()>0)
        return header.count();
    else
        return 0;
}

QVariant TableModel::data(const QModelIndex &index, int role) const
{
    //qd "data()"<<index.row()<<index.column()<<role;
    if(!index.isValid())
        return QVariant();

    if(index.row()>=userData.count())
        return QVariant();
    if(role==Qt::DisplayRole)
        return userData.value(index.row())->value(index.column());
    else
        return QVariant();
}

QVariant TableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if(role!=Qt::DisplayRole)
        return QVariant();
    if(orientation==Qt::Horizontal)
        return header.value(section);
    else return QString(tr("%1").arg(section));
}

bool TableModel::addRow(QStringList row)
{
    QStringList *newRow=new QStringList(row);
    //insertRows(userData.count(),1);
    userData.append(newRow);
    //this
    return true;
}

//QModelIndex TableModel::index(int row, int column, const QModelIndex &parent) const
//{
//    qd "index()"<<row<<column;
//    if(parent.isValid())
//        return QModelIndex();
//    if(row<0 || row>=userData.count())
//        return QModelIndex();
//    if(column<0 || column>=header.count())
//        return QModelIndex();
//    return createIndex(row,column,userData.at(row));
//}

bool TableModel::insertRows(int row, int count, const QModelIndex &parent)
{
    //qd "insertRows()";
    if(row<0 || row> userData.count())
        return false;
    beginInsertRows(parent,row,row+count-1);
    for(int i=0;i<count;i++){
        QStringList *oneData=new QStringList;
        for(int j=0;j<header.count();j++)
            oneData->append(QString());
        userData.insert(row,oneData);
    }
    endInsertRows();
    return true;
}

bool TableModel::removeRows(int row, int count, const QModelIndex &parent)
{
  //  qd "removeRows()";
    if(row<0 || row+count>userData.count())
        return false;
    beginRemoveRows(parent,row,row+count-1);
    for(int i=0;i<userData.count();i++){
        userData.removeAt(row);
    }
    endRemoveRows();
    return true;
}

