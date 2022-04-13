
import socket

HOST = "127.0.0.1"  # The server's hostname or IP address
PORT = 8876  # The port used by the server

with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as Csock:
    try:
        Csock.connect((HOST, PORT))
        data = Csock.recv(5).decode()
        print(data)
        if data == "Hello":
            Csock.sendall(b"Hello")
    except Exception as e:
        print(e)
