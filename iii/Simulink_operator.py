import numpy as np
import time
import signal
import sys
from multiprocessing.shared_memory import SharedMemory

import matlab.engine

# ---------------------------------------------------------------------------
# 動作モードの選択
#   "control" : 通常制御モード (operate_flexible_link)
#   "sysid"   : システム同定実験モード (seesaw_sysid, PRBS励振 + データ記録)
# ---------------------------------------------------------------------------
MODE     = "sysid"    # ← "control" or "sysid" に切り替えて使う
SIM_TIME = 60         # システム同定実験時間 [sec]（MODE="sysid" のときのみ使用）

# モードに応じてモデル名を自動選択
MODEL_TABLE = {
    "control": "operate_flexible_link",
    "sysid":   "seesaw_sysid",
}
model_name = MODEL_TABLE[MODE]

# --- 設定 ---
SHM_NAME             = "ball_pos"
CAMERA_READY_TIMEOUT = 15.0   # seconds: camera_worker の起動完了待ちタイムアウト

# --- shared_memory オフセット ---
OFFSET_POS      = 0   # float64, 8 bytes
OFFSET_DETECTED = 8   # uint8,   1 byte  (1=検出中, 0=未検出)
OFFSET_ALIVE    = 9   # uint8,   1 byte  (1=カメラ動作中, 0=停止)


def _read_shm(buf):
    """SHM から (pos, detected) を読み取るヘルパー"""
    pos      = float(np.frombuffer(bytes(buf[0:8]), dtype=np.float64)[0])
    detected = bool(buf[OFFSET_DETECTED])
    return pos, detected


def run_control(eng, shm_buf, start_time):
    """通常制御ループ (MODE="control")"""
    print(f"[Simulink_operator] control loop started (model={model_name})")
    prev_pos = 0.5

    while True:
        if shm_buf[OFFSET_ALIVE] == 0:
            print("[Simulink_operator] camera_worker が停止しました。終了します。")
            break

        pos, detected = _read_shm(shm_buf)
        if detected:
            prev_pos = pos

        eng.set_param(f"{model_name}/pos", "Value", str(prev_pos), nargout=0)
        print(f"[{time.time()-start_time:.3f}] pos={prev_pos:.4f}  detected={detected}")


def run_sysid(eng, shm_buf, start_time):
    """システム同定実験ループ (MODE="sysid")

    SIM_TIME 秒間、ボール位置を Simulink へ送り続ける。
    Simulink 内の To Workspace ブロックが u_log / y_log を記録する。
    実験終了後、MATLAB ワークスペースから .mat ファイルとして保存する。
    """
    print(f"[Simulink_operator] sysid loop started (model={model_name}, "
          f"sim_time={SIM_TIME}s)")
    prev_pos    = 0.5
    end_time    = time.time() + SIM_TIME

    while time.time() < end_time:
        if shm_buf[OFFSET_ALIVE] == 0:
            print("[Simulink_operator] camera_worker が停止しました。実験を中断します。")
            return

        pos, detected = _read_shm(shm_buf)
        if detected:
            prev_pos = pos

        eng.set_param(f"{model_name}/pos", "Value", str(prev_pos), nargout=0)
        elapsed = time.time() - start_time
        remaining = end_time - time.time()
        print(f"[{elapsed:.3f}s / 残り{remaining:.1f}s] "
              f"pos={prev_pos:.4f}  detected={detected}")

    # --- 実験終了: モデル停止 & データ保存 ---
    print("[Simulink_operator] 実験完了。Simulink モデルを停止しています...")
    eng.set_param(model_name, "SimulationCommand", "stop", nargout=0)
    time.sleep(1.0)   # To Workspace ブロックの書き込み完了を待つ

    # タイムスタンプ付きファイル名で保存
    ts = time.strftime("%Y%m%d_%H%M%S")
    save_name = f"sysid_data_{ts}.mat"
    try:
        eng.eval(
            f"save('{save_name}', 'u_log', 'y_log');",
            nargout=0
        )
        print(f"[Simulink_operator] データ保存完了: {save_name}")
        print("  → MATLAB で param_id_n4sid.m を実行してシステム同定を行ってください。")
        print(f"     load('{save_name}') してから param_id_n4sid を実行")
    except Exception as e:
        print(f"[Simulink_operator] WARNING: データ保存に失敗しました: {e}")
        print("  → Simulink の To Workspace ブロック名 (u_log / y_log) を確認してください。")


def main():
    START_TIME = time.time()

    # --- shared_memory にアタッチ (作成はしない) ---
    print(f"[Simulink_operator] mode={MODE}, model={model_name}")
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

    eng.load_system(model_name, nargout=0)
    eng.qc_build_model(model_name, nargout=0)
    eng.qc_start_model(model_name, nargout=0)

    # --- モード分岐 ---
    if MODE == "sysid":
        run_sysid(eng, buf, START_TIME)
    else:
        run_control(eng, buf, START_TIME)

    _shutdown(None, None)


if __name__ == "__main__":
    main()
