#ifndef TREEMODEL_H
#define TREEMODEL_H

#include <QAbstractItemModel>
#include <QStandardItemModel>
#include "DevRoot.h"

class TreeModel : public QAbstractItemModel
{
    Q_OBJECT
public:
    TreeModel(QObject *parent = 0);
    ~TreeModel();

    QVariant data(const QModelIndex &index, int role) const;
    bool setData(const QModelIndex & index, const QVariant & value, int role = Qt::EditRole);
    Qt::ItemFlags flags(const QModelIndex &index) const;
    QVariant headerData(int section, Qt::Orientation orientation,
                        int role = Qt::DisplayRole) const;
    QModelIndex index(int row, int column,
                      const QModelIndex &parent = QModelIndex()) const;
    QModelIndex parent(const QModelIndex &index) const;
    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    int columnCount(const QModelIndex &parent = QModelIndex()) const;

    void setCheckedStrList(CNodeBase *item, QStringList &checkedStrList);
    void getCheckedItemData(QString& resStr);

    void updateModel(const QModelIndex &index);

private:
    void setupModelData(/*const QStringList &lines, TreeItem *parent*/);
    void childItemChange(const QModelIndex &index,CNodeBase *item, int isChecked);
    void parentItemChange(const QModelIndex &index,CNodeBase *item);

    CDevRoot *m_pDevRoot;
    
};

#endif // TREEMODEL_H
