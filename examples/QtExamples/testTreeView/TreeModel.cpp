#include "TreeModel.h"
#include <QStringList>
#include <qDebug>
#include "NodeAA.h"
#include "NodeBB.h"
#include "NodeCC.h"

TreeModel::TreeModel(QObject *parent)
     : QAbstractItemModel(parent)
 {
     m_pDevRoot = new CDevRoot("根目录");
	 setupModelData();
 }

TreeModel::~TreeModel()
{
	delete m_pDevRoot;
}

QVariant TreeModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
    {
        return QVariant();
    }
    else if (role == Qt::DisplayRole)
    {
        CNodeBase *item = static_cast<CNodeBase*>(index.internalPointer());
        return item->getName();
    }
    else if(role == Qt::DecorationRole)
    {
        CNodeBase *item = static_cast<CNodeBase*>(index.internalPointer());
        if(item->getNodeType() == NODE_TYPE_FINAL)
            return QIcon(":/images/window.bmp");
        return QIcon(":/images/test.png");
    }
    //判断显示的对象是checkbox，并且位于第一列
    else if(role == Qt::CheckStateRole && index.column()==0)
    {
        CNodeBase *item = static_cast<CNodeBase*>(index.internalPointer());
        int checkedState = item->isChecked();
        if(CHECKBOX_CHECKED == checkedState)				return static_cast<int>(Qt::Checked);
        else if(CHECKBOX_UNCHECKED == checkedState)		return static_cast<int>(Qt::Unchecked);
        else if(CHECKBOX_PARTIALLYCHECKED == checkedState)	return static_cast<int>(Qt::PartiallyChecked);

//        CNodeBase *item = static_cast<CNodeBase*>(index.internalPointer());
//        int childCount = item->getChildCount();

//        if(0 == childCount)
//        {
//            if(CHECKBOX_CHECKED == item->isChecked())				return static_cast<int>(Qt::Checked);
//            else if(CHECKBOX_UNCHECKED == item->isChecked())		return static_cast<int>(Qt::Unchecked);
//            else if(CHECKBOX_PARTIALLYCHECKED == item->isChecked())	return static_cast<int>(Qt::PartiallyChecked);
//        }

//        int childCheckedCount = 0;
//        int childPartiallyCheckedCount = 0;
//        for(int i=0;i<childCount;i++)
//        {
//            CNodeBase *childItem = item->getChildDevice(i);
//            if(NULL == childItem)   continue;
//            int isChecked = childItem->isChecked();

//            if( CHECKBOX_CHECKED == isChecked)	childCheckedCount++;
//            else if( CHECKBOX_PARTIALLYCHECKED == isChecked) childPartiallyCheckedCount++;
//        }
//        if(childCheckedCount == childCount)
//        {
//            item->setCheckState(CHECKBOX_CHECKED);
//            return static_cast<int>(Qt::Checked);											//全选
//        }
//        else if(0 == childCheckedCount && 0 == childPartiallyCheckedCount)
//        {
//            item->setCheckState(CHECKBOX_UNCHECKED);
//            return static_cast<int>(Qt::Unchecked);											//全不选
//        }
//        else
//        {
//            item->setCheckState(CHECKBOX_PARTIALLYCHECKED);
//            return static_cast<int>(Qt::PartiallyChecked);									//部分选取
//        }
    }
    else if(role == Qt::UserRole)
    {
    }
    return QVariant();

}

bool TreeModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
//    if (role==Qt::CheckStateRole && index.column()==0)
//    {
//        CNodeBase *item = static_cast<CNodeBase*>(index.internalPointer());
//        if (value==Qt::Unchecked)
//        {
//            //m_checkedList.removeOne(index);
//            item->setCheckState(CHECKBOX_UNCHECKED);
//            emit(dataChanged(index, index));
//        }
//        else if(value==Qt::Checked)
//        {
//            //m_checkedList.append(index);
//            item->setCheckState(CHECKBOX_CHECKED);
//            emit(dataChanged(index, index));
//        }
//        //更新子节点选中状态
//        int childCount = rowCount(index);
//        if (childCount > 0)
//        {
//            //判断是否有子节点
//            for (int i=0; i<childCount; i++)
//            {
//                //获得子节点的index
//                QModelIndex child = this->index(i, 0, index);
//                //递归，改变子节点的checkbox状态
//                setData(child, value, Qt::CheckStateRole);
//            }
//        }
//    }

    return true;
}

