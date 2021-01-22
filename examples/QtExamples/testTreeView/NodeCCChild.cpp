#include "NodeCCChild.h"

CNodeCCChild::CNodeCCChild(CNodeBase *parent):CNodeBase(parent)
{
    m_type = NODE_TYPE_CC_CHILD;
    this->setName("NodeCCChild");
    for(int i=0;i<MAX_NODECC_CHILD_COUNT;i++)
    {
        char ch[40] = {0};
        sprintf(ch,"NodeCCChildChild%d",i+1);
        m_list[i] = new CNodeCCChildChild(this);
        m_list[i]->setName(ch);
    }
}

int CNodeCCChild::getChildCount()
{
    return MAX_NODECC_CHILD_COUNT;
}

CNodeBase *CNodeCCChild::getChildDevice(int index)
{
    return m_list[index];
}
