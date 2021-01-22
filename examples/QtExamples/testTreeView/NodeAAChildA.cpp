#include "NodeAAChildA.h"

CNodeAAChildA::CNodeAAChildA(CNodeBase *parent):CNodeBase(parent)
{
    m_type = NODE_TYPE_AA_CHILD;
    for(int i=0;i<MAX_NODEAACHILDA_COUNT;i++)
    {
        char ch[40] = {0};
        sprintf(ch,"NameAAChildA%d",i+1);
        m_list[i] = new CNodeBase(this);
        m_list[i]->setName(ch);
        m_list[i]->setType(NODE_TYPE_FINAL);
    }
}

int CNodeAAChildA::getChildCount()
{
    return MAX_NODEAACHILDA_COUNT;
}

CNodeBase *CNodeAAChildA::getChildDevice(int index)
{
    return m_list[index];
}
