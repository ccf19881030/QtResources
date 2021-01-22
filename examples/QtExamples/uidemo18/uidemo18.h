#ifndef UIDEMO18_H
#define UIDEMO18_H

#include <QWidget>

class QToolButton;

namespace Ui {
class UIDemo18;
}

class UIDemo18 : public QWidget
{
    Q_OBJECT

public:
    explicit UIDemo18(QWidget *parent = 0);
    ~UIDemo18();

private:
    Ui::UIDemo18 *ui;
    QList<QToolButton *> btns;

private slots:
    void initForm();
    void initNav();
    void buttonClicked();

private slots:
    void on_btnReturn_pressed();
    void on_btnMsg_pressed();
};

#endif // UIDEMO18_H
