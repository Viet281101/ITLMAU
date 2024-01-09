from tkinter import *
import sys
import random
import time
 
class Player:
 
    def __init__(self, canvas, x, y):
         
        self.canvas = canvas
        self.id = canvas.create_oval(0, 0, 20, 20, fill='blue')
        self.canvas.move(self.id, x, y)
        self.canvas_height = 600
        self.canvas_width = 600
 
    def move_left(self):
         
        pos = self.canvas.coords(self.id)
        if pos[0] > 0:
            self.canvas.move(self.id, -20, 0)
            bot_move(Game.bot_list)
 
    def move_up_left(self):
         
        pos = self.canvas.coords(self.id)
        if pos[0] > 0 and pos[1] > 0:
            self.canvas.move(self.id, -20, -20)
            bot_move(Game.bot_list)
             
    def move_down_left(self):
         
        pos = self.canvas.coords(self.id)
        if pos[0] > 0 and pos[3] < self.canvas_height:
            self.canvas.move(self.id, -20, 20)
            bot_move(Game.bot_list)
 
    def move_right(self):
         
        pos = self.canvas.coords(self.id)
        if pos[2] < self.canvas_width:
            self.canvas.move(self.id, 20, 0)
            bot_move(Game.bot_list)
 
    def move_up_right(self):
         
        pos = self.canvas.coords(self.id)
        if pos[2] < self.canvas_width and pos[1] > 0:
            self.canvas.move(self.id, 20, -20)
            bot_move(Game.bot_list)
 
    def move_down_right(self):
         
        pos = self.canvas.coords(self.id)
        if pos[2] < self.canvas_width and pos[3] < self.canvas_height:
            self.canvas.move(self.id, 20, 20)
            bot_move(Game.bot_list)
 
    def move_down(self):
         
        pos = self.canvas.coords(self.id)
        if pos[3] < self.canvas_height:
            self.canvas.move(self.id, 0, 20)
            bot_move(Game.bot_list)
 
    def move_up(self):
         
        pos = self.canvas.coords(self.id)
        if pos[1] > 0:
            self.canvas.move(self.id, 0, -20)
            bot_move(Game.bot_list)
 
    def wait(self):
         
        bot_move(Game.bot_list)
 
    def teleport(self):
         
        pos = self.canvas.coords(self.id)
        random_x = random.choice(list(range(0,581,20)))
        random_y = random.choice(list(range(0,581,20)))
        self.canvas.move(self.id, (random_x - pos[0]), (random_y - pos[1]))
        bot_move(Game.bot_list)
 
    def safe_port(self):
 
        range_x = list(range(0,581,20))
        range_y = list(range(0,581,20))
        range_tuples = []
        for i in range_x:
            for j in range_y:
                new_tuple = (i,j)
                range_tuples.append(new_tuple)
 
        pos = self.canvas.coords(self.id)
        bot_pos = []
        bot_ID_list = list(self.canvas.find_withtag('bot'))
        for i in bot_ID_list:
            i_pos = self.canvas.coords(i)
            bot_pos_tuple = (i_pos[0], i_pos[1])
            bot_pos.append(bot_pos_tuple)
 
        safe_tuples = []
        safe_tuples = [a for a in range_tuples if a not in bot_pos]
        safe_port_loc = random.sample(safe_tuples, 1)
 
        random_x = safe_port_loc[0][0]
        random_y = safe_port_loc[0][1]
        self.canvas.move(self.id, (random_x - pos[0]), (random_y - pos[1]))
 
 
class Bot:
 
    def __init__(self, canvas, player, x, y):
         
        self.canvas = canvas
        self.player = player
        self.id = canvas.create_rectangle(0, 0, 20, 20, fill='red', tags='bot')
        self.start_x = x
        self.start_y = y
        self.dead = False
        self.canvas.move(self.id, self.start_x, self.start_y)
 
    def draw(self):
         
        self.x = 0
        self.y = 0
        pos = self.canvas.coords(self.id)
        player_pos = self.canvas.coords(self.player.id)
        if pos[0] >= player_pos[2]:
            self.x = -20
        if pos[2] <= player_pos[0]:
            self.x = 20
        if pos[1] >= player_pos[3]:
            self.y = -20
        if pos[3] <= player_pos[1]:
            self.y = 20
        self.canvas.move(self.id, self.x, self.y)
 
    def hit_player(self):
        pos = self.canvas.coords(self.id)
        player_pos = self.canvas.coords(self.player.id)
        if pos == player_pos:
            time.sleep(.35)
            self.canvas.create_text(300, 50, text = 'GAME', font = ('Arial', 50))
            self.canvas.create_text(300, 200, text = 'OVER!', font = ('Arial', 50))
            self.canvas.create_text(300, 375, text = 'Hit V to play again or X to exit.', font = ('Arial', 35))
            Game.game_over = True
            return True
 
    def hit_bot(self):
        bot_ID_list = list(self.canvas.find_withtag('bot'))
        bot_ID_list.remove(self.id)
        pos = self.canvas.coords(self.id)
 
        for i in bot_ID_list:
            bot_pos = self.canvas.coords(i)
            if pos == bot_pos:
                self.canvas.itemconfig(self.id, fill='black')
                return True
 
    def bot_zapped(self, tuples):
         
        bot_pos = self.canvas.coords(self.id)
        bot_tuple = (bot_pos[0], bot_pos[1])
        if bot_tuple in tuples:
            self.canvas.delete(self.id)
            return True
        return False
 
 