Qt::ItemFlags TreeModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return 0;
    if (index.column()==0)   //如果是第一列的结点，则使其有显示checkbox的能力
        return Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsUserCheckable;

    return Qt::ItemIsEnabled | Qt::ItemIsSelectable;
}


QVariant TreeModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (orientation == Qt::Horizontal  && role == Qt::DisplayRole)
        return m_pDevRoot->getName();
    return QVariant();
}

QModelIndex TreeModel::index(int row, int column, const QModelIndex &parent) const
{
    if (!hasIndex(row, column, parent))
        return QModelIndex();

    CNodeBase *pNodeBase;

    if (!parent.isValid())//ROOT下挂装置NodeMac
    {
        CNodeBase *pNodeMac = m_pDevRoot->getNodeMac(row);
        return createIndex(row, column, pNodeMac);
    }
    pNodeBase = static_cast<CNodeBase*>(parent.internalPointer());
    if (pNodeBase->getNodeType() == NODE_TYPE_MAC && row == 0)//装置NodeMac下挂装置AA
    {
        CNodeMac *pNodeMac = static_cast<CNodeMac*>(parent.internalPointer());
        CNodeAA *P = pNodeMac->getChildDeviceAA();
        return createIndex(row,column,P);
    }
    else if (pNodeBase->getNodeType() == NODE_TYPE_MAC && row == 1)//装置NodeMac下挂装置BB
    {
        CNodeMac *pNodeMac = static_cast<CNodeMac*>(parent.internalPointer());
        CNodeBB *pNodeDeviceGroupFolder = pNodeMac->getChildDeviceBB();
        return createIndex(row,column,pNodeDeviceGroupFolder);
    }
    else if (pNodeBase->getNodeType() == NODE_TYPE_MAC && row == 2)//装置NodeMac下挂装置CC
    {
        CNodeMac *pNodeMac = static_cast<CNodeMac*>(parent.internalPointer());
        CNodeCC *pNodeDeviceGroupFolder = pNodeMac->getChildDeviceCC();
        return createIndex(row,column,pNodeDeviceGroupFolder);
    }
    else if (pNodeBase->getNodeType() == NODE_TYPE_AA)//装置AA下挂装置AA-CHILD
    {
        CNodeAA *pNodeDeviceFolder = static_cast<CNodeAA*>(parent.internalPointer());
        CNodeAAChildA *pNodeBase = static_cast<CNodeAAChildA*>(pNodeDeviceFolder->getChildDevice(row));
        return createIndex(row,column,pNodeBase);
    }
    else if (pNodeBase->getNodeType() == NODE_TYPE_AA_CHILD)//装置AA-CHILD下挂装置
    {
        CNodeAAChildA *pNodeDeviceFolder = static_cast<CNodeAAChildA*>(parent.internalPointer());
        CNodeBase *pNodeBase = pNodeDeviceFolder->getChildDevice(row);
        return createIndex(row,column,pNodeBase);
    }
    else if (pNodeBase->getNodeType() == NODE_TYPE_BB)//装置BB下挂装置BB-CHILD
    {
        CNodeBB *pNodeDeviceGroupFolder = static_cast<CNodeBB*>(parent.internalPointer());
        CNodeBase *pNodeBase = pNodeDeviceGroupFolder->getChildDevice(row);
        return createIndex(row,column,pNodeBase);
    }
    else if (pNodeBase->getNodeType() == NODE_TYPE_CC)//装置CC下挂装置CC-CHILD
    {
        CNodeCC *pNodeDeviceGroupFolder = static_cast<CNodeCC*>(parent.internalPointer());
        CNodeCCChild *pNodeBase = static_cast<CNodeCCChild*>(pNodeDeviceGroupFolder->getChildDevice(row));
        return createIndex(row,column,pNodeBase);
    }
    else if (pNodeBase->getNodeType() == NODE_TYPE_CC_CHILD)//装置CC-CHILD下挂装置CC-CHILD-CHILD
    {
        CNodeCCChild *pNodeDeviceGroupFolder = static_cast<CNodeCCChild*>(parent.internalPointer());
        CNodeCCChildChild *pNodeBase = static_cast<CNodeCCChildChild*>(pNodeDeviceGroupFolder->getChildDevice(row));
        return createIndex(row,column,pNodeBase);
    }
    else if (pNodeBase->getNodeType() == NODE_TYPE_CC_CHILD_CHILD)//装置CC-CHILD-CHILD下挂装置
    {
        CNodeCCChildChild *pNodeDeviceGroupFolder = static_cast<CNodeCCChildChild*>(parent.internalPointer());
        CNodeBase *pNodeBase = pNodeDeviceGroupFolder->getChildDevice(row);
        return createIndex(row,column,pNodeBase);
    }
    return QModelIndex();
}

