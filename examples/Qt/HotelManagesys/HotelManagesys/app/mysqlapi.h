#ifndef MYSQLAPI_H
#define MYSQLAPI_H

#include <QObject>
#include <QtSql>
#include <QTableView>
#include <QLabel>
#include <QPushButton>
#include <QComboBox>

/* 说明:mysql数据库操作头文件
 * 功能:用来对数据库进行查询等处理
 */
class MysqlApi : public QObject
{
    Q_OBJECT
public:
    explicit MysqlApi(QObject *parent = 0);

    //设置需要显示数据的表格,数据翻页对应的按钮
    void SetControl(QTableView *tableView,QLabel *labInfo,
                    QPushButton *btnFirst,QPushButton *btnPre,
                    QPushButton *btnNext,QPushButton *btnLast);
    //绑定数据到下拉框
    void BindData(QString columnName,QString tableName,QComboBox *cbox);
    //查找某个字段的最大值
    int SearchMaxValue(QString columnName,QString tableName);
    //绑定数据,带行数和条件和排序
    void BindData(QString tableName,QString orderColumn,QString orderType,int rowsCount,
                  QString columnNames[], int columnWidths[]);
    //将某个表中的数据绑定到指定的TableView上
    void MyBindTable(QString tableName, QTableView *tableView,
                     QString columnNames[], int columnWidths[]);
    
    void BindSql(QString sql);
    void BindDataSelect(QString tableName,QString orderColumn,
                        QString orderType,QString where,int rowsCount,
                        QString columnNames[], int columnWidths[]);
signals:
    
private slots:
private slots:
    void First();       //第一页
    void Previous();    //上一页
    void Next();        //下一页
    void Last();        //末一页
private:
    
};

#endif // MYSQLAPI_H
