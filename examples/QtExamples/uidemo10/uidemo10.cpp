#include "uidemo10.h"
#include "ui_uidemo10.h"
#include "iconhelper.h"

UIDemo10::UIDemo10(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::UIDemo10)
{
    ui->setupUi(this);
    this->initForm();    
}

UIDemo10::~UIDemo10()
{
    delete ui;
}

void UIDemo10::initForm()
{
    this->setProperty("form", true);
    this->setProperty("canMove", true);
    this->setWindowFlags(Qt::FramelessWindowHint | Qt::WindowSystemMenuHint | Qt::WindowMinMaxButtonsHint);
    this->setWindowTitle("metro风格主界面");

    int iconSize = 50;
    int iconWidth = 100;
    int iconHeight = 80;

    QList<QString> listColorBg;
    listColorBg << "#FF3739" << "#1A9FE0" << "#41BB1A" << "#1570A5" << "#FE781F" << "#9B59BB";
    QList<QString> listColorText;
    listColorText << "#FEFEFE" << "#FEFEFE" << "#FEFEFE" << "#FEFEFE" << "#FEFEFE" << "#FEFEFE";

    QList<QChar> listChar;
    listChar << 0xf2ba << 0xf002 << 0xf2c2 << 0xf02f << 0xf013 << 0xf021;
    QList<QString> listText;
    listText << "访客登记" << "记录查询" << "证件扫描" << "信息打印" << "系统设置" << "系统重启";

    QList<QToolButton *> btns = this->findChildren<QToolButton *>();
    for (int i = 0; i < btns.count(); i++) {
        QToolButton *btn = btns.at(i);
        btn->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
        btn->setIconSize(QSize(iconWidth, iconHeight));

        QPixmap pix = IconHelper::Instance()->getPixmap(listColorText.at(i), listChar.at(i), iconSize, iconWidth, iconHeight);
        btn->setIcon(QIcon(pix));
        btn->setText(listText.at(i));
        btn->setStyleSheet(QString("QToolButton{font:%1pt;color:%2;background-color:%3;border:none;border-radius:0px;}")
                           .arg(iconSize / 2).arg(listColorText.at(i)).arg(listColorBg.at(i)));

        connect(btn, SIGNAL(clicked(bool)), this, SLOT(buttonClicked()));
    }
}

void UIDemo10::buttonClicked()
{
    QToolButton *btn = (QToolButton *)sender();
    QString text = btn->text();
    qDebug() << text;

    if (text == "系统重启") {
        close();
    }
}
