#pragma once
#include "xlsxwriter.h"
#include "Day.h"
#include<iostream>
#include<string>

using namespace std;
class ScheduleGenerator
{
private:
	//日程表の日数
	int _daysNum;
	//日程表の時間単位(分)
	int _timeUnit_min;
	//日の開始時間
	int _startTime;
	//日の終了時間
	int _endTime;
	//日程初日
	Day _beginDay;
	//出力するエクセルファイルの名前
	const char* _fileName;
	//全ての日程のDayを格納する配列
	Day* allDaysArray = nullptr;
	//一日の縦のcell数
	int rowsPerDay;
	//実験最終日
	Day lastDay;

	lxw_workbook* workbook;
	lxw_worksheet* worksheet;
	lxw_format* border_format;
	lxw_format* normal_format;

	struct Cell
	{
		int x_pos;
		int y_pos;
	};

public:
	ScheduleGenerator (const char* fileName, int days_num, int timeunit_min,int startTime,int endTime, Day firstDay);
private:
	//日程中の日付を設定する
	void SetDataInPeriod();
	//週の記述
	void WriteWeek(Cell targetCell,Day targetDay);
	//罫線の記述
	void WriteLine(Cell leftTop,Cell rightDown);
	//曜日と日付を記入
	void WriteWeekAndDay(Cell cell,Day targetDay);
	//時間帯を記入
	void WriteTimeZone(Cell tmCell);
	//指定した範囲のセルを塗りつぶす
	void FillCells(Cell leftTop, Cell rightDown);
	
public:
	//エクセルファイルを描画
	int WriteFile();
};