#include "mainwin.h"

MainWin::MainWin(qint64 registry_stamp, QWidget* parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);

	auto registry_data = QDateTime::fromSecsSinceEpoch(registry_stamp);
	ui.edit_registry_date->setDateTime(registry_data);
	ui.edit_user_name->setText(UserInfo::UserName);
	ui.edit_password->setText(UserInfo::Password);
}

MainWin::~MainWin()
{}

void MainWin::on_btn_upload_saves_clicked()
{
	is_upload_ = true;
	ClientManager::Instance->ConnectServer();
}

void MainWin::on_btn_download_saves_clicked()
{
	is_upload_ = false;
}

void MainWin::OnEvent(const ResponsedEvent & event)
{
}

void MainWin::OnEvent(const ConnectedToServerEvent& event)
{
	if (is_upload_) {
		AppendLog("向主程序请求获取计时器缓存......");
		LocalClient::Instance->Request(kGetTimersTemp);
	}
}

void MainWin::OnEvent(const LocalServerResponsedEvent& event)
{
	switch (event.data.at(0))
	{
	case kSuccessGetTimersTemp:
	{
		QFile temp{ BasicConfig::TempFilePath };
		if (temp.open(QIODevice::ReadOnly)) {
			QTextStream in{ &temp };
			AppendLog("获取缓存成功!");
			AppendLog("向服务器发送数据......");
			AppendLog(in.readAll());
			//ClientManager::Instance->AutoRequest(Packet({ kUploadTimers, in.readAll().toUtf8() }));
		}
		else {
			AppendLog("无法打开临时文件获取计时器缓存!");
		}
		break;
	}
	case kFalidOpenTempFile:
	{
		AppendLog("无法打开临时文件写入计时器缓存!");
		ErrorOccurred();
		break;
	}
	default:
		break;
	}
}

void MainWin::OnEvent(const ConnectErrorEvent& event)
{
	AppendLog("服务器连接失败! 原因:" + event.err_msg);
	ErrorOccurred();
}

void MainWin::ErrorOccurred()
{
	QMessageBox::critical(this, "错误", "出现错误!");
}

void MainWin::AppendLog(const QString& msg)
{
	ui.edit_log->appendPlainText(msg);
}


void MainWin::on_btn_view_pwd_clicked(bool checked)
{
	ui.btn_view_pwd->setIcon(QIcon(checked ? ":/pictures/open_eyes.png" : ":/pictures/close_eyes.png"));
	ui.edit_password->setEchoMode(checked ? QLineEdit::Normal : QLineEdit::Password);
}