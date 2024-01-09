import tkinter as tk

on = 1
def close_frame(evt):
	global on, frame, lbx

	if on:
		frame.pack_forget()
		on = 0
	else:
		frame.pack_forget()
		frame1.pack_forget()
		create_frame()
		on = 1

root = tk.Tk()

def create_frame():
	"""create frame to be hidden when we press k"""
	global lbx, lbx1, frame, frame1

	frame = tk.Frame(root)
	frame.pack(side="left")
	lbx = tk.Listbox(frame, bg="gold")
	lbx.pack()
	lbx.insert(0, 1)
	frame1 = tk.Frame(root)
	frame1.pack()
	lbx1 = tk.Listbox(frame1, bg="black")
	lbx1.pack(side="left")
	lbx1.insert(0, 2)

create_frame()


root.bind("<Key>", close_frame)

root.mainloop()