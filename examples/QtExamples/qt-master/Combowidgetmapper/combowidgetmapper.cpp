#include "combowidgetmapper.h"
#include "ui_combowidgetmapper.h"

Combowidgetmapper::Combowidgetmapper(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Combowidgetmapper)
{
    ui->setupUi(this);

    setupModel();

    nameLabel = new QLabel(tr("Na&me:"));
    nameEdit = new QLineEdit();
    addressLabel = new QLabel(tr("&Address:"));
    addressEdit = new QTextEdit();
    typeLabel = new QLabel(tr("&Type:"));
    typeComboBox = new QComboBox();
    nextButton = new QPushButton(tr("&Next"));
    previousButton = new QPushButton(tr("&Previous"));

    //设定伙伴关系--例如对nameLabel使用快捷键时候，会自动跳到nameEdit上
    nameLabel->setBuddy(nameEdit);
    addressLabel->setBuddy(addressEdit);
    typeLabel->setBuddy(typeComboBox);

    //typeModel为QStringListModel *，存储三个基本数据：Home，Work和Other
    typeComboBox->setModel(typeModel);

    //mapper用于存储输入的数据
    mapper = new QDataWidgetMapper(this);
    mapper->setModel(model);
    mapper->addMapping(nameEdit, 0);
    mapper->addMapping(addressEdit, 1);
    //由于typeComboBox是通过模型typeModel来读取的，所以我们需要currentIndex属性来获取数据
    mapper->addMapping(typeComboBox, 2, "currentIndex");

    //信号槽的编写
    connect(previousButton, SIGNAL(clicked()),
            mapper, SLOT(toPrevious()));
    connect(nextButton, SIGNAL(clicked()),
            mapper, SLOT(toNext()));
    connect(mapper, SIGNAL(currentIndexChanged(int)),
            this, SLOT(updateButtons(int)));

    //界面布局
    QGridLayout *layout = new QGridLayout();
    layout->addWidget(nameLabel, 0, 0, 1, 1);
    layout->addWidget(nameEdit, 0, 1, 1, 1);
    layout->addWidget(previousButton, 0, 2, 1, 1);
    layout->addWidget(addressLabel, 1, 0, 1, 1);
    layout->addWidget(addressEdit, 1, 1, 2, 1);
    layout->addWidget(nextButton, 1, 2, 1, 1);
    layout->addWidget(typeLabel, 3, 0, 1, 1);
    layout->addWidget(typeComboBox, 3, 1, 1, 1);
    setLayout(layout);

    setWindowTitle(tr("Delegate Widget Mapper"));
    mapper->toFirst();
}

Combowidgetmapper::~Combowidgetmapper()
{
    delete ui;
}

void Combowidgetmapper::setupModel()
{
    QStringList items;
    items << tr("Home") << tr("Work") << tr("Other");
    typeModel = new QStringListModel(items, this);

    //创建一个5行3列的模型
    model = new QStandardItemModel(5, 3, this);
    QStringList names;
    names << "Alice" << "Bob" << "Carol" << "Donald" << "Emma";
    QStringList addresses;
    addresses << "<qt>123 Main Street<br/>Market Town</qt>"
              << "<qt>PO Box 32<br/>Mail Handling Service"
                 "<br/>Service City</qt>"
              << "<qt>The Lighthouse<br/>Remote Island</qt>"
              << "<qt>47338 Park Avenue<br/>Big City</qt>"
              << "<qt>Research Station<br/>Base Camp<br/>Big Mountain</qt>";

    QStringList types;
    types << "0" << "1" << "2" << "0" << "2";

    //将数据分别写入模型中
    for (int row = 0; row < 5; ++row) {
        QStandardItem *item = new QStandardItem(names[row]);
        model->setItem(row, 0, item);
        item = new QStandardItem(addresses[row]);
        model->setItem(row, 1, item);
        item = new QStandardItem(types[row]);
        model->setItem(row, 2, item);
    }
}

void Combowidgetmapper::updateButtons(int row)
{
    previousButton->setEnabled(row > 0);
    nextButton->setEnabled(row < model->rowCount() - 1);
}
