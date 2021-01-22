#include <QDirModel>
#include <QDebug>
#include <QMimeData>

#include "fileview.h"
#include "ui_fileview.h"

fileview::fileview(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::fileview)
{
    ui->setupUi(this);

    dirHistoryPosi = 0;

    popMenu = new QMenu(this);
    openAction = new QAction(QIcon(":/images/menu/menu"),tr("打开"),this);
    copyAction = new QAction(QIcon(":/images/menu/menu"),tr("复制文件"),this);
    pasteAction = new QAction(QIcon(":/images/menu/menu"),tr("粘贴到这里"),this);
    delAction = new QAction(QIcon(":/images/menu/menu"),tr("删除文件"),this);

    connect(copyAction,SIGNAL(triggered()),this,SLOT(triggercopyAction()));
    connect(pasteAction,SIGNAL(triggered()),this,SLOT(triggerpasteAction()));
    connect(delAction,SIGNAL(triggered()),this,SLOT(triggerdelAction()));
    connect(openAction,SIGNAL(triggered()),this,SLOT(triggeropenAction()));

    popMenu->addAction((openAction));
    popMenu->addSeparator();
    popMenu->addAction(copyAction);
    popMenu->addAction(pasteAction);
    popMenu->addSeparator();
    popMenu->addAction(delAction);


    listModel = new QFileSystemModel(this);
    listModel->setFilter(QDir::AllEntries | QDir::NoDotAndDotDot);
    //listModel->setFilter(QDir::AllEntries);
    listModel->setRootPath("/");

    ui->listView->setModel(listModel);
    //listModel->setFilter(QDir::AllEntries | QDir::NoDotAndDotDot);
    QModelIndex listcurrentIndex = listModel->index("/");
    //QModelIndex listcurrentIndex = listModel->setRootPath("/");
    ui->listView->setRootIndex(listcurrentIndex);
    //dirHistory.append(listcurrentIndex);
    //dirHistoryPosi = dirHistory.count();
    appendHistory(dirHistory,listcurrentIndex,dirHistoryPosi);

    ui->listView->setViewMode(QListView::IconMode);

    connect(ui->listView,SIGNAL(doubleClicked(QModelIndex)),this,SLOT(listDoubleClick(QModelIndex)));

    ui->treeView->setModel(listModel);
    connect(ui->treeView,SIGNAL(doubleClicked(QModelIndex)),this,SLOT(treeDoubleClick(QModelIndex)));


    connect(ui->listButton,SIGNAL(clicked()),this,SLOT(listClick()));
    connect(ui->detailButton,SIGNAL(clicked()),this,SLOT(detailClick()));
    connect(ui->backButton,SIGNAL(clicked()),this,SLOT(backClick()));
    connect(ui->forwardButton,SIGNAL(clicked()),this,SLOT(forwardClick()));
    connect(ui->aheadButton,SIGNAL(clicked()),this,SLOT(aheadClick()));

    connect(ui->treeView,SIGNAL(pressed(QModelIndex)),this,SLOT(displayMenu()));
    connect(ui->listView,SIGNAL(pressed(QModelIndex)),this,SLOT(displayMenu()));

    connect(ui->closeButton,SIGNAL(clicked()),this,SLOT(close()));

    connect(listModel,SIGNAL(dataChanged(QModelIndex,QModelIndex)),this,SLOT(changeModel()));

}

fileview::~fileview()
{
    delete ui;
}

void fileview::changeEvent(QEvent *e)
{
    QWidget::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}

void fileview::listDoubleClick(QModelIndex index)
{
    qDebug()<<listModel->fileName(index);
    //ui->listView->setCurrentIndex(index);
    //listModel->setFilter(QDir::AllEntries | QDir::NoDotAndDotDot);

    if(listModel->fileName(index) == "..")
    {
        if(dirHistory.count()>1)
        {
            ui->listView->setRootIndex(dirHistory.at(dirHistory.count()-2));
            dirHistory.removeLast();
        }
    }
    else if(listModel->fileName(index) == ".")
    {
    }
    else
    {
        ui->listView->setRootIndex(index);
        //dirHistory.append(index);
        appendHistory(dirHistory,index,dirHistoryPosi);
    }

}

void fileview::treeDoubleClick(QModelIndex index)
{
    qDebug()<<listModel->fileName(index);
    //ui->listView->setCurrentIndex(index);
    //listModel->setFilter(QDir::AllEntries | QDir::NoDotAndDotDot);

    if(listModel->fileName(index) == "..")
    {
        if(dirHistory.count()>1)
        {
            ui->listView->setRootIndex(dirHistory.at(dirHistory.count()-2));
            dirHistory.removeLast();
        }
    }
    else if(listModel->fileName(index) == ".")
    {
    }
    else
    {
        ui->treeView->setRootIndex(index);
        //dirHistory.append(index);
        appendHistory(dirHistory,index,dirHistoryPosi);
    }
}

void fileview::detailClick()
{
    //listModel->setFilter(QDir::AllEntries|QDir::NoDotAndDotDot);
    ui->stackedWidget->setCurrentIndex(1);

    //qDebug()<<dirHistory.count();
    ui->treeView->setRootIndex(dirHistory.at(dirHistoryPosi-1));
}

void fileview::listClick()
{
    //listModel->setFilter(QDir::AllEntries|QDir::NoDotAndDotDot);
    ui->stackedWidget->setCurrentIndex(0);
    ui->listView->setRootIndex(dirHistory.at(dirHistoryPosi-1));
}

