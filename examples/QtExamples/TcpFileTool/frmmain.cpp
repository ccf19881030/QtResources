#include "frmmain.h"
#include "ui_frmmain.h"
#include "api/myhelper.h"

#include <QAbstractItemModel>
#include <QAbstractItemView>
#include <QItemSelectionModel>
#include <QDirModel>

frmMain::frmMain(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::frmMain)
{
    ui->setupUi(this);
    this->InitStyle();
    this->InitForm();
    this->InitConfig();
    myHelper::FormInCenter(this);
}

frmMain::~frmMain()
{
    delete ui;
}

void frmMain::InitStyle()
{
    if (App::UseStyle) {
        this->max = false;
        this->location = this->geometry();
        this->setProperty("Form", true);
        this->setProperty("CanMove", true);
        this->setWindowFlags(Qt::FramelessWindowHint | Qt::WindowSystemMenuHint | Qt::WindowMinMaxButtonsHint);

        IconHelper::Instance()->SetIcoClose(ui->btnMenu_Close);
        IconHelper::Instance()->SetIcoNormal(ui->btnMenu_Max);
        IconHelper::Instance()->SetIcoMin(ui->btnMenu_Min);
        IconHelper::Instance()->SetIcoMain(ui->lab_Ico, App::FontSize);
        IconHelper::Instance()->SetIcoMenu(ui->btnMenu);

        connect(ui->btnMenu_Close, SIGNAL(clicked()), this, SLOT(close()));
        connect(ui->btnMenu_Min, SIGNAL(clicked()), this, SLOT(showMinimized()));

#ifdef __arm__
        ui->btnMenu_Max->click();
        ui->widget_menu->setVisible(false);
#else
        ui->widget_title->installEventFilter(this);
#endif
    } else {
        this->setWindowFlags(Qt::WindowSystemMenuHint | Qt::WindowMinMaxButtonsHint | Qt::WindowCloseButtonHint);
        this->resize(size().width(), size().height() - ui->widget_title->size().height());
        ui->widget_title->setVisible(false);
    }

    this->setWindowTitle(ui->lab_Title->text());
}

bool frmMain::eventFilter(QObject *obj, QEvent *event)
{
    if (obj == ui->widget_title) {
        if (event->type() == QEvent::MouseButtonDblClick) {
            this->on_btnMenu_Max_clicked();
            return true;
        }
    }
    return QObject::eventFilter(obj, event);
}

void frmMain::InitForm()
{
    QAction *act1 = new QAction("淡蓝色", this);
    QAction *act2 = new QAction("蓝色", this);
    QAction *act3 = new QAction("浅灰色", this);
    QAction *act4 = new QAction("深灰色", this);
    QAction *act5 = new QAction("灰色", this);
    QAction *act6 = new QAction("灰黑色", this);
    QAction *act7 = new QAction("黑色", this);
    QAction *act8 = new QAction("银色", this);
    QAction *act9 = new QAction("系统", this);

    ui->btnMenu->addAction(act1);
    ui->btnMenu->addAction(act2);
    ui->btnMenu->addAction(act3);
    ui->btnMenu->addAction(act4);
    ui->btnMenu->addAction(act5);
    ui->btnMenu->addAction(act6);
    ui->btnMenu->addAction(act7);
    ui->btnMenu->addAction(act8);
    ui->btnMenu->addAction(act9);

    connect(act1, SIGNAL(triggered(bool)), this, SLOT(ChangeStyle()));
    connect(act2, SIGNAL(triggered(bool)), this, SLOT(ChangeStyle()));
    connect(act3, SIGNAL(triggered(bool)), this, SLOT(ChangeStyle()));
    connect(act4, SIGNAL(triggered(bool)), this, SLOT(ChangeStyle()));
    connect(act5, SIGNAL(triggered(bool)), this, SLOT(ChangeStyle()));
    connect(act6, SIGNAL(triggered(bool)), this, SLOT(ChangeStyle()));
    connect(act7, SIGNAL(triggered(bool)), this, SLOT(ChangeStyle()));
    connect(act8, SIGNAL(triggered(bool)), this, SLOT(ChangeStyle()));
    connect(act9, SIGNAL(triggered(bool)), this, SLOT(ChangeStyle()));

    sendBytes = 0;
    sendBlockNumber = 0;
    sendMaxBytes = 0;

    receiveBytes = 0;
    receiveBlockNumber = 0;
    receiveMaxBytes = 0;

    ui->pbarSendData->setRange(0, 100);
    ui->pbarSendData->setValue(0);
    ui->pbarReceiveData->setRange(0, 100);
    ui->pbarReceiveData->setValue(0);

    receive = new ReceiveFileServer(this);
    connect(receive, SIGNAL(finished()), this, SLOT(receiveFinsh()));
    connect(receive, SIGNAL(message(QString)), this, SLOT(updateReceiveStatus(QString)));
    connect(receive, SIGNAL(receiveFileName(QString)), this, SLOT(receiveFileName(QString)));
    connect(receive, SIGNAL(receiveFileSize(qint64)), this, SLOT(setReceivePBar(qint64)));
    connect(receive, SIGNAL(receiveData(qint64)), this, SLOT(updateReceivePBar(qint64)));
}

