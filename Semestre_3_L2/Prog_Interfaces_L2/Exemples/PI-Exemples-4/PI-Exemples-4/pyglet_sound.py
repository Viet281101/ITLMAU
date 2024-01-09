from tkinter import *
from tkinter import filedialog
import pyglet
 
root = Tk()
root.title("Music Player")
root.geometry("500x600")
 
top_frame = Frame(root,width=500,height=400,bg="lightblue")
top_frame.pack(side=TOP)
 
bottom_frame = Frame(root,width=500,height=200,bg="lightgreen")
bottom_frame.pack(side=BOTTOM)
 
def browse_file():
    global filepath
    filepath = filedialog.askopenfilename(initialdir='../Desktop')
   
def play_song():
    global player
    player = pyglet.media.Player()
    src = pyglet.media.load(filepath)
    player.queue(src)
    player.play()
 
def stop_music():
    player.pause()
   
def resume_music():
    player.play()
 
button_play = Button(bottom_frame,text="Play",command=play_song)
button_play.place(x=100,y=50)
 
button_stop = Button(bottom_frame,text="Stop",command=stop_music)
button_stop.place(x=220,y=50)

button_resume = Button(bottom_frame,text="Pause",command=resume_music)
button_resume.place(x=350,y=50)
 
#img = PhotoImage(file='1.gif')
button_add_song = Button(top_frame,command=browse_file,text="browse")
button_add_song.pack()
 
root.resizable(False,False)
root.mainloop()