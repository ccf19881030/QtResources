#ifndef FILEVIEW_H
#define FILEVIEW_H

#include <QWidget>
#include <QDirModel>
#include <QFileSystemModel>
#include <QModelIndexList>
#include <QMenu>
#include <QAction>
#include <QtGui>

namespace Ui {
    class fileview;
}

class fileview : public QWidget {
    Q_OBJECT
public:
    fileview(QWidget *parent = 0);
    ~fileview();

protected:
    void changeEvent(QEvent *e);

private:
    Ui::fileview *ui;
public slots:

    void listDoubleClick(QModelIndex index);
    void treeDoubleClick(QModelIndex index);
    void detailClick();
    void listClick();
    void backClick();
    void forwardClick();
    void aheadClick();
    void displayMenu();
    void triggerdelAction();
    void triggercopyAction();
    void triggerpasteAction();
    void triggeropenAction();

    void changeModel();

public:
    //QFileSystemModel *comboModel;
    QFileSystemModel *listModel;

    QModelIndexList dirHistory;
    int dirHistoryPosi;

    QMenu *popMenu;

    QAction *copyAction;
    QAction *pasteAction;
    QAction *delAction;
    QAction *openAction;

    QFileInfo clipFileInfo;


    void appendHistory(QModelIndexList &modellist,QModelIndex model,int &listposi);
    void removeFirstHistory(QModelIndexList &modellist,int &listposi);
    void removeLastHistory(QModelIndexList &modellist,int &listposi);
};

#endif // FILEVIEW_H
