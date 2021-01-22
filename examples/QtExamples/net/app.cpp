#include "app.h"
#include "myhelper.h"

#ifdef __arm__
int App::LeftPanelWidth = 150;
int App::RightPanelWidth = 200;
QString App::PlatForm = "A9";
#else
int App::LeftPanelWidth = 120;
int App::RightPanelWidth = 170;
QString App::PlatForm = "WIN";
#endif

QString App::SendFileName = "send.txt";
QString App::DeviceFileName = "device.txt";

bool App::HexSendTcpServer = false;
bool App::HexReceiveTcpServer = false;
bool App::DebugTcpServer = false;
bool App::AutoSendTcpServer = false;
int App::IntervalTcpServer = 1000;
int App::TcpListenPort = 6000;

bool App::HexSendTcpClient = false;
bool App::HexReceiveTcpClient = false;
bool App::DebugTcpClient = false;
bool App::AutoSendTcpClient = false;
int App::IntervalTcpClient = 1000;
QString App::TcpServerIP = "127.0.0.1";
int App::TcpServerPort = 6000;

bool App::HexSendUdpServer = false;
bool App::HexReceiveUdpServer = false;
bool App::DebugUdpServer = false;
bool App::AutoSendUdpServer = false;
int App::IntervalUdpServer = 1000;
int App::UdpListenPort = 6000;
QString App::UdpClientIP = "127.0.0.1";
int App::UdpClientPort = 6000;

void App::ReadConfig()
{
	if (!CheckConfig()) {
		return;
	}

	QString fileName = QString("%1/%2_Config.ini").arg(AppPath).arg(AppName);
	QSettings set(fileName, QSettings::IniFormat);

	set.beginGroup("AppConfig");
	App::LeftPanelWidth = set.value("LeftPanelWidth").toInt();
	App::RightPanelWidth = set.value("RightPanelWidth").toInt();
	App::PlatForm = set.value("PlatForm").toString();
	App::SendFileName = set.value("SendFileName").toString();
	App::DeviceFileName = set.value("DeviceFileName").toString();
	set.endGroup();

	set.beginGroup("TcpServerConfig");
	App::HexSendTcpServer = set.value("HexSendTcpServer").toBool();
	App::HexReceiveTcpServer = set.value("HexReceiveTcpServer").toBool();
	App::DebugTcpServer = set.value("DebugTcpServer").toBool();
	App::AutoSendTcpServer = set.value("AutoSendTcpServer").toBool();
	App::IntervalTcpServer = set.value("IntervalTcpServer").toInt();
	App::TcpListenPort = set.value("TcpListenPort").toInt();
	set.endGroup();

	set.beginGroup("TcpClientConfig");
	App::HexSendTcpClient = set.value("HexSendTcpClient").toBool();
	App::HexReceiveTcpClient = set.value("HexReceiveTcpClient").toBool();
	App::DebugTcpClient = set.value("DebugTcpClient").toBool();
	App::AutoSendTcpClient = set.value("AutoSendTcpClient").toBool();
	App::IntervalTcpClient = set.value("IntervalTcpClient").toInt();
	App::TcpServerIP = set.value("TcpServerIP").toString();
	App::TcpServerPort = set.value("TcpServerPort").toInt();
	set.endGroup();

	set.beginGroup("UdpServerConfig");
	App::HexSendUdpServer = set.value("HexSendUdpServer").toBool();
	App::HexReceiveUdpServer = set.value("HexReceiveUdpServer").toBool();
	App::DebugUdpServer = set.value("DebugUdpServer").toBool();
	App::AutoSendUdpServer = set.value("AutoSendUdpServer").toBool();
	App::IntervalUdpServer = set.value("IntervalUdpServer").toInt();
	App::UdpListenPort = set.value("UdpListenPort").toInt();
    App::UdpClientIP = set.value("UdpClientIP").toString();
    App::UdpClientPort = set.value("UdpClientPort").toInt();
	set.endGroup();
}

