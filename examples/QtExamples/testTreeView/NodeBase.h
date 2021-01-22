// NodeBase.h: interface for the CNodeBase class.
// 定义：本类封装所有设备和装置的节点基类
// 作者：liuyuananfang 2013-03-19
//////////////////////////////////////////////////////////////////////
#ifndef NODEBASE_H
#define NODEBASE_H

#define NODE_TYPE_MAC_MANAGER (0) //类型：设备管理类
#define NODE_TYPE_MAC (1) //类型：设备
#define NODE_TYPE_AA (2) //类型：设备下挂子装置
#define NODE_TYPE_AA_CHILD (3) //类型：子装置下挂装置
#define NODE_TYPE_BB (4) //类型：
#define NODE_TYPE_BB_CHILD (5) //类型：
#define NODE_TYPE_CC (6) //类型：
#define NODE_TYPE_CC_CHILD (7) //类型：
#define NODE_TYPE_CC_CHILD_CHILD (8) //类型：
#define NODE_TYPE_FINAL (9) //类型：终端节点

#define MAX_LEN_NODE_NAME (40)  //节点名称最大长度

#define CHECKBOX_UNCHECKED	      (0)	//未选取
#define CHECKBOX_CHECKED		  (1)	//全选取
#define CHECKBOX_PARTIALLYCHECKED (2)	//部分选取

#include <string.h>
#include <stdio.h>

class CNodeBase
{
public:
    CNodeBase(CNodeBase *parent = NULL);
    ~CNodeBase();
    int setName(const char *name);
    int getName(char ch[],int len);
    const char *getName();

    virtual int getChildCount();
    virtual CNodeBase* getChildDevice(int index);

    void setParent(CNodeBase *pParent);
    CNodeBase * getParent();
    int getNodeType();
    void setType(int type);

    int isChecked(){return m_checked;}
    void setCheckState(int state){m_checked = state;}
protected:
    char m_name[MAX_LEN_NODE_NAME];
    int m_type;
    CNodeBase *m_pParent;

    int m_checked;
    int m_childCount;
};

#endif // NODEBASE_H
