#include "mysqlapi.h"
#include <QSqlQueryModel>
#include <QHeaderView>

int StartIndex;             //分页开始索引,每次翻页都变动
QString TempSql;            //临时SQL语句
QString Sql;

int RowsCount;              //每页显示行数
int RowsCountAll;           //总行数
int PageCount;              //总页数
int PageCurrent;            //当前第几页

QTableView *TableView;      //显示数据的表格对象
QLabel *LabInfo;            //显示翻页信息
QPushButton *BtnFirst;      //第一页按钮对象
QPushButton *BtnPre;        //上一页按钮对象
QPushButton *BtnNext;       //下一页按钮对象
QPushButton *BtnLast;       //末一页按钮对象

QSqlQueryModel *QueryModel; //查询模型

MysqlApi::MysqlApi(QObject *parent) :
    QObject(parent)
{
    StartIndex=0;
    TempSql="";
    Sql="";
    RowsCount=0;
    RowsCountAll=0;
    PageCount=0;
    PageCurrent=1;
}


/*
 *函数功能：设置绑定的也,按钮
*/
void MysqlApi::SetControl(QTableView *tableView, QLabel *labInfo, QPushButton *btnFirst, QPushButton *btnPre, QPushButton *btnNext, QPushButton *btnLast)
{
    TableView = tableView;
    LabInfo = labInfo;
    BtnFirst = btnFirst;
    BtnPre = btnPre;
    BtnNext = btnNext;
    BtnLast = btnLast;
    QueryModel = new QSqlQueryModel(TableView);

    //挂载翻页按钮事件
    connect(BtnFirst,SIGNAL(clicked()),this,SLOT(First()));
    connect(BtnPre,SIGNAL(clicked()),this,SLOT(Previous()));
    connect(BtnNext,SIGNAL(clicked()),this,SLOT(Next()));
    connect(BtnLast,SIGNAL(clicked()),this,SLOT(Last()));
}
/*
 *函数功能：绑定数据到下拉框
 *输入参数：绑定的字段名、表名、下拉框名称
 *输出参数：无
 *返回值：无
 *说明：该函数可以绑定任意字段到任意的下拉框
*/
void MysqlApi::BindData(QString columnName, QString tableName, QComboBox *cbox)
{
    QSqlQuery query;
    query.exec("select "+columnName+" from "+tableName+" order by "+columnName+" asc");
    while(query.next())
    {
        cbox->addItem(query.value(0).toString());
    }
}

/*
 *函数功能：查找任意表中某个字段名的最大值
 *输入参数：字段名、表名
 *输出参数：无
 *返回值：数据表中查询到的字段值
 *说明：
*/
int MysqlApi::SearchMaxValue(QString columnName, QString tableName)
{
    QSqlQuery query;
    int maxvalue = 0;
    QString sql = "select MAX("+columnName+") from "+tableName+";";
    qDebug() <<sql;
    query.exec(sql);
    if(query.next())
    {

        maxvalue = query.value(0).toInt();
    }
    return maxvalue;
}

void MysqlApi::BindData(QString tableName, QString orderColumn, QString orderType, int rowsCount, QString columnNames[], int columnWidths[])
{
    StartIndex = 0;//重置开始索引
    PageCurrent = 1;
    RowsCount = rowsCount;

    //开始分页绑定数据前,计算好总数据量以及行数
    TempSql = "select count(*) from "+tableName;
    QSqlQuery query;
    query.prepare(TempSql);
    query.exec();
    query.first();
    RowsCountAll = query.value(0).toInt();

    int yushu = RowsCountAll % RowsCount;
    //不存在余数,说明是整行,例如300%5==0
    if (yushu == 0)
    {
        if (RowsCountAll > 0 && RowsCountAll < RowsCount)
        {
            PageCount = 1;
        }
        else
        {
            PageCount=RowsCountAll/RowsCount;
        }
    }
    else
    {
        PageCount=RowsCountAll/RowsCount+1;
    }

    TempSql = "select RoomNo,Typename,Typrice,RoomState,RoomRemark from "+tableName+" where room.RoomTypeId=roomtype.RoomTypeId order by "+orderColumn+" "+orderType;
    Sql = QString("%1 limit %2,%3;").arg(TempSql).arg(StartIndex).arg(RowsCount);//组织分页SQL语句
    BindSql(Sql);

    //依次设置列标题、列宽等
    for (int i = 0;i<TableView->model()->columnCount();i++)
    {
        QueryModel->setHeaderData(i,Qt::Horizontal,columnNames[i]);//设置列标题
        TableView->setColumnWidth(i,columnWidths[i]);//设置列宽
    }


    TableView->horizontalHeader()->setHighlightSections(false);//点击表头时不对表头光亮
    TableView->setSelectionMode(QAbstractItemView::ContiguousSelection);//选中模式为多行选中
    TableView->setSelectionBehavior(QAbstractItemView::SelectRows);//选中整行
    TableView->setStyleSheet( "QTableView::item:hover{background-color:rgb(92,188,227,200)}"
                              "QTableView::item:selected{background-color:#1B89A1}");
}

