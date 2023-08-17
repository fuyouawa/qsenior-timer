#pragma once

#include <QObject>
#include <QMap>
#include "global/utils.h"
#include "global/event_types.h"
#include "global/client_looper.h"

class ClientManager  : public QObject
{
	Q_OBJECT

public:
	static ClientManager* const Instance;

	~ClientManager();

	void DisConnectServer();
	void ConnectServer();
	void AutoConnectServer();
	void Request(QString user_name, QString password, const Packet& packet);
	void AutoRequest(const Packet& packet);
	Packet DequeuePacket();

	bool IsConnecting();

private slots:
	void OnNewMsgReceived(PacketBuffer* packet_buf);
	void OnConnectedToServer();
	void OnConnectError(int status);
	void OnReadError(int status);

private:
	ClientManager(QObject* parent = nullptr);
};
