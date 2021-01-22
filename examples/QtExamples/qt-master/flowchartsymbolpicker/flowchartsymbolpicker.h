#ifndef FLOWCHARTSYMBOLPICKER_H
#define FLOWCHARTSYMBOLPICKER_H

#include <QDialog>
#include <QDialogButtonBox>
#include <QIcon>
#include <QListWidget>
#include <QVBoxLayout>

namespace Ui {
class flowchartsymbolpicker;
}

class flowchartsymbolpicker : public QDialog
{
    Q_OBJECT

public:
    flowchartsymbolpicker(const QMap<int, QString> &symbolMap,
                          QWidget *parent = 0);
    ~flowchartsymbolpicker();

    int selectedId() const { return id; }
    void done(int result);

private:
    QIcon iconForSymbol(const QString &symbolName);

    QListWidget *listWidget;
    QDialogButtonBox *buttonBox;
    int id;

private:
    Ui::flowchartsymbolpicker *ui;
};

#endif // FLOWCHARTSYMBOLPICKER_H
