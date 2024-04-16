//éQçl https ://nprogram.hatenablog.com/entry/2018/05/16/213033

#pragma once

#ifdef __cplusplus
#define DLL_EXPORT extern "C" __declspec(dllexport)
#else
#define DLL_EXPORT __declspec(dllexport)
#endif

DLL_EXPORT void __stdcall GenerateFile(const char* fileName, int days_num, int timeunit_min,
	int startTime, int endTime,int year, int month, int day);