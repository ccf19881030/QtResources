#include "frmnettool.h"
#include "ui_frmnettool.h"
#include "myhelper.h"
#include "app.h"
#include "tcpserver.h"

frmNetTool::frmNetTool(QWidget *parent) :
	QWidget(parent),
	ui(new Ui::frmNetTool)
{
	ui->setupUi(this);
	this->initConfig();
	this->initForm();
	this->readSendData();
	this->readDeviceData();
	myHelper::formInCenter(this);
}

frmNetTool::~frmNetTool()
{
	delete ui;
}

void frmNetTool::initForm()
{
	msgMaxCount = 50;
	countTcpServer = 0;
	countTcpClient = 0;
	countUdpServer = 0;

	QList<QHostAddress> addrs = QNetworkInterface::allAddresses();

	foreach (QHostAddress addr, addrs) {
		QString ip = addr.toString();

		if (ip.startsWith("192.168")) {
			this->setWindowTitle(QString("网络调试助手 本机IP[%1]").arg(ip));
			break;
		}
	}

	ui->btnSendTcpClient->setEnabled(false);
	ui->txtDataTcpClient->setReadOnly(true);
	ui->btnSendTcpServer->setEnabled(false);
	ui->txtDataTcpServer->setReadOnly(true);
	ui->btnSendUdpServer->setEnabled(false);
	ui->txtDataUdpServer->setReadOnly(true);

	tcpClient = new QTcpSocket(this);
	tcpClient->abort();
	connect(tcpClient, SIGNAL(readyRead()), this, SLOT(tcpClientReadData()));
	connect(tcpClient, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(tcpClientReadError()));

	tcpServer = new TcpServer(this);
	connect(tcpServer, SIGNAL(clientConnect(int, QString, int)),
	        this, SLOT(clientConnect(int, QString, int)));
	connect(tcpServer, SIGNAL(clientDisConnect(int, QString, int)),
	        this, SLOT(clientDisConnect(int, QString, int)));
	connect(tcpServer, SIGNAL(clientReadData(int, QString, int, QByteArray)),
	        this, SLOT(clientReadData(int, QString, int, QByteArray)));

	udpServer = new QUdpSocket(this);
	udpServer->abort();
	connect(udpServer, SIGNAL(readyRead()), this, SLOT(udpServerReadData()));
	connect(udpServer, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(udpServerReadError()));

	timerTcpClient = new QTimer(this);
	timerTcpClient->setInterval(App::IntervalTcpClient);
	connect(timerTcpClient, SIGNAL(timeout()), this, SLOT(sendDataTcpClient()));

	timerTcpServer = new QTimer(this);
	timerTcpServer->setInterval(App::IntervalTcpServer);
	connect(timerTcpServer, SIGNAL(timeout()), this, SLOT(sendDataTcpServer()));

	timerUdpServer = new QTimer(this);
	timerUdpServer->setInterval(App::IntervalUdpServer);
	connect(timerUdpServer, SIGNAL(timeout()), this, SLOT(sendDataUdpServer()));

	if (App::AutoSendTcpClient) {
		timerTcpClient->start();
	}

	if (App::AutoSendTcpServer) {
		timerTcpServer->start();
	}

	if (App::AutoSendUdpServer) {
		timerUdpServer->start();
	}

	connect(ui->btnSendTcpServer, SIGNAL(clicked()), this, SLOT(sendDataTcpServer()));
	connect(ui->btnSendTcpClient, SIGNAL(clicked()), this, SLOT(sendDataTcpClient()));
	connect(ui->btnSendUdpServer, SIGNAL(clicked()), this, SLOT(sendDataUdpServer()));
}

