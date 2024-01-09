from tkinter import *
import pygame

pygame.mixer.init()

mon_audio = pygame.mixer.Sound("retro.wav")

def play():
    mon_audio.play(-1)
def stop():
    mon_audio.stop()

fen = Tk()
Button(fen, text="Play", command = play, width = 30).pack()
Button(fen, text="strop", command = stop, width = 30).pack()

fen.mainloop()