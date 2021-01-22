#include "frmmain.h"
#include "ui_frmmain.h"

frmMain::frmMain(QWidget *parent) :
        QWidget(parent),
        ui(new Ui::frmMain)
{
    ui->setupUi(this);
    this->InitTab1();
    this->ChangeVisibleTab1(false);
    this->InitTab2();
    this->ChangeVisibleTab2(false);
    connect(ui->tabWidget,SIGNAL(currentChanged(int)),this,SLOT(TabChange(int)));
}

frmMain::~frmMain()
{
    delete ui;
}

void frmMain::TabChange(int index)
{
    if (index==0)
    {
        this->ChangeVisibleTab1(false);
    }
    else
    {
        this->ChangeVisibleTab2(false);
    }
}

void frmMain::InitTab1()
{
    mainLayout1=new QVBoxLayout();
    mainLayout1->setSpacing(0);
    mainLayout1->setContentsMargins(0,0,0,0);
    layout1=new QHBoxLayout();
    layout1->setSpacing(0);
    layout1->setContentsMargins(0,0,0,0);

    gauge1=new myGauge1(ui->fm1);
    gauge2=new myGauge2(ui->fm1);
    gauge2->setAnimating(true);

    gauge31=new myGauge3(ui->fm1);
    gauge31->setRange(0,50);
    gauge31->SetmyTopColor(Qt::red);
    connect(gauge31,SIGNAL(valueChanged(qreal)),this,SLOT(UpdateData3(qreal)));

    gauge32=new myGauge3(ui->fm1);
    gauge32->setRange(0,100);
    gauge32->SetmyTopColor(Qt::cyan);
    connect(gauge32,SIGNAL(valueChanged(qreal)),this,SLOT(UpdateData3(qreal)));

    gauge33=new myGauge3(ui->fm1);
    gauge33->setRange(30,120);
    gauge33->SetmyTopColor(Qt::green);
    connect(gauge33,SIGNAL(valueChanged(qreal)),this,SLOT(UpdateData3(qreal)));

    gauge41=new myGauge4(ui->fm1);
    gauge41->setValue(50);
    gauge41->SetmyLineColor(Qt::red);
    gauge42=new myGauge4(ui->fm1);
    gauge42->setValue(30);
    gauge42->SetmyLineColor(Qt::cyan);
    gauge43=new myGauge4(ui->fm1);
    gauge43->setValue(100);
    gauge43->SetmyLineColor(Qt::green);

    gauge5=new myGauge5(ui->fm1);

    gauge61=new myGauge6(ui->fm1);
    gauge61->setAnimating(true);
    gauge61->SetGraphColor(Qt::green);
    gauge62=new myGauge6(ui->fm1);
    gauge62->setAnimating(true);
    gauge62->SetGraphColor(Qt::blue);
    gauge63=new myGauge6(ui->fm1);
    gauge63->setAnimating(true);
    gauge63->SetGraphColor(Qt::red);

    gauge71=new myGauge7(ui->fm1);
    gauge71->SetGraphColor(Qt::red);
    gauge72=new myGauge7(ui->fm1);
    gauge72->SetGraphColor(Qt::green);
    gauge73=new myGauge7(ui->fm1);
    gauge73->SetGraphColor(Qt::blue);

    myprogressbar1=new myProgressBar(ui->fm1);
    myprogressbar1->setInterval(20);
    myprogressbar2=new myProgressBar(ui->fm1);
    myprogressbar2->setInterval(60);
    myprogressbar3=new myProgressBar(ui->fm1);
    myprogressbar3->setInterval(150);

    mybattery1=new myBattery(ui->fm1);
    mybattery2=new myBattery(ui->fm1);
    mybattery3=new myBattery(ui->fm1);
    mybattery4=new myBattery(ui->fm1);

    mycoolbar=new myCoolBar(ui->fm1);
    mycoolbar->setRange(0,100);
    mycoolbar->setValue(60);
    connect(mycoolbar,SIGNAL(valueChanged(int)),this,SLOT(UpdateData9(int)));

    myindicator1=new myIndicator(ui->fm1);
    myindicator1->SetForeColor(Qt::green);
    myindicator2=new myIndicator(ui->fm1);
    myindicator2->SetForeColor(Qt::red);
    myindicator3=new myIndicator(ui->fm1);
    myindicator3->SetForeColor(Qt::black);
    myindicator4=new myIndicator(ui->fm1);
    myindicator4->SetForeColor(Qt::blue);
    myindicator5=new myIndicator(ui->fm1);
    myindicator5->SetForeColor(Qt::cyan);

    myvolume1=new myVolume(ui->fm1);
    myvolume2=new myVolume(ui->fm1);
    myvolume3=new myVolume(ui->fm1);
    myvolume4=new myVolume(ui->fm1);
    myvolume5=new myVolume(ui->fm1);

    mainLayout1->addWidget(gauge1);
    mainLayout1->addWidget(gauge2);
    mainLayout1->addWidget(gauge31);
    mainLayout1->addWidget(gauge32);
    mainLayout1->addWidget(gauge33);
    mainLayout1->addWidget(gauge41);
    mainLayout1->addWidget(gauge42);
    mainLayout1->addWidget(gauge43);
    mainLayout1->addWidget(gauge5);

    mainLayout1->addWidget(myprogressbar1);
    mainLayout1->addWidget(myprogressbar2);
    mainLayout1->addWidget(myprogressbar3);

    mainLayout1->addWidget(mybattery1);
    mainLayout1->addWidget(mybattery2);
    mainLayout1->addWidget(mybattery3);
    mainLayout1->addWidget(mybattery4);
    mainLayout1->addWidget(mycoolbar);

    mainLayout1->addLayout(layout1);

    layout1->addWidget(gauge61);
    layout1->addWidget(gauge62);
    layout1->addWidget(gauge63);

    layout1->addWidget(gauge71);
    layout1->addWidget(gauge72);
    layout1->addWidget(gauge73);

    layout1->addWidget(myindicator1);
    layout1->addWidget(myindicator2);
    layout1->addWidget(myindicator3);
    layout1->addWidget(myindicator4);
    layout1->addWidget(myindicator5);

    layout1->addWidget(myvolume1);
    layout1->addWidget(myvolume2);
    layout1->addWidget(myvolume3);
    layout1->addWidget(myvolume4);
    layout1->addWidget(myvolume5);

    ui->fm1->setLayout(mainLayout1);

    updateTimer1=new QTimer(this);
    updateTimer1->setInterval(3000);
    connect(updateTimer1,SIGNAL(timeout()),this,SLOT(UpdateData1()));

    updateTimer2=new QTimer(this);
    updateTimer2->setInterval(3000);
    connect(updateTimer2,SIGNAL(timeout()),this,SLOT(UpdateData2()));

    updateTimer4=new QTimer(this);
    updateTimer4->setInterval(3000);
    connect(updateTimer4,SIGNAL(timeout()),this,SLOT(UpdateData4()));

    updateTimer5=new QTimer(this);
    updateTimer5->setInterval(3000);
    connect(updateTimer5,SIGNAL(timeout()),this,SLOT(UpdateData5()));

    updateTimer6=new QTimer(this);
    updateTimer6->setInterval(3000);
    connect(updateTimer6,SIGNAL(timeout()),this,SLOT(UpdateData6()));

    updateTimer7=new QTimer(this);
    updateTimer7->setInterval(3000);
    connect(updateTimer7,SIGNAL(timeout()),this,SLOT(UpdateData7()));

    updateTimer8=new QTimer(this);
    updateTimer8->setInterval(3000);
    connect(updateTimer8,SIGNAL(timeout()),this,SLOT(UpdateData8()));

    updateTimer10=new QTimer(this);
    updateTimer10->setInterval(3000);
    connect(updateTimer10,SIGNAL(timeout()),this,SLOT(UpdateData10()));

    updateTimer11=new QTimer(this);
    updateTimer11->setInterval(500);
    connect(updateTimer11,SIGNAL(timeout()),this,SLOT(UpdateData11()));
}

