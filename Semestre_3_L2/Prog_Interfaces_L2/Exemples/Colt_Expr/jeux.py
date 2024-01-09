from tkinter import *
from PIL import ImageTk,Image
from random import *




class jeu(Tk):
    
    def __init__(self):
        super().__init__()
        
        

        
        
        
        #creation de la fenetre//////////////////////////////////////////////////////


        self.can=Canvas(self,width=1920,height=800,bg="black")
        self.can.pack(side=TOP,padx=0,pady=0)

        
        self.createEnemies()
        self.createEnemies()
        self.createEnemies()
        
        #creation du train grace a la classe wagon///////////////////////////////////


        self.wagon=wagon(self.can,270,655,"wagon4.png")
        self.wagon2=wagon(self.can,920,655,"wagon3.png")
        self.train=wagon(self.can,1550,655,"train.png")


        #initialitation des joueurs//////////////////////////////////////////////////
        self.player=player(self,self.can,240,445,1)
        self.player2=player(self,self.can,900,445,2)
        #les boutton pour ce deplacer////////////////////////////////////////////////
        self.deplacement=deplacement(self,self.player,self.player2,"x_d",'courir1.png')
        self.deplacement_g=deplacement(self,self.player,self.player2,"x_g",'courir2.png')
        self.deplacement_y=deplacement(self,self.player,self.player2,"monte",'monte.png')
        self.deplacement_t=deplacement(self,self.player,self.player2,"tire",'shoot1.png')


        self.deplacement_y.place(x=1745,y=100)
        self.deplacement.place(x=1645,y=100)
        self.deplacement_g.place(x=1545,y=100)
        self.deplacement_t.place(x=1445,y=100)

        #button2////////////

        self.deplacement2=deplacement(self,self.player2,self.player,"x_d",'courir1.png')
        self.deplacement_g2=deplacement(self,self.player2,self.player,"x_g",'courir2.png')
        self.deplacement_y2=deplacement(self,self.player2,self.player,"monte",'monte.png')
        self.deplacement_t2=deplacement(self,self.player2,self.player,"tire",'shoot1.png')


        self.deplacement_y2.place(x=1745,y=200)
        self.deplacement2.place(x=1645,y=200)
        self.deplacement_g2.place(x=1545,y=200)  
        self.deplacement_t2.place(x=1445,y=200)

        
        
        
        #////////////////////////////////////////////////////////////////////////////
        #self.player.placement()
        #self.player2.placement()
    def createEnemies(self):

        le_decore(self, self.can)
        self.after(900, self.createEnemies)

        
        
        
class player(): 

    def __init__(self,parent,can,pl_x,pl_y,position):
        
        self.parent=parent
        self.pos=1100
        self.can=can
        self.pl_x=pl_x
        self.pl_y=pl_y

        self.position=position
        self.position_y=1
        self.dirct=1
        self.son_img()
        print(self.can.coords(self.img_j))

    def tirer(self,enemie):

        if self.dirct==1:
            if (self.can.coords(self.img_j)[0]- enemie.can.coords(enemie.img_j)[0])<0 and self.position_y==enemie.position_y:
                print("toucher")
                print((self.can.coords(self.img_j)[0]- enemie.can.coords(enemie.img_j)[0]))

            else :
                print("pas toucher")
                print((self.can.coords(self.img_j)[0]- enemie.can.coords(enemie.img_j)[0]))
        else:

            if (self.can.coords(self.img_j)[0]- enemie.can.coords(enemie.img_j)[0])>0 and self.position_y==enemie.position_y:
                print("toucher")
                print((self.can.coords(self.img_j)[0]- enemie.can.coords(enemie.img_j)[0]))

            else :
                print("pas toucher")
                print((self.can.coords(self.img_j)[0]- enemie.can.coords(enemie.img_j)[0]))


                



        
    def son_img(self):
        #image quand direct == a 1 //////////////////////////////////////////////////////////////
        self.i = Image.open("joueur.png")
        self.new=self.i.resize((100,140), Image.ANTIALIAS)
        self.img= ImageTk.PhotoImage(self.new)
        self.img_j= self.can.create_image(self.pl_x, self.pl_y, image = self.img)
        
        #image quand direct == a -1/////////////////////////////////////////////////////////////////////////////////////////
        self.r= Image.open("player_re.png")
        self.new_r=self.r.resize((100,140), Image.ANTIALIAS)
        self.img_r= ImageTk.PhotoImage(self.new_r)

        self.direction()
        
    def placement(self,x,y):
        
        

        self.can.move(self.img_j, x,y)
        
        
    def direction(self):
        if self.dirct == 1:
            self.can.itemconfig(self.img_j, image = self.img)
            print("ffd")
        else:
            self.can.itemconfig(self.img_j, image = self.img_r)
            print("oooo")


        
        


