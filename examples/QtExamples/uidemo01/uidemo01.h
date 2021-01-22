#ifndef UIDEMO01_H
#define UIDEMO01_H

#include <QDialog>

namespace Ui {
class UIDemo01;
}

class UIDemo01 : public QDialog
{
    Q_OBJECT

public:
    explicit UIDemo01(QWidget *parent = 0);
    ~UIDemo01();

protected:
    bool eventFilter(QObject *watched, QEvent *event);

private:
    Ui::UIDemo01 *ui;

private slots:
    void initForm();
    void buttonClick();

private slots:
    void on_btnMenu_Min_clicked();
    void on_btnMenu_Max_clicked();
    void on_btnMenu_Close_clicked();
};

#endif // UIDEMO01_H
