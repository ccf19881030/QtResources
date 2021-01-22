#ifndef COSTOMERREGISTERINFODIALOG_H
#define COSTOMERREGISTERINFODIALOG_H

#include <QDialog>
#include <QSqlQueryModel>
#include <QTableView>

namespace Ui {
class CostomerRegisterInfoDialog;
}

class CostomerRegisterInfoDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit CostomerRegisterInfoDialog(QWidget *parent = 0);
    ~CostomerRegisterInfoDialog();

    void InitForm();

    void RefreshInfo();                  //刷新操作
    //绑定客户信息
    void BindCustomInfo(QString tableName, QTableView *tableView,
                       QString columnNames[], int columnWidths[]);

    void ClearCustomerInfo();               //清除控件中显示的客户信息

    void SetLineEditNoEdit();              //设置lineEdit不可输入

    void SetLineEditEdit();                //设置lineEdit可输入

public slots:
    void showCustomerInfo();
    
private slots:

    void on_checkBoxPwd_clicked(bool checked);

    void on_pbnAddUser_clicked();

    void on_pbnModify_clicked();

    void on_pbnCancel_clicked();

    void on_pbnSave_clicked();

private:
    Ui::CostomerRegisterInfoDialog *ui;

    QSqlQueryModel *QueryModel;     //查询模型
    QTableView *TableView;          //显示数据的表格对象

    QString ColumnNames[8];         //列名数组声明
    int ColumnWidths[8];            //列宽数组声明
};

#endif // COSTOMERREGISTERINFODIALOG_H