void fileview::backClick()
{
    if(dirHistoryPosi>1)
    {
        dirHistoryPosi--;
        //qDebug()<<dirHistoryPosi;
        ui->listView->setRootIndex(dirHistory.at(dirHistoryPosi-1));
        ui->treeView->setRootIndex(dirHistory.at(dirHistoryPosi-1));
        ui->forwardButton->setEnabled(true);
    }
    else
    {
        ui->backButton->setEnabled(false);
    }
}

void fileview::forwardClick()
{
    if(dirHistoryPosi<dirHistory.count())
    {
        dirHistoryPosi++;
        //qDebug()<<dirHistoryPosi;
        ui->listView->setRootIndex(dirHistory.at(dirHistoryPosi-1));
        ui->treeView->setRootIndex(dirHistory.at(dirHistoryPosi-1));
        ui->backButton->setEnabled(true);
    }
    else
    {
        ui->forwardButton->setEnabled(false);
    }
}

void fileview::aheadClick()
{
    QModelIndex index;
    QFileInfo file;
    switch(ui->stackedWidget->currentIndex())
    {
    case 0:
        file = listModel->fileInfo(ui->listView->rootIndex());
        break;
    case 1:
        file = listModel->fileInfo(ui->treeView->rootIndex());
        break;
    }
    index = listModel->index(file.absolutePath());
    ui->listView->setRootIndex(index);
    ui->treeView->setRootIndex(index);
    appendHistory(dirHistory,index,dirHistoryPosi);


}

void fileview::appendHistory(QModelIndexList &modellist, QModelIndex model,int &listposi)
{
    //以下删除当前位置以后的全部位置记录
    while(listposi<modellist.count())
    {
        modellist.removeLast();
    }
    //////////////////////////////////
    modellist.append(model);
    listposi++;
    ui->backButton->setEnabled(true);
    ui->forwardButton->setEnabled(false);
}

void fileview::removeFirstHistory(QModelIndexList &modellist, int &listposi)
{
    if(modellist.count()>0)
    {
        modellist.removeFirst();
        listposi--;
    }
}
void fileview::removeLastHistory(QModelIndexList &modellist, int &listposi)
{
    if(modellist.count()>0)
    {
        modellist.removeLast();
        if(listposi>modellist.count())
        {
            listposi = modellist.count();
        }
    }
}

void fileview::displayMenu()
{
    QFileInfo disfile;
    switch(ui->stackedWidget->currentIndex())
    {
    case 0:
        disfile = listModel->fileInfo(ui->listView->currentIndex());

        break;
    case 1:
        disfile = listModel->fileInfo(ui->treeView->currentIndex());
        qDebug()<<"select file is"<<disfile.absoluteFilePath();
        break;
    }

    if(!disfile.isDir()) //是文件
    {
        openAction->setVisible(false);
        copyAction->setVisible(true);
        pasteAction->setVisible(false);
        delAction->setVisible(true);
    }
    else //是文件夹
    {
        openAction->setVisible(true);
        copyAction->setVisible(false);
        if(clipFileInfo.exists())
        {
            pasteAction->setVisible(true);
        }
        else
        {
            pasteAction->setVisible(false);
        }
        delAction->setVisible(false);
    }

    popMenu->exec(QCursor::pos()); // 菜单出现的位置为当前鼠标的位置
    //popMenu->menuAction()->setVisible(false);

}

void fileview::triggercopyAction()
{
    qDebug()<<"copy file";

    switch(ui->stackedWidget->currentIndex())
    {
    case 0:
        clipFileInfo = listModel->fileInfo(ui->listView->currentIndex());
        break;
    case 1:
        clipFileInfo = listModel->fileInfo(ui->treeView->currentIndex());
        break;
    }
    qDebug()<<clipFileInfo.absoluteFilePath();

}

void fileview::triggerpasteAction()
{
    QFileInfo pastefile;
    QString pastename;

    if(!clipFileInfo.exists()) return;

    switch(ui->stackedWidget->currentIndex())
    {
    case 0:
        pastefile = listModel->fileInfo(ui->listView->currentIndex());
        break;
    case 1:
        pastefile = listModel->fileInfo(ui->treeView->currentIndex());
        break;
    }

    if(pastefile == clipFileInfo)
    {
        qDebug()<<"file exist";
    }
    else if(!pastefile.isDir())
    {
        qDebug()<<"not dir";
    }
    else
    {
        pastename = pastefile.absoluteFilePath()+"/"+clipFileInfo.fileName();
        qDebug()<<"paste file is "<< pastename;
        if(QFile::exists(pastename))
        {
            QFile::remove(pastename);
        }
        if(QFile::copy(clipFileInfo.absoluteFilePath(),pastename))
        {
            qDebug()<<"copy success";
        }
        else
        {
            qDebug()<<"copy fail";
        }

    }

}

void fileview::triggerdelAction()
{
    qDebug()<<"del file";
    switch(ui->stackedWidget->currentIndex())
    {
    case 0:
        listModel->remove(ui->listView->currentIndex());
        break;
    case 1:
        listModel->remove(ui->treeView->currentIndex());
        break;
    }
}

void fileview::triggeropenAction()
{
    switch(ui->stackedWidget->currentIndex())
    {
    case 0:
        listDoubleClick(ui->listView->currentIndex());
        break;
    case 1:
        treeDoubleClick(ui->treeView->currentIndex());
        break;
    }

}

void fileview::changeModel()
{

}