void frmNetTool::initConfig()
{
	App::ReadConfig();

	QStringList interval;
	interval << "50" << "100" << "200" << "300";

	for (int i = 500; i < 10000; i = i + 500) {
		interval << QString("%1").arg(i);
	}

	ui->cboxIntervalTcpClient->addItems(interval);
	ui->cboxIntervalTcpServer->addItems(interval);
	ui->cboxIntervalUdpServer->addItems(interval);

	ui->frmTcpServer->setMinimumWidth(App::RightPanelWidth);
	ui->frmTcpServer->setMaximumWidth(App::RightPanelWidth);
	ui->frmTcpClient->setMinimumWidth(App::RightPanelWidth);
	ui->frmTcpClient->setMaximumWidth(App::RightPanelWidth);
	ui->frmUdpServer->setMinimumWidth(App::RightPanelWidth);
	ui->frmUdpServer->setMaximumWidth(App::RightPanelWidth);

	//Tcp server部分
	ui->ckHexSendTcpServer->setChecked(App::HexSendTcpServer);
	connect(ui->ckHexSendTcpServer, SIGNAL(stateChanged(int)), this, SLOT(saveConfig()));

	ui->ckHexReceiveTcpServer->setChecked(App::HexReceiveTcpServer);
	connect(ui->ckHexReceiveTcpServer, SIGNAL(stateChanged(int)), this, SLOT(saveConfig()));

	ui->ckDebugTcpServer->setChecked(App::DebugTcpServer);
	connect(ui->ckDebugTcpServer, SIGNAL(stateChanged(int)), this, SLOT(saveConfig()));

	ui->ckAutoSendTcpServer->setChecked(App::AutoSendTcpServer);
	connect(ui->ckAutoSendTcpServer, SIGNAL(stateChanged(int)), this, SLOT(saveConfig()));

	ui->cboxIntervalTcpServer->setEnabled(App::AutoSendTcpServer);
	ui->cboxIntervalTcpServer->setCurrentIndex(ui->cboxIntervalTcpServer->findText(QString::number(App::IntervalTcpServer)));
	connect(ui->cboxIntervalTcpServer, SIGNAL(currentIndexChanged(int)), this, SLOT(saveConfig()));

	ui->txtTcpListenPort->setText(QString::number(App::TcpListenPort));
	connect(ui->txtTcpListenPort, SIGNAL(textChanged(QString)), this, SLOT(saveConfig()));

	//Tcp client部分
	ui->ckHexSendTcpClient->setChecked(App::HexSendTcpClient);
	connect(ui->ckHexSendTcpClient, SIGNAL(stateChanged(int)), this, SLOT(saveConfig()));

	ui->ckHexReceiveTcpClient->setChecked(App::HexReceiveTcpClient);
	connect(ui->ckHexReceiveTcpClient, SIGNAL(stateChanged(int)), this, SLOT(saveConfig()));

	ui->ckDebugTcpClient->setChecked(App::DebugTcpClient);
	connect(ui->ckDebugTcpClient, SIGNAL(stateChanged(int)), this, SLOT(saveConfig()));

	ui->ckAutoSendTcpClient->setChecked(App::AutoSendTcpClient);
	connect(ui->ckAutoSendTcpClient, SIGNAL(stateChanged(int)), this, SLOT(saveConfig()));

	ui->cboxIntervalTcpClient->setEnabled(App::AutoSendTcpClient);
	ui->cboxIntervalTcpClient->setCurrentIndex(ui->cboxIntervalTcpClient->findText(QString::number(App::IntervalTcpClient)));
	connect(ui->cboxIntervalTcpClient, SIGNAL(currentIndexChanged(int)), this, SLOT(saveConfig()));

	ui->txtTcpServerIP->setText(App::TcpServerIP);
	connect(ui->txtTcpServerIP, SIGNAL(textChanged(QString)), this, SLOT(saveConfig()));

	ui->txtTcpServerPort->setText(QString::number(App::TcpServerPort));
	connect(ui->txtTcpServerPort, SIGNAL(textChanged(QString)), this, SLOT(saveConfig()));

	//Udp server部分
	ui->ckHexSendUdpServer->setChecked(App::HexSendUdpServer);
	connect(ui->ckHexSendUdpServer, SIGNAL(stateChanged(int)), this, SLOT(saveConfig()));

	ui->ckHexReceiveUdpServer->setChecked(App::HexReceiveUdpServer);
	connect(ui->ckHexReceiveUdpServer, SIGNAL(stateChanged(int)), this, SLOT(saveConfig()));

	ui->ckDebugUdpServer->setChecked(App::DebugUdpServer);
	connect(ui->ckDebugUdpServer, SIGNAL(stateChanged(int)), this, SLOT(saveConfig()));

	ui->ckAutoSendUdpServer->setChecked(App::AutoSendUdpServer);
	connect(ui->ckAutoSendUdpServer, SIGNAL(stateChanged(int)), this, SLOT(saveConfig()));

	ui->cboxIntervalUdpServer->setEnabled(App::AutoSendUdpServer);
	ui->cboxIntervalUdpServer->setCurrentIndex(ui->cboxIntervalUdpServer->findText(QString::number(App::IntervalUdpServer)));
	connect(ui->cboxIntervalUdpServer, SIGNAL(currentIndexChanged(int)), this, SLOT(saveConfig()));

	ui->txtUdpListenPort->setText(QString::number(App::UdpListenPort));
	connect(ui->txtUdpListenPort, SIGNAL(textChanged(QString)), this, SLOT(saveConfig()));

	ui->txtUdpClientIP->setText(App::UdpClientIP);
	connect(ui->txtUdpClientIP, SIGNAL(textChanged(QString)), this, SLOT(saveConfig()));

	ui->txtUdpClientPort->setText(QString::number(App::UdpClientPort));
	connect(ui->txtUdpClientPort, SIGNAL(textChanged(QString)), this, SLOT(saveConfig()));
}

