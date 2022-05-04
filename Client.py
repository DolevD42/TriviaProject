import socket
import json
ZERO = 126


HOST = "127.0.0.1"  # The server's hostname or IP address
PORT = 8876  # The port used by the server
LOGIN = {"username": "user1", "password": "1234"}
SIGN_IN = {"username": "user1", "password": "1234", "mail": "user1@gmail.com"}
# char-status ascii , binary buffer size 4 numbers , and json as is   ||send first
# char-status , every bit to char to ascii * 256 בחזקת n , and json string  ||get


def decimalToBinary(n):
    # converting decimal to binary
    # and removing the prefix(0b)
    return bin(n).replace("0b", "")


def binary_to_dict(the_binary):
    jsn = ''.join(chr(int(x, 2)) for x in the_binary.split())
    d = json.loads(jsn)
    return d


def build_message(code, buffer, jsonC):
    code = ord(code)
    buffer = decimalToBinary(buffer)
    jsonC = bytes(json.dumps(jsonC), "utf-8")
    message = f"{code}{buffer}{jsonC}"
    return message


def getting_message(message):
    message = bytes(message).decode()
    messageLen = bytes(message[1:5])


def getting_status(message):
    status = message[0]
    return bytes(status)

def main():
    runtime = 0
    message = build_message('1', 5, LOGIN)
    message = "";
    message += chr(39)
    message += chr(ZERO)
    message += chr(ZERO);
    message += chr(ZERO);
    message += chr(41);

    message += '{"username": "user1", "password": "1234"}'
    print("client message: " + message)
    with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as Csock:
        try:
            Csock.connect((HOST, PORT))
            Csock.sendall(message.encode())
            data = Csock.recv(1024).decode()
            print("server response: " + data)
        except Exception as e:
            print(e)


if __name__ == '__main__':
    main()
