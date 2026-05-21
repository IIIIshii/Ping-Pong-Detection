%% lqr_design.m
%  N4SID で同定したモデルを使って LQR ゲインを設計する
%
%  前提: param_id_n4sid.m を実行済みで sysid_result.mat が存在すること
%
%  使い方:
%    1. Q, R の重み行列をチューニングして実行
%    2. 閉ループ極がすべて左半平面（実部 < 0）になっていることを確認
%    3. lqr_result.mat に K_lqr が保存される
%       → operate_flexible_link.slx の Gain ブロックに設定する

clear; close all;

%% ========== ユーザ設定 ==========
% Q: 状態の重み（大きい成分 = その状態を積極的に安定化）
% R: 入力の重み（大きい = 省エネ優先、小さい = 速応答優先）
%
% 初回は Q = eye(n)*10, R = 1 から始めてチューニングする
% 例: ボール位置を特に重視したい場合は Q(1,1) を大きくする
Q_SCALE = 10;   % Q 全体のスケール (eye(n) * Q_SCALE)
R_VALUE = 1;    % 入力重み
%% ==================================

%% 1. 同定結果の読み込み
fprintf('=== LQR 設計 ===\n');
load('sysid_result.mat');  % Ac, Bc, Cc, Dc, sys_id_c, best_order, best_fit

fprintf('モデル情報: %d次 N4SID, フィット率=%.1f%%\n', best_order, best_fit);
fprintf('連続時間 A 行列:\n'); disp(Ac)
fprintf('連続時間 B 行列:\n'); disp(Bc)

n = size(Ac, 1);   % モデルの次数

%% 2. オープンループ極の確認
poles_ol = eig(Ac);
fprintf('オープンループ極:\n'); disp(poles_ol)
if any(real(poles_ol) > 0)
    fprintf('→ 不安定極あり（シーソーは本来不安定プラント: 正常）\n\n');
else
    fprintf('→ すべて安定（確認してください）\n\n');
end

%% 3. 可制御性の確認
rank_ctrl = rank(ctrb(Ac, Bc));
if rank_ctrl < n
    error('システムが可制御でありません (ランク %d / %d)。モデルを見直してください。', ...
          rank_ctrl, n);
end
fprintf('可制御性: ランク %d / %d ✓\n', rank_ctrl, n);

%% 4. LQR ゲインの設計
Q = eye(n) * Q_SCALE;
R = R_VALUE;

K_lqr = lqr(Ac, Bc, Q, R);

fprintf('\n--- LQR ゲイン K (Q_scale=%.1f, R=%.2f) ---\n', Q_SCALE, R_VALUE);
disp(K_lqr)

%% 5. 閉ループ極の確認
Ac_cl    = Ac - Bc * K_lqr;
poles_cl = eig(Ac_cl);
fprintf('閉ループ極:\n'); disp(poles_cl)

if all(real(poles_cl) < 0)
    fprintf('→ すべて左半平面 ✓ 安定\n');
else
    warning('閉ループ極に不安定な極があります。Q, R を調整してください。');
end

%% 6. 閉ループの応答シミュレーション（参考）
sys_cl = ss(Ac_cl, Bc, Cc, Dc);
t_sim  = 0:0.002:5;   % 5 秒間のシミュレーション
[y_cl, t_cl] = step(sys_cl, t_sim);

figure('Name', '閉ループ ステップ応答（参考）');
plot(t_cl, y_cl, 'b', 'LineWidth', 2);
xlabel('時間 [sec]'); ylabel('ボール位置（正規化）');
title(sprintf('LQR 閉ループ ステップ応答 (Q\\_scale=%.1f, R=%.2f)', Q_SCALE, R_VALUE));
grid on;

figure('Name', 'オープン/クローズドループ 極');
hold on;
plot(real(poles_ol), imag(poles_ol), 'rx', 'MarkerSize', 12, 'LineWidth', 2);
plot(real(poles_cl), imag(poles_cl), 'bo', 'MarkerSize', 12, 'LineWidth', 2);
yline(0, 'k--'); xline(0, 'k--');
legend('OL極（不安定可）', 'CL極（左半平面）');
xlabel('実部'); ylabel('虚部');
title('極の移動（Root Locus 的確認）');
grid on;

%% 7. Simulink への組み込みガイド
fprintf('\n=== Simulink への組み込み手順 ===\n');
fprintf('1. operate_flexible_link.slx を開く\n');
fprintf('2. Gain ブロックを追加して K_lqr を設定:\n');
fprintf('   Gain値: ['); fprintf('%.4f ', K_lqr); fprintf(']\n');
fprintf('3. 状態フィードバック: u = -K_lqr * x\n');
fprintf('   ※ x (状態) は N4SID モデルのオブザーバで推定する\n');
fprintf('4. iii/Simulink_operator.py の MODE を "control" に戻して起動\n');

%% 8. 保存
save('lqr_result.mat', 'K_lqr', 'Ac', 'Bc', 'Cc', 'Dc', ...
     'Q', 'R', 'poles_ol', 'poles_cl', 'Q_SCALE', 'R_VALUE');
fprintf('\nLQR 設計結果を lqr_result.mat に保存しました。\n');