void frmMain::ChangeStyle()
{
    QAction *act = (QAction *)sender();
    QString name = act->text();

    QString style = ":/qss/blue.css";
    if (name == "淡蓝色") {
        style = ":/qss/blue.css";
    } else if (name == "蓝色") {
        style = ":/qss/dev.css";
    } else if (name == "浅灰色") {
        style = ":/qss/lightgray.css";
    } else if (name == "深灰色") {
        style = ":/qss/darkgray.css";
    } else if (name == "灰色") {
        style = ":/qss/gray.css";
    } else if (name == "灰黑色") {
        style = ":/qss/brown.css";
    } else if (name == "黑色") {
        style = ":/qss/black.css";
    } else if (name == "银色") {
        style = ":/qss/silvery.css";
    } else if (name == "系统") {
        App::UseStyle = false;
        App::WriteConfig();
        qApp->exit();
        myHelper::Sleep(10);
        QProcess::startDetached(qApp->applicationFilePath(), QStringList());
    }

    if (style != App::StyleName) {
        App::StyleName = style;
        myHelper::SetStyle(App::StyleName);
        App::WriteConfig();
    }
}

void frmMain::InitConfig()
{
    ui->txtServerIP->setText(App::ServerIP);
    connect(ui->txtServerIP, SIGNAL(textChanged(QString)), this, SLOT(SaveConfig()));

    ui->txtServerPort->setText(QString::number(App::ServerPort));
    connect(ui->txtServerPort, SIGNAL(textChanged(QString)), this, SLOT(SaveConfig()));

    ui->txtSendFile->setText(App::SendFile);
    connect(ui->txtSendFile, SIGNAL(textChanged(QString)), this, SLOT(SaveConfig()));

    ui->txtListenPort->setText(QString::number(App::ListenPort));
    connect(ui->txtListenPort, SIGNAL(textChanged(QString)), this, SLOT(SaveConfig()));
}

void frmMain::SaveConfig()
{
    App::ServerIP = ui->txtServerIP->text();
    App::ServerPort = ui->txtServerPort->text().toInt();
    App::SendFile = ui->txtSendFile->text();
    App::ListenPort = ui->txtListenPort->text().toInt();
    App::WriteConfig();
}

void frmMain::on_btnMenu_Max_clicked()
{
    if (max) {
        this->setGeometry(location);
        IconHelper::Instance()->SetIcoNormal(ui->btnMenu_Max);
        ui->btnMenu_Max->setToolTip("最大化");
        this->setProperty("CanMove", true);
    } else {
        location = this->geometry();
        this->setGeometry(qApp->desktop()->availableGeometry());
        IconHelper::Instance()->SetIcoMax(ui->btnMenu_Max);
        ui->btnMenu_Max->setToolTip("还原");
        this->setProperty("CanMove", false);
    }
    max = !max;
}

