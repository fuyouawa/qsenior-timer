#include "local_client.h"

LocalClient* const LocalClient::Instance = new LocalClient();

LocalClient::LocalClient(QObject *parent)
	: QObject(parent),
	socket_(this)
{
	socket_.connectToServer(kLocalCommonName);

	connect(&socket_, &QLocalSocket::readyRead, [this]() {
		qteasylib::EventBus::Emit(LocalServerResponsedEvent({ socket_.readAll() }));
		});
}

LocalClient::~LocalClient()
{}

void LocalClient::Request(LocalRequestCode code)
{
	socket_.write(QByteArray(1, code));
	socket_.flush();
}
