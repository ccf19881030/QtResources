#include "window.h"
#include "ui_window.h"

Window::Window(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Window)
{
    ui->setupUi(this);

    //QItemEditorFactory提供一个widget，用来在视图中编辑数据
    QItemEditorFactory *factory = new QItemEditorFactory;

    //新建一个ColorListEditor编辑器
    QItemEditorCreatorBase *colorListCreator =
        new QStandardItemEditorCreator<ColorListEditor>();

    //将图像编辑器注册到QItemEditorFactory中
    factory->registerEditor(QVariant::Color, colorListCreator);

    QItemEditorFactory::setDefaultFactory(factory);

    createGUI();
}

Window::~Window()
{
    delete ui;
}

void Window::createGUI()
{
    QList<QPair<QString, QColor> > list;
    //新建三个默认的姓名--颜色对应数据
    list << QPair<QString, QColor>(tr("Alice"), QColor("aliceblue")) <<
            QPair<QString, QColor>(tr("Neptun"), QColor("aquamarine")) <<
            QPair<QString, QColor>(tr("Ferdinand"), QColor("springgreen"));

    //新建三行两列的数据
    QTableWidget *table = new QTableWidget(3, 2);
    //设定头部信息
    table->setHorizontalHeaderLabels(QStringList() << tr("Name")
                                                   << tr("Hair Color"));
    //Name这一列不可更改
    table->verticalHeader()->setVisible(false);
    table->resize(150, 50);

    //插入数据
    for (int i = 0; i < 3; ++i) {
        QPair<QString, QColor> pair = list.at(i);

        QTableWidgetItem *nameItem = new QTableWidgetItem(pair.first);
        QTableWidgetItem *colorItem = new QTableWidgetItem;
        colorItem->setData(Qt::DisplayRole, pair.second);

        table->setItem(i, 0, nameItem);
        table->setItem(i, 1, colorItem);
    }
    table->resizeColumnToContents(0);
    table->horizontalHeader()->setStretchLastSection(true);

    QGridLayout *layout = new QGridLayout;
    layout->addWidget(table, 0, 0);

    setLayout(layout);

    setWindowTitle(tr("Color Editor Factory"));
}
