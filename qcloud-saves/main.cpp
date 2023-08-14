#include "frame/loginwin.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    InitBasicConfig();
    ReadUserInfo();

    UvLooper::Instance->start();

    LoginWin* win = nullptr;
    if (UserInfo::UserName.isEmpty()) {
        win = new LoginWin();
        win->show();
    }
    else {

    }

    auto res = a.exec();
    UvLooper::Instance->stop();
    return res;
}
