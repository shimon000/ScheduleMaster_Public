#pragma once
#include <string>
#include <iostream>
#include<vector>
using namespace std;

enum WeekDay;

class Day
{
private:
	int _year;
	int _month;
	int _day;
	WeekDay _weekday;

	struct MonthLastDayPair
	{
		int month;
		int lastDay;
	};

	//月の最終日と月のペア
	MonthLastDayPair pairs[12];

private:
	//月の最終日と月のペアを初期化する
	void SetMonthLastDayPair();
	//うるう年の調整をする
	void OffsetDayOfUruYear();
	//曜日を計算する
	void CalcWeekday();

public:
	Day();
	Day(int year,int month,int day);

	//日付
	int Date();
	//月
	int Month();
	//年
	int Year();
	//曜日
	WeekDay Weekday();
	//日付と月を"n/n"という形で返す
	string GetDayString();
	//曜日を"N曜日"という形で返す
	const char* GetWeekDayChar();

	//オペレーター
	Day operator++(int x);
	Day operator--(int x);
	//左右対称性を確保するためグロ―バル演算子にする
	//private変数を使うためfriend関数にする
	friend bool operator< (const Day& left,const Day& right);
	friend bool operator> (const Day& left, const Day& right);
	friend bool operator<=(const Day& left, const Day& right);
	friend bool operator>=(const Day& left, const Day& right);
	friend bool operator==(const Day& left, const Day& right);
	friend bool operator!=(const Day& left, const Day& right);
};

enum WeekDay
{
	Sunday = 0,
	Monday = 1,
	Tuesday = 2,
	Wednesday = 3,
	Thursday = 4,
	Friday = 5,
	Saturday = 6
};