#ifndef NODECCCHILDCHILD_H
#define NODECCCHILDCHILD_H

#define MAX_NODECC_CHILD_CHILD_COUNT (8)

#include "NodeBase.h"
#include "NodeAAChildA.h"

class CNodeCCChildChild : public CNodeBase
{
public:
    CNodeCCChildChild(CNodeBase *parent);
    int getChildCount();
    CNodeBase *getChildDevice(int index);
private:
    CNodeBase *m_list[MAX_NODECC_CHILD_CHILD_COUNT];
};

#endif // NODECCCHILDCHILD_H
