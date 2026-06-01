import cv2
import numpy as np
import signal
import sys
from multiprocessing.shared_memory import SharedMemory

# --- 設定 ---
CAMERA_ID   = 0
HSV_LOWER   = np.array([0, 90, 150])
HSV_UPPER   = np.array([80, 255, 255])
MIN_RADIUS  = 2
MAX_RADIUS  = 150
SHM_NAME    = "ball_pos"
SHM_SIZE    = 16   # bytes
FRAME_WIDTH = 1920

# --- shared_memory オフセット ---
OFFSET_POS      = 0   # float64, 8 bytes
OFFSET_DETECTED = 8   # uint8,   1 byte  (1=検出中, 0=未検出)
OFFSET_ALIVE    = 9   # uint8,   1 byte  (1=カメラ動作中, 0=停止)


def main():
    # --- オーナーとして shared_memory を作成 ---
    shm = SharedMemory(name=SHM_NAME, create=True, size=SHM_SIZE)
    buf = np.frombuffer(shm.buf, dtype=np.uint8)

    # 初期値: 中央位置, 未検出, 未起動
    buf[0:8] = np.array([0.5], dtype=np.float64).view(np.uint8)
    buf[OFFSET_DETECTED] = 0
    buf[OFFSET_ALIVE]    = 0

    cap = None  # shutdown ハンドラから参照するため先に宣言

    def _shutdown(sig, frame):
        print("[camera_worker] shutting down...")
        buf[OFFSET_ALIVE] = 0
        if cap is not None:
            cap.release()
        cv2.destroyAllWindows()
        shm.close()
        shm.unlink()   # オーナーが shared_memory を解放する
        sys.exit(0)

    signal.signal(signal.SIGINT,  _shutdown)
    signal.signal(signal.SIGTERM, _shutdown)

    # --- カメラ初期化 ---
    print("[camera_worker] initializing camera...")
    cap = cv2.VideoCapture(CAMERA_ID)
    if not cap.isOpened():
        print("[camera_worker] ERROR: カメラを開けませんでした")
        shm.close()
        shm.unlink()
        sys.exit(1)

    cap.set(cv2.CAP_PROP_FRAME_WIDTH,  1920)
    cap.set(cv2.CAP_PROP_FRAME_HEIGHT, 1080)
    cap.set(cv2.CAP_PROP_FPS, 30)

    # 起動完了を通知
    buf[OFFSET_ALIVE] = 1
    print("[camera_worker] camera ready, detection loop started")

    # --- 検出ループ ---
    while True:
        ret, frame = cap.read()
        if not ret:
            break

        # 前処理
        blurred = cv2.GaussianBlur(frame, (9, 9), 0)
        hsv     = cv2.cvtColor(blurred, cv2.COLOR_BGR2HSV)

        # 色マスク
        mask = cv2.inRange(hsv, HSV_LOWER, HSV_UPPER)
        mask = cv2.erode(mask,  None, iterations=2)
        mask = cv2.dilate(mask, None, iterations=2)

        # 輪郭から最大の円形領域を選ぶ
        contours, _ = cv2.findContours(
            mask, cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_SIMPLE)
        ball = None
        if contours:
            c = max(contours, key=cv2.contourArea)
            (x, y), radius = cv2.minEnclosingCircle(c)
            area = cv2.contourArea(c)
            if area > 0:
                circularity = (4 * np.pi * area
                               / (cv2.arcLength(c, True) ** 2 + 1e-6))
                if MIN_RADIUS < radius < MAX_RADIUS and circularity > 0.7:
                    ball = (x, y, radius)

        if ball is not None:
            x, y, radius = ball
            _pos = (FRAME_WIDTH - x) / FRAME_WIDTH
            # shared_memory へ書き込み
            buf[0:8] = np.array([_pos], dtype=np.float64).view(np.uint8)
            buf[OFFSET_DETECTED] = 1
        else:
            # 未検出: detected フラグのみ落とす (pos は前回値を保持)
            buf[OFFSET_DETECTED] = 0

    # ループ脱出 (ret=False など)
    buf[OFFSET_ALIVE] = 0
    cap.release()
    cv2.destroyAllWindows()
    shm.close()
    shm.unlink()


if __name__ == "__main__":
    main()
