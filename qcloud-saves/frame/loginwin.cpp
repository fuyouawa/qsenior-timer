#include "loginwin.h"

LoginWin::LoginWin(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
}

LoginWin::~LoginWin()
{}

void LoginWin::OnEvent(const ResponsedEvent& event)
{
	switch (event.request_type)
	{
	case kSignin:
		switch (*event.resp_val.data())
		{
		case kSuccess:
			QMessageBox::information(this, "提示", "登录成功!");
			break;
		default:
			break;
		}
		break;
	default:
		break;
	}
}

bool LoginWin::CheckInput(QString user_name, QString password)
{
	if (user_name.isEmpty() || password.isEmpty()) {
		QMessageBox::warning(this, "警告", "您还有项没填写!");
		return false;
	}
	if (user_name.count() > 8 || password.count() > 16) {
		QMessageBox::warning(this, "警告", "账号的长度不能超过8个字符, 密码的长度不能超过16个字符!");
		return false;
	}
}

void LoginWin::on_btn_signin_clicked()
{
	auto user_name = ui.edit_user_name->text();
	auto password = ui.edit_password->text();
	if (!CheckInput(user_name, password)) return;
	CloudManager::Instance->Request(kSignin, CombineQStrs({ user_name, password }));
}