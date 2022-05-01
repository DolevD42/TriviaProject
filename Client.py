import socket
import json

HOST = "127.0.0.1"  # The server's hostname or IP address
PORT = 8876  # The port used by the server
LOGIN = {"username": "user1", "password": 1234}
SIGN_IN = {"username": "user1", "password": 1234, "mail": "user1@gmail.com"}
# char-status ascii , binary buffer size 4 numbers , and json as is   ||send
# char-status , every bit to char to ascii * 256 בחזקת n , and json string  ||get


def main():
    runtime = 0
    with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as Csock:
        try:
            Csock.connect((HOST, PORT))
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