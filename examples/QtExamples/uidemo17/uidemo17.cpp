#include "uidemo17.h"
#include "ui_uidemo17.h"
#include "iconhelper.h"
#include "flatui.h"

#pragma execution_character_set("utf-8")

UIDemo17::UIDemo17(QWidget *parent) : QDialog(parent), ui(new Ui::UIDemo17)
{
    ui->setupUi(this);
    this->initForm();
    this->initStyle();
    this->initList();
}

UIDemo17::~UIDemo17()
{
    delete ui;
}

bool UIDemo17::eventFilter(QObject *watched, QEvent *event)
{
    if (watched == ui->widgetTitle && event->type() == QEvent::MouseButtonDblClick) {
        this->on_btnMenu_Max_clicked();
        return true;
    }

    return QWidget::eventFilter(watched, event);
}

void UIDemo17::initForm()
{
    this->setProperty("form", true);
    this->setProperty("canMove", true);
    this->setWindowFlags(Qt::FramelessWindowHint | Qt::WindowSystemMenuHint | Qt::WindowMinMaxButtonsHint);

    IconHelper::Instance()->setIcon(ui->labIco, QChar(0xf0f4), 20);
    IconHelper::Instance()->setIcon(ui->btnMenu_Min, QChar(0xf068), 12);
    IconHelper::Instance()->setIcon(ui->btnMenu_Max, QChar(0xf067), 12);
    IconHelper::Instance()->setIcon(ui->btnMenu_Close, QChar(0xf00d), 12);

    IconHelper::Instance()->setIcon(ui->btnPlay, QChar(0xf04b), 13);
    IconHelper::Instance()->setIcon(ui->btnPre, QChar(0xf048), 12);
    IconHelper::Instance()->setIcon(ui->btnNext, QChar(0xf051), 12);

    ui->labTitle->setText("轻松云音乐");
    this->setWindowTitle(ui->labTitle->text());
    ui->widgetTitle->installEventFilter(this);

    ui->widgetBottom->setProperty("flag","btnPlay");
}

void UIDemo17::initStyle()
{
    QStringList qss;

    //全局无焦点虚边框,全局文字颜色,全局字号
    qss.append(QString("*{outline:0px;color:#ABD6FF;}"));
    qss.append(QString("QLabel#labTitle{font:%1pt;}").arg(14));

    //主界面顶部栏
    qss.append("QWidget#widgetTitle{background:qlineargradient"
               "(spread:pad,x1:0,y1:0,x2:1,y2:0,stop:0 #0973AB,stop:1 #098DCE);}"
               "QToolButton::menu-indicator{image:None;}");

    //主界面顶部右上角
    qss.append("QWidget#widgetMenu QAbstractButton{"
               "border:0px solid #FF0000;}");
    qss.append("QWidget#widgetMenu QAbstractButton:hover,"
               "QWidget#widgetMenu QAbstractButton:pressed{"
               "background:#067DB8;}");

    //左侧列表框
    qss.append(QString("QListView{padding:5px;background-color:rgba(29,34,40,100);font:%1pt;}").arg(12));
    qss.append("QListView::item:hover{background:#617D90;}");
    qss.append("QListView::item:selected{background:rgba(0,187,226,150);}");

    //边框颜色及宽度
    qss.append("QListView,QWidget#widgetBottom,QWidget#widgetWave{border-style:solid;border-color:#505050;}");
    qss.append("QListView{border-width:1px 1px 0px 1px;}");
    qss.append("QWidget#widgetBottom{border-width:1px 1px 1px 1px;}");
    qss.append("QWidget#widgetWave{border-width:1px 1px 0px 0px;}");

    //主界面
    qss.append("QWidget#widgetMain{background-color:rgba(29,34,40,220);}");

    //播放按钮
    qss.append("QWidget[flag=\"btnPlay\"] QAbstractButton{background:#E83C3C;color:#F0F0F0;}");
    qss.append("QWidget[flag=\"btnPlay\"] QAbstractButton:hover{background:#C62F2F;}");
    qss.append("#btnPlay{border-radius:17px;}");
    qss.append("#btnPre,#btnNext{border-radius:15px;}");

    //滑块条样式
    FlatUI::Instance()->setSliderQss(ui->slider, 8, "rgba(29,34,56,150)", "rgba(37,156,210,150)", "rgba(250,250,250,100)");

    //滚动条样式
    qss.append("QScrollBar:vertical{background:rgba(150,150,150,100);padding:0px;border-radius:10px;min-width:20px;max-width:20px;}"
               "QScrollBar::handle:vertical{background:#617D90;min-height:120px;border-radius:10px;}"
               "QScrollBar::handle:vertical:hover{background:#1ABC9C;}"
               "QScrollBar::handle:vertical:pressed{background:#1ABC9C;}"
               "QScrollBar::add-page:vertical{background:none;}"
               "QScrollBar::sub-page:vertical{background:none;}"
               "QScrollBar::add-line:vertical{background:none;}"
               "QScrollBar::sub-line:vertical{background:none;}");

    qApp->setStyleSheet(qss.join(""));
}

void UIDemo17::initList()
{
    ui->listWidget->addItem("刘德华 - 忘情水");
    ui->listWidget->addItem("张学友 - 吻别");
    ui->listWidget->addItem("郭富城 - 爱我");
    ui->listWidget->addItem("邓丽君 - 你怎么说");
}

void UIDemo17::on_btnMenu_Min_clicked()
{
    showMinimized();
}

void UIDemo17::on_btnMenu_Max_clicked()
{
    static bool max = false;
    static QRect location = this->geometry();

    if (max) {
        this->setGeometry(location);
    } else {
        location = this->geometry();
        this->setGeometry(qApp->desktop()->availableGeometry());
    }

    this->setProperty("canMove", max);
    max = !max;
}

void UIDemo17::on_btnMenu_Close_clicked()
{
    close();
}
