#include "client_manager.h"

ClientManager* const ClientManager::Instance = new ClientManager();

void ClientManager::OnConnectedToServer()
{
	QEasyEventBus::Emit(ConnectedToServerEvent());
}

ClientManager::ClientManager(QObject *parent)
	: QObject(parent)
{
}

void ClientManager::DisConnectServer()
{
	ClientLooper::Instance->stop();
	ClientLooper::Instance->wait();
	delete ClientLooper::Instance;
}

void ClientManager::ConnectServer()
{
	ClientLooper::Instance = new ClientLooper(this);
	connect(ClientLooper::Instance, &ClientLooper::newMsgReceived, this, &ClientManager::OnNewMsgReceived, Qt::QueuedConnection);
	connect(ClientLooper::Instance, &ClientLooper::connectedToServer, this, &ClientManager::OnConnectedToServer, Qt::QueuedConnection);
	ClientLooper::Instance->start();
}

void ClientManager::Request(const Packet& packet)
{
	QByteArray total{};
	total.append((char)packet.req_type);
	total.append(packet.data);
	ClientLooper::Instance->Send(total);
}

Packet ClientManager::DequeuePacket()
{
	auto packet = ClientLooper::Instance->Dequeue();
	RequestType type = (RequestType)packet.at(0);
	packet.remove(0, 1);
	return Packet({ type, packet });
}

ClientManager::~ClientManager()
{}

void ClientManager::OnNewMsgReceived(PacketBuffer* packet_buf) {
	QEasyEventBus::Emit(ResponsedEvent({ (RequestType)packet_buf->data[0] }));
}