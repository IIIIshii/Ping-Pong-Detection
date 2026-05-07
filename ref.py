import cv2
import socket
import struct
import numpy as np
import time

# --- 設定 ---
CAMERA_ID = 0
# オレンジのピンポン玉用 HSV 範囲（環境光で要調整）
HSV_LOWER = np.array([0, 90, 100])
HSV_UPPER = np.array([80, 255, 255])
MIN_RADIUS = 2      # 検出する最小半径（ピクセル）
MAX_RADIUS = 150    # 検出する最大半径（ピクセル）
# BALL_DIAMETER_MM = 40.0  #実直径

UDP_IP = "127.0.0.1"
UDP_PORT = 8080
sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)

def main():
    cap = cv2.VideoCapture(CAMERA_ID)
    if not cap.isOpened():
        print("カメラを開けませんでした")
        return

    # 可能ならカメラを高速モードに
    cap.set(cv2.CAP_PROP_FRAME_WIDTH, 1920)
    cap.set(cv2.CAP_PROP_FRAME_HEIGHT, 1080)
    cap.set(cv2.CAP_PROP_FPS, 30)
    # prev_pos = None      # (x, y) ピクセル
    # prev_time = None     # 秒
    # prev_radius = None

    while True:
        ret, frame = cap.read()
        if not ret:
            break
        now = time.time()

        # --- 前処理 ---
        blurred = cv2.GaussianBlur(frame, (9, 9), 0)
        hsv = cv2.cvtColor(blurred, cv2.COLOR_BGR2HSV)

        # --- 色マスク ---
        mask = cv2.inRange(hsv, HSV_LOWER, HSV_UPPER)
        mask = cv2.erode(mask, None, iterations=2)
        mask = cv2.dilate(mask, None, iterations=2)

        # --- 輪郭から最大の円形領域を選ぶ ---
        contours, _ = cv2.findContours(mask, cv2.RETR_EXTERNAL,
                                       cv2.CHAIN_APPROX_SIMPLE)
        ball = None  # (x, y, radius)
        if contours:
            c = max(contours, key=cv2.contourArea)
            (x, y), radius = cv2.minEnclosingCircle(c)
            area = cv2.contourArea(c)
            # 円形度チェック（1.0 に近いほど真円）
            if area > 0:
                circularity = 4 * np.pi * area / (cv2.arcLength(c, True) ** 2 + 1e-6)
                if MIN_RADIUS < radius < MAX_RADIUS and circularity > 0.7:
                    ball = (x, y, radius)

        # --- 速度計算 ---
        # speed_px = 0.0
        # speed_mm = 0.0
        if ball is not None:
            x, y, radius = ball
            # if prev_pos is not None and prev_time is not None:
            #     dt = now - prev_time
            #     if dt > 0:
            #         dx = x - prev_pos[0]
            #         dy = y - prev_pos[1]
            #         speed_px = np.hypot(dx, dy) / dt  # px/s
            #         # 既知サイズ法でスケール推定: 直径(px) ↔ 40mm
            #         mm_per_px = BALL_DIAMETER_MM / (2 * radius)
            #         speed_mm = speed_px * mm_per_px  # mm/s
            # 描画
            cv2.circle(frame, (int(x), int(y)), int(radius), (0, 255, 0), 2)
            cv2.circle(frame, (int(x), int(y)), 3, (0, 0, 255), -1)
            cv2.putText(frame,
                        f"pos=({int(x)},{int(y)})",
                        (10, 30), cv2.FONT_HERSHEY_SIMPLEX, 0.6,
                        (0, 255, 0), 2)

            # prev_pos = (x, y)
            # prev_time = now
            # prev_radius = radius

            # --- データ送信 ---
            data = struct.pack('ff', x, y)  # 位置のみ送る
            sock.sendto(data, (UDP_IP, UDP_PORT))

        cv2.imshow("Ball Tracker", frame)
        cv2.imshow("Mask", mask)
        if cv2.waitKey(1) & 0xFF == ord('q'):
            break

    cap.release()
    cv2.destroyAllWindows()

if __name__ == "__main__":
    main()