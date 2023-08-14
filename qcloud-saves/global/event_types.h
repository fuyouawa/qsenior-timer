#pragma once
#include "global/config.h"
#include <QtEasyLib/QEasyEventSystem>

struct ResponsedEvent {
	RequestType request_type;
	QByteArray resp_val;
};