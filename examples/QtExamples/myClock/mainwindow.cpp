#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QHBoxLayout>
#include <QDateTime>
#include <QDebug>
#include <QDesktopWidget>
#include <QMouseEvent>
#include <QDialog>
#include <QTableView>
#include <QStandardItemModel>
#include <QLineEdit>
#include <QPushButton>
#include "MyDialog.h"
#include <QDir>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    cenWidget = new QWidget();
    this->setCentralWidget(cenWidget);
    this->setWindowTitle("闹钟");
    this->setWindowFlags(this->windowFlags() | Qt::SubWindow | Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);
    this->setAttribute(Qt::WA_TranslucentBackground);
    this->setStyleSheet("background-image:url(:/images/bg.png)");
    this->setFixedSize(450,100);
    shouldMove = false;
    destopWidth = QApplication::desktop()->width();
    destopHeight = QApplication::desktop()->height();
    widgetWidth = 450;
    widgetHeight = 100;
    this->setGeometry(QRect(destopWidth-widgetWidth-10,destopHeight-widgetHeight-40,widgetWidth,widgetHeight));

    //系统托盘
    quitAction = new QAction("退出",this);
    setTimeAction = new QAction("设置闹钟",this);
    minAction = new QAction("隐藏",this);
    maxAction = new QAction("显示",this);
    connect(quitAction,SIGNAL(triggered(bool)),qApp,SLOT(quit()));
    connect(setTimeAction,SIGNAL(triggered(bool)),this,SLOT(setTime()));
    connect(minAction,SIGNAL(triggered(bool)),this,SLOT(setMinWidget()));
    connect(maxAction,SIGNAL(triggered(bool)),this,SLOT(setMaxWidget()));

    myMenu = new QMenu((QWidget*)QApplication::desktop());
    myMenu->addAction(setTimeAction);
    myMenu->addAction(minAction);
    myMenu->addAction(maxAction);
    myMenu->addAction(quitAction);
    //myMenu->addSeparator();

    //判断系统是否支持托盘图标
    if(!QSystemTrayIcon::isSystemTrayAvailable()){
        return;
    }
    myTrayIcon = new QSystemTrayIcon(this);
    myTrayIcon->setIcon(QIcon(":/images/title.ico"));
    myTrayIcon->setToolTip("闹钟");
    myTrayIcon->showMessage("托盘","托盘管理",QSystemTrayIcon::Information,10000);
    myTrayIcon->setContextMenu(myMenu);
    myTrayIcon->show();

    intiTime();

    //QTimer
    timer = new QTimer(this);
    timer->setInterval(500);
    timer->start();
    connect(timer,SIGNAL(timeout()),this,SLOT(updateTime()));

    //文件读写
    m_myFile = new MyFile();
    connect(m_myFile,SIGNAL(getReadFile(QVariantList)),this,SLOT(onGetReadFile(QVariantList)));
    connect(m_myFile,SIGNAL(getWriteResult(bool)),this,SLOT(onGetWriteResult(bool)));

//    m_myFile->writeFile(QDir::currentPath()+ "/0.ini",vList);
    m_myFile->readFile(QDir::currentPath()+ "/0.ini");

    //设置默认闹钟
    vMap.insert("time","00:00:00");
    vMap.insert("tips","给妈妈发微信");
    vList.append(vMap);
    vMap.insert("time","01:00:00");
    vMap.insert("tips","该喝水了");
    vList.append(vMap);

    clockFlag = 0;
    labelTip = new QLabel(QApplication::desktop());
    labelTip->adjustSize();
    labelTip->setGeometry((destopWidth-labelTip->width())/2,(destopHeight-labelTip->height())/2,labelTip->width(),labelTip->height());
    labelTip->setWindowFlags(Qt::FramelessWindowHint | Qt::SubWindow | Qt::WindowStaysOnTopHint);
    labelTip->hide();


    //设置闹钟面板
    setDialog = new MyDialog(this);
    setDialog->hide();
    setDialog->setFixedSize(400,200);
    setDialog->setGeometry((destopWidth-400)/2,(destopHeight-200)/2,400,200);
    setDialog->setWindowTitle("设置闹钟时间");
    connect(setDialog,SIGNAL(accepted()),setDialog,SLOT(hide()));

    //标题
    QLabel * l1 = new QLabel("闹钟",setDialog);
    QLabel * l2 = new QLabel("提醒",setDialog);
    l1->setAlignment(Qt::AlignHCenter);
    l2->setAlignment(Qt::AlignHCenter);
    QHBoxLayout * layout = new QHBoxLayout();
    layout->addWidget(l1);
    layout->addWidget(l2);

    vLayout = new QVBoxLayout();
    vLayout->addLayout(layout);

