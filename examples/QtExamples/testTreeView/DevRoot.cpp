#include "DevRoot.h"

CDevRoot::CDevRoot(char *macChar,CNodeBase *parent):CNodeBase(parent)
{
    m_type = NODE_TYPE_MAC_MANAGER;
    sprintf(m_name,"%s",macChar);
    m_macCount = 0;
}

CDevRoot::~CDevRoot()
{
}

void CDevRoot::appendChlid(CNodeMac *pNodeBase)
{
    m_pNodeMac[m_macCount] = pNodeBase;
    m_macCount = m_macCount + 1;
}

CNodeMac*CDevRoot::getNodeMac(int index)
{
    return m_pNodeMac[index];
}

CNodeBase *CDevRoot::getChildDevice(int index)
{
    return m_pNodeMac[index];
}

int CDevRoot::getMacCount()
{
    return m_macCount;
}

int CDevRoot::getChildCount()
{
    return m_macCount;
}

int CDevRoot::row(CNodeMac *pNodeBase)
{
	for (int i=0;i<m_macCount;i++)
	{
		if (memcmp(m_pNodeMac[i]->getName(),pNodeBase->getName(),sizeof(pNodeBase->getName())) == 0)
		{
			return i;
		}
	}
	return -1;
}
