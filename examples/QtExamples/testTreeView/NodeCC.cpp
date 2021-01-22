#include "NodeCC.h"

CNodeCC::CNodeCC(CNodeBase *parent):CNodeBase(parent)
{
    m_type = NODE_TYPE_CC;
    this->setName("NodeCC");
    for(int i=0;i<MAX_NODECC_COUNT;i++)
    {
        char ch[40] = {0};
        sprintf(ch,"NodeCCChild%d",i+1);
        m_list[i] = new CNodeCCChild(this);
        m_list[i]->setName(ch);
    }
}

int CNodeCC::getChildCount()
{
    return MAX_NODECC_COUNT;
}

CNodeBase *CNodeCC::getChildDevice(int index)
{
    return m_list[index];
}
