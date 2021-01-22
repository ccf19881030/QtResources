#ifndef MYDATAHELPER_H
#define MYDATAHELPER_H

#include <QObject>
#include <QTableView>
#include <QtSql>

class myDataHelper : public QObject
{
    Q_OBJECT
public:
    explicit myDataHelper(QObject *parent = 0);
    explicit myDataHelper(QString dataBaseName);

    QSqlDatabase myDatabase;
    QString strConnection;

public:
    void InitDataBase();//初始化数据库
    bool OpenDataBase();//打开数据库
    bool CloseDataBase();//关闭数据库

    bool ExecuteSql(QString sql);//执行SQL语句
    bool ExecuteSqls(QStringList sqlList);//执行一系列SQL语句

    bool BindData(QString sql,QTableView *view);//绑定查询后的数据到对应表格
    bool BindData(QString sql,QTableView *view,QStringList fieldList);//绑定查询后的数据到对应表格,按照fieldList顺序更改字段名称

signals:

public slots:

};

#endif // MYDATAHELPER_H
