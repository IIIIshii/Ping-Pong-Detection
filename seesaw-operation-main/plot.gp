set encoding utf8 # 文字化けを防ぐため、文字コードをUTF-8にする。

set datafile separator "," # csvに対応させる。

filename = "result-single-1"
# filename = "result-single-H-1"
# filename = "result-double-1"
# filename = "result-double_I-1"

set term pngcairo # pngファイルに出力する。
set output filename.".png" # ファイル名を設定する。

# 軸ラベルを設定する。
set xlabel 'Time [s]'
set ylabel 'Position [m]'
set y2label 'Input Value'
set ytics nomirror
set y2tics nomirror

# set logscale x # 横軸を対数スケールで表示する
# set logscale y # 縦軸を対数スケールで表示する
# set format x "10^{%L}"

# set grid
# set mxtics
# set grid xtics mxtics


# set xtics 1, 1, 4 # x軸の範囲を、1から4まで1刻みで表示させる。
# set yrange [-100:20] # y軸の範囲を1.5から9までにする。

# key(凡例)を設定する。
# set key spacing 1.5
# set key right bottom # 左上に表示
# set key at 0.45, 1e15 # (0.63, 0.9)を右上にして凡例を表示させる

# フォント設定
# 軸ラベルのフォントをメイリオにし、文字サイズを20にする。
set xlabel font "Meiryo,20"
set ylabel font "Meiryo,20"
set y2label font "Meiryo,20"
set tics font "Arial,10" # 目盛のフォントをArialにし、文字サイズを10にする。
set key font "Meiryo,11" # 凡例のフォントをメイリオにし、文字サイズを10にする。

# ラベルの位置調整を行う。デフォルトの位置からx, yだけズラす。
# set xlabel offset 0,-1
set ylabel offset 1,0
set y2label offset -1,0

# 見やすい色
array colors7[7] = ['#FF4B00', '#005AFF', '#03AF7A', '#4DC4FF', '#F6AA00', '#FFF100', '#000000']
array colors10[10] = ['#332288', '#88CCEE', '#44AA99', '#117733', '#999933', '#DDCC77', '#CC6677', '#882255', '#AA4499', '#DDDDDD']

# 1行目から順に、時刻・ボール位置・エンコーダ・入力（・目標値のsine wave）
plot filename.".txt" u 1:(($2)*1.06) title "ball" axis x1y1 pt 1 lc rgb colors7[1] w l,\
     filename.".txt" u 1:4 title "input" axis x1y2 pt 1 lc rgb colors7[2] w l
    #  filename.".txt" u 1:5 title "goal" pt 1 lc rgb colors7[3] w l

unset output # pngファイルを閉じる。
reset # 設定をリセットする。
quit # プログラムを終了する。
