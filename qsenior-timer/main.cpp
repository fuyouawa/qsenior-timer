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

#ifndef _DEBUG
	if (!IsRunAsAdmin()) {
		AskForAdmin();
		return 0;
	}
#endif // !_DEBUG


    InitBasicConfig();
    ReadSettings();
    if (BasicConfig::IsFirstRunApp) {
        AutoRegistryStartup();
    }
	TimerDb::Instance->Open();
	int res = 0;
	{
		MainWin w;
		w.show();
		res = a.exec();
	}
	TimerDb::Instance->Close();
	return res;
}