void frmMain::InitTab2()
{
    mainLayout2=new QVBoxLayout();
    mainLayout2->setSpacing(0);
    mainLayout2->setContentsMargins(0,0,0,0);
    layout2=new QHBoxLayout();
    layout2->setSpacing(0);
    layout2->setContentsMargins(0,0,0,0);

    mychart1=new myChart1(ui->fm2);
    mychart1->setTitle(tr("图表示例"));

    myflashlist=new myFlashList(ui->fm2);
    for(int i = 0;i < 100 ; i++)
    {
        myflashlist->addItem(tr("列表%1").arg(i));
    }
    connect(myflashlist,SIGNAL(sig_itemClicked(QString)),this,SLOT(UpdateData22(QString)));

    mybuttonboard=new myButtonBoard(ui->fm2);
    for(int i = 0;i < 100 ; i++)
    {
        mybuttonboard->addButton(tr("按钮%1").arg(i));
    }
    connect(mybuttonboard,SIGNAL(sig_ButtonClicked(QString)),this,SLOT(UpdateData23(QString)));

    mysliderbutton1=new mySliderButton(ui->fm2);
    mysliderbutton1->SetmyBGColor(QColor(46,132,243),QColor(39,110,203));

    mysliderbutton2=new mySliderButton(ui->fm2);
    mysliderbutton2->SetmyBGColor(QColor(255,177,42),QColor(225,156,37));

    mysliderbutton3=new mySliderButton(ui->fm2);
    mysliderbutton3->SetmyBGColor(QColor(148,255,82),QColor(133,229,73));

    connect(mysliderbutton1,SIGNAL(sig_itemClicked(QString)),this,SLOT(UpdateData24(QString)));
    connect(mysliderbutton2,SIGNAL(sig_itemClicked(QString)),this,SLOT(UpdateData24(QString)));
    connect(mysliderbutton3,SIGNAL(sig_itemClicked(QString)),this,SLOT(UpdateData24(QString)));
    mysliderbutton1->addItem("星期一");
    mysliderbutton1->addItem("星期二");
    mysliderbutton1->addItem("星期三");
    mysliderbutton1->addItem("星期四");
    mysliderbutton1->addItem("星期五");
    mysliderbutton1->addItem("星期六");
    mysliderbutton1->addItem("星期天");
    mysliderbutton2->addItem("星期一");
    mysliderbutton2->addItem("星期二");
    mysliderbutton2->addItem("星期三");
    mysliderbutton2->addItem("星期四");
    mysliderbutton2->addItem("星期五");
    mysliderbutton2->addItem("星期六");
    mysliderbutton2->addItem("星期天");
    mysliderbutton3->addItem("星期一");
    mysliderbutton3->addItem("星期二");
    mysliderbutton3->addItem("星期三");
    mysliderbutton3->addItem("星期四");
    mysliderbutton3->addItem("星期五");
    mysliderbutton3->addItem("星期六");
    mysliderbutton3->addItem("星期天");

    myphotoview=new myPhotoView(ui->fm2);
    myaroundcircle=new myAroundCircle(ui->fm2);

    myprogressbar11=new myProgressBar1(ui->fm2);
    myprogressbar12=new myProgressBar1(ui->fm2);
    myprogressbar13=new myProgressBar1(ui->fm2);

    mynewled=new myNewLed(ui->fm2);
    mynewled->SetmyLedColor(QColor(55,142,234),QColor(48,125,207));

    mywave=new myWave(ui->fm2);
    mywave->setChannelCount(100);

    for (int i=0;i<33;i++)
    {
        myWave1 *wave1=new myWave1(ui->fm2);
        mywave1.push_back(wave1);
        layout2->addWidget(wave1);
    }

    for (int i=0;i<50;i++)
    {
        myWave2 *wave2=new myWave2(ui->fm2);
        wave2->setMaximumWidth(10);
        wave2->setRange(0,100);
        mywave2.push_back(wave2);
        layout2->addWidget(wave2);
    }


    mainLayout2->addWidget(mychart1);
    mainLayout2->addWidget(myflashlist);
    mainLayout2->addWidget(mybuttonboard);
    mainLayout2->addWidget(mysliderbutton1);
    mainLayout2->addWidget(mysliderbutton2);
    mainLayout2->addWidget(mysliderbutton3);
    mainLayout2->addWidget(myphotoview);
    mainLayout2->addWidget(myaroundcircle);

    mainLayout2->addWidget(myprogressbar11);
    mainLayout2->addWidget(myprogressbar12);
    mainLayout2->addWidget(myprogressbar13);

    mainLayout2->addWidget(mynewled);

    mainLayout2->addWidget(mywave);


    mainLayout2->addLayout(layout2);
    ui->fm2->setLayout(mainLayout2);

    updateTimer21=new QTimer(this);
    updateTimer21->setInterval(300);
    connect(updateTimer21,SIGNAL(timeout()),this,SLOT(UpdateData21()));

    updateTimer27=new QTimer(this);
    updateTimer27->setInterval(300);
    connect(updateTimer27,SIGNAL(timeout()),this,SLOT(UpdateData27()));

    updateTimer28=new QTimer(this);
    updateTimer28->setInterval(1000);
    connect(updateTimer28,SIGNAL(timeout()),this,SLOT(UpdateData28()));

    updateTimer29=new QTimer(this);
    updateTimer29->setInterval(500);
    connect(updateTimer29,SIGNAL(timeout()),this,SLOT(UpdateData29()));

    updateTimer30=new QTimer(this);
    updateTimer30->setInterval(3000);
    connect(updateTimer30,SIGNAL(timeout()),this,SLOT(UpdateData30()));

    updateTimer31=new QTimer(this);
    updateTimer31->setInterval(1000);
    connect(updateTimer31,SIGNAL(timeout()),this,SLOT(UpdateData31()));

}

