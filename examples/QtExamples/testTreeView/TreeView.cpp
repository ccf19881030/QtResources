#include "TreeView.h"
#include <QDebug>

TreeView::TreeView()
{
    model = new QStandardItemModel(4,1);
            QStandardItem *item1 = new QStandardItem("first");
            QStandardItem *item2 = new QStandardItem("second");
            QStandardItem *item3 = new QStandardItem("third");
            QStandardItem *item4 = new QStandardItem("fourth");

            model->setItem(0, 0, item1);
            model->setItem(1, 0, item2);
            model->setItem(2, 0, item3);
            model->setItem(3, 0, item4);

     QStandardItem *item5 = new QStandardItem("fifth");
     item4->appendRow(item5);
            setModel(model);
}

QList<QStandardItem*> TreeView::returnTheItems()
{
        return model->findItems("*", Qt::MatchWildcard | Qt::MatchRecursive);
}

void TreeView::iterateOverItems()
{
        QList<QStandardItem*> list = returnTheItems();

        foreach (QStandardItem* item, list) {
                qDebug() << item->text();
        }
}