class deplacement(Button):
    def __init__(self,fenetre : Tk,player,enemie,direction,la_photo):
        super().__init__(fenetre,width=100,height=100,bg="black")
        self.fen=fenetre
        #mettre en place l image/////////////////////////////////////////////////////////////////
        self.enemie=enemie
        self.la_photo=la_photo
        self.img=Image.open(la_photo)
        self.img=self.img.resize((100, 100))
        self.image=ImageTk.PhotoImage(self.img)
        self.config(image=self.image)
        #////////////////////////////////////////////////////////////////////////////////////////
    
        self.player=player
        self.direction=direction
        if self.direction == "x_d":
            self.config(command=self.x_d)
        elif self.direction == "x_g":
            self.config(command=self.x_g)
        elif self.direction == "monte":
            self.config(command=self.monte)
        elif self.direction == "tire":
            self.config(command=self.tire)



    def monte(self):
        global pl_y
        if self.player.position_y ==0:
            
            self.player.placement(0,-260)
            self.player.position_y+=1

        else:
            
            self.player.position_y-=1
            self.player.placement(0,260)

        

    #deplacement du player a droite////////////////////////////////////////////////////////////////////////
    def x_d(self,nb=0):
        
        if self.player.position!=3:
            
            self.player.dirct = 1
            self.player.direction()
            
            self.player.placement(550,0)
            self.player.position +=1
       

    #deplacement du player a gauche////////////////////////////////////////////////////////////////////////
    def x_g(self):
        global pl_x
        if self.player.position != 1:
            
            self.player.dirct = -1
            self.player.direction()
            
            self.player.placement(-550,0)
            self.player.position -=1
        
        
    def tire(self):
        self.player.tirer(self.enemie)
        




class wagon(): 

    def __init__(self,can,x,y,la_photo):
        
        self.can=can
        self.x=x
        self.y=y
        self.la_photo = la_photo

        self.son_img()

    def son_img(self):
        
        self.i = Image.open(self.la_photo)
        self.new=self.i.resize((650,300), Image.ANTIALIAS)
        self.img= ImageTk.PhotoImage(self.new)
        self.img_j= self.can.create_image(self.x, self.y, image = self.img)

    


class le_decore():
    
    def __init__(self,parent,canvas):
        self.parent = parent                    
        self.canvas = canvas                    
        self.player = player                    
                             
        
        self.fallSpeed = 50                          
        self.yPosition = randint(0, 370)        
        self.xPosition = randint(1900,2200)
        self.isgood = randint(0, 1)             
        self.vitesse = randint(-25,-10) 
        self.goodItems = ["etoile.png","etoileV2.png","etoileV3.png","etoileV4.png","nuage.png"]
        
        
        # create falling items
         
        self.itemPhoto = PhotoImage(file = "{}" .format( choice(self.goodItems) ) )
        self.fallItem = self.canvas.create_image( (self.xPosition ,self.yPosition) , image=self.itemPhoto , tag="good" )
        
            
        # trigger falling item movement
        self.placement_dc()
        
        
    def placement_dc(self):
        # dont move x, move y
        self.canvas.move(self.fallItem, self.vitesse, 0)
        
        if (self.canvas.coords(self.fallItem)[0] < -100):
            self.canvas.delete(self.fallItem)                                           
        else:
            self.parent.after(self.fallSpeed, self.placement_dc)                         
            
        
                                                                      
    





fen=jeu()

fen.mainloop()
