


from tkinter import *

screen_width = 1920 // 2
screen_height = 1080 // 2
screen_geometry = '{}x{}'.format(screen_width, screen_height)

main_window = Tk()
main_window.title('Shop')
main_window.resizable(0, 0)
main_window.geometry(screen_geometry)

# background image
background_image = PhotoImage(file='red.png')
background_label = Label(main_window, image=background_image)
background_label.place(x=0, y=0, relwidth=1, relheight=1)

# keypad at the center of window
login_frame = Frame(main_window)
login_frame.place(relx=0.5, rely=0.5, anchor=CENTER)

display = Label(login_frame, bg='black', font=('', 20))
display.grid(row=0, column=0, columnspan=3, sticky='ew')

def input_digit(n):
    print(n)

font = ('', 16, 'bold')
numpad = []
for number in range(9):
    row = number // 3
    col = number % 3
    btn = Button(login_frame, text=number+1, font=font, width=5, height=2)
    btn.grid(row=row+1, column=col)
    btn.config(command=lambda n=number+1:input_digit(n))
    numpad.append(btn)

main_window.mainloop()

