import socket

HOST = "127.0.0.1"  # The server's hostname or IP address
PORT = 8876  # The port used by the server



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
        except Exception as e:
            print(e)


if __name__ == '__main__':
    main()