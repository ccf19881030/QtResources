#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "TreeModel.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_treeView_customContextMenuRequested(const QPoint&pos);
    
    void on_pushButton_clicked();

    void on_treeView_clicked(const QModelIndex &index);

private:
    Ui::MainWindow *ui;
    TreeModel *m_pTreeModel;
};

#endif // MAINWINDOW_H
