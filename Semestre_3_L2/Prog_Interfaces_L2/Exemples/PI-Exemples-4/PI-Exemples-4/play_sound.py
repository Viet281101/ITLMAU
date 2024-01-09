# importing required module
from playsound import playsound 
from tkinter import*

fen = Tk()
fen.title('Music player') 
fen.geometry("300x150")

def play():
	playsound('retro.mp3')

title=Label(fen, text="Music player", bd=9,
			font=("times new roman", 25, "italic"), bg="white", fg="black")
title.pack(side=TOP, fill=X)

play_button = Button(fen, text="Play", font=("Helvetica", 22),
					relief=GROOVE, command=play)
play_button.pack(pady=20)

fen.mainloop()

