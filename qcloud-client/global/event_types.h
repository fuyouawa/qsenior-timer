#pragma once
#include "global/config.h"
#include "local_common.h"
#include <qteasylib/event_system.h>

struct ResponsedEvent {
	RequestType type;
};

struct ConnectedToServerEvent{};

struct UvlibErrorEvent
{
	QString err_msg;
	QString err_name;
};

struct ConnectErrorEvent: public UvlibErrorEvent {};

struct LocalServerResponsedEvent
{
	QByteArray data;
};