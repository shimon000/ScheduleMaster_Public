#include "ScheduleGenerator.h"

ScheduleGenerator::ScheduleGenerator(
	const char* fileName, int days_num, int timeUnit_min, int startTime, int endTime,
	Day firstDay)
{
	this->_fileName = fileName;
	this->_daysNum = days_num;
	this->_timeUnit_min = timeUnit_min;
	this->_startTime = startTime;
	this->_endTime = endTime;
	this->_beginDay = firstDay;

	//�z��̃������𓮓I�m��
	allDaysArray = new Day[days_num];
	SetDataInPeriod();

	//�c��cell��
	rowsPerDay = (_endTime - _startTime) * 60 / _timeUnit_min;

	//�ŏI���̏�����
	Day tmp = _beginDay;
	for (int i = 1; i < days_num; i++)
		tmp++;
	lastDay = tmp;
}

void ScheduleGenerator::SetDataInPeriod()
{
	Day tmp;
	tmp = _beginDay;
	for (int i = 0; i < _daysNum; i++)
	{
		allDaysArray[i] = tmp;
		tmp++;
	}
}



int ScheduleGenerator::WriteFile()
{
	
	workbook = workbook_new(_fileName);
	worksheet = workbook_add_worksheet(workbook, NULL);

	// �r���̐ݒ�
	border_format = workbook_add_format(workbook);
	format_set_border(border_format, LXW_BORDER_THIN); 
	//������
	format_set_align(border_format, LXW_ALIGN_CENTER);
	//�t�H���g�̐ݒ�
	format_set_font_name(border_format, u8"���C���I");

	
	normal_format = workbook_add_format(workbook);
	format_set_font_name(normal_format, u8"���C���I");

	
	//�����L�����̍쐬
	worksheet_write_string(worksheet, 1, 1, u8"���O", border_format);
	worksheet_write_string(worksheet, 1, 2, u8"�i�������L���j", border_format);
	worksheet_write_string(worksheet, 1, 4, u8"�����ɎQ���ł��Ȃ�����h��Ԃ��Ă�������", normal_format);
	
	//�T�̐����J�E���g
	int weekNum = 0;
	Day tmpDayForCount = _beginDay;
	cout << lastDay.GetDayString() << endl;
	cout << lastDay.GetWeekDayChar() << endl;
	while (tmpDayForCount < lastDay || tmpDayForCount == lastDay)
	{
		if (tmpDayForCount.Weekday() == Sunday)
		{
			weekNum++;
			cout << tmpDayForCount.GetWeekDayChar() << tmpDayForCount.GetDayString() << endl;
		}
			
		tmpDayForCount++;
	}

	if (lastDay.Weekday() != Sunday)
		weekNum++;

	//�T���ƂɃt�@�C���ɏ�������
	Cell mondayCell = {3,3};
	int cellNum = (_endTime - _startTime) * 60 / _timeUnit_min;
	Day tmpDayForWrite = _beginDay;

	for (int i = 0; i < weekNum; i++)
	{
		WriteWeek(mondayCell,tmpDayForWrite);

		mondayCell.y_pos += cellNum + 5;
		for (int i = 0; i < 7; i++)
			tmpDayForWrite++;
	}
	
	return workbook_close(workbook);
}

void ScheduleGenerator::WriteWeek(Cell mondayCell,Day targetDay)
{
	Cell timeZoneBeginCell = { mondayCell.x_pos - 1,mondayCell.y_pos + 2 };
	Cell leftTopCell = { mondayCell.x_pos,mondayCell.y_pos+1};
	Cell rightDownCell = { mondayCell.x_pos + 6,mondayCell.y_pos + rowsPerDay+1};

	//�r�����L�q
	WriteLine(leftTopCell, rightDownCell);

	//���t�Ɨj���̕������L��
	WriteWeekAndDay(mondayCell,targetDay);
	
	//���ԑт��L��
	WriteTimeZone(timeZoneBeginCell);

}

void ScheduleGenerator::WriteLine(Cell leftTop,Cell rightDown)
{
	
	for (int x = leftTop.x_pos; x < rightDown.x_pos+1; x++)
	{
		for (int y = leftTop.y_pos; y < rightDown.y_pos+1; y++)
		{
			worksheet_write_string(worksheet, y, x, "", border_format);
		}
	}
}

void ScheduleGenerator::WriteWeekAndDay(Cell cell,Day targetDay)
{
	int dayOffset = 0;
	Cell beginCell = cell;
	worksheet_write_string(worksheet, cell.y_pos,cell.x_pos, u8"���j��", border_format);
	cell.x_pos++;
	worksheet_write_string(worksheet, cell.y_pos, cell.x_pos, u8"�Ηj��", border_format);
	cell.x_pos++;
	worksheet_write_string(worksheet, cell.y_pos, cell.x_pos, u8"���j��", border_format);
	cell.x_pos++;
	worksheet_write_string(worksheet, cell.y_pos, cell.x_pos, u8"�ؗj��", border_format);
	cell.x_pos++;						  			 
	worksheet_write_string(worksheet, cell.y_pos, cell.x_pos, u8"���j��", border_format);
	cell.x_pos++;						  			 
	worksheet_write_string(worksheet, cell.y_pos, cell.x_pos, u8"�y�j��", border_format);
	cell.x_pos++;						  			 
	worksheet_write_string(worksheet, cell.y_pos, cell.x_pos, u8"���j��", border_format);
	
	Day tmp = targetDay;
	cell = beginCell;
	while (tmp.Weekday() != Monday)
	{
		
		cell.x_pos++;
		tmp--;
	}
	cell = beginCell;
	cell.y_pos++;
	for (int i = 0; i < 7; i++)
	{
		worksheet_write_string(worksheet, cell.y_pos, cell.x_pos++, tmp.GetDayString().c_str(), border_format);
		tmp++;
	}

	
}

void ScheduleGenerator::WriteTimeZone(Cell tmCell)
{
	int cellNum = (_endTime - _startTime) * 60 / _timeUnit_min ;
	
	int min = 0;
	int hour = _startTime;
	string hour_string;
	string min_string;

	for (int i = 0; i < cellNum; i++)
	{
		hour_string = to_string(hour);
		min_string = to_string(min);

		string time_string = hour_string + " : " + min_string + " ~";
		worksheet_write_string(worksheet, tmCell.y_pos+i, tmCell.x_pos, time_string.c_str(), border_format);

		min = min + _timeUnit_min;

		if (min >= 60)
		{
			min = 0;
			hour++;
		}
	}
}

void ScheduleGenerator::FillCells(Cell leftTop, Cell rightDown)
{
	lxw_format* fill_format = workbook_add_format(workbook);
	format_set_bg_color(fill_format, 0x000000);

	for (int x = leftTop.x_pos; x < rightDown.x_pos + 1; x++)
	{
		for (int y = leftTop.y_pos; y < rightDown.y_pos + 1; y++)
		{
			worksheet_write_string(worksheet, y, x, "", fill_format);
		}
	}
}