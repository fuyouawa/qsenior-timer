#include "client_manager.h"


ClientManager* const ClientManager::Instance = new ClientManager();

void ClientManager::OnConnectedToServer()
{
	qteasylib::EventBus::Emit(ConnectedToServerEvent());
}

void ClientManager::OnConnectError(int status)
{
	qteasylib::EventBus::Emit(ConnectError({ uv_strerror(status), uv_err_name(status) }));
}

void ClientManager::OnReadError(int status)
{
	auto a = uv_strerror(status);
}

ClientManager::ClientManager(QObject *parent)
	: QObject(parent)
{
}

void ClientManager::DisConnectServer()
{
	ClientLooper::Instance->stop();
	ClientLooper::Instance->wait();
	ClientLooper::Instance->deleteLater();
	ClientLooper::Instance = nullptr;
}

void ClientManager::ConnectServer()
{
	ClientLooper::Instance = new ClientLooper(this);
	connect(ClientLooper::Instance, &ClientLooper::newMsgReceived, this, &ClientManager::OnNewMsgReceived, Qt::QueuedConnection);
	connect(ClientLooper::Instance, &ClientLooper::connectedToServer, this, &ClientManager::OnConnectedToServer, Qt::QueuedConnection);
	connect(ClientLooper::Instance, &ClientLooper::connectError, this, &ClientManager::OnConnectError, Qt::QueuedConnection);
	connect(ClientLooper::Instance, &ClientLooper::readError, this, &ClientManager::OnReadError, Qt::QueuedConnection);
	ClientLooper::Instance->start();
}

void ClientManager::AutoConnectServer()
{
	if (!IsConnecting())
		ConnectServer();
}

void ClientManager::Request(QString user_name, QString password, const Packet& packet)
{
	QMetaObject::invokeMethod(ClientLooper::Instance, "Send", Q_ARG(QByteArray,
			qteasylib::ToSha256(user_name.toUtf8()) +
			qteasylib::ToSha256(password.toUtf8()) +
			(char)packet.req_type +
			packet.data)
	);
}

void ClientManager::AutoRequest(const Packet& packet)
{
	Request(UserInfo::UserName, UserInfo::Password, packet);
}

Packet ClientManager::DequeuePacket()
{
	auto packet = ClientLooper::Instance->Dequeue();
	RequestType type = (RequestType)packet.at(0);
	packet.remove(0, 1);
	return Packet({ type, packet });
}

bool ClientManager::IsConnecting()
{
	return ClientLooper::Instance != nullptr && ClientLooper::Instance->is_connecting_;
}

ClientManager::~ClientManager()
{}

void ClientManager::OnNewMsgReceived(PacketBuffer* packet_buf) {
	qteasylib::EventBus::Emit(ResponsedEvent({ (RequestType)packet_buf->data[0] }));
}