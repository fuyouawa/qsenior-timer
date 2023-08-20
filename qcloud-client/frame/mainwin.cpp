#include "mainwin.h"

MainWin::MainWin(qint64 registry_stamp, QWidget* parent)
    : QMainWindow(parent),
	socket_(this)
{
    ui.setupUi(this);

	auto registry_data = QDateTime::fromSecsSinceEpoch(registry_stamp);
	ui.edit_registry_date->setDateTime(registry_data);
	ui.edit_user_name->setText(UserInfo::UserName);
	ui.edit_password->setText(UserInfo::Password);

	socket_.SetConnectedCb(this, [this]() {
		AppendLog("连接服务器成功!");
		if (is_upload_) {
			AppendLog("向服务器上传数据......");
			socket_.AutoRequest(Packet({ kUploadTimers, temp_ }));
			temp_.clear();
		}
		else {
			AppendLog("向服务器请求数据......");
			socket_.AutoRequest(Packet({ kDownloadTimers, QByteArray() }));
		}
		});

	socket_.SetBytesWrittenCb(this, [this](qint64 bytes) {
		if (is_upload_)
			AppendLog("上传数据成功! 数据大小: " + QString::number(bytes) + "字节");
		});

	socket_.SetErrorOccuredCb(this, [this](QTcpSocket::SocketError err) {
		EnableSavesOperBtns(true);
		AppendErrLog("服务器连接失败! 错误信息: " + socket_.ErrStr());
		});

	socket_.SetReceivedDataCb(this, [this](RequestType type) {
		EnableSavesOperBtns(true);
		socket_.DisConnectServer();
		switch (type)
		{
		case kUploadTimers:
		{
			auto packet = socket_.DequeuePacket();
			switch (packet.data.at(0))
			{
			case kSuccess:
			{
				AppendLog("保存数据成功!");
				break;
			}
			}
			break;
		}
		case kDownloadTimers:
		{
			auto packet = socket_.DequeuePacket();
			switch (packet.data.at(0))
			{
			case kSuccess:
			{
				AppendLog("请求数据成功!");
				AppendLog("将请求来的数据写入缓存文件......");
				QFile temp_file{ BasicConfig::TempFilePath };
				if (temp_file.open(QIODevice::WriteOnly)) {
					temp_file.write(packet.data.mid(1));
					AppendLog("成功写入缓存文件!");
					AppendLog("请求主程序更新数据库......");
					LocalClient::Instance->Request(kAssignTimersTemp);
				}
				else {
					AppendErrLog("无法打开缓存文件!");
				}
				break;
			}
			case kNoSaves:
			{
				AppendErrLog("请求数据失败, 您还没有上传任何存档!");
				break;
			}
			}
			break;
		}
		}
		});
}

MainWin::~MainWin()
{}

void MainWin::on_btn_upload_saves_clicked()
{
	is_upload_ = true;
	EnableSavesOperBtns(false);
	ui.edit_log->clear();
	AppendLog("向主程序请求获取计时器缓存......");
	LocalClient::Instance->Request(kGetTimersTemp);
}

void MainWin::on_btn_download_saves_clicked()
{
	is_upload_ = false;
	EnableSavesOperBtns(false);
	ui.edit_log->clear();
	AppendLog("连接服务器......");
	socket_.ConnectToServer();
}

void MainWin::OnEvent(const LocalServerResponsedEvent& event)
{
	switch (event.data.at(0))
	{
	case kSuccessGetTimersTemp:
	{
		QFile temp_file{ BasicConfig::TempFilePath };
		if (temp_file.open(QIODevice::ReadOnly)) {
			temp_ = temp_file.readAll();
			AppendLog("获取缓存成功!");
			AppendLog("连接服务器......");
			socket_.ConnectToServer();
		}
		else {
			AppendErrLog("无法打开临时文件获取计时器缓存!");
		}
		break;
	}
	case kFalidOpenTempFile:
	{
		AppendErrLog("主程序无法打开临时文件读写计时器缓存!");
		break;
	}
	default:
		break;
	}
}

void MainWin::EnableSavesOperBtns(bool enable)
{
	ui.btn_upload_saves->setEnabled(enable);
	ui.btn_download_saves->setEnabled(enable);
	ui.btn_logout->setEnabled(enable);
}
void MainWin::AppendLog(const QString& msg)
{
	ui.edit_log->appendPlainText(QDateTime::currentDateTime().toString("[HH:mm:ss] -> ") + msg);
}

void MainWin::AppendErrLog(const QString& msg)
{
	AppendLog(msg);
	QMessageBox::critical(this, "错误", "出现错误!");
}


void MainWin::on_btn_view_pwd_clicked(bool checked)
{
	ui.btn_view_pwd->setIcon(QIcon(checked ? ":/pictures/open_eyes.png" : ":/pictures/close_eyes.png"));
	ui.edit_password->setEchoMode(checked ? QLineEdit::Normal : QLineEdit::Password);
}