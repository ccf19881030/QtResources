#include "dialog.h"
#include "ui_dialog.h"

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
    listA = new ProjectListWidget;
    listB = new ProjectListWidget;
    buttonAToB = new QPushButton("->");
    buttonBToA = new QPushButton("<-");

    listA->addItem("Giosue Carducci");
    listA->addItem("Eyvind Johnson");
    listA->addItem("Sally Prudhomme");
    listA->addItem("Henryk Sienkiewicz");
    listA->addItem("Carl Spitteler");
    listA->addItem("Rabindranath Tagore");
    listA->addItem("Kawabata Yasunari");

    listB->addItem("Rudolf Eucken");
    listB->addItem("Anatole France");
    listB->addItem("Rudyard Kipling");
    listB->addItem("Thomas Mann");
    listB->addItem("Eugene O'Neill");
    listB->addItem("Sigrid Undset");


    buttonAToB->setText("->");
    buttonBToA->setText("<-");

    QVBoxLayout *buttonLayout = new QVBoxLayout;
    buttonLayout->addWidget(buttonAToB);
    buttonLayout->addWidget(buttonBToA);

    QHBoxLayout *hboxLayout = new QHBoxLayout;
    hboxLayout->addWidget(listA);
    hboxLayout->addLayout(buttonLayout);
    hboxLayout->addWidget(listB);
    setLayout(hboxLayout);

    setFixedHeight( sizeHint().height() );

    connect(buttonAToB, SIGNAL(clicked()),
            this, SLOT(AToB_clicked()));
    connect(buttonBToA, SIGNAL(clicked()),
            this, SLOT(BToA_clicked()));
}

Dialog::~Dialog()
{
    delete ui;
}
