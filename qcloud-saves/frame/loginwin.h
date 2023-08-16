#pragma once

#include <QMainWindow>
#include "ui_loginwin.h"
#include "global/client_manager.h"
#include "global/event_types.h"
#include "global/utils.h"

class LoginWin : public QMainWindow, QEasyEventHandler<ResponsedEvent>, QEasyEventHandler<ConnectedToServerEvent>
{
	Q_OBJECT

public:
	LoginWin(QWidget *parent = nullptr);
	~LoginWin();

private slots:
	void on_btn_signin_clicked();
	void on_btn_login_clicked();
	void on_btn_view_pwd_clicked(bool checked);

private:
	void OnEvent(const ResponsedEvent& event) override;
	void OnEvent(const ConnectedToServerEvent& event) override;

	bool CheckInput(QString user_name, QString password);

	Ui::LoginWinClass ui;

	bool is_signin_;
};
