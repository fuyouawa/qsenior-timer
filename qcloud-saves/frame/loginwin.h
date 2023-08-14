#pragma once

#include <QMainWindow>
#include "ui_loginwin.h"
#include "frame/mainwin.h"
#include "global/cloud_manager.h"
#include "global/event_types.h"

class LoginWin : public QMainWindow, QEasyEventHandler<ResponsedEvent>
{
	Q_OBJECT

public:
	LoginWin(QWidget *parent = nullptr);
	~LoginWin();

private slots:
	void on_btn_signin_clicked();

private:
	void OnEvent(const ResponsedEvent& event) override;


	bool CheckInput(QString user_name, QString password);

	Ui::LoginWinClass ui;
};
