#ifndef NODECCCHILD_H
#define NODECCCHILD_H

#define MAX_NODECC_CHILD_COUNT (3)

#include "NodeBase.h"
#include "NodeCCChildChild.h"

class CNodeCCChild : public CNodeBase
{
public:
    CNodeCCChild(CNodeBase *parent);
    int getChildCount();
    CNodeBase *getChildDevice(int index);
private:
    CNodeCCChildChild *m_list[MAX_NODECC_CHILD_COUNT];
};

#endif // NODECCCHILD_H
