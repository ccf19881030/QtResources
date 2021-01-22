#include "NodeBB.h"

CNodeBB::CNodeBB(CNodeBase *parent):CNodeBase(parent)
{
    m_type = NODE_TYPE_BB;
    this->setName("NodeBB");
    for(int i=0;i<MAX_NODEBB_COUNT;i++)
    {
        char ch[40] = {0};
        sprintf(ch,"NameBB%d",i+1);
        m_list[i] = new CNodeBBChildA(this);
        m_list[i]->setName(ch);
        m_list[i]->setType(NODE_TYPE_FINAL);
    }
}

int CNodeBB::getChildCount()
{
    return MAX_NODEBB_COUNT;
}

CNodeBase *CNodeBB::getChildDevice(int index)
{
    return m_list[index];
}
