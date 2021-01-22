#include "NodeMac.h"

CNodeMac::CNodeMac(CNodeBase *parent):CNodeBase(parent)
{
    m_type = NODE_TYPE_MAC;
    setName("NodeMac");
    m_pCNodeAA = new CNodeAA(this);
    m_pCNodeBB = new CNodeBB(this);
    m_pCNodeCC = new CNodeCC(this);
}

CNodeAA *CNodeMac::getChildDeviceAA()
{
    return m_pCNodeAA;
}

CNodeBB *CNodeMac::getChildDeviceBB()
{
    return m_pCNodeBB;
}

CNodeCC *CNodeMac::getChildDeviceCC()
{
    return m_pCNodeCC;
}

CNodeBase *CNodeMac::getChildDevice(int index)
{
    if(0 == index)  return m_pCNodeAA;
    else if(1 == index) return m_pCNodeBB;
    else if(2 == index) return m_pCNodeCC;
}

int CNodeMac::getChildCount()
{
    return 3;
}
