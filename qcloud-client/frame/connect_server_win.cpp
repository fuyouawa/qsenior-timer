#include "connect_server_win.h"

ConnectServerWin::ConnectServerWin(QWidget* parent)
	: QMainWindow(parent),
	socket_(parent)
{
	ui.setupUi(this);

	socket_.SetConnectedCb(this, [this]() {
		socket_.AutoRequest({ kGetUserProperty, QByteArray() });
		});

	socket_.SetErrorOccuredCb(this, [this](QTcpSocket::SocketError err) {
		ui.lab_msg->setText("服务器连接失败!\n错误信息: " + socket_.ErrStr());
		});

	socket_.SetReceivedDataCb(this, [this](RequestType type) {
		socket_.DisConnectServer();
		switch (type)
		{
		case kGetUserProperty:
		{
			auto packet = socket_.DequeuePacket();
			switch (packet.data.at(0))
			{
			case kSuccess:
			{
				qint64 stamp = 0;
				memcpy(&stamp, &packet.data[1], sizeof(qint64));
				MainWin::Instance = new MainWin(stamp);
				MainWin::Instance->show();
				this->deleteLater();
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
		});

	socket_.ConnectToServer();
}

ConnectServerWin::~ConnectServerWin()
{
}