void frmMain::ChangeVisibleTab1(bool b)
{
    gauge1->setVisible(b);

    gauge2->setVisible(b);

    gauge31->setVisible(b);
    gauge32->setVisible(b);
    gauge33->setVisible(b);

    gauge41->setVisible(b);
    gauge42->setVisible(b);
    gauge43->setVisible(b);

    gauge5->setVisible(b);

    gauge61->setVisible(b);
    gauge62->setVisible(b);
    gauge63->setVisible(b);

    gauge71->setVisible(b);
    gauge72->setVisible(b);
    gauge73->setVisible(b);

    myprogressbar1->setVisible(b);
    myprogressbar2->setVisible(b);
    myprogressbar3->setVisible(b);

    mybattery1->setVisible(b);
    mybattery2->setVisible(b);
    mybattery3->setVisible(b);
    mybattery4->setVisible(b);
    mycoolbar->setVisible(b);

    myindicator1->setVisible(b);
    myindicator2->setVisible(b);
    myindicator3->setVisible(b);
    myindicator4->setVisible(b);
    myindicator5->setVisible(b);

    myvolume1->setVisible(b);
    myvolume2->setVisible(b);
    myvolume3->setVisible(b);
    myvolume4->setVisible(b);
    myvolume5->setVisible(b);

    updateTimer11->stop();
    updateTimer10->stop();
    updateTimer8->stop();
    updateTimer7->stop();
    updateTimer6->stop();
    updateTimer5->stop();
    updateTimer4->stop();
    updateTimer2->stop();
    updateTimer1->stop();
}

