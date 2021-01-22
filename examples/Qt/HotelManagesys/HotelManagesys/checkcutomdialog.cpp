#include "checkcutomdialog.h"
#include "ui_checkcutomdialog.h"
#include "app/myhelper.h"

#include <QSqlQuery>
#include <QDebug>

CheckCutomDialog::CheckCutomDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CheckCutomDialog)
{
    ui->setupUi(this);
    this->InitForm();

}

CheckCutomDialog::~CheckCutomDialog()
{
    delete ui;
}

void CheckCutomDialog::InitForm()
{
    ui->pbnFindId->setFlat(true);
    ui->pbnFindTypeId->setFlat(true);

    ui->dateEditFrom->setDate(QDate::currentDate());
    ui->dateEditTo->setDate(QDate::currentDate());

    //正则表达式，对输入的内容进行限制，电话号码11位,身份证18位,房间号4位，房间类型编号1位
    QRegExp rxPhone("\\d{11}$");
    QRegExp rxIdcard("\\d{18}$");
    QRegExp rxRoomID("\\d{4}$");
    QRegExp rxRoomTypeId("\\d{1}$");

    QRegExpValidator *regPhone = new QRegExpValidator(rxPhone,this);
    QRegExpValidator *regIdcard = new QRegExpValidator(rxIdcard,this);
    QRegExpValidator *regRoomId = new QRegExpValidator(rxRoomID,this);
    QRegExpValidator *regRoomTypeId = new QRegExpValidator(rxRoomTypeId,this);

    ui->lineEditCustomPhone->setValidator(regPhone);
    ui->lineEditCustomIcard->setValidator(regIdcard);
    ui->lineEditRoomId->setValidator(regRoomId);
    ui->lineEditroomTypeId->setValidator(regRoomTypeId);
}

void CheckCutomDialog::on_pbnCheckOk_clicked()
{
    QString roomId = ui->lineEditRoomId->text();
    QString roomTypeId = ui->lineEditroomTypeId->text();
    //QString roomDate = ui->lineEditDay->text();
    QString roomDate = ui->dateEditFrom->text();
    QString roomCustomName = ui->lineEditCustomName->text();
    QString roomCustomIdcard = ui->lineEditCustomIcard->text();
    QString roomCustomSex = ui->comboBoxSex->currentText();
    QString roomCustomPhone = ui->lineEditCustomPhone->text();
    QString roomCustomCash = ui->lineEditCustomCash->text();
    QString roomCustomOrderId = ui->lineEditCustomOrderId->text();
    QString roomCustomRemark = ui->lineEditRemark->text();

    qDebug() <<roomDate;
    QString date = QDate::currentDate().toString("yyyyMMdd");

    ui->lineEditCustomOrderId->setText("1008"+date+roomCustomIdcard.right(4));
    QSqlQuery query;

    if(roomId.isEmpty() || roomTypeId.isEmpty()
            || roomDate.isEmpty() || roomCustomName.isEmpty()
            || roomCustomIdcard.isEmpty() || roomCustomCash.isEmpty())
    {
        myHelper::ShowMessageBoxInfo(tr("必须填满带*字段"));
    }
    else
    {
        QString sql ="INSERT INTO inroom(RoomNo,RoomTypeId,InRoomTime,InRoomName,InRoomIdCard,"
                "InRoomGender,InRoomPhone,InRoomCash,InRoomOrder,InRoomRemark)"
                "VALUES (:RoomNo,:RoomTypeId,:InRoomTime,:InRoomName,:InRoomIdCard,:InRoomGender,:InRoomPhone,:InRoomCash,:InRoomOrder,:InRoomRemark)";
        qDebug() <<sql;
        bool ok = query.prepare(sql);
        query.bindValue(":RoomNo",roomId);
        query.bindValue(":RoomTypeId",roomTypeId);
        query.bindValue(":InRoomTime",roomDate);
        query.bindValue(":InRoomName",roomCustomName);
        query.bindValue(":InRoomIdCard",roomCustomIdcard);
        query.bindValue(":InRoomGender",roomCustomSex);
        query.bindValue(":InRoomPhone",roomCustomPhone);
        query.bindValue(":InRoomCash",roomCustomCash);
        query.bindValue(":InRoomOrder",roomCustomOrderId);
        query.bindValue(":InRoomRemark",roomCustomRemark);
        query.setForwardOnly(true);
        query.exec();

        if(ok)
        {
            myHelper::ShowMessageBoxInfo(tr("注册成功!"));

            this->UpdateRoomeTableInfo("Room","满",roomId);

            myHelper::MyLoginBlog("logblog","来客登记","新客人入住","管理员");
        }
    }
}


/*
 *函数功能：更新房间状态
 *输入参数
*/
void CheckCutomDialog::UpdateRoomeTableInfo(QString tablename, QString updatename,QString roomNo)
{
    QString sql = "update "+tablename+" set RoomState = '"+updatename+"' where RoomNo ='"+roomNo+"';";
    qDebug() <<sql;
    QSqlQuery query;
    query.exec(sql);
    qDebug() <<"update roomstate success";
}
