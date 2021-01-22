#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

private slots:
    void on_btnLine_clicked();
    void on_btnLinex_clicked();
    void on_btnLiney_clicked();
    void on_btnBar_clicked();

    void on_btnBarx_clicked();

    void on_btnBary_clicked();

    void on_btnScatter_clicked();

    void on_btnK_clicked();

    void on_btnPie_clicked();

    void on_btnRadar_clicked();

    void on_btnChord_clicked();

    void on_btnGauge_clicked();

    void on_btnFunnel_clicked();

    void on_btnData_clicked();

private:
    Ui::Widget *ui;
};

#endif // WIDGET_H
