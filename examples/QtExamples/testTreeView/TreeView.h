#ifndef TREEVIEW_H
#define TREEVIEW_H

#include <QTreeView>
#include <QStandardItem>

class TreeView : public QTreeView
{
public:
    TreeView();
    void iterateOverItems();
    QList<QStandardItem*> returnTheItems();
private:
    QStandardItemModel *model;
};

#endif // TREEVIEW_H
