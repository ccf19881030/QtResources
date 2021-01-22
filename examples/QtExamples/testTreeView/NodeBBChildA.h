#ifndef NODEBBCHILDA_H
#define NODEBBCHILDA_H

#define MAX_NODEBBCHILDA_COUNT (4)

#include "NodeBase.h"

class CNodeBBChildA : public CNodeBase
{
public:
    CNodeBBChildA(CNodeBase *parent);
    int getChildCount();
    CNodeBase *getChildDevice(int index);

private:
    CNodeBase *m_list[MAX_NODEBBCHILDA_COUNT];
};

#endif // NODEBBCHILDA_H
