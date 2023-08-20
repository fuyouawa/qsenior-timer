#include "socket_manager.h"

SocketManager::SocketManager(QObject* parent)
	: QObject(parent),
	socket_(this),
	handler_()
{
	connect(&socket_, &QTcpSocket::readyRead, this, &SocketManager::OnReadyRead);
	handler_.proc_msg_cb_ = [this](PacketBuffer*& packet) {
		auto ppacket = Packet{
			(RequestType)packet->data[0],
			QByteArray(&packet->data[1], packet->size)
		};
		packets_queue_.enqueue(ppacket);
		free(packet);
		packet = nullptr;
		emit receivedData(ppacket.req_type);
	};
}

SocketManager::~SocketManager()
{
	DisConnectServer();
}

void SocketManager::SetConnectedCb(const QObject* context, const std::function<void()>& cb)
{
	disconnect(connected_connection_);
	connected_connection_ = connect(&socket_, &QTcpSocket::connected, cb);

	connect(context, &QObject::destroyed, this, [this]() {
		disconnect(connected_connection_);
		});
}

void SocketManager::SetReceivedDataCb(const QObject* context, const std::function<void(RequestType)>& cb)
{
	disconnect(received_data_connection_);
	received_data_connection_ = connect(this, &SocketManager::receivedData, cb);

	connect(context, &QObject::destroyed, this, [this]() {
		disconnect(received_data_connection_);
		});
}

void SocketManager::SetErrorOccuredCb(const QObject* context, const std::function<void(QTcpSocket::SocketError)>& cb)
{
	disconnect(error_occured_connection_);
	error_occured_connection_ = connect(&socket_, &QTcpSocket::errorOccurred, cb);

	connect(context, &QObject::destroyed, this, [this]() {
		disconnect(error_occured_connection_);
		});
}

void SocketManager::SetBytesWrittenCb(const QObject* context, const std::function<void(qint64 bytes)>& cb)
{
	disconnect(bytes_written_connection_);
	bytes_written_connection_ = connect(&socket_, &QTcpSocket::bytesWritten, cb);

	connect(context, &QObject::destroyed, this, [this]() {
		disconnect(bytes_written_connection_);
		});
}

void SocketManager::ConnectToServer()
{
	socket_.connectToHost(kServerHost, kPort);
}

void SocketManager::DisConnectServer()
{
	socket_.disconnectFromHost();
}

Packet SocketManager::DequeuePacket()
{
	return packets_queue_.dequeue();
}

QString SocketManager::ErrStr()
{
	return socket_.errorString();
}

bool SocketManager::IsConnected()
{
	return socket_.state() == QTcpSocket::ConnectedState;
}

void SocketManager::Request(const QString& user_name, const QString& password, const Packet& packet)
{
	socket_.write(ConstructPacket(user_name, password, packet));
}

void SocketManager::AutoRequest(const Packet& packet)
{
	Request(UserInfo::UserName, UserInfo::Password, packet);
}

QByteArray SocketManager::ConstructPacket(const QString& user_name, const QString& password, const Packet& packet)
{
	auto data = qteasylib::ToSha256(user_name.toUtf8()) +
		qteasylib::ToSha256(password.toUtf8()) +
		(char)packet.req_type +
		packet.data;

	QByteArray total;
	QDataStream stream(&total, QIODevice::WriteOnly);
	stream.setByteOrder(QDataStream::LittleEndian);
	stream << (buf_size_t)data.size();
	total.append(data);
	return total;
}

void SocketManager::OnReadyRead()
{
	handler_.OnDataReceived(socket_.readAll());
}

bool SocketManager::TcpHandler::OnDataReceived(const QByteArray& bytes)
{
	size_t seek = 0;
	auto len = bytes.size();
	auto base = bytes.data();

	while (seek < len) {
		if (packet_ == nullptr) {
			// 需要新的数据头
			auto buf_packet = (PacketBuffer*)(base + seek);
			if ((len - seek) >= sizeof(buf_size_t)) {
				// 至少有一个完整的buf_size_t
				packet_ = (PacketBuffer*)malloc(sizeof(buf_size_t) + buf_packet->size);
				packet_->size = buf_packet->size;
				packet_read_pos_ = sizeof(buf_size_t);
				size_t available_data = len - seek - sizeof(buf_size_t);

				if (packet_->size > available_data) {
					// 当前buffer里面的数据不足以填满这个包
					memcpy(packet_->data, buf_packet->data, available_data);
					packet_read_pos_ += available_data;
					return false;
				}
				else {
					// 当前buffer里面的数据超过了这个包的需求
					memcpy(packet_->data, buf_packet->data, packet_->size);
					seek += sizeof(buf_size_t) + packet_->size;
					proc_msg_cb_(packet_);
				}
			}
			else {
				// 不足以有一个完整的buf_size_t，存储当前的数据
				packet_ = (PacketBuffer*)malloc(sizeof(buf_size_t));
				size_t available_data = len - seek;
				memcpy(&(packet_->size), base + seek, available_data);
				packet_read_pos_ = available_data;
				return false;
			}
		}
		else {
			// 已有packet_
			if (packet_read_pos_ < sizeof(buf_size_t)) {
				// 尝试构建大小字段
				size_t need = sizeof(buf_size_t) - packet_read_pos_;
				size_t can_read = (std::min)(need, len - seek);
				memcpy(((char*)&(packet_->size)) + packet_read_pos_, base + seek, can_read);
				packet_read_pos_ += can_read;
				seek += can_read;
			}
			else {
				// 尝试填充数据字段
				size_t need = packet_->size - (packet_read_pos_ - sizeof(buf_size_t));
				size_t can_read = (std::min)(need, len - seek);
				memcpy(packet_->data + (packet_read_pos_ - sizeof(buf_size_t)), base + seek, can_read);
				packet_read_pos_ += can_read;
				seek += can_read;

				if (packet_read_pos_ == sizeof(buf_size_t) + packet_->size) {
					proc_msg_cb_(packet_);
				}
			}
		}
	}
	return true;
}