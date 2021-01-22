#ifndef NONLINEARALGEBRA_H
#define NONLINEARALGEBRA_H

#include"ui_nonLinearAlgebra.h"
#include"GeneticAlgorithm.h"
class nonLinearAlgebra:public QWidget, public Ui_nonLinearAlgebra
{
    Q_OBJECT
public:
    nonLinearAlgebra(QWidget* parent=0);
protected:
    void closeEvent(QCloseEvent *event);
private slots:
    void on_num0PushButton_clicked();
    void on_num1PushButton_clicked();
    void on_num2PushButton_clicked();
    void on_num3PushButton_clicked();
    void on_num4PushButton_clicked();
    void on_num5PushButton_clicked();
    void on_num6PushButton_clicked();
    void on_num7PushButton_clicked();
    void on_num8PushButton_clicked();
    void on_num9PushButton_clicked();
    void on_pointPushButton_clicked();
    void on_iPushButton_clicked();
    void on_leftbracketPushButton_clicked();
    void on_rightbracketPushButton_clicked();
    void on_variablePushButton_clicked();
    void on_addPushButton_clicked();
    void on_subtractPushButton_clicked();
    void on_multiplyPushButton_clicked();
    void on_powerPushButton_clicked();
    void on_backspacePushButton_clicked();
    void on_plainTextEdit_cursorPositionChanged ();
    void on_plainTextEdit_textChanged();
    void on_clearPushButton_clicked();
    void on_rootsPushButton_clicked();
    void on_valuesPushButton_clicked();
    void getValue();
    bool getPoly(Polynomial &poly, bool ok);
protected:
    bool eventFilter(QObject *target, QEvent *event);
private:
    QLineEdit *variableEdit,*resultEdit;
};
#endif // NONLINEARALGEBRA_H