void frmMain::on_btnSend_clicked()
{
    sendBytes = 0;
    sendBlockNumber = 0;
    sendMaxBytes = 0;

    if (App::ServerIP == "" || App::ServerPort == 0) {
        myHelper::ShowMessageBoxError("服务器IP地址和端口不能为空,请重新填写!");
        return;
    }

    if (App::SendFile == "" ) {
        myHelper::ShowMessageBoxError("发送文件不能为空,请选择要发送的文件!");
        return;
    }

    SendFileClient *send = new SendFileClient(this);
    connect(send, SIGNAL(disconnected()), this, SLOT(sendFinsh()));
    connect(send, SIGNAL(disconnected()), send, SLOT(deleteLater()));
    connect(send, SIGNAL(fileSize(qint64)), this, SLOT(setSendPBar(qint64)));
    connect(send, SIGNAL(bytesWritten(qint64)), this, SLOT(updateSendPBar(qint64)));
    connect(send, SIGNAL(message(QString)), this, SLOT(updateSendStatus(QString)));

    send->SendFile(App::SendFile, App::ServerIP, App::ServerPort);
}

void frmMain::updateSendPBar(qint64 size)
{
    sendBlockNumber ++;
    sendBytes += size;
    ui->pbarSendData->setValue(sendBytes);
    QString msg = QString("已发数据包:%1个 当前数据包大小:%2字节 已发字节:%3 总共字节:%4")
                  .arg(sendBlockNumber).arg(size).arg(sendBytes).arg(sendMaxBytes);
    ui->txtSendStatus->setText(msg);
    qApp->processEvents();
}

void frmMain::updateSendStatus(QString msg)
{
    qDebug() << "发送文件客户端:" << msg;
}

void frmMain::setSendPBar(qint64 size)
{
    sendMaxBytes = size;
    ui->pbarSendData->setRange(0, size - 1);
    ui->pbarSendData->setValue(0);
}

void frmMain::sendFinsh()
{
    ui->pbarSendData->setRange(0, 100);
    ui->pbarSendData->setValue(100);
    ui->txtSendStatus->setText("发送文件成功");
}

void frmMain::on_btnSelect_clicked()
{
    QString filter = "所有文件 (*.*)";
    ui->txtSendFile->setText(myHelper::GetFileName(filter));

    ui->pbarSendData->setRange(0, 100);
    ui->pbarSendData->setValue(0);
    ui->pbarReceiveData->setRange(0, 100);
    ui->pbarReceiveData->setValue(0);
}

void frmMain::on_btnListen_clicked()
{    
    if (App::ListenPort != 0) {
        if (ui->btnListen->text() == "开始监听") {
            bool ok = receive->startServer(App::ListenPort);
            if (ok) {
                ui->txtReceiveStatus->setText("监听成功");
                ui->btnListen->setText("停止监听");
            } else {
                ui->txtReceiveStatus->setText("监听失败");
            }
        } else {
            receive->stopServer();
            ui->txtReceiveStatus->setText("停止监听成功");
            ui->btnListen->setText("开始监听");
        }
    } else {
        myHelper::ShowMessageBoxError("监听端口不能为空,请重新填写!");
    }
    ui->pbarReceiveData->setRange(0, 100);
    ui->pbarReceiveData->setValue(0);
}

void frmMain::updateReceivePBar(qint64 size)
{
    receiveBlockNumber ++;
    receiveBytes += size;
    ui->pbarReceiveData->setValue(receiveBytes);
    QString msg = QString("已接收数据包:%1个 当前数据包大小:%2字节 已接收字节:%3 总共字节:%4")
                  .arg(receiveBlockNumber).arg(size).arg(receiveBytes).arg(receiveMaxBytes);
    ui->txtReceiveStatus->setText(msg);
    qApp->processEvents();
}

void frmMain::updateReceiveStatus(QString msg)
{
    qDebug() << "接收文件服务端:" << msg;
}

void frmMain::setReceivePBar(qint64 size)
{
    receiveBytes = 0;
    receiveBlockNumber = 0;
    receiveMaxBytes = size;
    ui->pbarReceiveData->setRange(0, size - 1);
    ui->pbarReceiveData->setValue(0);
}

void frmMain::receiveFinsh()
{
    ui->pbarReceiveData->setRange(0, 100);
    ui->pbarReceiveData->setValue(100);    
    ui->txtReceiveStatus->setText("发送文件成功");
}

void frmMain::receiveFileName(QString name)
{
    ui->pbarReceiveData->setRange(0, 100);
    ui->pbarReceiveData->setValue(100);
    ui->txtReceiveFile->setText(name);
}