void frmMain::ChangeVisibleTab2(bool b)
{
    mychart1->setVisible(b);
    myflashlist->setVisible(b);
    mybuttonboard->setVisible(b);

    mysliderbutton1->setVisible(b);
    mysliderbutton2->setVisible(b);
    mysliderbutton3->setVisible(b);

    myphotoview->setVisible(b);

    myaroundcircle->setVisible(b);

    myprogressbar11->setVisible(b);
    myprogressbar12->setVisible(b);
    myprogressbar13->setVisible(b);

    mynewled->setVisible(b);

    mywave->setVisible(b);

    for (int i=0;i<33;i++)
    {
        mywave1.at(i)->setVisible(b);
    }

    for (int i=0;i<50;i++)
    {
        mywave2.at(i)->setVisible(b);
    }

    updateTimer21->stop();
    updateTimer27->stop();
    updateTimer28->stop();
    updateTimer29->stop();
    updateTimer30->stop();
    updateTimer31->stop();
}

void frmMain::on_btnGauge1_clicked()
{
    this->ChangeVisibleTab1(false);
    gauge1->setVisible(true);
    updateTimer1->start();
}

void frmMain::UpdateData1()
{
    int value=qrand()%100;
    gauge1->setValue(value);
    ui->labValue1->setText(tr("当前值:%1").arg(value));
}

