#pragma once
#include <QLocalServer>
#include <QLocalSocket>
#include <QObject>
#include "global/utils.h"
#include "tools/timerdb.h"
#include "local_common.h"
#include "global/event_types.h"

class LocalServer  : public QObject
{
	Q_OBJECT

public:
	static LocalServer* const Instance;

	LocalServer(QObject *parent=nullptr);
	~LocalServer();

private slots:
	void OnLocalClientRequest();

private:
	QLocalServer server_;
	QLocalSocket* client_socket_;
};
