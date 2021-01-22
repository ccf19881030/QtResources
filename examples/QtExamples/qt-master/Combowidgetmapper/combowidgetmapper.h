#ifndef COMBOWIDGETMAPPER_H
#define COMBOWIDGETMAPPER_H

#include <QWidget>
#include <QComboBox>
#include <QDataWidgetMapper>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QStandardItemModel>
#include <QStringListModel>
#include <QTextEdit>
#include <QGridLayout>

namespace Ui {
class Combowidgetmapper;
}

class Combowidgetmapper : public QWidget
{
    Q_OBJECT

public:
    explicit Combowidgetmapper(QWidget *parent = 0);
    ~Combowidgetmapper();

private slots:
    //用于更新previousButton和nextButton按钮是否有效
    void updateButtons(int row);

private:
    //设定模型
    void setupModel();

    QLabel *nameLabel;
    QLabel *addressLabel;
    QLabel *typeLabel;
    QLineEdit *nameEdit;
    QTextEdit *addressEdit;
    QComboBox *typeComboBox;
    QPushButton *nextButton;
    QPushButton *previousButton;

    QStandardItemModel *model;
    QStringListModel *typeModel;
    QDataWidgetMapper *mapper;

private:
    Ui::Combowidgetmapper *ui;
};

#endif // COMBOWIDGETMAPPER_H
