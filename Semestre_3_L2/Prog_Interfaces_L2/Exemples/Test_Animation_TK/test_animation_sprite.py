

# import matplotlib.image as mpimg

# A = mpimg.imread(r'D:/python/spritsheet2.gif')
# for i in range(9):
#     B = A[0:49, 32 * i :32 * (i + 1), 0:4]
#     mpimg.imsave(r'D:/python/B' + str(i) + '.gif', B)


from tkinter import *
from PIL import Image, ImageTk

f = Tk()
can = Canvas(f, width=500, height = 500)
can.pack()

def attackA_sprite(item = None, index = 1):
    can.delete(item)

    B = can.B = PhotoImage(file='./AttactA/attack-A' + str(index) + '.png')
    item = can.create_image(100, 200, anchor=NW, image = B)
    index += 1
    if index == 7:
        index = 1
    can.after(100, attackA_sprite, item, index)

def attackA_sprite2(item2 = None, index = 1):
    can.delete(item2)

    rotate = rotate_img('./AttactA/attack-A' + str(index) + '.png', 180)
    rotate.save('./AttactA/attack-B' + str(index) + '.png')
    B1 = f.B1 = PhotoImage(file='./AttactA/attack-B' + str(index) + '.png')
    item2 = can.create_image(100, 300, anchor=NW, image = B1)
    index += 1
    if index == 7:
        index = 1
    f.after(100, attackA_sprite2, item2, index)


def rotate_img(img_path, rt_degr) -> None:
    img = Image.open(img_path)
    return img.rotate(rt_degr, expand=1)

attackA_sprite()
attackA_sprite2()
f.mainloop()

