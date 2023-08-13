#include "frame/mainwin.h"
#include <QtWidgets/QApplication>
#include <QSystemSemaphore>
#include <QSharedMemory>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

	QSystemSemaphore semaphore{ "QSystemSemaphore\\QSeniorTimer\\SingleApp", 1 };
	semaphore.acquire();

	QSharedMemory shared_memory("QSharedMemory\\QSeniorTimer\\SingleApp");
	bool is_running = false;
	if (shared_memory.attach()) {
		is_running = true;
	}
	else {
		shared_memory.create(1);
		is_running = false;
	}

	semaphore.release();

	if (is_running) {
		QMessageBox::warning(nullptr, "警告", "当前已有一个实例正在运行, 禁止多开, 会引发冲突!");
		return -1;
	}

	if (!IsRunAsAdmin()) {
		if (!AskForAdmin())
			QMessageBox::warning(nullptr, "警告", "如果您不给予管理员权限, 某些功能可能无法正常使用!");
		else
			return 0;
	}

    InitBasicConfig();
    ReadSettings();
    if (BasicConfig::IsFirstRunApp) {
        AutoRegistryStartup();
    }
    MainWin w;
    w.show();
    return a.exec();
}
