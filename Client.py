import socket
import json
#from bitarray import bitarray

ZERO = 126

HOST = "127.0.0.1"  # The server's hostname or IP address
PORT = 8876  # The port used by the server
LOGIN = {"username": "user1", "password": "1234"}
SIGN_IN = {"username": "user1", "password": "1234", "mail": "user1@gmail.com"}


# char-status ascii , binary buffer size 4 numbers , and json as is   ||send first
# char-status , every bit to char to ascii * 256 בחזקת n , and json string  ||get


def build_message(code, jsonC, sock):

    jsonC = json.dumps(jsonC)
    message = ''
    num = 0
    lenM = len(jsonC)
    for i in range(3, -1, -1):
        if i == 0:
            num = lenM
        else:
            num = int(lenM / pow(256, i))

        lenM = lenM - num
        if num == 0:
            num = 126
        message += chr(num)
    msgToSend = chr(code) + message + jsonC
    sock.sendall(msgToSend.encode())
    print("client message: " + msgToSend)


def getting_message(message):
    message = bytes(message).decode()
    messageLen = bytes(message[1:5])


def getting_status(message):
    status = message[0]
    return bytes(status)


def main():
    runtime = 0

    with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as Csock:
        try:
            Csock.connect((HOST, PORT))
            build_message(39, LOGIN, Csock)
            data = Csock.recv(1024).decode()
            print("server response: " + data)
        except Exception as e:
            print(e)


if __name__ == '__main__':
    main()
