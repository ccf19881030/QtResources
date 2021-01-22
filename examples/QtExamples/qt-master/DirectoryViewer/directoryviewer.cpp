#include "directoryviewer.h"
#include "ui_directoryviewer.h"

DirectoryViewer::DirectoryViewer(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DirectoryViewer)
{
    ui->setupUi(this);

    //新建模型QDirModel，并且设置只读属性，排序按照目录优先，不区分大小写和以名字排序
    model = new QDirModel;
    model->setReadOnly(false);
    model->setSorting(QDir::DirsFirst | QDir::IgnoreCase | QDir::Name);

    //新建视图QTreeView
    treeView = new QTreeView;
    //将视图和模型关联起来
    treeView->setModel(model);
    //设置视图的属性
    treeView->header()->setStretchLastSection(true);
    treeView->header()->setSortIndicator(0, Qt::AscendingOrder);
    treeView->header()->setSortIndicatorShown(true);
    treeView->header()->setSectionsClickable(true);

    QModelIndex index = model->index(QDir::currentPath());
    //设定模型数据可扩展
    treeView->expand(index);
    treeView->scrollTo(index);
    treeView->resizeColumnToContents(0);

    buttonBox = new QDialogButtonBox(Qt::Horizontal);
    QPushButton *mkdirButton = buttonBox->addButton(
            tr("&Create Directory..."), QDialogButtonBox::ActionRole);
    QPushButton *removeButton = buttonBox->addButton(tr("&Remove"),
            QDialogButtonBox::ActionRole);
    buttonBox->addButton(tr("&Quit"), QDialogButtonBox::AcceptRole);

    connect(mkdirButton, SIGNAL(clicked()),
            this, SLOT(createDirectory()));
    connect(removeButton, SIGNAL(clicked()), this, SLOT(remove()));
    connect(buttonBox, SIGNAL(accepted()), this, SLOT(accept()));

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(treeView);
    mainLayout->addWidget(buttonBox);
    setLayout(mainLayout);

    setWindowTitle(tr("Directory Viewer"));
}

DirectoryViewer::~DirectoryViewer()
{
    delete ui;
}

void DirectoryViewer::createDirectory()
{
    //找到要创建文件夹的位置
    QModelIndex index = treeView->currentIndex();
    if (!index.isValid())
        return;

    QString dirName = QInputDialog::getText(this,
                              tr("Create Directory"),
                              tr("Directory name"));
    if (!dirName.isEmpty()) {
        //创建文件夹
        if (!model->mkdir(index, dirName).isValid())
            QMessageBox::information(this, tr("Create Directory"),
                    tr("Failed to create the directory"));
    }
}

void DirectoryViewer::remove()
{
    QModelIndex index = treeView->currentIndex();
    if (!index.isValid())
        return;

    bool ok;
    //判断是文件夹还是文件
    if (model->fileInfo(index).isDir()) {
        ok = model->rmdir(index);
    } else {
        ok = model->remove(index);
    }
    if (!ok)
        QMessageBox::information(this, tr("Remove"),
                tr("Failed to remove %1").arg(model->fileName(index)));
}