//    for(int i=0;i<vList.size();i++){
//        QVariantMap map = vList.at(i).toMap();
//        QLineEdit * time = new QLineEdit(this);
//        QLineEdit * tips = new QLineEdit(this);
//        time->setText(map.value("time").toString());
//        tips->setText(map.value("tips").toString());
////        time->setFixedSize(100,30);
////        tips->setFixedSize(100,30);

//        QHBoxLayout * layout = new QHBoxLayout();
//        layout->addWidget(time);
//        layout->addWidget(tips);

//        vLayout->addLayout(layout);
//    }
    //1 line
    time1 = new QLineEdit(this);
    tips1 = new QLineEdit(this);
    time1->setText(vList.at(0).toMap().value("time").toString());
    tips1->setText(vList.at(0).toMap().value("tips").toString());
    connect(time1,SIGNAL(textChanged(QString)),this,SLOT(saveClockTime1(QString)));
    connect(tips1,SIGNAL(textChanged(QString)),this,SLOT(saveClockTips1(QString)));
    QHBoxLayout * layout1 = new QHBoxLayout();
    layout1->addWidget(time1);
    layout1->addWidget(tips1);
    vLayout->addLayout(layout1);
    //2 line
    time2 = new QLineEdit(this);
    tips2 = new QLineEdit(this);
    time2->setText(vList.at(1).toMap().value("time").toString());
    tips2->setText(vList.at(1).toMap().value("tips").toString());
    connect(time2,SIGNAL(textChanged(QString)),this,SLOT(saveClockTime2(QString)));
    connect(tips2,SIGNAL(textChanged(QString)),this,SLOT(saveClockTips2(QString)));
    QHBoxLayout * layout2 = new QHBoxLayout();
    layout2->addWidget(time2);
    layout2->addWidget(tips2);
    vLayout->addLayout(layout2);
    //说明
    QLabel * labelT1 = new QLabel(this);
    labelT1->setText("闹钟1：定时提醒");
    QLabel * labelT2 = new QLabel(this);
    labelT2->setText("闹钟2：频率提醒");
    //add button
    QPushButton * button = new QPushButton();
    button->setText("+");
    button->hide();
    button->setGeometry(setDialog->width()-100-5,setDialog->height()-30-5,100,30);
    connect(button,SIGNAL(clicked(bool)),this,SLOT(addClock()));

    vLayout->addWidget(labelT1);
    vLayout->addWidget(labelT2);
    vLayout->addStretch();

    setDialog->setLayout(vLayout);
}

MainWindow::~MainWindow()
{
    exit();
    delete ui;
}

void MainWindow::intiTime()
{
    //初始化图片路径
    listPath.append(":/images/0.png");
    listPath.append(":/images/1.png");
    listPath.append(":/images/2.png");
    listPath.append(":/images/3.png");
    listPath.append(":/images/4.png");
    listPath.append(":/images/5.png");
    listPath.append(":/images/6.png");
    listPath.append(":/images/7.png");
    listPath.append(":/images/8.png");
    listPath.append(":/images/9.png");

    label1 = new QLabel(this);
    label2 = new QLabel(this);
    label3 = new QLabel(this);
    label4 = new QLabel(this);
    label5 = new QLabel(this);
    label6 = new QLabel(this);
    labelDot1 = new QLabel(this);
    labelDot2 = new QLabel(this);

//    label1->setMinimumSize(92,254);
//    label2->setMinimumSize(92,254);
//    label3->setMinimumSize(92,254);
//    label4->setMinimumSize(92,254);
//    label5->setMinimumSize(92,254);
//    label6->setMinimumSize(92,254);


    label1->setPixmap(QPixmap(listPath[0]));
    label2->setPixmap(QPixmap(listPath[0]));
    label3->setPixmap(QPixmap(listPath[0]));
    label4->setPixmap(QPixmap(listPath[0]));
    label5->setPixmap(QPixmap(listPath[0]));
    label6->setPixmap(QPixmap(listPath[0]));
    labelDot1->setPixmap(QPixmap(":/images/dot.png"));
    labelDot2->setPixmap(QPixmap(":/images/dot.png"));

    QHBoxLayout * hLayout = new QHBoxLayout();
    hLayout->addWidget(label1);
    hLayout->addWidget(label2);
    hLayout->addWidget(labelDot1);
    hLayout->addWidget(label3);
    hLayout->addWidget(label4);
    hLayout->addWidget(labelDot2);
    hLayout->addWidget(label5);
    hLayout->addWidget(label6);
    hLayout->setSpacing(0);
    hLayout->setMargin(0);

    cenWidget->setLayout(hLayout);
}

