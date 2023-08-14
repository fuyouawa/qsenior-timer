#pragma once

#include <QMessageBox>
#include <QThread>
#include <QApplication>
#include <libuv/uv.h>
#include "global/config.h"

#define MALLOC_OBJ(type) (type*)malloc(sizeof(type))
#define MALLOC_OBJS(type, count) (type*)malloc(sizeof(type) * count)
#define FREE(ptr) free(ptr)

class UvLooper  : public QThread
{
	Q_OBJECT

public:
	static UvLooper* const Instance;
	inline static constexpr int kPort = 8888;

	~UvLooper();

	void run() override;
	void stop();

	void Send(const QByteArray& buf);

signals:
	void writeError(int status);
	void newMsgResponsed(const QByteArray& val);

private:
	static void on_connect(uv_connect_t* req, int status);
	static void on_write(uv_write_t* req, int status);
	static void alloc_buffer(uv_handle_t* handle, size_t suggested_size, uv_buf_t* buf);
	static void on_close(uv_handle_t* handle);
	static void on_read(uv_stream_t* tcp, ssize_t nread, const uv_buf_t* buf);

	UvLooper(QObject *parent=nullptr);

	uv_loop_t* loop_;
	uv_tcp_t* client_;
};