# camera_worker.pyが共有メモリへ書き込んだボール位置を読み取る
# MATLAB/Simulinkの制御モデルへ送信する
# camera_worker.pyを先に起動しておく

#ライブラリ
import numpy as np
import time
# SIGINT/SIGTERM のハンドリング
import signal
# プロセス終了用
import sys
# 共有メモリ
from multiprocessing.shared_memory import SharedMemory
# Python から MATLAB エンジンを操作するための公式モジュール
import matlab.engine

# 設定
#共有メモリの識別名 (camera_worker.py と一致させる)
SHM_NAME = "ball_pos"
#camera_worker の起動待ち用のタイムアウト
CAMERA_READY_TIMEOUT = 15.0

# 共有メモリ
# camera_worker.py 側と同じレイアウト定義(詳細はcamera_worker.pyを参照)
OFFSET_POS      = 0
OFFSET_DETECTED = 8
OFFSET_ALIVE    = 9


def main():
    # 経過時間用
    START_TIME = time.time()
    # 共有メモリにつなぐ
    print("[Simulink_operator] attaching to shared memory...")
    try:
        shm = SharedMemory(name=SHM_NAME, create=False)
    except FileNotFoundError:
        # camera_workerが共有メモリをまだ作っていない
        print("[Simulink_operator] ERROR: camera_worker.py が起動していません。"
              "先に camera_worker.py を起動してください。")
        sys.exit(1)

   # アクセス用numpyビュー
    buf = np.frombuffer(shm.buf, dtype=np.uint8)

    def _shutdown(sig, frame):
        # 終了処理
        print("[Simulink_operator] shutting down...")
        # unlinkしない(オーナーはcamera_workerなので)
        shm.close()
        sys.exit(0)

    # OSからのシグナルに対する終了処理を登録
    signal.signal(signal.SIGINT,  _shutdown)
    signal.signal(signal.SIGTERM, _shutdown)

    #　camera_workerの起動を待つ
    # OFFSET_ALIVE = 1になるまでポーリング
    print("[Simulink_operator] waiting for camera_worker to be ready...")
    deadline = time.time() + CAMERA_READY_TIMEOUT
    while time.time() < deadline:
        if buf[OFFSET_ALIVE] == 1:
            break
        # CPU を食い潰さないよう100ms毎にチェック
        time.sleep(0.1)
    else:
        # breakせずタイムアウトに到達したときに実行される
        print(f"[Simulink_operator] ERROR: {CAMERA_READY_TIMEOUT}秒以内に"
              "camera_worker が起動しませんでした")
        _shutdown(None, None)

    # MATLAB,Simulink起動
    # 事前にMATLAB側でmatlab.engine.shareEngineを実行して共有しておく
    print("[Simulink_operator] camera ready, connecting to MATLAB...")
    # MATLABセッションに接続
    eng = matlab.engine.connect_matlab()

    # 制御対象のSimulinkモデル
    model_name = 'operate_flexible_link'
    # モデルをロード
    eng.load_system(model_name, nargout=0)
    # QUARCによるリアルタイム実行用ビルド
    eng.qc_build_model(model_name, nargout=0)
    # モデルの実行を開始
    eng.qc_start_model(model_name, nargout=0)

    print("[Simulink_operator] Simulink started, entering control loop")

    # 未検出時に送る前回値(初期値:中央)
    # 検出が一度も成功しないうちはこの値がSimulinkに送られる
    prev_pos = 0.5

    # 制御ループ
    while True:
        # camera_worker が落ちてたら明示的に検出して終了
        if buf[OFFSET_ALIVE] == 0:
            print("[Simulink_operator] camera_worker が停止しました。終了します。")
            break

        # 共有メモリから位置を読み取り
        # bytesでコピーしてからfrombufferに渡して書き込みと競合しないように
        pos      = float(np.frombuffer(bytes(buf[0:8]), dtype=np.float64)[0])
        # 検出フラグ
        detected = bool(buf[OFFSET_DETECTED])

        if detected:
            # 未検出時は更新しない
            prev_pos = pos

        # Simulinkに送信
        # モデルのpos(定数ブロック)のValueを書き換える
        eng.set_param(f"{model_name}/pos", "Value", str(prev_pos), nargout=0)
        # 経過時間 / 送信した位置 / 検出状態
        print(f"[{time.time()-START_TIME:.3f}] pos={prev_pos}  detected={detected}")

    # ループ脱出時 (camera_worker 停止検知) の後始末
    _shutdown(None, None)


if __name__ == "__main__":
    main()
