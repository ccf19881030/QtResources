#include "NodeBase.h"

/*********************************************************************
功能：构造函数
参数：parent，指向父节点
返回：无
作者：liuyuananfang  2013-03-19
*********************************************************************/
CNodeBase::CNodeBase(CNodeBase *parent)
{
    memset(m_name,0,sizeof(m_name));
    m_pParent = parent;

    m_checked = false;
    m_childCount = 0;
}

/*********************************************************************
功能：析构函数
参数：无
返回：无
作者：liuyuananfang  2013-03-19
*********************************************************************/
CNodeBase::~CNodeBase()
{
}

/*********************************************************************
功能：设置节点名称
参数：name，节点新名称
返回：<0，失败。-1，传入参数非法
     >0，成功
作者：liuyuananfang  2013-03-19
*********************************************************************/
int CNodeBase::setName(const char *name)
{
    if(NULL == name)  return -1;
    memset(m_name,0,MAX_LEN_NODE_NAME);
    memcpy(m_name,name,strlen(name));
    return 1;
}

/*********************************************************************
功能：获取节点名称
参数：ch，传出参数，存放节点名称
     len,ch分配的内存大小
返回：<0，失败。-1，传入参数非法
     >0，成功
作者：liuyuananfang  2013-03-19
*********************************************************************/
int CNodeBase::getName(char ch[], int len)
{
    if(NULL == ch)  return -1;
    if(len < MAX_LEN_NODE_NAME) return -1;

    memcpy(ch,m_name,MAX_LEN_NODE_NAME);
    return 1;
}

const char * CNodeBase::getName()
{
    return m_name;
}

int CNodeBase::getChildCount()
{
    return m_childCount;
}

CNodeBase *CNodeBase::getChildDevice(int index)
{
    return NULL;
}

void CNodeBase::setParent( CNodeBase *pParent )
{
	m_pParent = pParent;
}

CNodeBase * CNodeBase::getParent()
{
	return m_pParent;
}

int CNodeBase::getNodeType()
{
    return m_type;
}

void CNodeBase::setType(int type)
{
    m_type = type;
}
