from tkinter import *

app = Tk()
cnv = Canvas(app, bg="ivory", \
    height=200, width= 200)
cnv.pack()
cnv.create_oval(0, 0, 200, 200, \
    outline="red", width=10)
cnv.create_line(0, 0, 200, 200,\
    fill="black", width=10)
cnv.create_line(0, 200, 200, 0, \
    fill="black", width=10)
app.mainloop()
