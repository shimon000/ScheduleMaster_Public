# ScheduleMaster

研究室での実験に必要な日程調整表を楽に作成したいと思い制作したアプリです。
# 実行環境
- Windows
# 使用ライブラリ
- libxlsxwriter \
https://github.com/jmcnamara/libxlsxwriter
- zlib \
https://zlib.net/
- WPF UI \
https://wpfui.lepo.co/
# 担当箇所
UI部分にはWPF UIのテンプレートを使用しています。 \
担当箇所は 担当箇所.txt から確認できます。
# 実行ファイルのダウンロード
実行ファイルはReleaseからダウンロードできます。
# 実行方法
1.ダウンロードした実行ファイルの中にあるScheguleMaster.exeを起動します\
2.アプリが起動し、ウィンドウが表示されます
# 使用方法
実行ファイルを起動すると以下のような入力画面が表示されます \
実験期間の欄に実験開始日と実験終了日を \
実験時間の欄に一日の実験開始時間と実験終了時間を \
単位時間の欄に日程表の最小時間単位を入力します。
![image1](https://github.com/shimon000/ScheduleMaster_Public/assets/97788241/585fe241-e6d6-47b6-a312-666aef233ac6)
上記の設定で作成ボタンを押すと\
以下のようなエクセルファイルが出力されます

![image2](https://github.com/shimon000/ScheduleMaster_Public/assets/97788241/68dfc307-b231-48b6-96e5-10215c511755)

実験開始日が含まれた週の初日から、実験終了日が含まれた週の最終日まで描画されます。
