import numpy as np
import time
import signal
import sys
from multiprocessing.shared_memory import SharedMemory

import matlab.engine

# --- 設定 ---
SHM_NAME             = "ball_pos"
CAMERA_READY_TIMEOUT = 15.0   # seconds: camera_worker の起動完了待ちタイムアウト

# --- shared_memory オフセット ---
OFFSET_POS      = 0   # float64, 8 bytes
OFFSET_DETECTED = 8   # uint8,   1 byte  (1=検出中, 0=未検出)
OFFSET_ALIVE    = 9   # uint8,   1 byte  (1=カメラ動作中, 0=停止)


def main():
    START_TIME = time.time()
    # --- shared_memory にアタッチ (作成はしない) ---
    print("[Simulink_operator] attaching to shared memory...")
    try:
        shm = SharedMemory(name=SHM_NAME, create=False)
    except FileNotFoundError:
        print("[Simulink_operator] ERROR: camera_worker.py が起動していません。"
              "先に camera_worker.py を起動してください。")
        sys.exit(1)

    buf = np.frombuffer(shm.buf, dtype=np.uint8)

    def _shutdown(sig, frame):
        print("[Simulink_operator] shutting down...")
        shm.close()   # unlink は呼ばない (オーナーは camera_worker)
        sys.exit(0)

    signal.signal(signal.SIGINT,  _shutdown)
    signal.signal(signal.SIGTERM, _shutdown)

    # --- camera_worker の起動完了を待機 ---
    print("[Simulink_operator] waiting for camera_worker to be ready...")
    deadline = time.time() + CAMERA_READY_TIMEOUT
    while time.time() < deadline:
        if buf[OFFSET_ALIVE] == 1:
            break
        time.sleep(0.1)
    else:
        print(f"[Simulink_operator] ERROR: {CAMERA_READY_TIMEOUT}秒以内に"
              "camera_worker が起動しませんでした")
        _shutdown(None, None)

    # --- MATLAB / Simulink 起動 ---
    print("[Simulink_operator] camera ready, connecting to MATLAB...")
    eng = matlab.engine.connect_matlab()

    model_name = 'operate_flexible_link'
    eng.load_system(model_name, nargout=0)
    eng.qc_build_model(model_name, nargout=0)
    eng.qc_start_model(model_name, nargout=0)

    print("[Simulink_operator] Simulink started, entering control loop")

    prev_pos = 0.5   # 未検出時に送る前回値 (初期値: 中央)

    # --- 制御ループ ---
    while True:
        # camera_worker の生存確認
        if buf[OFFSET_ALIVE] == 0:
            print("[Simulink_operator] camera_worker が停止しました。終了します。")
            break

        # shared_memory から位置を読み取り
        pos      = float(np.frombuffer(bytes(buf[0:8]), dtype=np.float64)[0])
        detected = bool(buf[OFFSET_DETECTED])

        if detected:
            prev_pos = pos   # 検出時のみ更新

        # Simulink へ送信 (未検出時は前回値を保持して送信)
        eng.set_param(f"{model_name}/pos", "Value", str(prev_pos), nargout=0)
        print(f"[{time.time()-START_TIME:.3f}] pos={prev_pos}  detected={detected}")

    _shutdown(None, None)


if __name__ == "__main__":
    main()
