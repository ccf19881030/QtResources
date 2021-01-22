#ifndef NODEMAC_H
#define NODEMAC_H

#include "NodeBase.h"
#include "NodeAA.h"
#include "NodeBB.h"
#include "NodeCC.h"

class CNodeMac : public CNodeBase
{
public:
    CNodeMac(CNodeBase *parent);
    CNodeAA * getChildDeviceAA();
    CNodeBB * getChildDeviceBB();
    CNodeCC * getChildDeviceCC();
    CNodeBase *getChildDevice(int index);
    int getChildCount();

private:
    CNodeAA *m_pCNodeAA;
    CNodeBB *m_pCNodeBB;
    CNodeCC *m_pCNodeCC;
};

#endif // NODEMAC_H
