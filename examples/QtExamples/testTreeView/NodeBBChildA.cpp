#include "NodeBBChildA.h"

CNodeBBChildA::CNodeBBChildA(CNodeBase *parent):CNodeBase(parent)
{
    m_type = NODE_TYPE_BB_CHILD;
    for(int i=0;i<MAX_NODEBBCHILDA_COUNT;i++)
    {
        char ch[40] = {0};
        sprintf(ch,"NameBBChildA%d",i+1);
        m_list[i] = new CNodeBase(this);
        m_list[i]->setName(ch);
    }
}

int CNodeBBChildA::getChildCount()
{
    return MAX_NODEBBCHILDA_COUNT;
}

CNodeBase *CNodeBBChildA::getChildDevice(int index)
{
    return m_list[index];
}
