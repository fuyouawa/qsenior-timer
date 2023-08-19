#include "client_looper.h"

void ClientLooper::on_connect(uv_connect_t* req, int status)
{
	if (status < 0) {
        Deallocator(req);
        emit Instance->connectError(status);
        return;
	}
	uv_stream_t* stream = req->handle;
	uv_read_start(stream, alloc_buffer, on_read);
	Deallocator(req);
    Instance->is_connecting_ = true;
	emit Instance->connectedToServer();
}

void ClientLooper::on_write(uv_write_t* req, int status)
{
	if (status < 0) {
		emit Instance->writeError(status);
	}
	Deallocator(req);
}

void ClientLooper::alloc_buffer(uv_handle_t* handle, size_t suggested_size, uv_buf_t* buf)
{
	*buf = uv_buf_init(Allocator<char>(suggested_size), suggested_size);
}

void ClientLooper::on_close(uv_handle_t* handle)
{
	Deallocator(handle);
}

void ClientLooper::on_read(uv_stream_t* tcp, ssize_t nread, const uv_buf_t* buf)
{
	if (nread >= 0) {
        Instance->handler_.OnDataReceived(buf->base, nread);
	}
	else {
        emit Instance->readError(nread);
		uv_close((uv_handle_t*)tcp, on_close);
	}

	Deallocator(buf->base);
}

void ClientLooper::stop_async_cb(uv_async_t* handle)
{
    uv_stop(Instance->loop_);
    uv_walk(Instance->loop_, [](uv_handle_t* handle, void* arg) {
        if (!uv_is_closing(handle))
            uv_close(handle, on_close);
        }, NULL);
}

void ClientLooper::Deallocator(void* ptr)
{
	free(ptr);
}

ClientLooper::ClientLooper(QObject *parent)
	: QThread(parent),
	loop_(nullptr),
	client_(nullptr),
    handler_(),
    is_connecting_(false)
{}

ClientLooper::~ClientLooper()
{
}

void ClientLooper::run()
{
	loop_ = uv_default_loop();
	client_ = Allocator<uv_tcp_t>(1);
    stop_async_ = Allocator<uv_async_t>(1);
	uv_tcp_init(loop_, client_);

	sockaddr_in dest;
	uv_ip4_addr("127.0.0.1", kPort, &dest);
	uv_tcp_connect(Allocator<uv_connect_t>(1), client_, (const struct sockaddr*)&dest, on_connect);

    uv_async_init(loop_, stop_async_, stop_async_cb);

	uv_run(loop_, UV_RUN_DEFAULT);

	uv_loop_close(loop_);

    is_connecting_ = false;
    emit eventLoopStopped();
}

void ClientLooper::stop()
{
    ClearQueue();
    uv_async_send(stop_async_);
}

bool ClientLooper::Send(const QByteArray& buf)
{
	if (buf.size() >= kMaxBufSize) {
		return false;
	}
	auto packet_size = sizeof(PacketBuffer::size) + buf.size();
	auto buf_size = buf.size();

	auto packet = (PacketBuffer*)malloc(packet_size);
	if (packet)
	{
		packet->size = buf_size;
		memcpy(packet->data, buf.data(), buf_size);

		auto write_req = Allocator<uv_write_t>(1);
		auto uv_buf = uv_buf_init((char*)packet, packet_size);
		uv_write(write_req, (uv_stream_t*)client_, &uv_buf, 1, on_write);

		free(packet);
		return true;
	}
	return false;
}

QByteArray ClientLooper::Dequeue()
{
    auto packet = packets_queue_.dequeue();
    QByteArray tmp{ packet->data, packet->size };
    free(packet);
    return tmp;
}

void ClientLooper::ClearQueue()
{
    for (auto& pack : packets_queue_) {
        if (pack)
            free(pack);
    }
}

bool ClientLooper::TcpHandler::OnDataReceived(const char* base, buf_size_t len)
{
    size_t seek = 0;
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
                    ProcessMessage(packet_);
                    packet_ = nullptr;
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
                    ProcessMessage(packet_);
                    packet_ = nullptr;
                }
            }
        }
    }
    return true;
}

void ClientLooper::TcpHandler::ProcessMessage(PacketBuffer* packet)
{
    Instance->packets_queue_.enqueue(packet);
    emit ClientLooper::Instance->newMsgReceived(packet);
}