class Game:
 
    bot_list = []
    game_over = False
    score = 0
    zap_count = 1
    safeprt_count = 1
     
    def __init__(self):
        self.tk = Tk()
        self.tk.title("Robots!")
        self.tk.resizable(0, 0)
        self.tk.wm_attributes("-topmost", 1)
        self.game_round = 1
        self.round_over = False
        self.rt_id = None
        self.st_id = None
        self.zap_id = None
        self.start_round()
        self.tk.mainloop()
         
    def start_round(self):
 
        if self.round_over == True and self.canvas is not None:
            self.canvas.destroy()
            self.game_round += 1
            self.rt_id = None
            self.st_id = None
            self.zap_id = None
            self.round_over = False
        self.canvas = Canvas(self.tk, width=800, height=600, bd=0, highlightthickness=0)
        self.canvas.create_rectangle(0, 0, 600, 600, fill='ivory')
        self.canvas.create_line(600, 0, 600, 600)
         
        Game.zap_count = 1
        Game.safeprt_count = 1
        self.display_stats()
        self.canvas.pack()
        self.canvas.bind_all('<KeyPress-Left>', self.player_move_left)
        self.canvas.bind_all('<KeyPress-4>', self.player_move_left)
        self.canvas.bind_all('<KeyPress-Home>', self.player_move_up_left)
        self.canvas.bind_all('<KeyPress-7>', self.player_move_up_left)
        self.canvas.bind_all('<KeyPress-End>', self.player_move_down_left)
        self.canvas.bind_all('<KeyPress-1>', self.player_move_down_left)
        self.canvas.bind_all('<KeyPress-Right>', self.player_move_right)
        self.canvas.bind_all('<KeyPress-6>', self.player_move_right)
        self.canvas.bind_all('<KeyPress-Prior>', self.player_move_up_right)
        self.canvas.bind_all('<KeyPress-9>', self.player_move_up_right)
        self.canvas.bind_all('<KeyPress-Next>', self.player_move_down_right)
        self.canvas.bind_all('<KeyPress-3>', self.player_move_down_right)
        self.canvas.bind_all('<KeyPress-Up>', self.player_move_up)
        self.canvas.bind_all('<KeyPress-8>', self.player_move_up)
        self.canvas.bind_all('<KeyPress-Down>', self.player_move_down)
        self.canvas.bind_all('<KeyPress-2>', self.player_move_down)
        self.canvas.bind_all('<KeyPress-b>', self.player_wait)
        self.canvas.bind_all('<KeyPress-a>', self.player_safe_port)        
        self.canvas.bind_all('<KeyPress-Return>', self.player_teleport)
        self.canvas.bind_all('<KeyPress-space>', self.player_zap)
        self.canvas.bind_all('<KeyPress-v>', self.restart_round)
        self.canvas.bind_all('<KeyPress-X>', self.end_game)
        self.canvas.bind_all('<KeyPress-x>', self.end_game)

         
        self.bot_count = self.game_round * 5
        Game.bot_list = []
        range_x = list(range(0,581,20))
        range_y = list(range(0,581,20))
        range_tuples = []
        for i in range_x:
            for j in range_y:
                new_tuple = (i,j)
                range_tuples.append(new_tuple)
        random_tuple = random.sample(range_tuples, self.bot_count + 1)
         
        self.player = Player(self.canvas, random_tuple[0][0], random_tuple[0][1])
         
        Game.bot_list = [Bot(self.canvas, self.player, random_tuple[i + 1][0], \
                        random_tuple[i + 1][1]) for i in range(0, self.bot_count)]
 
    def player_move_left(self, evt):
         
        if Game.game_over == False:
            self.player.move_left()
            self.advance_turn()
                 
    def player_move_up_left(self, evt):
         
        if Game.game_over == False:
            self.player.move_up_left()
            self.advance_turn()
             
    def player_move_down_left(self, evt):
         
        if Game.game_over == False:
            self.player.move_down_left()
            self.advance_turn()
             
    def player_move_right(self, evt):
         
        if Game.game_over == False:
            self.player.move_right()
            self.advance_turn()
             
    def player_move_up_right(self, evt):
         
        if Game.game_over == False:
            self.player.move_up_right()       
            self.advance_turn()
         
    def player_move_down_right(self, evt):
         
        if Game.game_over == False:
            self.player.move_down_right()
            self.advance_turn()
 
    def player_move_up(self, evt):
         
        if Game.game_over == False:
            self.player.move_up()
            self.advance_turn()
         
    def player_move_down(self, evt):
         
        if Game.game_over == False:
            self.player.move_down()
            self.advance_turn()
         
    def player_wait(self, evt):
         
        if Game.game_over == False:
            self.player.wait()
            self.advance_turn()
         
    def player_teleport(self, evt):
         
        self.player.teleport()
        self.advance_turn()
 
    def player_zap(self, evt):
         
        if Game.game_over == False and Game.zap_count > 0:
            Game.zap_count -= 1
            player_pos = self.canvas.coords(self.player.id)
            touching_x = [(player_pos[0] - 20), player_pos[0], (player_pos[0] + 20)]
            touching_y = [(player_pos[1] - 20), player_pos[1], (player_pos[1] + 20)]
            touching_tuples = []
            for i in touching_x:
                for j in touching_y:
                    new_tuple = (i, j)
                    touching_tuples.append(new_tuple)
            for i in Game.bot_list:
                if i.dead == False and i.bot_zapped(touching_tuples) == True:
                    i.dead = True
                    Game.score += 20
        self.advance_turn()
 
    def player_safe_port(self, evt):
         
        if Game.game_over == False and Game.safeprt_count > 0:
            Game.safeprt_count -= 1
            self.player.safe_port()
            self.advance_turn()

    def wait_cycle(self):
         
        if Game.game_over == False and self.round_over == False:
            self.player.wait()
            self.tk.update()
            time.sleep(.15)
            if round_end(Game.bot_list) == True:
                self.round_over = True
                Game.score += 50
                self.start_round()
                return
            elif Game.game_over == False and self.round_over == False:
                self.tk.after(1, self.wait_cycle())
 
    def advance_turn(self):
         
        if round_end(Game.bot_list) == True:
            self.round_over = True
            Game.score += 50
            self.start_round()
        self.display_stats()
 
    def display_stats(self):
         
        round_text = 'Tour: ' + str(self.game_round)
        score_text = 'Score: ' + str(Game.score)
        zaps_text = 'Zapper: ' + str(Game.zap_count)
        ports_text = 'Teleportation: ' + str(Game.safeprt_count)
        instruction_text = 'Instructions:\nSe déplacer avec le clavier\n<a> Se téleporter\n<Return> Déplacement aléatoire\n<b> Attendre un tour\n<Space> Zapper les robots adjacents'
        if self.rt_id is not None and self.st_id is not None and\
           self.zap_id is not None and self.sp_id is not None:
            self.canvas.itemconfig(self.rt_id, text = round_text)
            self.canvas.itemconfig(self.st_id, text = score_text)
            self.canvas.itemconfig(self.zap_id, text = zaps_text)
            self.canvas.itemconfig(self.sp_id, text = ports_text)
        else:
            self.rt_id = self.canvas.create_text(700, 100, text = round_text, font = ('Arial', 15))
            self.st_id = self.canvas.create_text(700, 150, text = score_text, font = ('Arial', 15))
            self.zap_id = self.canvas.create_text(700, 250, text = zaps_text, font = ('Arial', 15))
            self.sp_id = self.canvas.create_text(700, 300, text = ports_text, font = ('Arial', 15))
            self.instruct = self.canvas.create_text(700, 400, text = instruction_text, justify='left', font = ('Arial', 10))
             
    def end_game(self, evt):
         
        if Game.game_over == True:
            self.tk.destroy()
            sys.exit()
 
    def restart_round(self, evt):
         
        if Game.game_over == True:
            self.rt_id = None
            self.game_round = 1
            self.canvas.destroy()
            Game.bot_list = []
            Game.game_over = False
            Game.score = 0
            Game.zap_count = 1
            Game.safeprt_count = 1
            self.start_round()
 
def bot_move(bot_list):
     
    for i in bot_list:
        if i.dead == False:
            i.draw()
    for i in bot_list:
        if i.hit_player() == True:
            Game.game_over = True
        if i.dead == False and i.hit_bot() == True:
            Game.score += 20
            i.dead = True                
 
def round_end(bot_list):
     
    bots_alive = False
    for i in bot_list:
        if i.dead == False:
            bots_alive = True
    if bots_alive == True:
        return False
    return True
            
Game()