void frmMain::on_btnGauge2_clicked()
{
    this->ChangeVisibleTab1(false);
    gauge2->setVisible(true);    
    updateTimer2->start();
}

void frmMain::UpdateData2()
{
    int value=qrand()%100;
    gauge2->setValue(value);
    ui->labValue1->setText(tr("当前值:%1").arg(value));
}

void frmMain::on_btnGauge3_clicked()
{
    this->ChangeVisibleTab1(false);
    gauge31->setVisible(true);
    gauge32->setVisible(true);
    gauge33->setVisible(true);
}

void frmMain::UpdateData3(qreal value)
{
    ui->labValue1->setText(tr("当前值:%1").arg(value));
}

void frmMain::on_btnGauge4_clicked()
{
    this->ChangeVisibleTab1(false);
    gauge41->setVisible(true);
    gauge42->setVisible(true);
    gauge43->setVisible(true);
    updateTimer4->start();
}

void frmMain::UpdateData4()
{
    int value1=qrand()%100;
    int value2=qrand()%100;
    int value3=qrand()%100;
    gauge41->setValue(value1);
    gauge42->setValue(value2);
    gauge43->setValue(value3);
    ui->labValue1->setText(tr("当前值:%1 %2 %3").arg(value1).arg(value2).arg(value3));
}

void frmMain::on_btnGauge5_clicked()
{
    this->ChangeVisibleTab1(false);
    gauge5->setVisible(true);
    updateTimer5->start();
}

void frmMain::UpdateData5()
{
    int value=qrand()%100;
    gauge5->setValue(value);
    ui->labValue1->setText(tr("当前值:%1").arg(value));
}

void frmMain::on_btnGauge6_clicked()
{
    this->ChangeVisibleTab1(false);
    gauge61->setVisible(true);
    gauge62->setVisible(true);
    gauge63->setVisible(true);
    updateTimer6->start();
}

void frmMain::UpdateData6()
{
    int value1=qrand()%100;
    int value2=qrand()%100;
    int value3=qrand()%100;
    gauge61->setValue(value1);
    gauge62->setValue(value2);
    gauge63->setValue(value3);
    ui->labValue1->setText(tr("当前值:%1 %2 %3").arg(value1).arg(value2).arg(value3));
}

void frmMain::on_btnGauge7_clicked()
{
    this->ChangeVisibleTab1(false);
    gauge71->setVisible(true);
    gauge72->setVisible(true);
    gauge73->setVisible(true);
    updateTimer7->start();
}

void frmMain::UpdateData7()
{
    int value1=qrand()%100;
    int value2=qrand()%100;
    int value3=qrand()%100;
    gauge71->setValue(value1);
    gauge72->setValue(value2);
    gauge73->setValue(value3);
    ui->labValue1->setText(tr("当前值:%1 %2 %3").arg(value1).arg(value2).arg(value3));
}

