#pragma once

#include <QObject>
#include <QLocalSocket>
#include "event_types.h"
#include "local_common.h"

class LocalClient  : public QObject
{
	Q_OBJECT

public:
	static LocalClient* const Instance;

	LocalClient(QObject *parent=nullptr);
	~LocalClient();

	void Request(LocalRequestCode code);

private:
	QLocalSocket socket_;
};
