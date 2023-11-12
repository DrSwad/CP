import socket
import sys

SERVER_HOST = sys.argv[1]
SERVER_PORT = sys.argv[2]
BUFFER_SIZE = 1024 * 128 # 128KB max size of messages, feel free to increase

# create the socket object
s = socket.socket()
# connect to the server
s.connect((SERVER_HOST, int(SERVER_PORT)))

at_query = 1
while (at_query <= 1000):
  response = s.recv(BUFFER_SIZE).decode()
  print(response)
  response = response.split()[-1]

  i = 0
  j = len(response) - 1
  ans = 0
  while (i < j):
    if response[i] != response[j]:
      ans = ans + 1
    i = i + 1
    j = j - 1
  s.send((str(ans) + '\n').encode())

  at_query += 1

response = s.recv(BUFFER_SIZE).decode()
print(response)