// This Source Code Form is subject to the terms of the MIT License.
// If a copy of the MIT was not distributed with this file, You can obtain one at https://opensource.org/licenses/MIT.
// Copyright (C) Leszek Pomianowski and WPF UI Contributors.
// All Rights Reserved.

using Microsoft.Win32;
using System.Runtime.InteropServices;
using Wpf.Ui.Appearance;

namespace NewGUI.ViewModels.Pages
{
    /// <summary>
    /// エクセルファイルを作成するページのViewmodel
    /// ここのクラス名を変更するとジェネレーターの問題でエラーが起こるのでテンプレートままにしておく
    /// </summary>
    public partial class DashboardViewModel : ObservableObject
    {
        private string _timeUnit;
        public string TimeUnit
        {
            get { return _timeUnit; }
            set
            {
                if (_timeUnit != value)
                {
                    _timeUnit = value;
                    timeUnit_min = ConvertStringToInt(value);
                }
            }
        }

        private string _beginTime;
        public string BeginTime
        {
            get { return _beginTime; }
            set
            {
                if( _beginTime != value)
                {
                    _beginTime = value;
                    beginTime_int = ConvertStringToInt(value);
                }
            }
        }

        private string _endTime;
        public string EndTime
        {
            get { return _endTime; }
            set
            {
                if(_endTime != value)
                {
                    _endTime = value;
                    endTime_int = ConvertStringToInt(value);
                }
            }
        }

        private DateTime _beginDate;
        public DateTime BeginDate
        {
            get { return _beginDate; }
            set
            {
                if (_beginDate != value)
                {
                    _beginDate = value;
                }
            }
        }

        private DateTime _endDate;
        public DateTime EndDate
        {
            get { return _endDate; }
            set
            {
                if(_endDate != value)
                {
                    _endDate = value;
                }
            }
        }

        private int timeUnit_min = -1;
        private int beginDate_int = -1;
        private int endDate_int = -1;
        private int beginTime_int = -1;
        private int endTime_int = -1;

        [RelayCommand]
        private void OnPressSaveButton()
        {
            if(beginTime_int*beginDate_int*beginTime_int*endDate_int*endTime_int*timeUnit_min < 0)
            {
                MessageBox.Show("すべての値を設定してください", "Alart");
                return;
            }


            int daysNum = (_endDate - _beginDate).Days + 1;
            if (daysNum < 0)
            {
                MessageBox.Show("実験開始日と実験終了日が不正な値です", "Alart");
                return;
            }
            
            if(endTime_int - beginTime_int <= 0)
            {
                MessageBox.Show("実験開始時刻と実験終了時刻が不正な値です", "Alart");
                return;
            }


            var dialog = new SaveFileDialog();
            //保存はエクセルファイルにする
            dialog.Filter = "xlsxファイル|*.xlsx";

            //ユーザーが保存ボタンを押したかどうか
            bool isCorrect = dialog.ShowDialog() ?? false;

            if (!isCorrect)
                return;

            string fileName = dialog.FileName;

            Algorithm.Generate(fileName, daysNum, timeUnit_min, beginTime_int, endTime_int, _beginDate.Year, _beginDate.Month, _beginDate.Day);
        }
        /// <summary>
        /// "System 1 時"や"System 15 分"などの文字列をint型に変換する
        /// </summary>

        private int ConvertStringToInt(string str)
        {
            string[] tmp = str.Split(' ');
            if (tmp.Length < 2 || tmp == null)
                return 0;
            int result = int.Parse(tmp[1]);
            return result;
        }
    }

    internal class Algorithm
    {
        [DllImport("Algorithm64.dll")]
        static extern void GenerateFile(string fileName, int days_num,
            int timeunit_min, int startTime, int endTime,
            int year, int month, int day);

        static public void Generate(string fileName, int days_num,
            int timeunit_min, int startTime, int endTime,
            int year, int month, int day)
        {
            GenerateFile(fileName, days_num, timeunit_min, startTime, endTime, year, month, day);
        }
    }

}
