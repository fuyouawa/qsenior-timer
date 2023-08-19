#include "connect_server_win.h"

ConnectServerWin::ConnectServerWin(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	ClientManager::Instance->AutoConnectServer();
}

ConnectServerWin::~ConnectServerWin()
{
}

void ConnectServerWin::OnEvent(const ResponsedEvent& event)
{
	switch (event.type)
	{
	case kGetUserProperty:
	{
		auto packet = ClientManager::Instance->DequeuePacket();
		ClientManager::Instance->DisConnectServer();
		switch (packet.data.at(0))
		{
		case kSuccess:
		{
			qint64 stamp = 0;
			memcpy(&stamp, &packet.data[1], sizeof(qint64));
			MainWin::Instance = new MainWin(stamp);
			MainWin::Instance->show();
			close();
			delete this;
			break;
		}
		default:
		{
			ui.lab_msg->setText("获取用户信息失败!\n请重启本程序进行重新登录");
			break;
		}
		}
		break;
	}
	default:
		break;
	}
}

void ConnectServerWin::OnEvent(const ConnectedToServerEvent& event)
{
	ClientManager::Instance->AutoRequest({ kGetUserProperty, QByteArray() });
}

void ConnectServerWin::OnEvent(const ConnectErrorEvent& event)
{
	ui.lab_msg->setText("服务器连接失败!\n错误名称: " + event.err_name + "\n错误信息: " + event.err_msg);
	ClientManager::Instance->DisConnectServer();
}
