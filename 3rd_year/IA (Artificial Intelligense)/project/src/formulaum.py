import pygame as pg
import pygame_menu
from pathlib import Path
from graph import Graph
from generator import Map
import node




class Interface:
    def __init__(self):
        self.input_file_name = ""
        self.paths_points = [] # lista de listas
        self.paths_full = [] # lista de listas
        self.value_map = []
        self.txt_map = []
        self.l = 20 # aka height
        self.c = 20 # aka width
        self.g = Graph()
        self.map = Map()
        self.dif = int(600 / self.c) #px
        self.mainmenu = None
        self.gen_menu = None
        self.editmap = None
        self.editor_screen = None
        self.mouse_x = 0
        self.mouse_y = 0
        self.font1 = pg.font.SysFont("sans serif", 5)
        self.font2 = pg.font.SysFont("sans serif", 20)
        self.surface = pg.display.set_mode((600, 400))
        self.search_type = 1


    def load_map(self):
        #try:
            self.txt_map = []
            self.value_map = []
            self.g.clear_map()
            self.read_file()
            self.edit_map()
        #except:
        #    print("Mapa não existe")

    def generate_map(self):
        self.txt_map = []
        self.value_map = []
        self.g.clear_map()
        self.txt_map = self.map.generate(self.c,self.l)
        self.convert_map()
        self.edit_map()

        #self.edit_map()
        #os.system("cat " + file_name)

    def read_file(self):
        self.txt_map = []
        with open(self.input_file_name, 'r') as f:
            lines = f.readlines()
        for l in lines:
            line = []
            for c in l:
                line.append(c)
            self.txt_map.append(line)
        self.convert_map()
    
    def get_map(self):
        return self.txt_map

    def set_input_file_name(self,map_input_file):
        self.input_file_name = ""
        source_path = Path(__file__).resolve()
        inputs_dir = str(source_path.parent.parent) + '/labyrinths/'
        file = inputs_dir + str(map_input_file) + ".txt"
        self.input_file_name = file
    
    def set_map_width(self,map_width):
        if map_width == '' or int(map_width) <= 0: map_width = 1
        self.c = int(map_width)
        self.dif = int(600 / self.c)
    
    def set_map_height(self,map_height):
        if map_height == '': map_height = 1
        self.l = int(map_height)
    
    # Highlight the cell selected
    def draw_box(self):
        for i in range(2):
            pg.draw.line(self.editor_screen, (150, 100, 100), (self.mouse_x * self.dif, (self.mouse_y + i)*self.dif), (self.mouse_x * self.dif + self.dif, (self.mouse_y + i)*self.dif), 2)
            pg.draw.line(self.editor_screen, (150, 100, 100), ( (self.mouse_x + i)* self.dif, self.mouse_y * self.dif ), ((self.mouse_x + i) * self.dif, self.mouse_y * self.dif + self.dif), 2)
    
    # Fill value entered in cell	
    def draw_val(self,val):
        text1 = self.font1.render(str(val), 1, (0, 0, 0))
        self.editor_screen.blit(text1, (self.mouse_x * self.dif + 15, self.mouse_y * self.dif + 15))

    def valid(self, i, j,val):
        if i > self.c or i < 0 or j > self.l or j < 0:
            return False
        if val == 4 or val == 2:
            return True
        else: return (self.value_map[i][j] != 1)

    def get_cord(self,pos):
        self.mouse_x = pos[0]//self.dif
        self.mouse_y = pos[1]//self.dif

    def get_type(self,val):
        if val == 3:
            ret = "P"
        elif val == 4:
            ret = "F"
        else:
            ret = "X"
        return ret

    def clear_paths(self):
        self.paths_full = []
        self.paths_points = []
        self.g.clear_path()

    def run_search(self):
        self.clear_paths()
        self.save()
        self.g.generate_graph(self.input_file_name)

        # if not changed, main menu's search type selector stores a "selector class" into the search_type variable
        if self.search_type == 1 or type(self.search_type) != int : #default BFS
            self.paths_full = self.g.searchBFS()
            
        elif self.search_type == 2: #GCA
            (self.paths_full,self.paths_points) = self.g.searchGCA()
        

        if self.search_type == 3: #A*
            #(self.path_full,self.path_points) = self.g.searchAstar()
            self.paths_full = self.g.searchAestrela()

        if self.search_type == 4: #DFS
            self.paths_full= self.g.searchDFS()
        




    # Display instruction for the game
    def instruction(self):
        color = (206, 212, 218)
        text1 = self.font2.render("P - INSERIR PLAYER", 1, color)
        text2 = self.font2.render("F - INSERIR LINHA DE META", 1, color)
        text3 = self.font2.render("R - RESET AO MAPA", 1, color)
        text4 = self.font2.render("S - GUARDAR MAPA", 1, color)
        text5 = self.font2.render("ENTER - COMEÇAR PROCURA", 1, color)
        text6 = self.font2.render("W - COLOCAR PAREDE", 1, color)
        text7 = self.font2.render("C - COLOCAR CAMINHO", 1, color)


        self.editor_screen.blit(text1, (20, 610))
        self.editor_screen.blit(text2, (20, 630))
        self.editor_screen.blit(text3, (20, 650))
        self.editor_screen.blit(text4, (20, 670))
        self.editor_screen.blit(text5, (20, 690))
        self.editor_screen.blit(text6, (220, 610))
        self.editor_screen.blit(text7, (220, 630))



    # opens map editor
    def edit_map(self):
        self.editor_screen = pg.display.set_mode((600, 720))
        run = True
        flag1 = 0
        flag2 = 0
        rs = 0
        error = 0
        val = 0
        # The loop thats keep the window running
        while run:
            
            # dark color background
            self.editor_screen.fill((33, 37, 41))
            # Loop through the events stored in event.get()
            for event in pg.event.get():
                # Quit the game window
                if event.type == pg.QUIT:
                    run = False
                # Get the mouse position to insert car or finish line
                if event.type == pg.MOUSEBUTTONDOWN:
                    flag1 = 1
                    pos = pg.mouse.get_pos()
                    self.get_cord(pos)
                # Get the number to be inserted if key pressed
                if event.type == pg.KEYDOWN:
                    if event.key == pg.K_LEFT:
                        self.mouse_x-= 1
                        flag1 = 1
                    if event.key == pg.K_RIGHT:
                        self.mouse_x+= 1
                        flag1 = 1
                    if event.key == pg.K_UP:
                        self.mouse_y-= 1
                        flag1 = 1
                    if event.key == pg.K_DOWN:
                        self.mouse_y+= 1
                        flag1 = 1
                    if event.key == pg.K_p:
                        val = 3
                        flag1 = 1
                    if event.key == pg.K_f:
                        val = 4
                        flag1 = 1
                    if event.key == pg.K_w:
                        val = 1
                        flag1 = 1
                    if event.key == pg.K_c:
                        val = 2
                        flag1 = 1
                    if event.key == pg.K_RETURN:
                        flag2 = 0
                        self.run_search()
                        flag2 = 1
                    if event.key == pg.K_s:
                        flag2 = 0
                        self.save()
                    if event.key == pg.K_r:
                        rs = 1
                        flag2 = 0
                    if event.key == pg.K_ESCAPE:
                        run = False
            if val != 0:
                if self.valid(int(self.mouse_y), int(self.mouse_x),val) == True:
                    if self.value_map[int(self.mouse_y)][int(self.mouse_x)] == 3 and val == 3: # se já tem um player na posição tira
                        val = 2
                    self.value_map[int(self.mouse_y)][int(self.mouse_x)] = val
                    self.txt_map[int(self.mouse_y)][int(self.mouse_x)] = self.get_type(val)
                    flag1 = 0
                    self.draw_val(val)
                val = 0
            if rs != 0:
                try:
                    self.read_file()
                except:
                    print("Não tens backups prévios deste mapa")
                rs = 0

            self.draw_map()
            if flag1 == 1:
                self.draw_box()
            if flag2 == 1:
                self.draw_path()
            self.instruction()
            # Update window
            pg.display.update()
        self.surface = pg.display.set_mode((600, 400))

    def set_search_type(self, value, type):
        self.search_type = type
    
    def main_menu(self):
        self.mainmenu = pygame_menu.Menu('FormulaUM', 600, 400, theme=pygame_menu.themes.THEME_DARK)

        self.mainmenu.add.text_input('Mapa: ', default=self.input_file_name, copy_paste_enable=True, onchange=self.set_input_file_name)    

        self.mainmenu.add.button('Carregar mapa', self.load_map)
        self.mainmenu.add.button('Novo mapa', self.generate_map_menu) #leva ao menu de gerar um mapa


        self.search_type = self.mainmenu.add.selector('Tipo de procura :', [('BFS', 1), ('GCA+', 2), ('A*',3), ('DFS',4)], onchange=self.set_search_type)

        self.mainmenu.add.button('Quit', pygame_menu.events.EXIT)

        self.mainmenu.mainloop(self.surface)

    def generate_map_menu(self):
        self.gen_menu = pygame_menu.Menu('Novo mapa', 600, 400, theme=pygame_menu.themes.THEME_DARK)
        map_height = self.gen_menu.add.text_input('Altura: ', default=self.l, copy_paste_enable=True, onchange=self.set_map_height)
        map_width = self.gen_menu.add.text_input('Largura: ', default=self.c, copy_paste_enable=True, onchange=self.set_map_width)
        self.gen_menu.add.button('Gerar mapa', self.generate_map)
        self.mainmenu._open(self.gen_menu)

    def save(self):
        with open(self.input_file_name, 'w') as f:
            for l in self.value_map:
                for value in l:
                    if value == 1:
                        c = 'X'
                    elif value == 2:
                        c = '-'
                    elif value == 3:
                        c = 'P'
                    elif value == 4:
                        c = 'F'
                    else:
                        continue
                    f.write(c + ' ')
                f.write('\n')

    def convert_map(self):
        lines = 0
        self.value_map = []
        for l in self.txt_map:
            cols = 0
            row = []
            for c in l:
                
                if c=='X':
                    value = 1
                elif c=='-':
                    value = 2
                elif c=='P':
                    value = 3
                elif c=='F':
                    value = 4
                else:
                    continue
                cols += 1
                row.append(value)
            lines += 1
            self.value_map.append(row)
        self.set_map_width(cols)
        self.set_map_height(lines)

    # coloring the map
    def draw_map(self):
        finish_line_count = 0
        for l in range (self.l):
            for c in range (self.c):
                if self.value_map[l][c] == 1: #wall - green
                    pg.draw.rect(self.editor_screen, (98, 148, 96), (c * self.dif, l * self.dif, self.dif + 1, self.dif + 1))
                if self.value_map[l][c] == 2: #floor - grey
                    pg.draw.rect(self.editor_screen, (150, 190, 140), (c * self.dif, l * self.dif, self.dif + 1, self.dif + 1))
                if self.value_map[l][c] == 3: #player - blue
                    pg.draw.rect(self.editor_screen, (40,138,173), (c * self.dif, l * self.dif, self.dif + 1, self.dif + 1))
                if self.value_map[l][c] == 4: #finish - b&w
                    if finish_line_count%2 == 0: color = (254,254,227)
                    else: color = (54,54,54)
                    finish_line_count += 1
                    pg.draw.rect(self.editor_screen, color, (c * self.dif, l * self.dif, self.dif + 1, self.dif + 1))
                if self.value_map[l][c] == 5: #path points - red
                    pg.draw.rect(self.editor_screen, (251,97,7), (c * self.dif, l * self.dif, self.dif + 1, self.dif + 1))
                if self.value_map[l][c] == 6: #full path - yellow
                    pg.draw.rect(self.editor_screen, (243,222,54), (c * self.dif, l * self.dif, self.dif + 1, self.dif + 1))

    def draw_path(self):
        if len(self.paths_full) > 0:
            for path_full in self.paths_full:
                for node in path_full:
                    (l,c) = node.getPos()
                    pg.draw.rect(self.editor_screen, (243,222,54), (l * self.dif, c * self.dif, self.dif + 1, self.dif + 1))
            for path_points in self.paths_points:
                for node in path_points:
                    (l,c) = node.getPos()
                    pg.draw.rect(self.editor_screen, (238, 75, 43), (l * self.dif, c * self.dif, self.dif + 1, self.dif + 1))

def main():
    i = Interface()
    i.main_menu()

    

if __name__ == '__main__':
    pg.init()
    pg.font.init()
    pg.display.set_caption("FormulaUM")
    main()
    pg.quit()
