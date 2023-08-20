#pragma once

#include <QTcpSocket>
#include <QObject>
#include <QThread>
#include <QQueue>
#include "global/utils.h"

class SocketManager  : public QObject
{
	Q_OBJECT

public:
	inline static const char* kServerHost = "127.0.0.1";
	inline static constexpr int kPort = 8888;
	SocketManager(QObject *parent=nullptr);
	~SocketManager();

	void SetConnectedCb(const QObject* context, const std::function<void()>& cb);
	void SetReceivedDataCb(const QObject* context, const std::function<void(RequestType)>& cb);
	void SetErrorOccuredCb(const QObject* context, const std::function<void(QTcpSocket::SocketError)>& cb);
	void SetBytesWrittenCb(const QObject* context, const std::function<void(qint64)>& cb);
	void ConnectToServer();
	void DisConnectServer();
	Packet DequeuePacket();

	QString ErrStr();

	bool IsConnected();

	void Request(const QString& user_name, const QString& password, const Packet& packet);
	void AutoRequest(const Packet& packet);

signals:
	void receivedData(RequestType type);

private slots:
	void OnReadyRead();

private:
	class TcpHandler
	{
	public:
		~TcpHandler() = default;
		TcpHandler() = default;

		bool OnDataReceived(const QByteArray& bytes);

		buf_size_t packet_read_pos_;
		PacketBuffer* packet_;
		std::function<void(PacketBuffer*&)> proc_msg_cb_;
	};
	QByteArray ConstructPacket(const QString& user_name, const QString& password, const Packet& packet);

	QMetaObject::Connection bytes_written_connection_;
	QMetaObject::Connection connected_connection_;
	QMetaObject::Connection error_occured_connection_;
	QMetaObject::Connection received_data_connection_;
	QTcpSocket socket_;
	TcpHandler handler_;
	QQueue<Packet> packets_queue_;
};
