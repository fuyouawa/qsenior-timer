#include "loginwin.h"

LoginWin::LoginWin(QWidget *parent)
	: QMainWindow(parent),
	is_signin_(false)
{
	ui.setupUi(this);
}

LoginWin::~LoginWin()
{}

void LoginWin::on_btn_login_clicked()
{
	if (!CheckInput(ui.edit_user_name->text(), ui.edit_password->text())) return;
	if (QMessageBox::question(this, "警告", "密码一旦创建无法更改!(至少目前没有更改的功能)\n请确保您设定的密码能够记住!") == QMessageBox::Yes) {
		is_signin_ = false;
		ClientManager::Instance->ConnectServer();
	}
}

void LoginWin::on_btn_view_pwd_clicked(bool checked)
{
	ui.btn_view_pwd->setIcon(QIcon(checked ? ":/pictures/open_eyes.png" : ":/pictures/close_eyes.png"));
	ui.edit_password->setEchoMode(checked ? QLineEdit::Normal : QLineEdit::Password);
}

void LoginWin::OnEvent(const ResponsedEvent& event)
{
	switch (event.type)
	{
	case kSignin:
	{
		auto packet = ClientManager::Instance->DequeuePacket();
		ClientManager::Instance->DisConnectServer();
		switch (packet.data.at(0))
		{
		case kSuccess:
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
		auto packet = ClientManager::Instance->DequeuePacket();
		ClientManager::Instance->DisConnectServer();
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
}

void LoginWin::OnEvent(const ConnectedToServerEvent& event)
{
	auto data = CombineQStrs({ ui.edit_user_name->text(), ui.edit_password->text() });
	ClientManager::Instance->Request({ is_signin_ ? kSignin : kLogin,  data });
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

void LoginWin::on_btn_signin_clicked()
{
	if (!CheckInput(ui.edit_user_name->text(), ui.edit_password->text())) return;
	is_signin_ = true;
	ClientManager::Instance->ConnectServer();
}