#pragma once
#include "global/config.h"
#include <qteasylib/event_system.h>

struct ResponsedEvent {
	RequestType type;
};

struct ConnectedToServerEvent{};

struct UvlibError
{
	QString err_msg;
	QString err_name;
};

struct ConnectError: public UvlibError {};