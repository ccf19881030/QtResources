#ifndef COLORNAMESDIALOG_H
#define COLORNAMESDIALOG_H

#include <QDialog>
#include <QStringListModel>
#include <QSortFilterProxyModel>
#include <QListView>
#include <QLabel>
#include <QLineEdit>
#include <QComboBox>
#include <QGridLayout>

namespace Ui {
class ColorNamesDialog;
}

class ColorNamesDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ColorNamesDialog(QWidget *parent = 0);
    ~ColorNamesDialog();

private slots:
    void reapplyFilter();

private:
    QStringListModel *sourceModel;
    QSortFilterProxyModel *proxyModel;
    QListView *listView;
    QLabel *filterLabel;
    QLabel *syntaxLabel;
    QLineEdit *filterLineEdit;
    QComboBox *syntaxComboBox;

private:
    Ui::ColorNamesDialog *ui;
};

#endif // COLORNAMESDIALOG_H