void frmMain::on_btnProgressBar_clicked()
{
    this->ChangeVisibleTab1(false);
    myprogressbar1->setVisible(true);
    myprogressbar2->setVisible(true);
    myprogressbar3->setVisible(true);
}


void frmMain::on_btnBattery_clicked()
{
    this->ChangeVisibleTab1(false);
    mybattery1->setVisible(true);
    mybattery2->setVisible(true);
    mybattery3->setVisible(true);
    mybattery4->setVisible(true);
    updateTimer8->start();
}

void frmMain::UpdateData8()
{
    int value1=qrand()%100;
    int value2=qrand()%100;
    int value3=qrand()%100;
    int value4=qrand()%100;
    mybattery1->setValue(value1);
    mybattery2->setValue(value2);
    mybattery3->setValue(value3);
    mybattery4->setValue(value4);
    ui->labValue1->setText(tr("当前值:%1 %2 %3 %4").arg(value1).arg(value2).arg(value3).arg(value4));
}

void frmMain::on_btnCoolBar_clicked()
{
    this->ChangeVisibleTab1(false);
    mycoolbar->setVisible(true);
}

void frmMain::UpdateData9(int value)
{
    ui->labValue1->setText(tr("当前值:%1").arg(value));
}

void frmMain::on_btnIndicator_clicked()
{
    this->ChangeVisibleTab1(false);
    myindicator1->setVisible(true);
    myindicator2->setVisible(true);
    myindicator3->setVisible(true);
    myindicator4->setVisible(true);
    myindicator5->setVisible(true);
    updateTimer10->start();
}

void frmMain::UpdateData10()
{
    int value1=qrand()%100;
    int value2=qrand()%100;
    int value3=qrand()%100;
    int value4=qrand()%100;
    int value5=qrand()%100;
    myindicator1->setValue(value1);
    myindicator2->setValue(value2);
    myindicator3->setValue(value3);
    myindicator4->setValue(value4);
    myindicator5->setValue(value5);

    ui->labValue1->setText(tr("当前值:%1 %2 %3 %4 %5").arg(value1).arg(value2).arg(value3).arg(value4).arg(value5));
}

void frmMain::on_btnVolume_clicked()
{
    this->ChangeVisibleTab1(false);
    myvolume1->setVisible(true);
    myvolume2->setVisible(true);
    myvolume3->setVisible(true);
    myvolume4->setVisible(true);
    myvolume5->setVisible(true);
    updateTimer11->start();
}

void frmMain::UpdateData11()
{
    int value1=qrand()%10;
    int value2=qrand()%10;
    int value3=qrand()%10;
    int value4=qrand()%10;
    int value5=qrand()%10;    
    myvolume1->setValue(value1);
    myvolume2->setValue(value2);
    myvolume3->setValue(value3);
    myvolume4->setValue(value4);
    myvolume5->setValue(value5);
    ui->labValue1->setText(tr("当前值:%1 %2 %3 %4 %5").arg(value1).arg(value2).arg(value3).arg(value4).arg(value5));
}

void frmMain::on_btnChart1_clicked()
{
    this->ChangeVisibleTab2(false);
    mychart1->setVisible(true);
    updateTimer21->start();
}

void frmMain::UpdateData21()
{
    int value=qrand()%100;
    mychart1->addData(value);
    ui->labValue2->setText(tr("当前值:%1").arg(value));
}

void frmMain::on_btnFlashList_clicked()
{
    this->ChangeVisibleTab2(false);
    myflashlist->setVisible(true);
}

void frmMain::UpdateData22(QString txt)
{
    ui->labValue2->setText(tr("当前值:%1").arg(txt));
}

void frmMain::on_btnButtonBoard_clicked()
{
    this->ChangeVisibleTab2(false);
    mybuttonboard->setVisible(true);
}

