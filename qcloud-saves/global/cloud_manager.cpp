#include "cloud_manager.h"

CloudManager* const CloudManager::Instance = new CloudManager();

CloudManager::CloudManager(QObject *parent)
	: QObject(parent)
{
	connect(UvLooper::Instance, &UvLooper::newMsgResponsed, this, &CloudManager::OnNewMsgResponsed);
}

void CloudManager::Request(RequestType type, const QByteArray& buf)
{
	QByteArray total{};
	total.append((char)type);
	total.append(buf);
	UvLooper::Instance->Send(total);
}

CloudManager::~CloudManager()
{}

void CloudManager::OnNewMsgResponsed(const QByteArray& val) {
	ResponsedEvent event = {
		(RequestType)*val.data(),
		QByteArray(val.data() + 1, val.size() - 1)
	};
	QEasyEventBus::Emit(std::move(event));
}