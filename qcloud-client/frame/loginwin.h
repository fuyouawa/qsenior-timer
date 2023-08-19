#pragma once

#include <QMainWindow>
#include "ui_loginwin.h"
#include "global/client_manager.h"
#include "global/event_types.h"
#include "global/utils.h"

class LoginWin : public QMainWindow,
	qteasylib::EventHandler<ResponsedEvent>,
	qteasylib::EventHandler<ConnectedToServerEvent>,
	qteasylib::EventHandler<ConnectErrorEvent>
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
	void OnEvent(const ConnectErrorEvent& event) override;

	bool CheckInput(QString user_name, QString password);
	void AutoRequest();
	void RequestSigninOrLogin(bool is_signin);
	void EnableButtons(bool enable);

	Ui::LoginWinClass ui;

	bool is_signin_;
};
