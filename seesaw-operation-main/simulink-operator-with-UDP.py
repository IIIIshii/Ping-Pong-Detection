
import matlab.engine
import time
import socket
import struct

# UDPの受け取り用
sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
sock.bind(("10.232.42.210", 8080))

# MATLABを起動
eng = matlab.engine.connect_matlab()

# 必要ならQUARCにパスを通す（$ which qc_build_model（MATLAB）で見つかるはず）
# quarc_path = "path/to/quarc"
# eng.addpath(eng.genpath(quarc_path), nargout=0)

# モデルをロード
model_name = 'operate_flexible_link'
eng.load_system(model_name, nargout=0)

# QUARCモデルを開始
eng.qc_build_model(model_name, nargout=0) # 最初だけ
eng.qc_start_model(model_name, nargout=0)

print("operation start!!")

startTime = time.perf_counter()
while True: 
	now = time.perf_counter() - startTime
	# 座標の受け取り
	data, addr = sock.recvfrom(8)
	_pos = struct.unpack('<d', data)[0]
	time.sleep(1/60)

	# リアルタイムでパラメータを変更（MATLABの変数を経由）
	eng.workspace['pos'] = _pos

	# リアルタイムでデータを取得（MATLABの変数を経由）
	try:
			# 'out' という名前で To Workspace ブロックが書き出している前提
			# out = eng.workspace['out']
			print(f"{now} {_pos} {out}")
	except:
			print(f"{now} {_pos} error")
			pass


print("終了！")

# モデルの停止
eng.qc_stop_model(model_name, nargout=0)