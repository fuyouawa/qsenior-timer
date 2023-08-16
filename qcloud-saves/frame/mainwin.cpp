#include "mainwin.h"

MainWin::MainWin(QWidget* parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);

	auto registry_data = QDateTime::fromSecsSinceEpoch(UserInfo::RegistryStamp);
	ui.edit_registry_date->setDateTime(registry_data);
	ui.edit_user_name->setText(UserInfo::UserName);
	ui.edit_password->setText(UserInfo::Password);
}

MainWin::~MainWin()
{}

void MainWin::OnEvent(const ResponsedEvent & event)
{

}

void MainWin::OnEvent(const ConnectedToServerEvent& event)
{
}

void MainWin::on_btn_view_pwd_clicked(bool checked)
{
	ui.btn_view_pwd->setIcon(QIcon(checked ? ":/pictures/open_eyes.png" : ":/pictures/close_eyes.png"));
	ui.edit_password->setEchoMode(checked ? QLineEdit::Normal : QLineEdit::Password);
}