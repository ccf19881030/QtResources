#ifndef TEAMLEADERSDIALOG_H
#define TEAMLEADERSDIALOG_H

#include <QDialog>
#include <QListView>
#include <QDialogButtonBox>
#include <QStringListModel>
#include <QPushButton>
#include <QVBoxLayout>

namespace Ui {
class TeamLeadersDialog;
}

class TeamLeadersDialog : public QDialog
{
    Q_OBJECT 

public:
    TeamLeadersDialog(const QStringList &leaders, QWidget *parent = 0);
    ~TeamLeadersDialog();

    QStringList leaders() const;

private slots:
    void insert();
    void del();

private:
    QListView *listView;
    QDialogButtonBox *buttonBox;
    QStringListModel *model;

private:
    Ui::TeamLeadersDialog *ui;
};

#endif // TEAMLEADERSDIALOG_H
