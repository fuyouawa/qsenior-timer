#include "connect_server_win.h"

ConnectServerWin::ConnectServerWin(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	ClientManager::Instance->ConnectServer();
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
		switch (packet.data.at(0))
		{
		case kSuccess:
		{
			qint64 stamp = 0;
			memcpy(&stamp, &packet.data[1], sizeof(qint64));
			UserInfo::RegistryStamp = stamp;
			MainWin::Instance = new MainWin();
			MainWin::Instance->show();
			close();
			delete this;
			break;
		}
		default:
		{
			ui.lab_msg->setText("疑似缓存文件损坏!\n请重启本程序进行重新登录");
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
	auto data = CombineQStrs({ UserInfo::UserName, UserInfo::Password });
	ClientManager::Instance->Request(Packet({ kGetUserProperty, data }));
}
