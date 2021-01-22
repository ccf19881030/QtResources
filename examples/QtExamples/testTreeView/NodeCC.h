#ifndef NODECC_H
#define NODECC_H

#define MAX_NODECC_COUNT (4)

#include "NodeBase.h"
#include "NodeCCChild.h"

class CNodeCC : public CNodeBase
{
public:
    CNodeCC(CNodeBase *parent);
    int getChildCount();
    CNodeBase *getChildDevice(int index);
private:
    CNodeCCChild *m_list[MAX_NODECC_COUNT];
};

#endif // NODECC_H