void MainWindow::updateTime()
{
    QDateTime dateTime = QDateTime::currentDateTime();

    QDate date = dateTime.date();
    QTime time = dateTime.time();
    checkClock(time.toString("hh:mm:ss"));

    int hour = time.hour();
    int minute = time.minute();
    int second = time.second();

    int hour1 = hour / 10;
    int hour2 = hour % 10;
    int minute1 = minute / 10;
    int minute2 = minute % 10;
    int second1 = second / 10;
    int second2 = second % 10;

    label1->setPixmap(QPixmap(listPath[hour1]));
    label2->setPixmap(QPixmap(listPath[hour2]));
    label3->setPixmap(QPixmap(listPath[minute1]));
    label4->setPixmap(QPixmap(listPath[minute2]));
    label5->setPixmap(QPixmap(listPath[second1]));
    label6->setPixmap(QPixmap(listPath[second2]));
}

void MainWindow::exit()
{
    myTrayIcon->hide();
}

void MainWindow::setTime()
{
    setDialog->show();
}

void MainWindow::setMinWidget()
{
    this->hide();
}

void MainWindow::setMaxWidget()
{
    this->show();
}

void MainWindow::addClock()
{
    int size = vList.size();
    if(size >= 5){
        return;
    }
    //add
    QVariantMap map;
    map.insert("time","00:00:00");
    map.insert("tips","闹钟");
    vList.append(map);

    QLineEdit * time = new QLineEdit(this);
    QLineEdit * tips = new QLineEdit(this);
    time->setText("00:00:00");
    tips->setText("闹钟");
    connect(time,SIGNAL(textChanged(QString)),this,SLOT(saveClockTime(QString)));
    connect(tips,SIGNAL(textChanged(QString)),this,SLOT(saveClockTips(QString)));

    QHBoxLayout * llayout = new QHBoxLayout();
    llayout->addWidget(time);
    llayout->addWidget(tips);

    vLayout->insertLayout(size+1,llayout);
}

void MainWindow::saveClockTime1(QString str)
{
    QVariantMap _map = vList.at(0).toMap();
    _map.insert("time",str);
    vList.replace(0,_map);

    m_myFile->writeFile(QDir::currentPath()+ "/0.ini",vList);
}
void MainWindow::saveClockTime2(QString str)
{
    QVariantMap _map = vList.at(1).toMap();
    _map.insert("time",str);
    vList.replace(1,_map);
    m_myFile->writeFile(QDir::currentPath()+ "/0.ini",vList);
}

void MainWindow::saveClockTips1(QString str)
{
    QVariantMap _map = vList.at(0).toMap();
    _map.insert("tips",str);
    vList.replace(0,_map);
    m_myFile->writeFile(QDir::currentPath()+ "/0.ini",vList);
}
void MainWindow::saveClockTips2(QString str)
{
    QVariantMap _map = vList.at(1).toMap();
    _map.insert("tips",str);
    vList.replace(1,_map);
    m_myFile->writeFile(QDir::currentPath()+ "/0.ini",vList);
}

void MainWindow::hideLabelTip()
{
    labelTip->hide();
}

void MainWindow::onGetReadFile(QVariantList list)
{
    vList = list;
    time1->setText(vList.at(0).toMap().value("time").toString());
    tips1->setText(vList.at(0).toMap().value("tips").toString());
    time2->setText(vList.at(1).toMap().value("time").toString());
    tips2->setText(vList.at(1).toMap().value("tips").toString());
}

