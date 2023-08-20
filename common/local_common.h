#pragma once

inline const char* kLocalCommonName = "QLocal\\QSeniorTimer\\Common";

enum LocalRequestCode
{
	kGetTimersTemp,
	kAssignTimersTemp
};

enum LocalResponseCode
{
	kSuccessGetTimersTemp,
	kFalidOpenTempFile,
	kSuccessAssignTimersTemp,
	kDataBroken,
};