void frmNetTool::saveConfig()
{
	App::HexSendTcpServer = ui->ckHexSendTcpServer->isChecked();
	App::HexReceiveTcpServer = ui->ckHexReceiveTcpServer->isChecked();
	App::DebugTcpServer = ui->ckDebugTcpServer->isChecked();

	bool autoSendTcpServer = ui->ckAutoSendTcpServer->isChecked();

	if (autoSendTcpServer != App::AutoSendTcpServer) {
		App::AutoSendTcpServer = autoSendTcpServer;
		ui->cboxIntervalTcpServer->setEnabled(App::AutoSendTcpServer);

		if (App::AutoSendTcpServer) {
			timerTcpServer->start();
		} else {
			timerTcpServer->stop();
		}
	}

	App::IntervalTcpServer = ui->cboxIntervalTcpServer->currentText().toInt();
	timerTcpServer->setInterval(App::IntervalTcpServer);

	App::TcpListenPort = ui->txtTcpListenPort->text().toInt();

	App::HexSendTcpClient = ui->ckHexSendTcpClient->isChecked();
	App::HexReceiveTcpClient = ui->ckHexReceiveTcpClient->isChecked();
	App::DebugTcpClient = ui->ckDebugTcpClient->isChecked();

	bool autoSendTcpClient = ui->ckAutoSendTcpClient->isChecked();

	if (autoSendTcpClient != App::AutoSendTcpClient) {
		App::AutoSendTcpClient = autoSendTcpClient;
		ui->cboxIntervalTcpClient->setEnabled(App::AutoSendTcpClient);

		if (App::AutoSendTcpClient) {
			timerTcpClient->start();
		} else {
			timerTcpClient->stop();
		}
	}

	App::IntervalTcpClient = ui->cboxIntervalTcpClient->currentText().toInt();
	timerTcpClient->setInterval(App::IntervalTcpClient);

	App::TcpServerIP = ui->txtTcpServerIP->text();
	App::TcpServerPort = ui->txtTcpListenPort->text().toInt();

	App::HexSendUdpServer = ui->ckHexSendUdpServer->isChecked();
	App::HexReceiveUdpServer = ui->ckHexReceiveUdpServer->isChecked();
	App::DebugUdpServer = ui->ckDebugUdpServer->isChecked();

	bool autoSendUdpServer = ui->ckAutoSendUdpServer->isChecked();

	if (autoSendUdpServer != App::AutoSendUdpServer) {
		App::AutoSendUdpServer = autoSendUdpServer;
		ui->cboxIntervalUdpServer->setEnabled(App::AutoSendUdpServer);

		if (App::AutoSendUdpServer) {
			timerUdpServer->start();
		} else {
			timerUdpServer->stop();
		}
	}

	App::IntervalUdpServer = ui->cboxIntervalUdpServer->currentText().toInt();
	timerUdpServer->setInterval(App::IntervalUdpServer);

	App::UdpListenPort = ui->txtUdpListenPort->text().toInt();
	App::UdpClientIP = ui->txtUdpClientIP->text();
	App::UdpClientPort = ui->txtUdpClientPort->text().toInt();

	App::WriteConfig();
}

