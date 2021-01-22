#ifndef NODEAACHILDA_H
#define NODEAACHILDA_H

#define MAX_NODEAACHILDA_COUNT (6)

#include "NodeBase.h"

class CNodeAAChildA : public CNodeBase
{
public:
    CNodeAAChildA(CNodeBase *parent);
    int getChildCount();
    CNodeBase *getChildDevice(int index);

private:
    CNodeBase *m_list[MAX_NODEAACHILDA_COUNT];
};

#endif // NODEAACHILDA_H