QModelIndex TreeModel::parent(const QModelIndex &index) const
{
    if (!index.isValid())
    {
        return QModelIndex();
    }

    CNodeBase *childItem = static_cast<CNodeBase*>(index.internalPointer());
    CNodeBase *parentItem = childItem->getParent();

    if (parentItem->getNodeType() == NODE_TYPE_MAC_MANAGER)//设备管理
    {
        return QModelIndex();
    }
    else if(parentItem->getNodeType() == NODE_TYPE_MAC)//设备
    {
        return createIndex(0, 0, parentItem);
    }
    else if(parentItem->getNodeType() == NODE_TYPE_AA)//设备下挂装置AA
    {
        return createIndex(0, 0, parentItem);
    }
    else if(parentItem->getNodeType() == NODE_TYPE_AA_CHILD)//装置AA下挂装置
    {
        return createIndex(0, 0, parentItem);
    }
    else if(parentItem->getNodeType() == NODE_TYPE_BB)//设备下挂装置BB
    {
        return createIndex(1, 0, parentItem);
    }
    else if(parentItem->getNodeType() == NODE_TYPE_CC)//设备下挂装置CC
    {
        return createIndex(2, 0, parentItem);
    }
    else if(parentItem->getNodeType() == NODE_TYPE_CC_CHILD)//装置CC下挂装置CC-CHILD
    {
        return createIndex(0, 0, parentItem);
    }
    else if(parentItem->getNodeType() == NODE_TYPE_CC_CHILD_CHILD)//装置CC-CHILD-CHILD下挂装置
    {
        return createIndex(0, 0, parentItem);
    }
    return QModelIndex();
}

int TreeModel::rowCount(const QModelIndex &parent) const
{
    CNodeBase *parentItem;
    if (parent.column() > 0)
    {
        return 0;
    }
    if (!parent.isValid())
    {
        return m_pDevRoot->getMacCount();
    }
    parentItem = static_cast<CNodeBase*>(parent.internalPointer());
    if(parentItem->getNodeType() == NODE_TYPE_MAC)//设备下挂数量
    {
        CNodeMac *p = static_cast<CNodeMac*>(parent.internalPointer());
        return p->getChildCount();
    }
    else if(parentItem->getNodeType() == NODE_TYPE_AA)//装置AA下挂数量
    {
        CNodeAA *p = static_cast<CNodeAA*>(parent.internalPointer());
        return p->getChildCount();
    }
    else if(parentItem->getNodeType() == NODE_TYPE_AA_CHILD)//装置AA下挂装置AA-CHILD下挂数量
    {
        CNodeAAChildA *p = static_cast<CNodeAAChildA*>(parent.internalPointer());
        return p->getChildCount();
    }
    else if(parentItem->getNodeType() == NODE_TYPE_BB)//装置BB下挂数量
    {
        CNodeBB *p = static_cast<CNodeBB*>(parent.internalPointer());
        return p->getChildCount();
    }
    else if(parentItem->getNodeType() == NODE_TYPE_CC)//装置CC下挂数量
    {
        CNodeCC *p = static_cast<CNodeCC*>(parent.internalPointer());
        return p->getChildCount();
    }
    else if(parentItem->getNodeType() == NODE_TYPE_CC_CHILD)//装置CC-CHILD下挂数量
    {
        CNodeCCChild *p = static_cast<CNodeCCChild*>(parent.internalPointer());
        return p->getChildCount();
    }
    else if(parentItem->getNodeType() == NODE_TYPE_CC_CHILD_CHILD)//装置CC-CHILD-CHILD下挂数量
    {
        CNodeCCChildChild *p = static_cast<CNodeCCChildChild*>(parent.internalPointer());
        return p->getChildCount();
    }

    return 0;
}

