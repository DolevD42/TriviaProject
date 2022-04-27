import socket
import json

HOST = "127.0.0.1"  # The server's hostname or IP address
PORT = 8876  # The port used by the server
LOGIN = {"username": "user1", "password": 1234}
SIGN_IN = {"username": "user1", "password": 1234, "mail": "user1@gmail.com"}


def main():
    runtime = 0
    with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as Csock:
        try:
            Csock.connect((HOST, PORT))
            if runtime == 0:
                data = Csock.recv(5).decode()
                print(data)
                if data == "Hello":
                    Csock.sendall(b"Hello")
                    runtime = 1
            data = Csock.recv(1024).decode()
            print(data)
            data = json.loads(data)
            if data.status == 1:
                messageToSend = json.dumps(LOGIN)
                Csock.sendall(messageToSend.encode())
        except Exception as e:
            print(e)


if __name__ == '__main__':
    main()