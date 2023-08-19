#include "local_server.h"

LocalServer* const LocalServer::Instance = new LocalServer();

LocalServer::LocalServer(QObject *parent)
	: QObject(parent),
	server_(this),
	client_socket_(nullptr),
	temp_file_(this)
{
	if (temp_file_.open()) {
		temp_file_.close();
	}
	else {
		ShowErrorMsg("临时文件创建失败!", 0);
		QApplication::exit(-1);
	}

	server_.listen(kLocalCommonName);

	connect(&server_, &QLocalServer::newConnection, [this]() {
		client_socket_ = server_.nextPendingConnection();
		connect(client_socket_, &QLocalSocket::readyRead, this, &LocalServer::OnLocalClientRequest);
		});
}

LocalServer::~LocalServer()
{}

QString LocalServer::TempFilePath()
{
	return temp_file_.fileName();
}

void LocalServer::OnLocalClientRequest()
{
	auto data = client_socket_->readAll();
	switch (data.at(0))
	{
	case kGetTimersTemp:
	{
		if (temp_file_.open()) {
			QFile file{ "E:\\Resources\\Test\\temp.txt" };
			file.open(QIODevice::WriteOnly);
			//QTextStream out(&temp_file_);
			QTextStream out(&file);
			QJsonObject total;
			TimerDb::Instance->ForeachBuffer([this, &total](const QString& timer_name, const QByteArray& data) {
				total[timer_name] = QString::fromUtf8(data);
				return true;
				});
			out << QJsonDocument(total).toJson(QJsonDocument::Compact);
			temp_file_.close();
			client_socket_->write(QByteArray(1, kSuccessGetTimersTemp));
			client_socket_->flush();
		}
		else {
			client_socket_->write(QByteArray(1, kFalidOpenTempFile));
			client_socket_->flush();
		}
		break;
	}
	default:
		break;
	}
}
