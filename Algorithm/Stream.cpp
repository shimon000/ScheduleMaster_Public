#include <iostream>
#include "Stream.h"
#include"ScheduleGenerator.h"


DLL_EXPORT void __stdcall GenerateFile(
	const char* fileName, int days_num, int timeunit_min,
	int startTime, int endTime,int year,int month,int day)
{
	Day firstDay(year, month, day);

	ScheduleGenerator generator(
		fileName, days_num, timeunit_min,
		startTime, endTime,firstDay);

	generator.WriteFile();

}