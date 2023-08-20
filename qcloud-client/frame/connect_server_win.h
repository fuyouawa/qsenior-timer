#pragma once

#include <QMainWindow>
#include <QJsonDocument>
#include "ui_connect_server_win.h"
#include "frame/mainwin.h"
#include "global/event_types.h"
#include "global/socket_manager.h"

class ConnectServerWin : public QMainWindow
{
	Q_OBJECT

public:
	ConnectServerWin(QWidget *parent = nullptr);
	~ConnectServerWin();

private:
	Ui::ConnectServerWinClass ui;
	SocketManager socket_;
};
