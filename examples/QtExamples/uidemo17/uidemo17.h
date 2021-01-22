#ifndef UIDEMO17_H
#define UIDEMO17_H

#include <QDialog>

namespace Ui {
class UIDemo17;
}

class UIDemo17 : public QDialog
{
    Q_OBJECT

public:
    explicit UIDemo17(QWidget *parent = 0);
    ~UIDemo17();

protected:
    bool eventFilter(QObject *watched, QEvent *event);

private:
    Ui::UIDemo17 *ui;    

private slots:
    void initForm();
    void initStyle();
    void initList();

private slots:
    void on_btnMenu_Min_clicked();
    void on_btnMenu_Max_clicked();
    void on_btnMenu_Close_clicked();
};

#endif // UIDEMO17_H
