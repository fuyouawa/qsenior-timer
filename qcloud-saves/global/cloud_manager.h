#pragma once

#include <QObject>
#include <QMap>
#include "global/event_types.h"
#include "global/uvlooper.h"

class CloudManager  : public QObject
{
	Q_OBJECT

public:
	static CloudManager* const Instance;

	~CloudManager();

	void Request(RequestType type, const QByteArray& buf);

private slots:
	void OnNewMsgResponsed(const QByteArray& val);

private:
	CloudManager(QObject* parent = nullptr);
};
