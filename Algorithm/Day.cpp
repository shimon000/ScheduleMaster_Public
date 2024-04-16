#include "Day.h"

//デフォルトコンストラクタ2024年1月1日として設定
Day::Day()
{
	this->_year = 2024;
	this->_month = 1;
	this->_day = 1;
    this->_weekday = Monday;
    SetMonthLastDayPair();
    OffsetDayOfUruYear();
}

Day::Day(int year, int month, int day)
{
    bool isCorrect = true;

    this->_year = year;
    this->_month = month;
    this->_day = day;
    
    SetMonthLastDayPair();
    OffsetDayOfUruYear();
    
    if (year < 1)
        isCorrect = false;
    if (month < 1 || month > 12)
        isCorrect = false;
    if (day < 1 || day > pairs[month - 1].lastDay)
        isCorrect = false;

    if (!isCorrect)
        cout << "日付が異常値です" << endl;

    CalcWeekday();
}

int  Day::Date(){ return _day; }
int Day::Month() { return _month; }
int Day::Year() { return _year; }
WeekDay Day::Weekday() { return _weekday; }

void Day::CalcWeekday()
{
    //2024年1月1日を基準日とする
    Day tmp;
    
    bool isThisSmaller = *this < tmp;

    //基準日から差の日分操作する
    while (tmp != *this)
    {
        if (isThisSmaller)
        {
            tmp--;
        }
        else
        {
            tmp++;
        }
    }

    this->_weekday = tmp.Weekday();
}

void Day::SetMonthLastDayPair()
{
    pairs[0].month = 1;
    pairs[0].lastDay = 31;

    pairs[1].month = 2;
    pairs[1].lastDay = 28; 

    pairs[2].month = 3;
    pairs[2].lastDay = 31;

    pairs[3].month = 4;
    pairs[3].lastDay = 30;

    pairs[4].month = 5;
    pairs[4].lastDay = 31;

    pairs[5].month = 6;
    pairs[5].lastDay = 30;

    pairs[6].month = 7;
    pairs[6].lastDay = 31;

    pairs[7].month = 8;
    pairs[7].lastDay = 31;

    pairs[8].month = 9;
    pairs[8].lastDay = 30;

    pairs[9].month = 10;
    pairs[9].lastDay = 31;

    pairs[10].month = 11;
    pairs[10].lastDay = 30;

    pairs[11].month = 12;
    pairs[11].lastDay = 31;
}

void Day::OffsetDayOfUruYear()
{
    if (this->_year % 4 == 0)
    {
        if (this->_year % 100 == 0 && this->_year % 400 != 0)
            return;

        pairs[1].lastDay = 29;
    }
    else
    {
        pairs[1].lastDay = 28;
    }
}

string Day::GetDayString()
{
    string day_str = to_string(this->_day);
    string month_str = to_string(this->_month);

    string result = month_str + "/" + day_str;

    return result;
}

const char* Day::GetWeekDayChar()
{
    const char* week_str[] = {"日曜日", "月曜日", "火曜日", "水曜日", "木曜日", "金曜日", "土曜日"};
 
    //weekDayを対応するint型にキャスト
    int week_int = static_cast<int>(_weekday);

    return week_str[week_int];
}

Day Day::operator++(int x)
{
    //日付更新
    _day++;
    if (_day > pairs[_month-1].lastDay)
    {
        _month++;
        _day = 1;
        if (_month > 12)
        {
            _year++;
            _month = 1;
        }
    }

    //曜日更新
    _weekday = static_cast<WeekDay>((static_cast<int>(_weekday) + 1) % 7);

    OffsetDayOfUruYear();

    return *this;
}

Day Day::operator--(int x)
{
    //日付更新
    _day--;
    if (_day < 1)
    {
        _month--;
        if (_month < 1)
        {
            _year--;
            _month = 12;
        }
        _day = pairs[_month - 1].lastDay;
    }

    //曜日更新
    int weekday_int = static_cast<int>(_weekday) - 1;
    if (weekday_int < 0)
        weekday_int = 6;
    _weekday = static_cast<WeekDay>(weekday_int);

    OffsetDayOfUruYear();

    return *this;
}

bool operator<(const Day& left, const Day& right)
{
    //年を比べる
    if (left._year < right._year)
        return true;
    if (left._year > right._year)
        return false;
    //月を比べる
    if (left._month < right._month)
        return true;
    if (left._month > right._month)
        return false;
    //日を比べる
    if (left._day < right._day)
        return true;
    if (left._day > right._day)
        return false;

    //日付が一致するのでfalseを返す
    return false;
}
bool operator>(const Day& left, const Day& right) { return right < left; }
bool operator<=(const Day& left, const Day& right) { return !(left > right); }
bool operator>=(const Day& left, const Day& right) { return !(left < right); }
bool operator==(const Day& left, const Day& right)
{
    if (left._year == right._year && left._month == right._month && left._day == right._day)
    {
        return true;
    }
    else
    {
        return false;
    }
}
bool operator!=(const Day& left, const Day& right) { return !(left == right); }