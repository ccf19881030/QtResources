#ifndef NODEAA_H
#define NODEAA_H

#define MAX_NODEAA_COUNT (4)

#include "NodeBase.h"
#include "NodeAAChildA.h"

class CNodeAA : public CNodeBase
{
public:
    CNodeAA(CNodeBase *parent);
    int getChildCount();
    CNodeBase *getChildDevice(int index);
private:
    CNodeAAChildA *m_list[MAX_NODEAA_COUNT];
};

#endif // NODEAA_H
