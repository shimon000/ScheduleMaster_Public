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

    cout << "�����X�P�W���[���\�̃e���v���[�g���쐬���܂� " << endl;
    cout << "�����J�n�N�𐼗�œ��͂��Ă�������" << endl;
    cin >> _year;
    cout << "���Ɏ����J�n������͂��Ă�������" << endl;
    cin >> _month;
    cout << "���Ɏ����J�n������͂��Ă�������" << endl;
    cin >> _day;
    

    Day firstday(_year, _month, _day);
    cout << _year << "/" << _month << "/" << _day  << " " << firstday.GetWeekDayChar() << "�������J�n���Ƃ��܂�" << endl;

    cout << "�����Ď������v������o�^���܂�\n���p�����œ��͂��Ă�������" << endl;
    cin >> _daysNum;
    cout << "�������v������" << _daysNum << "���œo�^���܂�" << endl;

    for (;;)
    {
        int ans;
        cout << "�����ē����\�̍ŏ��P�ʂ�o�^���܂�\n15���̏ꍇ��\"0\"��\n30���̏ꍇ��\"1\"��\n�P���Ԃ̏ꍇ��\"2\"����͂��Ă�������" << endl;
        cin >> ans;
        if ((ans != 0) && (ans != 1) && (ans != 2))
        {
            cout << "0 1 2 �̂ǂꂩ����͂��Ă�������" << endl;
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
        cout << "�����ē����\�̊J�n������o�^���܂��J�n������0~24���甼�p�œ��͂��Ă�������" << endl;
        cin >> _startTime;
        cout << "�Ō�ɓ����\�̏I��������o�^���܂��I��������0~24���甼�p�œ��͂��Ă�������" << endl;
        cin >> _endTime;

        if (_endTime <= _startTime)
        {
            cout << "�I���������J�n���ԈȑO�ɂȂ��Ă��܂�" << endl;
        }
        else
        {
            break;
        }
    }
    
    cout << "���͂���ꂳ�܂ł���\n�����\��exe�t�@�C�����u����Ă���f�B���N�g���ɍ쐬���܂�" << endl;

    ScheduleGenerator generator("result.xlsx", _daysNum, _timeUnit_min, _startTime, _endTime,firstday);

    generator.WriteFile();
}