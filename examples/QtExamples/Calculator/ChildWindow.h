#ifndef CHILDWINDOW_H
#define CHILDWINDOW_H
#include"ui_history.h"
#include"ui_about.h"
#include"ui_constant.h"
#include"ui_variable.h"
class History:public QDialog, public Ui::history_Dialog
{
    Q_OBJECT
public:
    History( QWidget* parent=0);
private slots:
    void on_clearPushButton_clicked();
    void on_usePushButton_clicked();
    void on_deletePushButton_clicked();
    void on_copyPushButton_clicked();
    void on_plainTextEdit_cursorPositionChanged();
protected:
    bool eventFilter(QObject *target, QEvent *event);
};
class About:public QDialog,public Ui::aboutDialog
{
    Q_OBJECT
public:
    About(QWidget* parent=0);

};
class Constant:public QDialog,public Ui::constantDialog
{
    Q_OBJECT
public:
    Constant(QWidget* parent=0);
};
class Variable:public QDialog,public Ui::variableDialog
{

    //设置单实例模式
    Q_OBJECT
private:
    static Variable* m_instance;     //静态指针
    Variable(QWidget* parent);
public:
    static Variable* getInstance(QWidget *parent)   //设置public的静态函数来获取实例
    {
        if(!m_instance)
            m_instance = new Variable(parent);
        return m_instance;
    }
private slots:
    void clearVariables();
    void updateVariables(QTableWidgetItem *item);
};
#endif // CHILDWINDOW_H
