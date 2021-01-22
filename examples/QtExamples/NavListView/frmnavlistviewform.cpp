#include "frmnavlistviewform.h"
#include "ui_frmnavlistviewform.h"
#include "qabstractitemmodel.h"
#include "qdebug.h"

frmNavListViewForm::frmNavListViewForm(QWidget *parent) :
	QWidget(parent),
	ui(new Ui::frmNavListViewForm)
{
	ui->setupUi(this);
	this->initForm();
}

frmNavListViewForm::~frmNavListViewForm()
{
	delete ui;
}

void frmNavListViewForm::initForm()
{
	ui->listView->setIcoColorBg(false);
	ui->listView->setColorLine(QColor(32, 53, 74));
	ui->listView->setColorBg(QColor(52, 73, 94), QColor(24, 189, 155), QColor(24, 189, 155, 150));
	ui->listView->setColorText(QColor(254, 255, 255), QColor(252, 252, 252), QColor(0, 0, 0));

	//设置数据方式
	QStringList listItem;
    listItem.append("主界面||0|游龙");

	listItem.append("系统设置||0|");
	listItem.append("防区信息|系统设置||");
	listItem.append("位置调整|系统设置||");
	listItem.append("地图编辑|系统设置||");

	listItem.append("警情查询||0|");
	listItem.append("记录查询|警情查询||");
	listItem.append("图像查询|警情查询||");
	listItem.append("视频查询|警情查询||");
	listItem.append("数据回放|警情查询||");

	listItem.append("信息管理||0|");
	listItem.append("学生管理|信息管理|0|");
	listItem.append("教师管理|信息管理|0|");
	listItem.append("成绩管理|信息管理|0|");

	listItem.append("帮助文档||1|");

	ui->listView->setData(listItem);

	//加载xml文件形式
    //ui->listView->readData(":/image/config.xml");
}

void frmNavListViewForm::on_listView_pressed()
{
	QModelIndex index = ui->listView->currentIndex();
	QString text = index.data().toString();

	if (text == "主界面") {
		ui->stackedWidget->setCurrentIndex(0);
	} else if (text == "防区信息") {
		ui->stackedWidget->setCurrentIndex(1);
	} else if (text == "地图编辑") {
		ui->stackedWidget->setCurrentIndex(2);
	} else if (text == "位置调整") {
		ui->stackedWidget->setCurrentIndex(3);
	}
}
