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

	//���̍ŏI���ƌ��̃y�A
	MonthLastDayPair pairs[12];

private:
	//���̍ŏI���ƌ��̃y�A������������
	void SetMonthLastDayPair();
	//���邤�N�̒���������
	void OffsetDayOfUruYear();
	//�j�����v�Z����
	void CalcWeekday();

public:
	Day();
	Day(int year,int month,int day);

	//���t
	int Date();
	//��
	int Month();
	//�N
	int Year();
	//�j��
	WeekDay Weekday();
	//���t�ƌ���"n/n"�Ƃ����`�ŕԂ�
	string GetDayString();
	//�j����"N�j��"�Ƃ����`�ŕԂ�
	const char* GetWeekDayChar();

	//�I�y���[�^�[
	Day operator++(int x);
	Day operator--(int x);
	//���E�Ώ̐����m�ۂ��邽�߃O���\�o�����Z�q�ɂ���
	//private�ϐ����g������friend�֐��ɂ���
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