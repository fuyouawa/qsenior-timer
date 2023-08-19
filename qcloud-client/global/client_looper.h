#pragma once

#include <QMessageBox>
#include <QThread>
#include <QApplication>
#include <libuv/uv.h>
#include <QQueue>
#include "global/config.h"

class ClientManager;

class ClientLooper  : public QThread
{
	Q_OBJECT

public:
	inline static ClientLooper* Instance = nullptr;
	inline static constexpr int kPort = 8888;

	~ClientLooper();

	void run() override;
	void stop();

signals:
	void writeError(int status);
	void readError(int status);
	void connectError(int status);
	void connectedToServer();
	void newMsgReceived(PacketBuffer* packet);
	void eventLoopStopped();

private:
	class TcpHandler
	{
	public:
		~TcpHandler() = default;
		TcpHandler() = default;

		bool OnDataReceived(const char* base, buf_size_t len);

		void ProcessMessage(PacketBuffer* packet);

		buf_size_t packet_read_pos_;
		PacketBuffer* packet_;
	};
	friend class ClientManager;

	static void on_connect(uv_connect_t* req, int status);
	static void on_write(uv_write_t* req, int status);
	static void alloc_buffer(uv_handle_t* handle, size_t suggested_size, uv_buf_t* buf);
	static void on_close(uv_handle_t* handle);
	static void on_read(uv_stream_t* tcp, ssize_t nread, const uv_buf_t* buf);
	static void stop_async_cb(uv_async_t* handle);

	template<class T>
	static T* Allocator(size_t count) {
		auto ptr= (T*)malloc(sizeof(T) * count);
		memset(ptr, 0, sizeof(T) * count);
		return ptr;
	}
	static void Deallocator(void* ptr);

	ClientLooper(QObject *parent=nullptr);

	Q_INVOKABLE bool Send(const QByteArray& buf);
	QByteArray Dequeue();

	void ClearQueue();

	uv_loop_t* loop_;
	uv_tcp_t* client_;
	uv_async_t* stop_async_;
	QQueue<PacketBuffer*> packets_queue_;
	TcpHandler handler_;

	bool is_connecting_;
};