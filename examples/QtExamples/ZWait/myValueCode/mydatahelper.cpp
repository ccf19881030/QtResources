#include "mydatahelper.h"

#include <QHeaderView>

myDataHelper::myDataHelper(QObject *parent) :
    QObject(parent)
{
}

myDataHelper::myDataHelper(QString dataBaseName) :
    QObject()
{
    this->strConnection=dataBaseName;
}

void myDataHelper::InitDataBase()
{
    this->myDatabase=QSqlDatabase::addDatabase("QSQLITE","mydatasqlite");
    this->myDatabase.setDatabaseName(this->strConnection);
}

bool myDataHelper::OpenDataBase()
{
    //如果还没初始化则初始化数据库
    if (this->myDatabase.databaseName()=="")
    {
        this->InitDataBase();
    }

    return this->myDatabase.open();
}

bool myDataHelper::CloseDataBase()
{
    if (this->myDatabase.isOpen())
    {
        this->myDatabase.close();        
    }
    return true;
}

bool myDataHelper::ExecuteSql(QString sql)
{
    if (this->myDatabase.isOpen())
    {
        QSqlQueryModel *model=new QSqlQueryModel;
        model->setQuery(sql,this->myDatabase);//执行语句，注意最好需要指定数据库
        return true;
    }
    return false;
    this->CloseDataBase();
}

bool myDataHelper::ExecuteSqls(QStringList sqlList)
{
    if (this->myDatabase.isOpen())
    {
        QSqlQueryModel *model=new QSqlQueryModel;
        for (int i=0;i<sqlList.length();++i)
        {
            model->setQuery(sqlList.at(i),this->myDatabase);//执行语句，注意最好需要指定数据库
        }
        this->myDatabase.commit();
        return true;
    }
    return false;
    this->CloseDataBase();
}

bool myDataHelper::BindData(QString sql, QTableView *view)
{
    if (this->myDatabase.isOpen())
    {
        QSqlQueryModel *model=new QSqlQueryModel;
        model->setQuery(sql,this->myDatabase);//执行语句，注意最好需要指定数据库
        view->setModel(model);
        return true;
    }
    return false;
    this->CloseDataBase();
}

bool myDataHelper::BindData(QString sql, QTableView *view, QStringList fieldList)
{
    if (this->myDatabase.isOpen())
    {
        QSqlQueryModel *model=new QSqlQueryModel;
        model->setQuery(sql,this->myDatabase);//执行语句，注意最好需要指定数据库
        for (int i=0;i<fieldList.length();++i)
        {
            model->setHeaderData(i,Qt::Horizontal,fieldList.at(i));
        }
        view->setModel(model);
        view->verticalHeader()->hide();//隐藏左边那列
        return true;
    }
    return false;
    this->CloseDataBase();
}
