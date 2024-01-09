

from socket import *
from threading import *
from tkinter import *


HOST : str = "127.0.0.1"
PORT : int = 7500
ADDR : tuple = (HOST, PORT)
FORMAT : str = "utf-8"

clientSocket = socket(AF_INET, SOCK_STREAM)
clientSocket.setsockopt(SOL_SOCKET, SO_REUSEADDR, 1)

clientSocket.connect(ADDR)


window = Tk()
window.title("Connected To: " + HOST + ":" + str(PORT))

txtMessages = Text(window, width=50)
txtMessages.tag_configure("tag-right", justify="right")
txtMessages.tag_add("tag-right", 1.0, "end")
txtMessages.grid(row=0, column=0, padx=10, pady=10)

txtYourMessage = Entry(window, width=50)
txtYourMessage.insert(0, "Your message")
txtYourMessage.grid(row=1, column=0, padx=10, pady=10)

def sendMessage():
    clientMessage = txtYourMessage.get()
    txtMessages.insert(END, "\n" + "You: "+ clientMessage)
    clientSocket.send(clientMessage.encode(FORMAT))

btnSendMessage = Button(window, text="Send", width=20, command=sendMessage)
btnSendMessage.grid(row=2, column=0, padx=10, pady=10)

def recvMessage():
    while True:
        serverMessage = clientSocket.recv(1024).decode(FORMAT)
        print(serverMessage)
        txtMessages.insert(END, "\n"+serverMessage)

recvThread = Thread(target=recvMessage)
recvThread.daemon = True
recvThread.start()

window.iconphoto(False, PhotoImage(file=str("chat_ca.png")))
window.wm_attributes("-topmost", 1)
window.mainloop()





