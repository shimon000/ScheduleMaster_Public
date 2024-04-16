#pragma once
#include "xlsxwriter.h"
#include "Day.h"
#include<iostream>
#include<string>

using namespace std;
class ScheduleGenerator
{
private:
	//�����\�̓���
	int _daysNum;
	//�����\�̎��ԒP��(��)
	int _timeUnit_min;
	//���̊J�n����
	int _startTime;
	//���̏I������
	int _endTime;
	//��������
	Day _beginDay;
	//�o�͂���G�N�Z���t�@�C���̖��O
	const char* _fileName;
	//�S�Ă̓�����Day���i�[����z��
	Day* allDaysArray = nullptr;
	//����̏c��cell��
	int rowsPerDay;
	//�����ŏI��
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
	//�������̓��t��ݒ肷��
	void SetDataInPeriod();
	//�T�̋L�q
	void WriteWeek(Cell targetCell,Day targetDay);
	//�r���̋L�q
	void WriteLine(Cell leftTop,Cell rightDown);
	//�j���Ɠ��t���L��
	void WriteWeekAndDay(Cell cell,Day targetDay);
	//���ԑт��L��
	void WriteTimeZone(Cell tmCell);
	//�w�肵���͈͂̃Z����h��Ԃ�
	void FillCells(Cell leftTop, Cell rightDown);
	
public:
	//�G�N�Z���t�@�C����`��
	int WriteFile();
};