void frmNetTool::appendTcpClient(quint8 type, QString msg)
{
	if (countTcpClient > msgMaxCount) {
		ui->txtDataTcpClient->clear();
		countTcpClient = 0;
	}

	QString str;

	if (type == 0) {
		str = ">> 发送 :";
		ui->txtDataTcpClient->setTextColor(QColor("dodgerblue"));
	} else if (type == 1) {
		str = "<< 接收 :";
		ui->txtDataTcpClient->setTextColor(QColor("red"));
	}

	ui->txtDataTcpClient->append(QString("时间[%1] %2 %3").arg(TIMEMS).arg(str).arg(msg));
	countTcpClient++;
}

void frmNetTool::appendTcpServer(quint8 type, QString msg)
{
	if (countTcpServer > msgMaxCount) {
		ui->txtDataTcpServer->clear();
		countTcpServer = 0;
	}

	QString str;

	if (type == 0) {
		str = ">> 发送 :";
		ui->txtDataTcpServer->setTextColor(QColor("dodgerblue"));
	} else if (type == 1) {
		str = "<< 接收 :";
		ui->txtDataTcpServer->setTextColor(QColor("red"));
	}

	ui->txtDataTcpServer->append(QString("时间[%1] %2 %3").arg(TIMEMS).arg(str).arg(msg));
	countTcpServer++;
}

void frmNetTool::sendDataUdpServer()
{
	QString data = ui->cboxSendUdpServer->currentText();
	sendDataUdpServer(data);
}

void frmNetTool::sendDataUdpServer(QString data)
{
	QString ip = ui->txtUdpClientIP->text();
	int port = ui->txtUdpClientPort->text().toInt();
	sendDataUdpServer(ip, port, data);
}

void frmNetTool::sendDataUdpServer(QString ip, int port, QString data)
{
	if (!data.isEmpty()) {
		QByteArray buffer;

		if (App::HexSendUdpServer) {
			buffer = myHelper::hexStrToByteArray(data);
		} else {
			buffer = myHelper::asciiStrToByteArray(data);
		}

		udpServer->writeDatagram(buffer, QHostAddress(ip), port);

		QString str = QString("目标:%1[%2] ").arg(ip).arg(port);
		appendUdpServer(0, str + data);
	}
}

void frmNetTool::appendUdpServer(quint8 type, QString msg)
{
	if (countUdpServer > msgMaxCount) {
		ui->txtDataUdpServer->clear();
		countUdpServer = 0;
	}

	QString str;

	if (type == 0) {
		str = ">> 发送 :";
		ui->txtDataUdpServer->setTextColor(QColor("dodgerblue"));
	} else if (type == 1) {
		str = "<< 接收 :";
		ui->txtDataUdpServer->setTextColor(QColor("red"));
	}

	ui->txtDataUdpServer->append(QString("时间[%1] %2 %3").arg(TIMEMS).arg(str).arg(msg));
	countUdpServer++;
}

void frmNetTool::tcpClientReadData()
{
	if (tcpClient->bytesAvailable() <= 0) {
		return;
	}

	QByteArray data = tcpClient->readAll();
	QString buffer;

	if (App::HexReceiveTcpClient) {
		buffer = myHelper::byteArrayToHexStr(data);
	} else {
		buffer = myHelper::byteArrayToAsciiStr(data);
	}

	appendTcpClient(1, buffer);

	if (App::DebugTcpClient) {
		int count = keys.count();

		for (int i = 0; i < count; i++) {
			if (keys.at(i) == buffer) {
				sendDataTcpClient(values.at(i));
				break;
			}
		}
	}
}

void frmNetTool::tcpClientReadError()
{
	tcpClient->disconnectFromHost();
	ui->btnTcpConnect->setText("连接");
	ui->btnSendTcpClient->setEnabled(false);
	ui->cboxSendTcpClient->lineEdit()->clear();
	appendTcpClient(1, QString("连接服务器失败,原因 : %1").arg(tcpClient->errorString()));
}

void frmNetTool::clientReadData(int , QString ip, int port, QByteArray data)
{
	QString buffer;

	if (App::HexReceiveTcpServer) {
		buffer = myHelper::byteArrayToHexStr(data);
	} else {
		buffer = myHelper::byteArrayToAsciiStr(data);
	}

	appendTcpServer(1, QString("%1 [%2:%3]").arg(buffer).arg(ip).arg(port));

	if (App::DebugTcpServer) {
		int count = keys.count();

		for (int i = 0; i < count; i++) {
			if (keys.at(i) == buffer) {
				sendDataTcpServer(ip, port, values.at(i));
				break;
			}
		}
	}
}

