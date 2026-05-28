# ピンポン玉の位置を検出して共有メモリに書き込む
# このプロセスは常時起動しておく
# Simulink_operator.py から共有メモリ経由で位置情報を読み取り、制御に利用

# ライブラリ
# OpenCV
import cv2
import numpy as np
# SIGINT/SIGTERM のハンドリング(Ctrl+C 終了など)
import signal
# プロセス終了用(sys.exit)
import sys
# 共有メモリ
from multiprocessing.shared_memory import SharedMemory

# 設定
# 接続中のカメラのID
CAMERA_ID = 0
# 検出するボール色のHSV上下限 (ピンポン玉は黄色)
HSV_LOWER = np.array([0, 90, 150])
HSV_UPPER = np.array([80, 255, 255])
# 検出円の半径範囲[px] (ノイズ扱い < 検出 < 誤検出)
MIN_RADIUS = 2
MAX_RADIUS = 150
# 共有メモリの識別名 (Simulink_operator側と一致させる)
SHM_NAME = "ball_pos"
# 共有メモリのサイズ (位置8B + フラグ2B + 予約6B)
SHM_SIZE = 16
# フレーム幅[px] (位置の正規化するのに使用)
FRAME_WIDTH = 1920

# 共有メモリ
# 共有メモリ内のデータレイアウトを定義 (Simulink_operator.pyと同じ値)
# float64,8バイト、ボールの座標(0 ~ 1)
OFFSET_POS = 0
# uint8,1バイト (1=検出中, 0=未検出)、現フレームでボールを検出できたか
OFFSET_DETECTED = 8
# uint8,1バイト (1=カメラ動作中, 0=停止)、このプロセスの生存フラグ
OFFSET_ALIVE = 9


def main():
    # 共有メモリ作成
    # 終了時はunlinkで解放
    shm = SharedMemory(name=SHM_NAME, create=True, size=SHM_SIZE)
    # numpy配列としてバイト単位でアクセスできるようラップ
    buf = np.frombuffer(shm.buf, dtype=np.uint8)

    # 初期値は中央位置(0.5)、未検出、未起動
    buf[0:8] = np.array([0.5], dtype=np.float64).view(np.uint8)
    buf[OFFSET_DETECTED] = 0
    buf[OFFSET_ALIVE] = 0
    
    # shutdownから参照するため先に宣言
    cap = None

    # 終了処理の定義 (シグナルハンドラとループ脱出後の両方から呼ばれる)
    def _shutdown(sig, frame):
        print("[camera_worker] shutting down...")
        # Simulink_operatorに停止を通知
        buf[OFFSET_ALIVE] = 0
        if cap is not None:
            # 解放
            cap.release()
        # 終了、解放
        cv2.destroyAllWindows()
        shm.close()
        shm.unlink()
        sys.exit(0)

    # OS からのシグナルで終了できるようハンドラを登録
    # Ctrl+C
    signal.signal(signal.SIGINT,  _shutdown)
    #killとか
    signal.signal(signal.SIGTERM, _shutdown)

    # カメラ初期化
    print("[camera_worker] initializing camera...")
    # カメラデバイスをオープン
    cap = cv2.VideoCapture(CAMERA_ID)
    if not cap.isOpened():
        # 共有メモリを片付ける
        print("[camera_worker] ERROR: カメラを開けませんでした")
        shm.close()
        shm.unlink()
        sys.exit(1)

    # 解像度等設定 (対応していなければ無視)
    cap.set(cv2.CAP_PROP_FRAME_WIDTH,  1920)
    cap.set(cv2.CAP_PROP_FRAME_HEIGHT, 1080)
    cap.set(cv2.CAP_PROP_FPS, 30)

    # 起動完了を通知
    # Simulink_operatorにフラグで通知(共有メモリ)
    buf[OFFSET_ALIVE] = 1
    print("[camera_worker] camera ready, detection started")

    # 検出ループ
    while True:
        # 1フレーム取得
        ret, frame = cap.read()
        if not ret:
            break

        # 前処理: ノイズ除去とHSV変換
        # ガウシアンブラーで少しぼかす(ノイズ除去)
        blurred = cv2.GaussianBlur(frame, (9, 9), 0)
        # HSVへ変換(色相で検出するため)
        hsv = cv2.cvtColor(blurred, cv2.COLOR_BGR2HSV)

        # 色マスク
        # 1.ボール色の範囲だけ白(255)にする2値画像を生成
        mask = cv2.inRange(hsv, HSV_LOWER, HSV_UPPER)
        # 2.収縮(小さなノイズを除去、大きい要素(ピンポン領域)のみ残す)
        mask = cv2.erode(mask,  None, iterations=2)
        # 3.膨張(ピンポン領域のみもとに戻す)
        mask = cv2.dilate(mask, None, iterations=2)

        # 輪郭から最大の円形領域を選ぶ
        # 外側の輪郭のみを抽出
        contours, _ = cv2.findContours(
            mask, cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_SIMPLE)
        ball = None
        if contours:
            # 最大面積の輪郭を候補とする
            c = max(contours, key=cv2.contourArea)
            # その輪郭を囲む最小円
            (x, y), radius = cv2.minEnclosingCircle(c)
            area = cv2.contourArea(c)
            if area > 0:
                # 円形度(1.0 に近いほど真円に近い (4πA/L²))
                # 1e-6 は周長0の割り算を避けるため使用
                circularity = (4 * np.pi * area
                               / (cv2.arcLength(c, True) ** 2 + 1e-6))
                # 半径と円形度の両方が条件を満たす場合のみボールとして採用
                if MIN_RADIUS < radius < MAX_RADIUS and circularity > 0.7:
                    ball = (x, y, radius)

        if ball is not None:
            x, y, radius = ball
            # 画面右端を0、左端を1とした位置(カメラ反転に対応するため FRAME_WIDTH - x)
            _pos = (FRAME_WIDTH - x) / FRAME_WIDTH
            # 共有メモリへ書き込み
            # float64を8バイト列として書き込み、Simulink_operatorが同形式で読む
            buf[0:8] = np.array([_pos], dtype=np.float64).view(np.uint8)
            # 検出成功フラグを立てる
            buf[OFFSET_DETECTED] = 1
        else:
            # 未検出: detected フラグのみ落とす(posは前回のを保持)
            # Simulink側でフラグが0の時は前回位置を維持
            buf[OFFSET_DETECTED] = 0
        # デバッグ用にカメラ映像をウィンドウ表示
        cv2.imshow("track", frame)
        # qで終了
        if cv2.waitKey(1) & 0xFF == ord('q'):
            break

    # ループ終了
    # ハンドラと同じ後始末を行う
    buf[OFFSET_ALIVE] = 0
    cap.release()
    cv2.destroyAllWindows()
    shm.close()
    shm.unlink()


if __name__ == "__main__":
    main()
