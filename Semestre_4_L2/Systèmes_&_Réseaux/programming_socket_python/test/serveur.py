

import socket
import threading


HEADER : int = 1024
PORT : int = 5050
HOST : str = socket.gethostbyname(socket.gethostname())
# print(f"Server host is starting on {HOST}")
ADDR : tuple = (HOST, PORT)
FORMAT : str = "utf-8"


server : socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
server.bind(ADDR)


server.listen()


clients : list = []
nicknames : list = []


#### broadcast function
def broadcast(message : str) -> None:
    for client in clients:
        client.send(message)


#### handle function
def handle(client : socket.socket) -> None:
    while True:
        try:
            message : str = client.recv(HEADER).decode(FORMAT)
            print(f"{nicknames[clients.index(client)]} : {message}")
            broadcast(message)
        except:
            index : int = clients.index(client)
            clients.remove(client)
            client.close()
            nickname : str = nicknames[index]
            broadcast(f"{nickname} left the chat!\n".encode(FORMAT))
            nicknames.remove(nickname)
            break


#### receive function
def receive() -> None:
    while True:
        client, addr = server.accept()
        print(f"Connected with {str(addr)}!")
        
        client.send("NICK".encode(FORMAT))
        nickname : str = client.recv(HEADER).decode(FORMAT)
        
        nicknames.append(nickname)
        clients.append(client)
        
        print(f"Nickname of the client is {nickname}!")
        broadcast(f"{nickname} joined the chat!\n".encode(FORMAT))
        client.send("Connected to the server!".encode(FORMAT))
        
        thread : threading.Thread = threading.Thread(target=handle, args=(client,))
        thread.start()



#### main function
def main() -> None:
    print(f"Server is listening on {HOST}")
    receive()
    print("Server is closed!")
    


if __name__ == "__main__":
    main()


