#include "flowchartsymbolpicker.h"
#include "ui_flowchartsymbolpicker.h"

flowchartsymbolpicker::flowchartsymbolpicker(
        const QMap<int, QString> &symbolMap, QWidget *parent)
    : QDialog(parent)
{
    ui->setupUi(this);

    id = -1;

    //视图
    listWidget = new QListWidget;
    listWidget->setIconSize(QSize(60, 60));

    //创建一个项视图类来查看数据
    QMapIterator<int, QString> i(symbolMap);
    while (i.hasNext()) {
        i.next();
        //为每一个数据构建一个项视图(MV结构：M为模型数据：i.value()，而V为视图：listWidget)
        QListWidgetItem *item = new QListWidgetItem(i.value(),
                                                    listWidget);
        //设定一个Icon(视图)
        item->setIcon(iconForSymbol(i.value()));
        //将ID保存到QListWidgetItem中去---Qt::UserRole为自定义角色(模型数据)
        item->setData(Qt::UserRole, i.key());
    }

    buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok
                                     | QDialogButtonBox::Cancel);

    connect(buttonBox, SIGNAL(accepted()), this, SLOT(accept()));
    connect(buttonBox, SIGNAL(rejected()), this, SLOT(reject()));

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(listWidget);
    mainLayout->addWidget(buttonBox);
    setLayout(mainLayout);

    setWindowTitle(tr("Flowchart Symbol Picker"));
}

flowchartsymbolpicker::~flowchartsymbolpicker()
{
    delete ui;
}

void flowchartsymbolpicker::done(int result)
{
    id = -1;
    if (result == QDialog::Accepted) {
        QListWidgetItem *item = listWidget->currentItem();
        if (item)
            id = item->data(Qt::UserRole).toInt();
    }
    QDialog::done(result);
}

QIcon flowchartsymbolpicker::iconForSymbol(const QString &symbolName)
{
    QString fileName = ":/images/" + symbolName.toLower();
    fileName.replace(' ', '-');
    return QIcon(fileName);
}
