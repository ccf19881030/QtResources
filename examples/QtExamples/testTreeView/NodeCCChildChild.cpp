#include "NodeCCChildChild.h"

CNodeCCChildChild::CNodeCCChildChild(CNodeBase *parent):CNodeBase(parent)
{
    m_type = NODE_TYPE_CC_CHILD_CHILD;
    this->setName("NodeCCChildChild");
    for(int i=0;i<MAX_NODECC_CHILD_CHILD_COUNT;i++)
    {
        char ch[40] = {0};
        sprintf(ch,"NameCCChildChild%d",i+1);
        m_list[i] = new CNodeBase(this);
        m_list[i]->setName(ch);
        m_list[i]->setType(NODE_TYPE_FINAL);
    }
}

int CNodeCCChildChild::getChildCount()
{
    return MAX_NODECC_CHILD_CHILD_COUNT;
}

CNodeBase *CNodeCCChildChild::getChildDevice(int index)
{
    return m_list[index];
}
