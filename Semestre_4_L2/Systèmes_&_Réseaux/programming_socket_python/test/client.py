
import socket
import threading
from tkinter import *
import tkinter.scrolledtext
from tkinter import simpledialog
from datetime import datetime


HOST : str = socket.gethostbyname(socket.gethostname())
PORT : int = 5050
HEADER : int = 1024
FORMAT : str = "utf-8"



class Client:
    def __init__(self, host:str, port:int) -> None:
        
        self.socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        self.socket.connect((host, port))
        
        msg : tkinter.Tk = tkinter.Tk()
        msg.withdraw()
        
        self.nickname : str = simpledialog.askstring("Nickname", "Please choose a nickname", parent=msg)
        
        self.gui_done : bool = False
        self.running : bool = True
        
        self.gui_thread : threading.Thread = threading.Thread(target=self.gui_loop)
        self.receive_thread : threading.Thread = threading.Thread(target=self.receive)
        
        self.gui_thread.start()
        self.receive_thread.start()
        
    
    def gui_loop(self) -> None:
        self.win = tkinter.Tk()
        self.win.configure(bg="lightgray")
        
        self.chat_label = tkinter.Label(self.win, text="Chat:", bg="lightgray")
        self.chat_label.config(font=("Arial", 12))
        self.chat_label.pack(padx=20, pady=5)
        
        self.text_area = tkinter.scrolledtext.ScrolledText(self.win)
        self.text_area.pack(padx=20, pady=5)
        self.text_area.config(state="disabled")
        
        self.msg_label = tkinter.Label(self.win, text="Message:", bg="lightgray")
        self.msg_label.config(font=("Arial", 12))
        self.msg_label.pack(padx=20, pady=5)
        
        self.input_area = tkinter.Text(self.win, height=3)
        self.input_area.pack(padx=20, pady=5)
        
        self.send_button = tkinter.Button(self.win, text="Send", command=self.write)
        self.send_button.config(font=("Arial", 12))
        self.send_button.pack(padx=20, pady=5)
        
        self.gui_done = True
        self.win.protocol("WM_DELETE_WINDOW", self.stop)
        
        self.win.mainloop()
        
    
    def write(self) -> None:
        time : str = datetime.now().strftime("%H:%M:%S")
        message : str = f"{self.nickname} ~{time} : {self.input_area.get('1.0', END)}"
        self.socket.send(message.encode(FORMAT))
        self.input_area.delete("1.0", END)
        
    
    def receive(self) -> None:
        while self.running:
            try:
                message : str = self.socket.recv(HEADER).decode(FORMAT)
                if message == "NICK":
                    self.socket.send(self.nickname.encode(FORMAT))
                else:
                    if self.gui_done:
                        self.text_area.config(state="normal")
                        self.text_area.insert(END, message)
                        self.text_area.yview(END)
                        self.text_area.config(state="disabled")
            except ConnectionAbortedError:
                break
            except:
                print("An error occured!")
                self.socket.close()
                break
    
    
    def disconnect(self) -> None:
        self.socket.sendall("DISCONNECT".encode(FORMAT))
    
    
    def stop(self) -> None:
        self.running = False
        self.win.destroy()
        self.socket.close()
        exit(0)




client = Client(HOST, PORT)

