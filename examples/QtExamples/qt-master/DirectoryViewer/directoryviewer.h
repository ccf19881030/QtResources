#ifndef DIRECTORYVIEWER_H
#define DIRECTORYVIEWER_H

#include <QDialog>
#include <QTreeView>
#include <QDirModel>
#include <QDialogButtonBox>
#include <QPushButton>
#include <QVBoxLayout>
#include <QInputDialog>
#include <QMessageBox>

namespace Ui {
class DirectoryViewer;
}

class DirectoryViewer : public QDialog
{
    Q_OBJECT

public:
    explicit DirectoryViewer(QWidget *parent = 0);
    ~DirectoryViewer();

private slots:
    void createDirectory();
    void remove();

private:
    QTreeView *treeView;
    QDirModel *model;
    QDialogButtonBox *buttonBox;

private:
    Ui::DirectoryViewer *ui;
};

#endif // DIRECTORYVIEWER_H