/*
 *函数功能：绑定任意表中的数据到tableview中
*/
void MysqlApi::MyBindTable(QString tableName, QTableView *tableView, QString columnNames[], int columnWidths[])
{
    TableView = tableView;
    QString sql = "SELECT * FROM " + tableName;
    QueryModel->setQuery(sql);
    TableView->setModel(QueryModel);

    //依次设置列标题、列宽等
    for (int i = 0;i<TableView->model()->columnCount();i++)
    {
        QueryModel->setHeaderData(i,Qt::Horizontal,columnNames[i]);     //设置列标题
        TableView->setColumnWidth(i,columnWidths[i]);                   //设置列宽
    }

    TableView->horizontalHeader()->setHighlightSections(false);         //点击表头时不对表头光亮
    TableView->setSelectionMode(QAbstractItemView::ContiguousSelection);//选中模式为多行选中
    TableView->setSelectionBehavior(QAbstractItemView::SelectRows);     //选中整行
    TableView->setStyleSheet( "QTableView::item:hover{background-color:rgb(92,188,227,200)}"
                              "QTableView::item:selected{background-color:#1B89A1}");
}

void MysqlApi::BindSql(QString sql)
{
    QueryModel->setQuery(sql);
    TableView->setModel(QueryModel);
    LabInfo->setText(QString("共有%1条数据  共%2页  当前第%3页").arg(RowsCountAll).arg(PageCount).arg(PageCurrent));
}

void MysqlApi::BindDataSelect(QString tableName, QString orderColumn, QString orderType, QString where, int rowsCount, QString columnNames[], int columnWidths[])
{
    StartIndex=0;//重置开始索引
    PageCurrent=1;
    RowsCount=rowsCount;

    //开始分页绑定数据前,计算好总数据量以及行数
    TempSql="select count(*) from "+tableName+" "+where;
    QSqlQuery query;
    query.prepare(TempSql);//分行写的时候注意空格不能少
    query.exec();
    query.first();
    RowsCountAll= query.value(0).toInt();

    int yushu=RowsCountAll % RowsCount;
    //不存在余数,说明是整行,例如300%5==0
    if (yushu==0) {
        if (RowsCountAll>0 && RowsCountAll<RowsCount){
            PageCount=1;
        }else{
            PageCount=RowsCountAll/RowsCount;
        }
    }else{
        PageCount=RowsCountAll/RowsCount+1;
    }

    TempSql="select * from "+tableName+" "+where+" order by "+orderColumn+" "+orderType;
    Sql=QString("%1 limit %2,%3;").arg(TempSql).arg(StartIndex).arg(RowsCount);//组织分页SQL语句
    BindSql(Sql);

    //依次设置列标题、列宽等
    for (int i=0;i<TableView->model()->columnCount();i++){
        QueryModel->setHeaderData(i,Qt::Horizontal,columnNames[i]);//设置列标题
        TableView->setColumnWidth(i,columnWidths[i]);//设置列宽
    }


    TableView->horizontalHeader()->setHighlightSections(false);//点击表头时不对表头光亮
    TableView->setSelectionMode(QAbstractItemView::SingleSelection);//选中模式为单行选中
    TableView->setSelectionBehavior(QAbstractItemView::SelectRows);//选中整行
    TableView->setStyleSheet( "QTableView::item:hover{background-color:rgb(92,188,227,200)}"
                              "QTableView::item:selected{background-color:#1B89A1}");
}

void MysqlApi::First()
{
    if (PageCount>1)
    {
        StartIndex=0;
        PageCurrent=1;
        Sql=QString("%1 limit %2,%3;").arg(TempSql).arg(StartIndex).arg(RowsCount);//组织分页SQL语句
        BindSql(Sql);
    }
}

void MysqlApi::Previous()
{
    if (PageCurrent>1)
    {
        PageCurrent--;
        StartIndex-=RowsCount;
        Sql=QString("%1 limit %2,%3;").arg(TempSql).arg(StartIndex).arg(RowsCount);//组织分页SQL语句
        BindSql(Sql);
    }
}

void MysqlApi::Next()
{
    if (PageCurrent<PageCount)
    {
        PageCurrent++;
        StartIndex+=RowsCount;
        Sql=QString("%1 limit %2,%3;").arg(TempSql).arg(StartIndex).arg(RowsCount);//组织分页SQL语句
        BindSql(Sql);
    }
}

void MysqlApi::Last()
{
    if (PageCount>0)
    {
        StartIndex=(PageCount-1)*RowsCount;
        PageCurrent=PageCount;
        Sql=QString("%1 limit %2,%3;").arg(TempSql).arg(StartIndex).arg(RowsCount);//组织分页SQL语句
        BindSql(Sql);
    }
}
