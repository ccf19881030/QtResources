#include "teamleadersdialog.h"
#include "ui_teamleadersdialog.h"

TeamLeadersDialog::TeamLeadersDialog(const QStringList &leaders,
                                     QWidget *parent) :
    QDialog(parent),
    ui(new Ui::TeamLeadersDialog)
{
    ui->setupUi(this);
    //新建一个QStringListModel模型
    model = new QStringListModel(this);
    //初始化模型数据
    model->setStringList(leaders);

    //listView为视图，数据从模型model中获取
    listView = new QListView;
    listView->setModel(model);
    listView->setEditTriggers(QAbstractItemView::AnyKeyPressed
                              | QAbstractItemView::DoubleClicked);

    buttonBox = new QDialogButtonBox();
    QPushButton *insertButton = buttonBox->addButton(tr("&Insert"),
            QDialogButtonBox::ActionRole);
    QPushButton *deleteButton = buttonBox->addButton(tr("&Delete"),
            QDialogButtonBox::ActionRole);
    buttonBox->addButton(QDialogButtonBox::Ok);
    buttonBox->addButton(QDialogButtonBox::Cancel);

    connect(insertButton, SIGNAL(clicked()), this, SLOT(insert()));
    connect(deleteButton, SIGNAL(clicked()), this, SLOT(del()));
    connect(buttonBox, SIGNAL(accepted()), this, SLOT(accept()));
    connect(buttonBox, SIGNAL(rejected()), this, SLOT(reject()));

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(listView);
    mainLayout->addWidget(buttonBox);
    setLayout(mainLayout);

    setWindowTitle(tr("Team Leaders"));
}

TeamLeadersDialog::~TeamLeadersDialog()
{
    delete ui;
}

QStringList TeamLeadersDialog::leaders() const
{
    return model->stringList();
}

void TeamLeadersDialog::insert()
{
    //模型用于操作实际的数据--如新增一行，删除一行，然后通过视图来显示
    int row = listView->currentIndex().row();
    model->insertRows(row, 1);

    //但是新增一行的内容必须在视图上进行填写
    QModelIndex index = model->index(row);
    listView->setCurrentIndex(index);
    listView->edit(index);
}

void TeamLeadersDialog::del()
{
    model->removeRows(listView->currentIndex().row(), 1);
}
