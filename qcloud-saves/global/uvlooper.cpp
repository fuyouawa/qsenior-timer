#include "uvlooper.h"

UvLooper* const UvLooper::Instance = new UvLooper();


void UvLooper::on_connect(uv_connect_t* req, int status)
{
	if (status < 0) {
		QMessageBox::critical(nullptr, "严重异常", QString("服务器连接失败! \n原因: ") + uv_strerror(status));
		QApplication::exit(-1);
	}
	uv_stream_t* stream = req->handle;
	uv_read_start(stream, alloc_buffer, on_read);
	FREE(req);
}

void UvLooper::on_write(uv_write_t* req, int status)
{
	if (status < 0) {
		emit Instance->writeError(status);
	}
	FREE(req);
}

void UvLooper::alloc_buffer(uv_handle_t* handle, size_t suggested_size, uv_buf_t* buf)
{
	*buf = uv_buf_init(MALLOC_OBJS(char, suggested_size), suggested_size);
}

void UvLooper::on_close(uv_handle_t* handle)
{
	FREE(handle);
}

void UvLooper::on_read(uv_stream_t* tcp, ssize_t nread, const uv_buf_t* buf)
{
	if (nread >= 0) {
		emit Instance->newMsgResponsed(QByteArray(buf->base, buf->len));
	}
	else {
		uv_close((uv_handle_t*)tcp, NULL);
	}

	FREE(buf->base);
}

UvLooper::UvLooper(QObject *parent)
	: QThread(parent),
	loop_(nullptr),
	client_(nullptr)
{}

UvLooper::~UvLooper()
{}

void UvLooper::run()
{
	loop_ = uv_default_loop();
	client_ = MALLOC_OBJ(uv_tcp_t);
	uv_tcp_init(loop_, client_);

	sockaddr_in dest;
	uv_ip4_addr("127.0.0.1", kPort, &dest);
	uv_tcp_connect(MALLOC_OBJ(uv_connect_t), client_, (const struct sockaddr*)&dest, on_connect);

	uv_run(loop_, UV_RUN_DEFAULT);

	uv_loop_close(loop_);
}

void UvLooper::stop()
{
	uv_stop(loop_);
}

void UvLooper::Send(const QByteArray& buf)
{
	auto write_req = MALLOC_OBJ(uv_write_t);
	auto uv_buf = uv_buf_init((char*)buf.data(), buf.size());
	uv_write(write_req, (uv_stream_t*)client_, &uv_buf, 1, on_write);
}
