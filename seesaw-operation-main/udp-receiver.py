
import time
import socket
import struct


sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
sock.bind(("10.232.42.210", 8080))

startTime = time.perf_counter()
while True: 
	now = time.perf_counter() - startTime

	data, addr = sock.recvfrom(8)
	pos = struct.unpack('<d', data)[0]

	print(f"{now} {pos}")
	time.sleep(1/60)