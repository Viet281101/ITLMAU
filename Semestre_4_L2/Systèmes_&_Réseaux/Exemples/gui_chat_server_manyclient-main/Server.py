

from socket import *
from threading import *


HOST : str = "127.0.0.1"
PORT : int = 7500
ADDR : tuple = (HOST, PORT)
FORMAT : str = "utf-8"

clients : set = set()

hostSocket = socket(AF_INET, SOCK_STREAM)
hostSocket.setsockopt(SOL_SOCKET, SO_REUSEADDR,1)

hostSocket.bind(ADDR)
hostSocket.listen()


def clientThread(clientSocket, clientAddress) -> None:
    while True:
        message = clientSocket.recv(1024).decode(FORMAT)
        print(clientAddress[0] + ":" + str(clientAddress[1]) +" says: "+ message)
        for client in clients:
            if client is not clientSocket:
                client.send((clientAddress[0] + ":" + str(clientAddress[1]) +" says: "+ message).encode(FORMAT))

        if not message:
            clients.remove(clientSocket)
            print(clientAddress[0] + ":" + str(clientAddress[1]) +" disconnected")
            break

    clientSocket.close()




def main() -> None:
    print ("Waiting for connection...")
    while True:
        clientSocket, clientAddress = hostSocket.accept()
        clients.add(clientSocket)
        print ("Connection established with: ", clientAddress[0] + ":" + str(clientAddress[1]))
        thread = Thread(target=clientThread, args=(clientSocket, clientAddress, ))
        thread.start()



if __name__ == "__main__":
    main()



