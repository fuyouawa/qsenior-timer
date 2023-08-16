#pragma once

#include <QObject>
#include <QMap>
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
	void Request(const Packet& packet);
	Packet DequeuePacket();

private slots:
	void OnNewMsgReceived(PacketBuffer* packet_buf);
	void OnConnectedToServer();

private:
	ClientManager(QObject* parent = nullptr);
};
