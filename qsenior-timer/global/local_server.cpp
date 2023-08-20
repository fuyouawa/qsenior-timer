#include "local_server.h"

LocalServer* const LocalServer::Instance = new LocalServer();

LocalServer::LocalServer(QObject *parent)
	: QObject(parent),
	server_(this),
	client_socket_(nullptr)
{
	server_.listen(kLocalCommonName);

	connect(&server_, &QLocalServer::newConnection, [this]() {
		client_socket_ = server_.nextPendingConnection();
		connect(client_socket_, &QLocalSocket::readyRead, this, &LocalServer::OnLocalClientRequest);
		});
}

LocalServer::~LocalServer()
{}

void LocalServer::OnLocalClientRequest()
{
	auto data = client_socket_->readAll();
	switch (data.at(0))
	{
	case kGetTimersTemp:
	{
		QFile file{ BasicConfig::TempFilePath };
		if (file.open(QIODevice::WriteOnly)) {
			QJsonObject total;
			TimerDb::Instance->ForeachBuffer([this, &total](const QString& timer_name, const QByteArray& data) {
				total[timer_name] = QString::fromUtf8(data);
				return true;
				});
			file.write(QJsonDocument(total).toJson(QJsonDocument::Compact));
			client_socket_->write(QByteArray(1, kSuccessGetTimersTemp));
			client_socket_->flush();
		}
		else {
			client_socket_->write(QByteArray(1, kFalidOpenTempFile));
			client_socket_->flush();
		}
		break;
	}
	case kAssignTimersTemp:
	{
		QFile file{ BasicConfig::TempFilePath };
		if (file.open(QIODevice::ReadOnly)) {
			QJsonParseError err;
			auto doc = QJsonDocument::fromJson(file.readAll(), &err);
			if (err.error != QJsonParseError::NoError) {
				ShowErrorMsg("������ʱ�ļ��еļ�ʱ������ʱ���ʹ���! \n������Ϣ: " + err.errorString() + "\nԭ�������������!", 1, MainWinPtr);
				return;
			}
			if (!doc.isObject()) {
				ShowErrorMsg("������ʱ�ļ��еļ�ʱ������ʱ���ʹ���: ������!", 1, MainWinPtr);
				return;
			}
			qteasylib::EventBus::Emit(NeedAssignNewTimersEvent({ doc.object() }));
		}
		else {
			ShowErrorMsg("�޷�����ʱ�ļ���ȡ�������·����ļ�ʱ������!", 1, MainWinPtr);
			return;
		}
		break;
	}
	default:
		break;
	}
}
