
#include "adddialog.h"
#include "addresswidget.h"

#include <QtWidgets>

AddressWidget::AddressWidget(QWidget *parent)
    : QTabWidget(parent)
{
    table = new TableModel(this);
    newAddressTab = new NewAddressTab(this);
    //新增一个地址时候，触发sendDetails信号，而addEntry接收到新增的“姓名--地址”数据
    connect(newAddressTab, SIGNAL(sendDetails(QString, QString)),
        this, SLOT(addEntry(QString, QString)));

    addTab(newAddressTab, "Address Book");

    setupTabs();
}

void AddressWidget::addEntry()
{
    AddDialog aDialog;

    if (aDialog.exec()) {
        QString name = aDialog.nameText->text();
        QString address = aDialog.addressText->toPlainText();

        addEntry(name, address);
    }
}

void AddressWidget::addEntry(QString name, QString address)
{
    //当前table表格的数据（这里会产生9张table表格）
    QList<QPair<QString, QString> >list = table->getList();
    QPair<QString, QString> pair(name, address);

    //姓名--地址不可重复
    if (!list.contains(pair)) {
        //在table的第0行0列（第一个参数）新增一行（第二个参数）
        table->insertRows(0, 1, QModelIndex());

        //index为第0行0列
        QModelIndex index = table->index(0, 0, QModelIndex());
        table->setData(index, name, Qt::EditRole);
        //index为第0行第1列
        index = table->index(0, 1, QModelIndex());
        table->setData(index, address, Qt::EditRole);
        //新增姓名--地址后，删除newAddressTab
        removeTab(indexOf(newAddressTab));
    } else {
        QMessageBox::information(this, tr("Duplicate Name"),
            tr("The name \"%1\" already exists.").arg(name));
    }
}

void AddressWidget::editEntry()
{
    //得到当前的QTableView
    QTableView *temp = static_cast<QTableView*>(currentWidget());
    //QSortFilterProxyModel在model和view之间提供排序和过滤
    QSortFilterProxyModel *proxy = static_cast<QSortFilterProxyModel*>(temp->model());
    //选择model
    QItemSelectionModel *selectionModel = temp->selectionModel();

    //得到当前所要被修改的索引---这里indexes实际上就一项（因为只允许选择一行）
    QModelIndexList indexes = selectionModel->selectedRows();
    QString name;
    QString address;
    int row = -1;

    foreach (QModelIndex index, indexes) {
        //mapToSource：Returns the source model index corresponding to the given proxyIndex from the sorting filter model.
        row = proxy->mapToSource(index).row();
        //得到姓名数据---这里table指针是一个模型，关联具体表格
        QModelIndex nameIndex = table->index(row, 0, QModelIndex());
        QVariant varName = table->data(nameIndex, Qt::DisplayRole);
        name = varName.toString();

        //得到地址数据
        QModelIndex addressIndex = table->index(row, 1, QModelIndex());
        QVariant varAddr = table->data(addressIndex, Qt::DisplayRole);
        address = varAddr.toString();
    }

    AddDialog aDialog;
    aDialog.setWindowTitle(tr("Edit a Contact"));

    //只允许更改地址
    aDialog.nameText->setReadOnly(true);
    aDialog.nameText->setText(name);
    aDialog.addressText->setText(address);

    if (aDialog.exec()) {
        QString newAddress = aDialog.addressText->toPlainText();
        if (newAddress != address) {
            //得到第row行第二列（1）的索引，通过setData来更新数据
            QModelIndex index = table->index(row, 1, QModelIndex());
            table->setData(index, newAddress, Qt::EditRole);
        }
    }
}

void AddressWidget::removeEntry()
{
    QTableView *temp = static_cast<QTableView*>(currentWidget());
    QSortFilterProxyModel *proxy = static_cast<QSortFilterProxyModel*>(temp->model());
    QItemSelectionModel *selectionModel = temp->selectionModel();

    QModelIndexList indexes = selectionModel->selectedRows();

    foreach (QModelIndex index, indexes) {
        int row = proxy->mapToSource(index).row();
        //从row行开始删除一行
        table->removeRows(row, 1, QModelIndex());
    }

    if (table->rowCount(QModelIndex()) == 0) {
        insertTab(0, newAddressTab, "Address Book");
    }
}

//实现九列表格框
void AddressWidget::setupTabs()
{
    QStringList groups;
    groups << "ABC" << "DEF" << "GHI" << "JKL" << "MNO" << "PQR" << "STU" << "VW" << "XYZ";

    for (int i = 0; i < groups.size(); ++i) {
        QString str = groups.at(i);
        QString regExp = QString("^[%1].*").arg(str);

        //设定过滤模型--在model（模型中专门用于处理数据，而view则用于显示数据）
        proxyModel = new QSortFilterProxyModel(this);
        proxyModel->setSourceModel(table);
        proxyModel->setFilterRegExp(QRegExp(regExp, Qt::CaseInsensitive));
        proxyModel->setFilterKeyColumn(0);

        //将过滤模型添加到视图中：则数据显示之前会被自动过滤（这里的过滤是自动排序）
        QTableView *tableView = new QTableView;
        tableView->setModel(proxyModel);

        //允许用户选择行
        tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
        tableView->horizontalHeader()->setStretchLastSection(true);
        tableView->verticalHeader()->hide();
        tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
        //允许用户选择一整行
        tableView->setSelectionMode(QAbstractItemView::SingleSelection);

        tableView->setSortingEnabled(true);

        //此信号槽的作用不太理解---
        connect(tableView->selectionModel(),
            SIGNAL(selectionChanged(QItemSelection,QItemSelection)),
            this, SIGNAL(selectionChanged(QItemSelection)));

        //这里新建的一张表格是groups的一部分（groups包含九张表格）
        addTab(tableView, str);
    }
}

void AddressWidget::readFromFile(const QString &fileName)
{
    QFile file(fileName);

    if (!file.open(QIODevice::ReadOnly)) {
        QMessageBox::information(this, tr("Unable to open file"),
            file.errorString());
        return;
    }

    QList<QPair<QString, QString> > pairs = table->getList();
    QDataStream in(&file);
    in >> pairs;

    if (pairs.isEmpty()) {
        QMessageBox::information(this, tr("No contacts in file"),
                                 tr("The file you are attempting to open contains no contacts."));
    } else {
        for (int i=0; i<pairs.size(); ++i) {
            QPair<QString, QString> p = pairs.at(i);
            addEntry(p.first, p.second);
        }
    }
}

void AddressWidget::writeToFile(const QString &fileName)
{
    QFile file(fileName);

    if (!file.open(QIODevice::WriteOnly)) {
        QMessageBox::information(this, tr("Unable to open file"), file.errorString());
        return;
    }

    QList<QPair<QString, QString> > pairs = table->getList();
    QDataStream out(&file);
    out << pairs;
}
