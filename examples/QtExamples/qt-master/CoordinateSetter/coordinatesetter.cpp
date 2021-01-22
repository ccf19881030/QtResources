#include "coordinatesetter.h"
#include "ui_coordinatesetter.h"

CoordinateSetter::CoordinateSetter(QList<QPointF> *coords,
                                   QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CoordinateSetter)
{
    ui->setupUi(this);

    coordinates = coords;

    //创建0行两列
    tableWidget = new QTableWidget(0, 2);
    tableWidget->setHorizontalHeaderLabels(
            QStringList() << tr("X") << tr("Y"));

    for (int row = 0; row < coordinates->count(); ++row) {
        QPointF point = coordinates->at(row);
        //新增一行并显示行的内容
        addRow();
        tableWidget->item(row, 0)->setText(QString::number(point.x()));
        tableWidget->item(row, 1)->setText(QString::number(point.y()));
    }

    buttonBox = new QDialogButtonBox(Qt::Horizontal);
    QPushButton *addRowButton = buttonBox->addButton(tr("&Add Row"),
            QDialogButtonBox::ActionRole);
    buttonBox->addButton(QDialogButtonBox::Ok);
    buttonBox->addButton(QDialogButtonBox::Cancel);

    connect(addRowButton, SIGNAL(clicked()), this, SLOT(addRow()));
    connect(buttonBox, SIGNAL(accepted()), this, SLOT(accept()));
    connect(buttonBox, SIGNAL(rejected()), this, SLOT(reject()));

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(tableWidget);
    mainLayout->addWidget(buttonBox);
    setLayout(mainLayout);

    setWindowTitle(tr("Coordinate Setter"));
}

CoordinateSetter::~CoordinateSetter()
{
    delete ui;
}


//done的作用是当用户按下OK或者cancel后，执行的动作
void CoordinateSetter::done(int result)
{
    //当接收到Accepted信号后，将数据存入coordinates中
    if (result == QDialog::Accepted) {
        coordinates->clear();
        for (int row = 0; row < tableWidget->rowCount(); ++row) {
            double x = tableWidget->item(row, 0)->text().toDouble();
            double y = tableWidget->item(row, 1)->text().toDouble();
            coordinates->append(QPointF(x, y));
        }
    }
    QDialog::done(result);
}

void CoordinateSetter::addRow()
{
    int row = tableWidget->rowCount();

    //在row后面插入一行，此时tableWidget为新增的一行
    tableWidget->insertRow(row);

    //设置第一列
    QTableWidgetItem *item0 = new QTableWidgetItem;
    item0->setTextAlignment(Qt::AlignRight | Qt::AlignVCenter);
    tableWidget->setItem(row, 0, item0);

    //设置第二列
    QTableWidgetItem *item1 = new QTableWidgetItem;
    item1->setTextAlignment(Qt::AlignRight | Qt::AlignVCenter);
    tableWidget->setItem(row, 1, item1);

    tableWidget->setCurrentItem(item0);
}
