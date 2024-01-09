

# import tkinter
# from tkinter import *


# top = tkinter.Tk()

# frame = Frame(top, width=1000, height=1000, background="bisque")
# frame.pack()

# bottomframe = Frame(top, width=1000, height=1000, background="red")
# bottomframe.pack( side = BOTTOM )


# def creatLayers(no_of_layers, max_nodes_in_each_layer, frame1=bottomframe):
#     print ('here2')

#     listLayerRect=[]
#     listDelimiterRect=[]

#     #The canvas is created here.
#     mainCanvas=tkinter.Canvas(frame1, bg="white", height=1000, width=1000)
#     mainCanvas.pack(side=LEFT)

#     for i in range (0,no_of_layers):            
#         print ('here3')

#         x=15*i

#         #rectangles that are being drawn on the canvas.
#         mainCanvas.create_polygon(x,0,x+10,0,x+10,1000,x,1000, outline='gray', fill='gray', width=2)

# #        listLayerRect.append(Tkinter.Canvas(frame1, bg="blue", height=1000, width=30))
# #        listDelimiterRect.append(Tkinter.Canvas(frame1, bg="yellow", height=1000, width=30))


# L1 = Label(frame, text="Layers")
# E1 = Entry(frame, bd =8)
# L2 = Label(frame, text="Layers2")

# def helloCallBack(E=E1,):
#    # tkMessageBox.showinfo( "Hello Python", "Hello World")
#    k=int(E.get())
#    print ('here')
#    print (k)

#    creatLayers(k,k)      

# B = tkinter.Button(frame, text ="Enter", command = helloCallBack)

# B.pack(side=LEFT)
# #L1.pack(side=LEFT)
# E1.pack(side=LEFT)
# #L2.pack(side=LEFT)

# top.mainloop()








from tkinter import *


window = Tk()
window.geometry("1200x700")
window.configure(bg = "#ffffff")


def btn_clicked():
    print("Button Clicked")

frame1 =Frame(window, width=1200, height=700)
frame1.grid(row=0, column=0)


def load_page():
    frame1.tkraise()
    frame1.pack_propagate(False)
    canvas = Canvas(
        frame1,
        bg = "#263ff8",
        height = 100,
        width = 200,
        bd = 10,
        highlightthickness = 0,
        relief = "ridge")
    canvas.place(x = 0, y = 0)

    #background_img = PhotoImage(file = f"background.png")
    #background = canvas.create_image(
        #601.0, 341.0,
        #image=background_img)

    #img0 = PhotoImage(file = f"img0.png")
    boton = Button(canvas,
        #image = img0,
        borderwidth = 0,
        highlightthickness = 0,
        command = btn_clicked,
        relief = "flat")

    boton.place(
        x = 85, y = 71,
        width = 30,
        height =29)
    

load_page()
window.resizable(False, False)
window.mainloop()