void frmMain::UpdateData23(QString txt)
{
    ui->labValue2->setText(tr("当前值:%1").arg(txt));
}

void frmMain::on_btnSliderButton_clicked()
{
    this->ChangeVisibleTab2(false);
    mysliderbutton1->setVisible(true);
    mysliderbutton2->setVisible(true);
    mysliderbutton3->setVisible(true);
}

void frmMain::UpdateData24(QString txt)
{
    ui->labValue2->setText(tr("当前值:%1").arg(txt));
}

void frmMain::on_btnPhotoView_clicked()
{
    this->ChangeVisibleTab2(false);
    QString strFolder = QFileDialog::getExistingDirectory();
    if (strFolder.length()==0)
    {
        QMessageBox::information(this,QString::fromLocal8Bit("提示"),QString::fromLocal8Bit("你没有选择图片文件"));
        return;
    }
    myphotoview->load(strFolder);
    myphotoview->setVisible(true);
}

void frmMain::on_btnAroundCircle_clicked()
{
    this->ChangeVisibleTab2(false);
    myaroundcircle->setVisible(true);
}

void frmMain::on_btnProgressBar1_clicked()
{
    this->ChangeVisibleTab2(false);
    myprogressbar11->setVisible(true);
    myprogressbar12->setVisible(true);
    myprogressbar13->setVisible(true);
    updateTimer27->start();
}

void frmMain::UpdateData27()
{
    int value1=qrand()%100;
    int value2=qrand()%100;
    int value3=qrand()%100;
    myprogressbar11->setValue(value1);
    myprogressbar12->setValue(value2);
    myprogressbar13->setValue(value3);
    ui->labValue2->setText(tr("当前值:%1 %2 %3").arg(value1).arg(value2).arg(value3));
}

void frmMain::on_btnNewLed_clicked()
{
    this->ChangeVisibleTab2(false);
    mynewled->setVisible(true);
    updateTimer28->start();
}

void frmMain::UpdateData28()
{
    int value=qrand()%9;
    int red1=qrand()%255;
    int green1=qrand()%255;
    int blue1=qrand()%255;

    QColor c1=QColor::fromRgb(red1,green1,blue1);
    //QColor c2=QColor::fromRgb(red2,green2,blue2);

    mynewled->SetmyLedColor(c1,c1);//注释这句也行，已经初始化了颜色

    mynewled->setNumber(value);
    ui->labValue2->setText(tr("当前值:%1").arg(value));
}

void frmMain::on_btnWave_clicked()
{
    this->ChangeVisibleTab2(false);
    mywave->setVisible(true);
    updateTimer29->start();
}

void frmMain::UpdateData29()
{
    QVector<int> DataVec;

    for(int index = 0;index < 100 ; index++)
    {
        DataVec.push_back(qrand()%100);
    }
    mywave->setChannelData(DataVec);
}

void frmMain::on_btnWave1_clicked()
{
    this->ChangeVisibleTab2(false);

    for (int i=0;i<33;i++)
    {
        mywave1.at(i)->setVisible(true);
    }
    updateTimer30->start();
}

void frmMain::UpdateData30()
{
    for (int i=0;i<33;i++)
    {
        qApp->processEvents();
        mywave1.at(i)->setValue(qrand()%100);
    }
}

void frmMain::on_btnWave2_clicked()
{
    this->ChangeVisibleTab2(false);

    for (int i=0;i<50;i++)
    {
        mywave2.at(i)->setVisible(true);
    }
    updateTimer31->start();
}

void frmMain::UpdateData31()
{
    for (int i=0;i<50;i++)
    {
        qApp->processEvents();
        if (i<10)
        {
            mywave2.at(i)->setValue(qrand()%30);
        }
        else if (i<20 && i>10)
        {
            mywave2.at(i)->setValue(qrand()%60);
        }
        else
        {
            mywave2.at(i)->setValue(qrand()%100);
        }
    }
}