int TreeModel::columnCount(const QModelIndex &parent) const
{
	return 1;
}


void TreeModel::setupModelData()
{
     CNodeMac *p = new CNodeMac(m_pDevRoot);
     m_pDevRoot->appendChlid(p);
}

void TreeModel::setCheckedStrList(CNodeBase *item, QStringList &checkedStrList)
{
    if(NULL == item)    return;
    if (item->isChecked())
    {
        checkedStrList.append(item->getName());
    }

    int childCount = item->getChildCount();
    if (childCount > 0)
    {
        // 判断是否有子节点
        for (int i=0; i<childCount; i++)
        {
            CNodeBase *child = item->getChildDevice(i);
            // 递归调用setCheckedStrList;
            setCheckedStrList(child, checkedStrList);
        }
    }
}

void TreeModel::getCheckedItemData(QString& resStr)
{
    QStringList checkedStrList;
    setCheckedStrList(m_pDevRoot, checkedStrList);

    for (int i=0; i<checkedStrList.size(); i++)
    {
        resStr += checkedStrList[i] + QString("\n");
    }
}

void TreeModel::updateModel(const QModelIndex &index)
{
    CNodeBase *item = static_cast<CNodeBase*>(index.internalPointer());
    int isChecked = item->isChecked();
    int newCheckState;
    if((CHECKBOX_UNCHECKED == isChecked) || (CHECKBOX_PARTIALLYCHECKED == isChecked)) newCheckState = CHECKBOX_CHECKED;
    else if(CHECKBOX_CHECKED == isChecked) newCheckState = CHECKBOX_UNCHECKED;


    //更新子节点选中状态
    childItemChange(index,item,newCheckState);
    //更新父节点选中状态
    parentItemChange(index,item);

    //this->reset();

}

void TreeModel::childItemChange(const QModelIndex &index,CNodeBase *item, int isChecked)
{
    item->setCheckState(isChecked);
    //更新子节点选中状态
    int childCount = item->getChildCount();
    for (int i=0; i<childCount; i++)
    {
        //递归，改变子节点的checkbox状态
        CNodeBase *childItem = item->getChildDevice(i);
        childItem->setCheckState(isChecked);
        QModelIndex childIndex = this->index(i, 0, index);
        childItemChange(childIndex,childItem,isChecked);
        emit(dataChanged(index, index));
    }
}

void TreeModel::parentItemChange(const QModelIndex &index,CNodeBase *item)
{
    CNodeBase *parentItem = item->getParent();
    if(NULL == parentItem)  return;


    int selectedCount = 0;//选中的子节点个数
    int partiallySelectedCount = 0;//部分选中的子节点个数
    int childCount = parentItem->getChildCount();
    for(int i=0;i<childCount;i++)
    {
        CNodeBase *childItem = parentItem->getChildDevice(i);
        int checkedState = childItem->isChecked();
        if(CHECKBOX_CHECKED == checkedState)    selectedCount++;
        else if(CHECKBOX_PARTIALLYCHECKED == checkedState)  partiallySelectedCount++;
    }

    //全部选中
    if(selectedCount == childCount)
    {
        parentItem->setCheckState(CHECKBOX_CHECKED);
    }
    //未选中
    else if(0 == selectedCount && 0 == partiallySelectedCount)
    {
        parentItem->setCheckState(CHECKBOX_UNCHECKED);
    }
    else//部分选中
    {
        parentItem->setCheckState(CHECKBOX_PARTIALLYCHECKED);
    }

    emit(dataChanged(index, index));
    //递归调用
    QModelIndex parentIndex = this->parent(index);
    parentItemChange(parentIndex,parentItem);
}