void frmNetTool::clientConnect(int , QString ip, int port)
{
    appendTcpServer(1, QString("客户端[%1:%2] 上线").arg(ip).arg(port));

	ui->listTcpClient->clear();
	ui->listTcpClient->addItems(tcpServer->getClientInfo());
	ui->labTcpClientCount->setText(QString("已连接客户端共 %1 个").arg(tcpServer->getClientCount()));

	int count = ui->listTcpClient->count();

	if (count > 0) {
		ui->listTcpClient->setCurrentRow(count - 1);
	}
}

void frmNetTool::clientDisConnect(int , QString ip, int port)
{
	appendTcpServer(1, QString("客户端[%1:%2] 下线").arg(ip).arg(port));

	ui->listTcpClient->clear();
	ui->listTcpClient->addItems(tcpServer->getClientInfo());
	ui->labTcpClientCount->setText(QString("已连接客户端共 %1 个").arg(tcpServer->getClientCount()));

	int count = ui->listTcpClient->count();

	if (count > 0) {
		ui->listTcpClient->setCurrentRow(count - 1);
	}
}

void frmNetTool::udpServerReadData()
{
	QHostAddress senderServerIP;
	quint16 senderServerPort;
	QByteArray data;
	QString buffer;

	do {
		data.resize(udpServer->pendingDatagramSize());
		udpServer->readDatagram(data.data(), data.size(), &senderServerIP, &senderServerPort);

		if (App::HexReceiveUdpServer) {
			buffer = myHelper::byteArrayToHexStr(data);
		} else {
			buffer = myHelper::byteArrayToAsciiStr(data);
		}

		QString str = QString("来自:%1[%2] ").arg(senderServerIP.toString()).arg(senderServerPort);
		appendUdpServer(1, str + buffer);

		if (App::DebugUdpServer) {
			int count = keys.count();

			for (int i = 0; i < count; i++) {
				if (keys.at(i) == buffer) {
					sendDataUdpServer(values.at(i));
					break;
				}
			}
		}
	} while (udpServer->hasPendingDatagrams());
}

void frmNetTool::udpServerReadError()
{
	appendUdpServer(1, QString("发生错误,原因 : %1").arg(udpServer->errorString()));
}

void frmNetTool::readSendData()
{
	QString fileName = QString("%1/%2").arg(AppPath).arg(App::SendFileName);
	QFile file(fileName);

	if (!file.exists()) {
		return;
	}

	ui->cboxSendTcpClient->clear();
	ui->cboxSendTcpServer->clear();
	ui->cboxSendUdpServer->clear();

	file.open(QFile::ReadOnly | QIODevice::Text);
	QTextStream in(&file);
	QString line;

	do {
		line = in.readLine();

		if (line != "") {
			ui->cboxSendTcpClient->addItem(line);
			ui->cboxSendTcpServer->addItem(line);
			ui->cboxSendUdpServer->addItem(line);
		}
	} while (!line.isNull());

	file.close();
}

void frmNetTool::readDeviceData()
{
	QString fileName = QString("%1/%2").arg(AppPath).arg(App::DeviceFileName);
	QFile file(fileName);

	if (!file.exists()) {
		return;
	}

	file.open(QFile::ReadOnly | QIODevice::Text);
	QTextStream in(&file);
	QString line;

	do {
		line = in.readLine();

		if (line != "") {
			QStringList list = line.split(";");
			QString key = list.at(0);
			QString value;

			for (int i = 1; i < list.count(); i++) {
				value += QString("%1;").arg(list.at(i));
			}

			//去掉末尾分号
			value = value.mid(0, value.length() - 1);

			keys.append(key);
			values.append(value);
		}
	} while (!line.isNull());

	file.close();
}

void frmNetTool::sendDataTcpServer()
{
	QString data = ui->cboxSendTcpServer->currentText();
	sendDataTcpServer(data);
}

