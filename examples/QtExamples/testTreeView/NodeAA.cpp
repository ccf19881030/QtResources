#include "NodeAA.h"

CNodeAA::CNodeAA(CNodeBase *parent):CNodeBase(parent)
{
    m_type = NODE_TYPE_AA;
    this->setName("NodeAA");
    for(int i=0;i<MAX_NODEAA_COUNT;i++)
    {
        char ch[40] = {0};
        sprintf(ch,"NameAA%d",i+1);
        m_list[i] = new CNodeAAChildA(this);
        m_list[i]->setName(ch);
//        sprintf(&m_list[i],&node,sizeof(CNodeAAChildA));
    }
}

int CNodeAA::getChildCount()
{
    return MAX_NODEAA_COUNT;
}

CNodeBase *CNodeAA::getChildDevice(int index)
{
    return m_list[index];
}
