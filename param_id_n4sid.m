%% param_id_n4sid.m
%  N4SID でシーソーシステムを同定し、状態空間モデル (A, B, C, D) を推定する
%
%  前提:
%    1. seesaw_sysid.slx で PRBS 励振実験を実施済み
%    2. iii/Simulink_operator.py (MODE="sysid") でデータが保存済み
%       → sysid_data_YYYYMMDD_HHMMSS.mat に u_log, y_log が入っている
%
%  使い方:
%    1. 下の DATA_FILE に保存された .mat ファイルのパスを設定して実行
%    2. コンソールにフィット率が表示される (目安: 70%以上で実用可)
%    3. sysid_result.mat に A, B, C, D, sys_id が保存される
%       → lqr_design.m で LQR ゲインを設計する

clear; close all;

%% ========== ユーザ設定 ==========
DATA_FILE = 'sysid_data_latest.mat'; % 実験データファイル名（最新のものに変更）
DT        = 0.002;                   % サンプリング時間 [sec] (Simulinkに合わせる)
N_ORDER_RANGE = 2:6;                 % 試す次数の範囲 (2〜6次)
TRAIN_RATIO   = 0.6;                 % 学習データの割合
%% ==================================

fprintf('=== N4SID システム同定 ===\n');
fprintf('データファイル: %s\n', DATA_FILE);

%% 1. データ読み込み
load(DATA_FILE);   % u_log, y_log (timeseries or struct) が読み込まれる

% To Workspace ブロックの出力形式が timeseries の場合
if isa(u_log, 'timeseries')
    u_data = u_log.Data;
    y_data = y_log.Data;
elseif isstruct(u_log)
    u_data = u_log.Data;
    y_data = y_log.Data;
else
    u_data = u_log;
    y_data = y_log;
end

% 列ベクトルに統一
u_data = u_data(:);
y_data = y_data(:);

N = length(u_data);
fprintf('データ点数: %d (%.1f 秒 @ dt=%.3f sec)\n', N, N*DT, DT);

%% 2. データの前処理（平均除去）
%    つり合い点まわりの線形化モデルを同定するため、直流成分を除く
u_mean = mean(u_data);
y_mean = mean(y_data);
u_data = u_data - u_mean;
y_data = y_data - y_mean;
fprintf('平均除去: u_mean=%.4f, y_mean=%.4f\n', u_mean, y_mean);

%% 3. iddata オブジェクト作成・学習/検証分割
data_all = iddata(y_data, u_data, DT);

split_idx  = floor(N * TRAIN_RATIO);
data_est   = data_all(1:split_idx);
data_val   = data_all(split_idx+1:end);
fprintf('学習データ: %d点 / 検証データ: %d点\n', split_idx, N-split_idx);

%% 4. N4SID で複数の次数を試してフィット率を比較
fprintf('\n--- 次数選択 ---\n');
best_fit   = -Inf;
best_sys   = [];
best_order = 0;
fit_table  = zeros(length(N_ORDER_RANGE), 1);

for idx = 1:length(N_ORDER_RANGE)
    n_order = N_ORDER_RANGE(idx);
    try
        sys_candidate = n4sid(data_est, n_order, 'Ts', DT);
        [~, fit_val]  = compare(data_val, sys_candidate);
        fit_table(idx) = fit_val;
        fprintf('  次数 %d: フィット率 = %5.1f%%\n', n_order, fit_val);

        if fit_val > best_fit
            best_fit   = fit_val;
            best_sys   = sys_candidate;
            best_order = n_order;
        end
    catch e
        fprintf('  次数 %d: 同定失敗 (%s)\n', n_order, e.message);
        fit_table(idx) = NaN;
    end
end

fprintf('\n★ 最適次数: %d次 (検証フィット率: %.1f%%)\n', best_order, best_fit);
if best_fit < 70
    warning(['フィット率が %.1f%% と低めです。\n' ...
             '→ 実験時間を長くするか、PRBS 振幅を調整してみてください。'], best_fit);
end

%% 5. 同定結果の取得
sys_id = best_sys;
[A, B, C, D] = ssdata(sys_id);

fprintf('\n--- 同定された離散時間モデル (dt=%.3f sec) ---\n', DT);
fprintf('A 行列 (%dx%d):\n', size(A,1), size(A,2)); disp(A)
fprintf('B 行列:\n'); disp(B)
fprintf('C 行列:\n'); disp(C)
fprintf('D 行列:\n'); disp(D)

%% 6. 連続時間モデルへ変換
sys_id_c = d2c(sys_id, 'zoh');
[Ac, Bc, Cc, Dc] = ssdata(sys_id_c);
fprintf('--- 連続時間モデル ---\n');
fprintf('極 (Ac の固有値):\n'); disp(eig(Ac))

%% 7. 可制御・可観測性チェック
n = size(A, 1);
rank_ctrl = rank(ctrb(A, B));
rank_obs  = rank(obsv(A, C));
fprintf('可制御行列ランク: %d / %d  %s\n', rank_ctrl, n, ...
    ternary(rank_ctrl == n, '✓ 可制御', '✗ 不可制御'));
fprintf('可観測行列ランク: %d / %d  %s\n', rank_obs,  n, ...
    ternary(rank_obs  == n, '✓ 可観測', '✗ 不可観測'));

%% 8. プロット
figure('Name', '同定モデル検証');
compare(data_val, sys_id);
title(sprintf('同定モデル vs 実測（%d次 N4SID, fit=%.1f%%）', best_order, best_fit));

figure('Name', '次数 vs フィット率');
bar(N_ORDER_RANGE, fit_table);
xlabel('モデル次数'); ylabel('フィット率 [%]');
title('次数選択'); grid on;
yline(70, 'r--', '70% 目標ライン');

figure('Name', 'Bode 線図');
bode(sys_id_c); grid on;
title('同定モデルの Bode 線図（連続時間）');

%% 9. 保存
save('sysid_result.mat', 'A', 'B', 'C', 'D', ...
     'Ac', 'Bc', 'Cc', 'Dc', ...
     'sys_id', 'sys_id_c', 'best_fit', 'best_order', ...
     'u_mean', 'y_mean', 'DT');
fprintf('\n同定結果を sysid_result.mat に保存しました。\n');
fprintf('次のステップ: lqr_design.m を実行してください。\n');


%% ========== ローカル関数 ==========
function str = ternary(cond, a, b)
    if cond; str = a; else; str = b; end
end