void App::WriteConfig()
{
	QString fileName = QString("%1/%2_Config.ini").arg(AppPath).arg(AppName);
	QSettings set(fileName, QSettings::IniFormat);

	set.beginGroup("AppConfig");
	set.setValue("LeftPanelWidth", App::LeftPanelWidth);
	set.setValue("RightPanelWidth", App::RightPanelWidth);
	set.setValue("PlatForm", App::PlatForm);
	set.setValue("SendFileName", App::SendFileName);
	set.setValue("DeviceFileName", App::DeviceFileName);
	set.endGroup();

	set.beginGroup("TcpServerConfig");
	set.setValue("HexSendTcpServer", App::HexSendTcpServer);
	set.setValue("HexReceiveTcpServer", App::HexReceiveTcpServer);
	set.setValue("DebugTcpServer", App::DebugTcpServer);
	set.setValue("AutoSendTcpServer", App::AutoSendTcpServer);
	set.setValue("IntervalTcpServer", App::IntervalTcpServer);
	set.setValue("TcpListenPort", App::TcpListenPort);
	set.endGroup();

	set.beginGroup("TcpClientConfig");
	set.setValue("HexSendTcpClient", App::HexSendTcpClient);
	set.setValue("HexReceiveTcpClient", App::HexReceiveTcpClient);
	set.setValue("DebugTcpClient", App::DebugTcpClient);
	set.setValue("AutoSendTcpClient", App::AutoSendTcpClient);
	set.setValue("IntervalTcpClient", App::IntervalTcpClient);
	set.setValue("TcpServerIP", App::TcpServerIP);
	set.setValue("TcpServerPort", App::TcpServerPort);
	set.endGroup();

	set.beginGroup("UdpServerConfig");
	set.setValue("HexSendUdpServer", App::HexSendUdpServer);
	set.setValue("HexReceiveUdpServer", App::HexReceiveUdpServer);
	set.setValue("DebugUdpServer", App::DebugUdpServer);
	set.setValue("AutoSendUdpServer", App::AutoSendUdpServer);
	set.setValue("IntervalUdpServer", App::IntervalUdpServer);
	set.setValue("UdpListenPort", App::UdpListenPort);
    set.setValue("UdpClientIP", App::UdpClientIP);
    set.setValue("UdpClientPort", App::UdpClientPort);
	set.endGroup();
}

void App::NewConfig()
{
#if (QT_VERSION <= QT_VERSION_CHECK(5,0,0))
#endif
	WriteConfig();
}

bool App::CheckConfig()
{
	QString fileName = QString("%1/%2_Config.ini").arg(AppPath).arg(AppName);

	//如果配置文件大小为0,则以初始值继续运行,并生成配置文件
	QFile file(fileName);

	if (file.size() == 0) {
		NewConfig();
		return false;
	}

	//如果配置文件不完整,则以初始值继续运行,并生成配置文件
	if (file.open(QFile::ReadOnly)) {
		bool ok = true;

		while (!file.atEnd()) {
			QString line = file.readLine();
			line = line.replace("\r", "");
			line = line.replace("\n", "");
			QStringList list = line.split("=");

			if (list.count() == 2) {
				if (list.at(1) == "") {
					ok = false;
					break;
				}
			}
		}

		if (!ok) {
			NewConfig();
			return false;
		}
	} else {
		NewConfig();
		return false;
	}

	return true;
}

void App::WriteError(QString str)
{
	QString fileName = QString("%1/%2_Error_%3.txt").arg(AppPath).arg(AppName).arg(QDATE);
	QFile file(fileName);
	file.open(QIODevice::WriteOnly | QIODevice::Append | QFile::Text);
	QTextStream stream(&file);
	stream << DATETIME << "  " << str << "\n";
}

void App::NewDir(QString dirName)
{
	//如果路径中包含斜杠字符则说明是绝对路径
	//linux系统路径字符带有 /  windows系统 路径字符带有 :/
	if (!dirName.startsWith("/") && !dirName.contains(":/")) {
		dirName = QString("%1/%2").arg(AppPath).arg(dirName);
	}

	QDir dir(dirName);

	if (!dir.exists()) {
		dir.mkpath(dirName);
	}
}
