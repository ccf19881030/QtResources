#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "TreeView.h"
//#include <QModelIndexindex>
#include <QDebug>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);


    m_pTreeModel = new TreeModel(this);
    ui->treeView->setModel(m_pTreeModel);
    ui->treeView->setContextMenuPolicy(Qt::CustomContextMenu);//设置treeview 能够使用右键菜单
    ui->treeView->setSelectionMode(QAbstractItemView::ExtendedSelection);//设置treeview 能够被多选
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_treeView_customContextMenuRequested(const QPoint &pos)
{
    QModelIndex curItem=ui->treeView->indexAt(pos);  //获取当前被点击的节点
    bool isValid = curItem.isValid();
//    qDebug()<<"on_treeView_customContextMenuRequested";
    QModelIndex index=ui->treeView->currentIndex();
    CNodeBase *item = static_cast<CNodeBase*>(index.internalPointer());//内部数据指针
    qDebug()<<"NodeType:"<<item->getNodeType();

    QString fileName=ui->treeView->model()->data(index).toString();
    QModelIndex parentIndex = ui->treeView->model()->parent(index);
    CNodeBase *parentItem = static_cast<CNodeBase*>(parentIndex.internalPointer());
    if(parentItem != NULL)
        qDebug()<<"parentNodeType:"<<parentItem->getNodeType();

    QMenu*menu=new QMenu;
    menu->addAction(QString(tr("%1-Export").arg(fileName)));

//    menu->addAction(QString(tr("%1-Import").arg(fileName)),this,SLOT(slotTest()));

//    menu->addAction(QString(tr("%1-Export").arg(fileName)),this,SLOT(slotTest()));

    menu->exec(QCursor::pos());

}

//获取被选中的节点
void MainWindow::on_pushButton_clicked()
{
    QModelIndexList	selectedList = ui->treeView->selectionModel()->selectedIndexes();
    foreach(QModelIndex modelIndex,selectedList)
    {
        CNodeBase *node = static_cast<CNodeBase*>(modelIndex.internalPointer());
        qDebug()<<node->getName();
    }

    QString resStr;
    m_pTreeModel->getCheckedItemData(resStr);
    QMessageBox::information(this, "just for test", resStr);
    qDebug()<<resStr;
}

void MainWindow::on_treeView_clicked(const QModelIndex &index)
{
    m_pTreeModel->updateModel(index);

//    CNodeBase *clickedItem = static_cast<CNodeBase*>(index.internalPointer());

//    ui->treeView->collapseAll();
    ui->treeView->collapse(index);
    ui->treeView->expand(index);
//    QModelIndex parentIndex = index.parent();
//    while(parentIndex.isValid())
//    {
//        ui->treeView->collapse(parentIndex);
//        ui->treeView->expand(parentIndex);
//        parentIndex = parentIndex.parent();
//    }
//    ui->treeView->collapse(index);
//    ui->treeView->expand(index);
//    ui->treeView->scrollTo(index);
}
