#include "frame/loginwin.h"
#include "frame/connect_server_win.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    InitBasicConfig();
    ReadUserInfo();
    LoginWin* login_win = nullptr;
    ConnectServerWin* connect_server_win = nullptr;
    if (UserInfo::UserName.isEmpty()) {
        login_win = new LoginWin();
        login_win->show();
    }
    else {
        connect_server_win = new ConnectServerWin();
        connect_server_win->show();
    }
    auto res = a.exec();
    return res;
}
