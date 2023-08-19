#pragma once

inline const char* kLocalCommonName = "QLocal\\QSeniorTimer\\Common";

enum LocalRequestCode
{
	kGetTimersTemp
};

enum LocalResponseCode
{
	kSuccessGetTimersTemp,
	kFalidOpenTempFile
};