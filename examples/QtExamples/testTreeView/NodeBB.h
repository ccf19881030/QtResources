#ifndef NODEBB_H
#define NODEBB_H

#define MAX_NODEBB_COUNT (5)

#include "NodeBase.h"
#include "NodeBBChildA.h"

class CNodeBB : public CNodeBase
{
public:
    CNodeBB(CNodeBase *parent);
    int getChildCount();
    CNodeBase *getChildDevice(int index);

private:
    CNodeBBChildA *m_list[MAX_NODEBB_COUNT];
};

#endif // NODEBB_H
