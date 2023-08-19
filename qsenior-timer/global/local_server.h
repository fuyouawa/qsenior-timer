#pragma once
#include <QLocalServer>
#include <QLocalSocket>
#include <QTemporaryFile>
#include <QObject>
#include "global/utils.h"
#include "tools/timerdb.h"
#include "local_common.h"

class LocalServer  : public QObject
{
	Q_OBJECT

public:
	static LocalServer* const Instance;

	LocalServer(QObject *parent=nullptr);
	~LocalServer();

	QString TempFilePath();

private slots:
	void OnLocalClientRequest();

private:
	QTemporaryFile temp_file_;
	QLocalServer server_;
	QLocalSocket* client_socket_;
};
