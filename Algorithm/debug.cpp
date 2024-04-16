#include "xlsxwriter.h"
#include "Day.h"
#include "ScheduleGenerator.h"
#include<iostream>
using namespace std;

int main() {
    int _year;
    int _month;
    int _day;
    int _daysNum;
    int _timeUnit_min;
    int _startTime;
    int _endTime;

    cout << "実験スケジュール表のテンプレートを作成します " << endl;
    cout << "実験開始年を西暦で入力してください" << endl;
    cin >> _year;
    cout << "次に実験開始月を入力してください" << endl;
    cin >> _month;
    cout << "次に実験開始日を入力してください" << endl;
    cin >> _day;
    

    Day firstday(_year, _month, _day);
    cout << _year << "/" << _month << "/" << _day  << " " << firstday.GetWeekDayChar() << "を実験開始日とします" << endl;

    cout << "続いて実験所要日数を登録します\n半角数字で入力してください" << endl;
    cin >> _daysNum;
    cout << "実験所要日数を" << _daysNum << "日で登録します" << endl;

    for (;;)
    {
        int ans;
        cout << "続いて日程表の最小単位を登録します\n15分の場合は\"0\"を\n30分の場合は\"1\"を\n１時間の場合は\"2\"を入力してください" << endl;
        cin >> ans;
        if ((ans != 0) && (ans != 1) && (ans != 2))
        {
            cout << "0 1 2 のどれかを入力してください" << endl;
        }
        else
        {
            switch (ans)
            {
                case 0:
                    _timeUnit_min = 15;
                    break;
                case 1:
                    _timeUnit_min = 30;
                    break;
                case 2:
                    _timeUnit_min = 60;
                    break;
            default:
                cout << "ERROR:" << endl;
                break;
            }
            break;
        }
    }

    for (;;)
    {
        cout << "続いて日程表の開始時刻を登録します開始時刻を0~24から半角で入力してください" << endl;
        cin >> _startTime;
        cout << "最後に日程表の終了時刻を登録します終了時刻を0~24から半角で入力してください" << endl;
        cin >> _endTime;

        if (_endTime <= _startTime)
        {
            cout << "終了時刻が開始時間以前になっています" << endl;
        }
        else
        {
            break;
        }
    }
    
    cout << "入力お疲れさまでした\n日程表をexeファイルが置かれているディレクトリに作成します" << endl;

    ScheduleGenerator generator("result.xlsx", _daysNum, _timeUnit_min, _startTime, _endTime,firstday);

    generator.WriteFile();
}