void MainWindow::onGetWriteResult(bool b)
{
    qDebug()<<"write result =="<<b;
}

void MainWindow::mousePressEvent(QMouseEvent * event)
{
    if(event->button() != Qt::LeftButton) return;
    shouldMove = true;
    formerMainPos = this->pos();
    formerMousePos = event->globalPos();
    event->accept();
}

void MainWindow::mouseMoveEvent(QMouseEvent *event)
{
    //到了桌面一角，不能移动窗口
    if(shouldMove)
    {
        //移动时候最好不要移出桌面
        QPoint pos = event->globalPos();
        int x = pos.x()-formerMousePos.x();
        int y = pos.y()-formerMousePos.y();
        move(formerMainPos.x()+x,formerMainPos.y()+y);
    }
    event->accept();
}

void MainWindow::mouseReleaseEvent(QMouseEvent *event)
{
    if(event->button() != Qt::LeftButton) return;
    //松手后保证窗口完整的显示在桌面上
    QPoint pos = event->globalPos();
    QRect rect = this->geometry();

    int x = pos.x()-formerMousePos.x();
    int y = pos.y()-formerMousePos.y();
    int left = 0;
    int right = destopWidth-widgetWidth-10;
    int top = 0;
    int bottom = destopHeight-widgetHeight-40;

    if(shouldMove)
    {
        //x,y表示移动方向,为了检测边界，需要 分别移动
        if(x < 0 && rect.x() < left){
            move(left,this->pos().y());
        }
        else if(x > 0 && rect.x() > right){
            move(right,this->pos().y());
        }
        else{
            move(formerMainPos.x()+x,this->pos().y());
        }
        if(y < 0 && rect.y() < top){
            move(this->pos().x(),top);
        }
        else if(y > 0 && rect.y() > bottom){
            move(this->pos().x(),bottom);
        }
        else{
            move(this->pos().x(),formerMainPos.y()+y);
        }
    }
    shouldMove = false;
    event->accept();
}

void MainWindow::checkClock(QString str)
{
    QString clock1Time = vList.at(0).toMap().value("time").toString();
    QString clock1Tip = vList.at(0).toMap().value("tips").toString();
    QString clock2Time = vList.at(1).toMap().value("time").toString();
    QString clock2Tip = vList.at(1).toMap().value("tips").toString();

    QStringList strList = str.split(":");
    int num = (strList[0]).toInt()*3600 + (strList[1]).toInt()*60 + (strList[2]).toInt();//当前时间
    QStringList strList2 = clock2Time.split(":");
    int jiangeNum = (strList2[0]).toInt()*3600 + (strList2[1]).toInt()*60 + (strList2[2]).toInt();//间隔时间
    if(clock1Time == str){
        //响
        if(!labelTip->isHidden()){
            return;
        }

        labelTip->setText(clock1Tip);
        QFont ft;
        ft.setPointSize(100);
        labelTip->setFont(ft);
        labelTip->adjustSize();
        labelTip->setGeometry((destopWidth-labelTip->width())/2,(destopHeight-labelTip->height())/2,labelTip->width(),labelTip->height());

        labelTip->show();
        QTimer * myTimer = new QTimer(this);
        myTimer->setInterval(3000);
        myTimer->start();
        connect(myTimer,SIGNAL(timeout()),this,SLOT(hideLabelTip()));
    }
    //喝水提醒
//    else if(clock2Time == str){

//    }

    if(clockFlag == 0){
        clockFlag = num;
    }
    else{
        if(num - clockFlag >= jiangeNum){
            //响
            if(!labelTip->isHidden()){
                return;
            }
            clockFlag = num;
            labelTip->setText(clock2Tip);
            QFont ft;
            ft.setPointSize(100);
            labelTip->setFont(ft);
            labelTip->adjustSize();
            labelTip->setGeometry((destopWidth-labelTip->width())/2,(destopHeight-labelTip->height())/2,labelTip->width(),labelTip->height());
            labelTip->show();
            QTimer * myTimer = new QTimer(this);
            myTimer->setInterval(3000);
            myTimer->start();
            connect(myTimer,SIGNAL(timeout()),this,SLOT(hideLabelTip()));
        }
    }
}
