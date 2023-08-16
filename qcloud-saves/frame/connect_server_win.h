#pragma once

#include <QMainWindow>
#include <QJsonDocument>
#include "ui_connect_server_win.h"
#include "frame/mainwin.h"
#include "global/client_manager.h"
#include "global/event_types.h"

class ConnectServerWin : public QMainWindow, QEasyEventHandler<ResponsedEvent>, QEasyEventHandler<ConnectedToServerEvent>
{
	Q_OBJECT

public:
	ConnectServerWin(QWidget *parent = nullptr);
	~ConnectServerWin();

private:
	void OnEvent(const ResponsedEvent& event) override;
	void OnEvent(const ConnectedToServerEvent& event) override;

	Ui::ConnectServerWinClass ui;
};
