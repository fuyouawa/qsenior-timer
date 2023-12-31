﻿#include "loginwin.h"

LoginWin::LoginWin(QWidget* parent)
	: QMainWindow(parent),
	is_signin_(false),
	socket_(parent)
{
	ui.setupUi(this);
	socket_.SetConnectedCb(this, [this]() {
		RequestSigninOrLogin(is_signin_);
		});

	socket_.SetErrorOccuredCb(this, [this](QTcpSocket::SocketError err) {
		QMessageBox::critical(this, "严重错误", "服务器连接失败!\n错误信息:" + socket_.ErrStr());
		});

	socket_.SetReceivedDataCb(this, [this](RequestType type) {
		switch (type)
		{
		case kSignin:
		{
			auto packet = socket_.DequeuePacket();
			switch (packet.data.at(0))
			{
			case kSuccess:
				socket_.DisConnectServer();
				QMessageBox::information(this, "提示", "登录成功!");
				UserInfo::UserName = ui.edit_user_name->text();
				UserInfo::Password = ui.edit_password->text();
				SaveUserInfo();
				RestartApp();
				break;
			default:
				QMessageBox::information(this, "提示", "账号或者密码错误!");
				break;
			}
			break;
		}
		case kLogin:
		{
			auto packet = socket_.DequeuePacket();
			switch (packet.data.at(0))
			{
			case kSuccess:
				QMessageBox::information(this, "提示", "注册成功, 现在您可以登录了!");
				ui.edit_user_name->setText("");
				ui.edit_password->setText("");
				break;
			case kUserNameRepeat:
				QMessageBox::information(this, "提示", "已有相同的用户名!");
				break;
			}
			break;
		}
		default:
			break;
		}
		EnableButtons(true);
		});

	socket_.ConnectToServer();
}

LoginWin::~LoginWin()
{}

void LoginWin::on_btn_login_clicked()
{
	if (QMessageBox::question(this, "警告", "密码一旦创建无法更改!(至少目前没有更改的功能)\n请确保您设定的密码能够记住!") == QMessageBox::Yes) {
		is_signin_ = false;
		AutoRequest();
	}
}

void LoginWin::on_btn_view_pwd_clicked(bool checked)
{
	ui.btn_view_pwd->setIcon(QIcon(checked ? ":/pictures/open_eyes.png" : ":/pictures/close_eyes.png"));
	ui.edit_password->setEchoMode(checked ? QLineEdit::Normal : QLineEdit::Password);
}

bool LoginWin::CheckInput(QString user_name, QString password)
{
	if (user_name.isEmpty() || password.isEmpty()) {
		QMessageBox::warning(this, "警告", "您还有项没填写!");
		return false;
	}
	if (user_name.count() > 8 || password.count() > 26 || user_name.count() < 4 || password.count() < 8) {
		QMessageBox::warning(this, "警告", "账号的长度必须在4-8个字符之间!\n密码的长度必须在8-26个字符之间!");
		return false;
	}
	return true;
}

void LoginWin::AutoRequest()
{
	if (!socket_.IsConnected())
		socket_.ConnectToServer();
	else
		RequestSigninOrLogin(is_signin_);
}

void LoginWin::RequestSigninOrLogin(bool is_signin)
{
	auto user_name = ui.edit_user_name->text();
	auto password = ui.edit_password->text();
	if (!CheckInput(user_name, password)) return;
	EnableButtons(false);
	if (is_signin_) {
		socket_.Request(user_name, password, { kSignin, QByteArray() });
	}
	else {
		socket_.Request(user_name, password, { kLogin, CombineQStrs({user_name, password}) });
	}
}

void LoginWin::EnableButtons(bool enable)
{
	ui.btn_login->setEnabled(enable);
	ui.btn_signin->setEnabled(enable);
}

void LoginWin::on_btn_signin_clicked()
{
	is_signin_ = true;
	AutoRequest();
}