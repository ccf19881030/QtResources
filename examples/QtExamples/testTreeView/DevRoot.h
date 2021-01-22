#ifndef DEVROOT_H
#define DEVROOT_H
#define MAC_NODE_CHILD (100)
#include "NodeBase.h"
#include "NodeMac.h"

class CDevRoot : public CNodeBase
{
public:
    CDevRoot(char *macChar,CNodeBase *parent=0);
    ~CDevRoot();
    void appendChlid(CNodeMac *pNodeBase);
    CNodeMac *getNodeMac(int index);
    CNodeBase *getChildDevice(int index);
    int getMacCount();
    int getChildCount();
    int row(CNodeMac *pNodeBase);
private:
    CNodeMac *m_pNodeMac[MAC_NODE_CHILD];
    int m_macCount;
};

#endif // DEVROOT_H
