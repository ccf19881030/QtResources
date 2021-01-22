#ifndef UIDEMO10_H
#define UIDEMO10_H

#include <QDialog>

namespace Ui {
class UIDemo10;
}

class UIDemo10 : public QDialog
{
    Q_OBJECT

public:
    explicit UIDemo10(QWidget *parent = 0);
    ~UIDemo10();

private:
    Ui::UIDemo10 *ui;

private slots:
    void initForm();
    void buttonClicked();
};

#endif // UIDEMO10_H