void frmNetTool::sendDataTcpServer(QString data)
{
	if (!tcpServer->isListening()) {
		return;
	}

	if (data.isEmpty()) {
		return;
	}

	bool all = ui->ckAllTcpServer->isChecked();
	QString str = ui->listTcpClient->currentIndex().data().toString();

	//没有一个连接则不用处理
	if (str.isEmpty()) {
		return;
	}

	QStringList list = str.split(":");
	QString ip = list.at(0);
	int port = list.at(1).toInt();

	QByteArray buffer;

	if (App::HexSendTcpServer) {
		buffer = myHelper::hexStrToByteArray(data);
	} else {
		buffer = myHelper::asciiStrToByteArray(data);
	}

	if (!all) {
		tcpServer->sendData(ip, port, buffer);
	} else {
		tcpServer->sendData(buffer);
	}

	appendTcpServer(0, data);
}

void frmNetTool::sendDataTcpServer(QString ip, int port, QString data)
{
	if (!tcpServer->isListening()) {
		return;
	}

	QByteArray buffer;

	if (App::HexSendTcpServer) {
		buffer = myHelper::hexStrToByteArray(data);
	} else {
		buffer = myHelper::asciiStrToByteArray(data);
	}

	tcpServer->sendData(ip, port, buffer);
	appendTcpServer(0, data);
}

void frmNetTool::sendDataTcpClient()
{
	QString data = ui->cboxSendTcpClient->currentText();
	sendDataTcpClient(data);
}

void frmNetTool::sendDataTcpClient(QString data)
{
	if (!tcpClient->isWritable()) {
		return;
	}

	if (data.isEmpty()) {
		return;
	}

	if (!ui->btnSendTcpClient->isEnabled()) {
		return;
	}

	QByteArray buffer;

	if (App::HexSendTcpClient) {
		buffer = myHelper::hexStrToByteArray(data);
	} else {
		buffer = myHelper::asciiStrToByteArray(data);
	}

	tcpClient->write(buffer);
	appendTcpClient(0, data);
}

void frmNetTool::on_btnTcpListen_clicked()
{
	if (ui->btnTcpListen->text() == "监听") {
		bool ok = tcpServer->listen(QHostAddress::Any, App::TcpServerPort);

		if (ok) {
			ui->btnTcpListen->setText("停止");
			ui->btnSendTcpServer->setEnabled(true);
			appendTcpServer(0, "监听成功");
		} else {
			appendTcpServer(1, "监听失败,请检查端口是否被占用");
		}
	} else {
		ui->listTcpClient->clear();
		tcpServer->closeAll();
		ui->btnTcpListen->setText("监听");
		ui->btnSendTcpServer->setEnabled(false);
		appendTcpServer(0, "停止监听成功");
	}
}

void frmNetTool::on_btnClearTcpServer_clicked()
{
	ui->txtDataTcpServer->clear();
	countTcpServer = 0;
}

void frmNetTool::on_btnTcpConnect_clicked()
{
	if (ui->btnTcpConnect->text() == "连接") {
		tcpClient->connectToHost(App::TcpServerIP, App::TcpServerPort);

		if (tcpClient->waitForConnected(1000)) {
			ui->btnTcpConnect->setText("断开");
			ui->btnSendTcpClient->setEnabled(true);
			appendTcpClient(0, "连接服务器成功");
		} else {
			appendTcpClient(1, "连接服务器失败");
		}
	} else {
		tcpClient->disconnectFromHost();

		if (tcpClient->state() == QAbstractSocket::UnconnectedState || tcpClient->waitForDisconnected(1000)) {
			ui->btnTcpConnect->setText("连接");
			ui->btnSendTcpClient->setEnabled(false);
			appendTcpClient(0, "断开连接成功");
		}
	}
}

void frmNetTool::on_btnClearTcpClient_clicked()
{
	ui->txtDataTcpClient->clear();
	countTcpClient = 0;
}

void frmNetTool::on_btnUdpListen_clicked()
{
	if (ui->btnUdpListen->text() == "监听") {
		bool ok = udpServer->bind(App::UdpListenPort);

		if (ok) {
			ui->btnUdpListen->setText("停止");
			ui->btnSendUdpServer->setEnabled(true);
			appendUdpServer(0, "监听成功");
		} else {
			appendUdpServer(1, "监听失败,请检查端口是否被占用");
		}
	} else {
		udpServer->abort();
		ui->btnUdpListen->setText("监听");
		ui->btnSendUdpServer->setEnabled(false);
		appendUdpServer(0, "停止监听成功");
	}
}

void frmNetTool::on_btnClearUdpServer_clicked()
{
	ui->txtDataUdpServer->clear();
	countUdpServer = 0;
}
