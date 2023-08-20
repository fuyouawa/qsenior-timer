#pragma once

#include <QMainWindow>
#include <QMessageBox>
#include "ui_loginwin.h"
#include "global/event_types.h"
#include "global/utils.h"
#include "global/socket_manager.h"

class LoginWin : public QMainWindow
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
	bool CheckInput(QString user_name, QString password);
	void AutoRequest();
	void RequestSigninOrLogin(bool is_signin);
	void EnableButtons(bool enable);

	Ui::LoginWinClass ui;
	SocketManager socket_;
	bool is_signin_;
};
