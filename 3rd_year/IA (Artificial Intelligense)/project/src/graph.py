import numpy as np
from car import car
from math import inf
from queue import Queue
from node import Node


class Graph:

    def __init__(self, directed=False):
        '''
        Constructor of class Graph

        Parameters:
        directed (Boolean): If graph is oriented or not
        '''
        # self.g_nodes = []   # lista de nodos do grafo (nodos)
        self.g_nodes = {}   # dicionário de nodos do grafo (nodos)
        # se o grafo é direcionado ou nao (boolean)
        self.g_directed = directed
        # dicionario para armazenar os nodos, arestas  e pesos (int:set(nodo,custo))
        self.g_graph = {}
        self.g_h = {}         # dicionário para armazenar heuristica para cada nodo
        self.map_height = 0
        self.map_width = 0
        self.paths = []  # lista de listas de nodos
        self.complete_paths = []
        self.players = []  # lista de ids dos nodos player
        self.players_cars = []  # lista de carros dos player
        self.finish = []  # ids da meta
        self.map = []  # map of ids
        self.map_mat = None

    # string representation of the graph
    def __str__(self):
        res = ""
        for key in self.g_graph.keys():
            res = res + "node " + str(key) + ": " + \
                str(self.g_graph[key]) + "\n"
        return res

    def add_edge(self, n1, n2, weight):
        '''
        Method that given two nodes (object) add weighted edge

        Parameters:
        n1 (Object): Node object
        n2 (Object): Node object
        weight (int): Weight of edge
        '''
        node1 = n1.getId()  # gets the node id
        node2 = n2.getId()  # gets the node id
        if (n1 not in self.g_nodes.keys()):
            self.g_nodes[node1] = n1
            self.g_graph[node1] = set()
        else:
            n1 = self.g_nodes.get(node1)

        if (n2 not in self.g_nodes):
            self.g_nodes[node2] = n2
            self.g_graph[node2] = set()
        else:
            n2 = self.g_nodes.get(node2)

        self.g_graph[node1].add((n2, weight))

    def get_edges(self, row_length):
        '''
        Getter that make connection between all nodes

        Parameters:
        row_length (int): Length of matrix row
        '''
        total_nodes = len(self.g_nodes)
        for n1 in self.g_nodes.keys():
            neighbours = self.search_neighbours(n1)
            for id in neighbours:
                if id < total_nodes and id >= 0:
                    node2 = self.get_node_by_id(id)
                    weight = self.get_weight(node2.getType())
                    self.g_graph[n1].add((node2, weight))

    def print_edge(self):
        '''
        Method that prints all graph edges

        Return:
        String of all graph edges
        '''
        listE = ""
        for nodo in self.g_graph.keys():
            for (nodo2, cost) in self.g_graph[nodo]:
                listE = listE + nodo + " ->" + \
                    nodo2 + " cost:" + str(cost) + "\n"
        return listE

    def get_node_by_id(self, id):
        '''
        Getter for node of certaing id

        Parameters:
        id (String): ID of wanted node

        Return:
        Node of certain id
        '''
        return self.g_nodes.get(id)

    def generate_graph(self, map_input):
        '''
        Function that generates map based on a txt file input

        Parameter:
        map_inpput (String): Path to file
        '''
        self.clear_map()
        len = self.parser(map_input)
        self.get_edges(len)
        # print(self.g_nodes.values()) # NOTE: Prints in terminal dictionary

    def parser(self, map_input):
        '''
        Method that parsers txt_file into graph modes

        Parameters:
        map_input (String): Path to file

        Return:
        Amount of nodes in graph
        '''
        ids = 0
        y = 0
        x = 0
        row=[]

        with open(map_input) as txt:
            lines = txt.readlines()

        for l in lines:
            row = []
            id_row = []
            x = 0
            for c in l:

                if c == 'X':
                    node = Node(ids, "WALL", x, y)
                    self.g_h[ids] = 50
                elif c == '-':
                    node = Node(ids, "PATH", x, y)
                    self.g_h[ids] = 1
                elif c == 'P':
                    node = Node(ids, "PLAYER", x, y)
                    self.players.append(ids)
                    self.g_h[ids] = 0
                elif c == 'F':
                    node = Node(ids, "FINISH", x, y)
                    self.finish.append(ids)
                    self.g_h[ids] = 0
                else:
                    continue

                self.g_nodes[node.getId()] = node
                self.g_graph[ids] = set()
                row.append(node)
                id_row.append(ids)
                x += 1
                ids += 1
            self.map.append(id_row)
            y += 1
            self.map_height = y
            self.map_width = x
        self.graph2map()
        return len(row)

    def get_weight(self, type):
        '''
        Method that gets weight of certain piece given type

        Parameters:
        type (Boolean): Type of piece, if is inside of map or not

        Return:
        Weight of certain component in map, if is outside disponible path is 25 else is 1
        '''
        if type:
            return 1
        else:
            return 25

    def get_arc_cost(self, node1, node2):
        '''
        Method that gets cost between given nodes

        Parameters:
        node1 (String): ID of node
        node2 (String): ID of node

        Return:
        Cost between given nodes
        '''
        custoT = inf
        a = self.g_graph[node1]    # lista de arestas para aquele nodo
        for (nodo, custo) in a:
            if nodo == node2:
                custoT = custo

        return custoT

    def calcule_cost(self, caminho):
        '''
        Method that after calculates cost of given path by adding all nodes weight

        Parameters:
        caminho (array): array of node id's that make part of result path 

        Return:
        Cost of path
        '''
        teste = caminho
        custo = 0
        i = 0
        while i+1 < len(teste):
            custo = custo + self.get_arc_cost(teste[i], teste[i+1])
            i = i+1
        return custo

    def searchBFS(self):
        '''
        High level BFS functions caller
        '''
        #TODO: tirar for loop
        # o loop corre a procura para um player de cada vez
        # é suposto adaptar o algoritmo para receber a lista de players (self.players) e ele próprio iterar por cada um deles
        for player in self.players:
            start = self.get_node_by_id(player)
            
            # este loop pode manter-se, só pega nos ids dos nodos da meta e coloca numa lista de nodos para passar ao BFS
            end = []
            for ids in self.finish:
                end.append(self.get_node_by_id(ids))
            
            self.BFS(start, end)
            
        return self.paths

    def searchDFS(self):
        '''
        High level DFS functions caller
        '''
        for player in self.players:
            start = self.get_node_by_id(player)
            end = []
            for ids in self.finish:
                end.append(self.get_node_by_id(ids))
            
            path=[]
            visited=set()
            self.paths.append(self.DFS(start,end,path,visited))
        
        return self.paths

    def searchGCA(self):
        '''
        High level GCA search functions caller
        '''
        #TODO: tirar for loop
        # o loop corre a procura para um player de cada vez
        # é suposto adaptar o algoritmo para receber a lista de players (self.players) e ele próprio iterar por cada um deles

        # for player in self.players:
        #     start = self.get_node_by_id(player)
        start_nodes = [self.get_node_by_id(p) for p in self.players]
        self.players_cars = [car(p.getId(), p.getPosX(), p.getPosY(), (0, 0), (0, 0), p) for p in start_nodes]

        # este loop pode manter-se, só pega nos ids dos nodos da meta e coloca numa lista de nodos para passar ao BFS
        end = []
        for id in self.finish:
            end.append(self.get_node_by_id(id))
            
        self.GCA(end)
        self.get_inbetweeners()
        
        return (self.complete_paths,self.paths)

    def searchAestrela(self):
        '''
        High level A* search functions caller
        '''
        for p in self.players:
            start = self.get_node_by_id(p)
            
            end = []
            for id in self.finish:
                end.append(self.get_node_by_id(id))
           
            self.paths.append(self.Aestrela(start, end))

        #self.get_inbetweeners()
        return self.paths

    def searchAstar(self):
        '''
        High level A* search functions caller
        '''
        start_nodes = [self.get_node_by_id(p) for p in self.players]
        self.players_cars = [car(p.getId(), p.getPosX(), p.getPosY(), (0, 0), (0, 0), p) for p in start_nodes]
            
        end = []
        for id in self.finish:
            end.append(self.get_node_by_id(id))
            
        self.Astar(end)
        self.get_inbetweeners()
        return (self.complete_paths,self.paths)
    
    def searchGreedy(self):
        '''
        High level Greedy search functions caller
        '''
        start_nodes = [self.get_node_by_id(p) for p in self.players]
        self.players_cars = [car(p.getId(), p.getPosX(), p.getPosY(), (0, 0), (0, 0), p) for p in start_nodes]

        end = []
        for id in self.finish:
            end.append(self.get_node_by_id(id))

        self.greedy(end)
        self.get_inbetweeners()

    def get_id_from_position(self, pos):
        return self.map[pos[1]][pos[0]]

    def node_has_player(self,node):
        return node.getType() == "PLAYER"

    def valid_position(self, pos):
        # return (0 <= pos[0] < self.map_width) and (0 <= pos[1] < self.map_height) and not self.node_has_player(self.get_node_by_id(self.get_id_from_position(pos)))
        return (0 <= pos[0] < self.map_width) and (0 <= pos[1] < self.map_height) and pos not in [p.getPos() for p in self.players_cars]

    # calculas as posições que o carro alcança para as possíveis acelerações dando a sua velocidade e posição
    def get_reachable(self, car_in):
        r = []
        acel = [(1, 1), (1, 0), (1, -1), (0, 1), (0, 0),
                (0, -1), (-1, 1), (-1, 0), (-1, -1)]

        # para todas as acelerações possíveis, coloca numa lista as posições para onde o player pode ir
        for a in acel:
            c = car(0, car_in.getPosX(), car_in.getPosY(), a, car_in.getVel())
            c.next_position()
            if self.valid_position(c.getPos()):
                node_id = self.get_id_from_position(c.getPos())
                r.append((self.get_node_by_id(node_id), c,
                         not self.check_wall(car_in, c)))
                # if self.check_wall(car_in, c):
                #     r.append((self.get_node_by_id(node_id), c))
                # self.path.append(self.get_node_by_id(node_id))

        return r

    def check_wall(self, c1, c2):
        for p in plotLine(c1.getPos(), c2.getPos()):
            if self.get_node_by_id(self.get_id_from_position(p)).getType() == "WALL":
                return False
        return True

    def BFS(self, start, end):
        '''
        Breadth-First algorithm
        Parameters:
        start (NODE) : Starting position NODE
        end (NODE) : NODE target
        Returns:
        final path (node list)
        '''
        #TODO: criar ciclo a preparar queues, parents e sets para todos os jogadores//carros
        #TODO: colocar estes data sets como atributos dos carros
        path = []

        visited = set()
        visited.add(start)
        q = Queue()
        q.put(start)
        u = None

        parent = dict()
        parent[start] = None

        path_found = False

        
        
        while not q.empty():
            #TODO: loop a iterar pelos vários players
            #TODO: verificação se todos os players têm a queue vazia
            u = q.get()
            if u in end:
                path_found = True
                break

            for (adjacente,custo) in self.g_graph[u.getId()]:
                if adjacente not in visited:
                    if adjacente.getType() != "WALL":
                        visited.add(adjacente)
                        q.put(adjacente)
                        parent[adjacente] = u
            #TODO: reordenar a lista de players por velocidades dos carros
            #TODO: função de comparação de velocidades (somas dos absolutos das componentes das velocidades dos dois carros)
        

        if path_found:
            path.append(u)
            while u != start:
                path.append(parent[u])
                u = parent[u]

            path.reverse()
            self.paths.append(path)
        return path

    def GCA(self, target_nodes):
        '''
        Breadth-First algorithm

        Parameters:
        start (NODE) : Starting position NODE
        end (array of NODES) : Array that contains NODES of finish line

        Returns:
        final path (node list)
        '''
        for p in self.players_cars:
            p.path = []

            # Set of visited nodes to prevent loops
            p.visited = set()
            p.queue = Queue()

            # Add the start_node to the queue and visited list
            p.visited.add(p.start_node)
            p.queue.put((p.start_node, p, False))

            # start_node has no parents
            p.parent = dict()
            p.parent[p.start_node] = None
            p.current_node = None
            
            p.path_found = False


        while any([not (p.queue.empty() or p.path_found) for p in self.players_cars]):
            for p in self.players_cars:
                if p.path_found:
                    continue

                (p.current_node, c, crash) = p.queue.get()

                if crash:
                    previous_node = p.parent[p.current_node]
                    new_car = car(previous_node.getId(), previous_node.getPosX(
                    ), previous_node.getPosY(), (0, 0), (0, 0))
                    p.queue.put((previous_node, new_car, False))
                    continue

                if p.current_node in target_nodes:
                    p.path_found = True
                    continue

                # procura nos nodos "possíveis"
                # se algum dos nodos no caminho corresponde a WALL volta para a última posição
                for (next_node, new_car, crash) in self.get_reachable(c):
                    if next_node not in p.visited:
                        p.queue.put((next_node, new_car, crash))
                        p.parent[next_node] = p.current_node
                        p.visited.add(next_node)

            self.players_cars = sorted(self.players_cars, key=lambda x: abs(x.vel[0]) + abs(x.vel[1]), reverse=True)

        # Path reconstruction
        for p in self.players_cars:
            if p.path_found:
                p.path.append(p.current_node)
                while p.current_node != p.start_node:
                    p.path.append(p.parent[p.current_node])
                    p.current_node = p.parent[p.current_node]
                p.path.reverse()
                self.paths.append(p.path)

        # print([p.path for p in self.players])
        return [p.path for p in self.players_cars]

    def greedy(self, target_nodes):
        # open_list é uma lista de nodos visitados, mas com vizinhos
        # que ainda não foram todos visitados, começa com o  start
        # closed_list é uma lista de nodos visitados
        # e todos os seus vizinhos também já o foram
        for p in self.players_cars:
            p.open_list = set([p.start_node])
            p.closed_list = set([])

            # parents é um dicionário que mantém o antecessor de um nodo
            # começa com start
            p.parents = {}
            p.parents[p.start_node] = p.start_node

        # while len(open_list) > 0:
        while any([len(p.open_list) > 0 for p in self.players_cars]):
            for p in self.players_cars:
                if len(p.open_list) <= 0 or p.path_found:
                    continue
                
                if crash:
                    previous_node = p.parent[p.current_node]
                    new_car = car(previous_node.getId(), previous_node.getPosX(
                    ), previous_node.getPosY(), (0, 0), (0, 0))
                    p.queue.put((previous_node, new_car, False))
                    continue

                new_car = car(previous_node.getId(), previous_node.getPosX(), previous_node.getPosY(), (0, 0), (0, 0))
                n = None

                # encontraf nodo com a menor heuristica
                for v in p.open_list:
                    if n == None or self.m_h[v] < self.m_h[n]:
                        n = v

                if n == None:
                    print('Path does not exist!')
                    return None

                # se o nodo corrente é o destino
                # reconstruir o caminho a partir desse nodo até ao start
                # seguindo o antecessor
                if n in target_nodes:
                    p.path_found = True
                    p.path = []

                    while p.parents[n] != n:
                        p.path.append(n)
                        n = p.parents[n]

                    p.path.append(p.start)

                    p.path.reverse()

                    p.custo = self.calculate_cost(p.path)

                # para todos os vizinhos  do nodo corrente
                for (m, weight) in self.get_reachable(n):
                    # Se o nodo corrente nao esta na open nem na closed list
                    # adiciona-lo à open_list e marcar o antecessor
                    if m not in p.open_list and m not in p.closed_list:
                        p.open_list.add(m)
                        p.parents[m] = n

                # remover n da open_list e adiciona-lo à closed_list
                # porque todos os seus vizinhos foram inspecionados
                p.open_list.remove(n)
                p.closed_list.add(n)

            self.players_cars = sorted(self.players_cars, key=lambda x: abs(x.vel[0]) + abs(x.vel[1]), reverse=True)

        print('Path does not exist!')
        return None

    def calculate_cost(self, caminho):
        # caminho é uma lista de nodos
        teste = caminho
        custo = 0
        i = 0
        while i + 1 < len(teste):
            custo = custo + self.get_arc_cost(teste[i], teste[i + 1])
            #print(teste[i])
            i = i + 1
        return custo

    def Aestrela(self, start, end):
        # open_list é uma lista de nodos visitados, mas com vizinhos
        # que ainda não foram todos visitados, começa com o  start
        # closed_list é uma lista de nodos visitados
        # e todos os seus vizinhos também já o foram
        open_list = set([start])
        closed_list = set([])

        # parents é um dicionário que mantém o antecessor de um nodo
        # começa com start
        parents = {}
        parents[start] = start

        distances = {}
        distances[start] = 0

        while len(open_list) > 0:
            n = None

            # encontrar nodo com a menor heuristica + custo
            for v in open_list:
                if n == None or distances[v] + self.g_h[v] < distances[n] + self.g_h[n]:
                    n = v

            if n == None:
                print('Path does not exist!')
                return None

            # se o nodo corrente é o destino
            # reconstruir o caminho a partir desse nodo até ao start
            # seguindo o antecessor
            if n in end:
                reconst_path = []

                while parents[n] != n:
                    reconst_path.append(n)
                    n = parents[n]

                reconst_path.append(start)

                reconst_path.reverse()

                return reconst_path

            # para todos os vizinhos  do nodo corrente
            for (m, weight) in self.g_graph[n.getId()]:
                # Se o nodo corrente nao esta na open nem na closed list
                # adiciona-lo à open_list e marcar o antecessor
                if m not in open_list and m not in closed_list:
                    open_list.add(m)
                    parents[m] = n
                    distances[m] = distances[n] + weight
                else:
                    if distances[m] > distances[n] + weight:
                        distances[m] = distances[n] + weight
                        parents[m] = n
 
                        if m in closed_list:
                            closed_list.remove(m)
                            open_list.add(m)

            open_list.remove(n)
            closed_list.add(n)
        print('Path does not exist!')
        return None

    def searchDFS(self):
        '''
        High level DFS functions caller
        '''
        for player in self.players:
            start = self.get_node_by_id(player)
            end = []
            for ids in self.finish:
                end.append(self.get_node_by_id(ids))
            
            path=[]
            visited=set()
            self.paths.append(self.DFS(start,end,path,visited))
        
        return self.paths
    
    def DFS(self,start, end,path=[],visited=set()):
        '''
        Depth-First algorithm
        Parameters:
        start (NODE) : Starting position NODE
        end list (NODE) : NODE target
        Returns:
        final path (node list)
        '''
        path.append(start)
        visited.add(start)

        if start in end:
            return path
        for (adjacente, peso) in self.g_graph[start]:
            if adjacente not in visited:
                if adjacente.getType() != "WALL":
                    resultado = self.DFS(adjacente, end, path, visited)
                    if resultado is not None:
                        return resultado
        path = []  # se nao encontra remover o que está no caminho......
        return None

    # algoritmo A* mas com velocidade e aceleração, não passou nos testes
    def Astar(self, end=[]):
        '''
        Implementation of informed search algorithm A-star

        Parameters:
        start (String): initial point to start algorithm
        end (Array): list of possible end points to end algorithm

        Return:
        Path from start to end node
        '''
    	
        for p in self.players_cars:
            p.path = []
            # open_list is a list of nodes which have been visited, but who's neighbors
            # haven't all been inspected, starts off with the start node
            # closed_list is a list of nodes which have been visited
            # and who's neighbors have been inspected
            p.open_list = set([p.start_node])
            p.closed_list = set([])
            p.queue.put((p.start_node,p,False))

            # g contains current distances from start_node to all other nodes
            # the default value (if it's not found in the map) is +infinity
            p.g = {}

            p.g[p.start_node] = 0

            # parents contains an adjacency map of all nodes
            p.parents = {}
            p.parents[p.start_node] = p.start_node

            path_found = 0

        for p in self.players_cars:
            while len(p.open_list) > 0:
                n = None
                # find a node with the lowest value of f() - evaluation function
                calc_heurist = {}
                
                for v in p.open_list:
                    if n == None:
                        n = v
                    else:
                        flag = 1
                        calc_heurist[v] = p.g[v] + self.getH(v)
                        min_estima = self.calcula_est(calc_heurist)
                        n = min_estima
                    
                    
                if n == None:
                    print('Path does not exist!')
                    return None


                (p.current_node, c, crash) = p.queue.get()

                if crash:
                    previous_node = p.parents[p.current_node]
                    new_car = car(previous_node.getId(),previous_node.getPosX(), previous_node.getPosY(),(0,0),(0,0))
                    p.queue.put((previous_node,new_car,False))
                    continue

                # if the current node is one of the stop_node
                # then we begin reconstructin the path from it to the start_node
                
                if p.current_node in end:
                    p.path = []

                    while p.parents[p.current_node] != p.current_node:
                        print("primeiro while")
                        p.path.append(p.current_node)
                        p.current_node = p.parents[p.current_node]

                    p.path.append(p.start_node)

                    p.path.reverse()
                    print(p.path)
                    #print('Path found: {}'.format(reconst_path))
                    self.paths.append(p.path)

                # for all neighbors of the current node do
                for (next_node, new_car, crash) in self.get_reachable(c):
                    weight = abs(new_car.getVelL() + new_car.getVelC())
                    # if the current node isn't in both open_list and closed_list
                    # add it to open_list and note n as it's parent
                    if next_node not in p.open_list and next_node not in p.closed_list:
                        p.queue.put((next_node,new_car,crash))
                        p.open_list.add(next_node)
                        p.parents[next_node] = p.current_node
                        p.g[next_node] = p.g[p.current_node] + weight

                    # otherwise, check if it's quicker to first visit n, then m
                    # and if it is, update parent data and g data
                    # and if the node was in the closed_list, move it to open_list
                    else:
                        if p.g[next_node] > p.g[p.current_node] + weight:
                            p.g[next_node] = p.g[p.current_node] + weight
                            p.parents[next_node] = p.current_node

                            if next_node in p.closed_list:
                                p.closed_list.remove(next_node)
                                p.open_list.add(next_node)

                # remove n from the open_list, and add it to closed_list
                # because all of his neighbors were inspected
                p.closed_list.add(p.current_node)
                p.open_list.remove(p.current_node)

            print('Path does not exist!')

        return [p.path for p in self.players_cars]

    def calcula_est(self, estima):
        l = list(estima.keys())
        min_estima = estima[l[0]]
        node = l[0]
        for k, v in estima.items():
            if v < min_estima:
                min_estima = v
                node = k
        return node
    
    def getH(self, nodo):
        if nodo not in self.g_h.keys():
            return 1000
        else:
            return (self.g_h[nodo])

    def in_top_row(self, id):
        row = []
        for x in range(0, self.map_width):
            row.append(x)
        return any(x == id for x in row)

    def in_bottom_row(self, id):
        row = []
        for x in range(self.map_width*(self.map_height-1), (self.map_width*self.map_height)):
            row.append(x)
        return any(x == id for x in row)

    def in_right_column(self, id):
        return (id % self.map_width) == 0

    def in_left_column(self, id):
        return ((id+1) % self.map_width) == 0

    # get node's neighbours ids in form of list
    def search_neighbours(self, id):
        '''
        Function that indicates neightbours of certain node identified by ID

        Parameters:
        id (int): Id of node
        row_length: Length of rows in matrix

        Return:
        Array of node neightbours
        '''
        row_length = self.map_width
        neighbours = []

        # general cases
        if not self.in_top_row(id) and not self.in_left_column(id) and not self.in_right_column(id) and not self.in_bottom_row(id):
            neighbours.append(id-row_length-1)  # diag. top left
            neighbours.append(id-row_length)  # up
            neighbours.append(id+row_length-1)  # diag. bottom left
            neighbours.append(id-row_length+1)  # diag. top right
            neighbours.append(id+row_length+1)  # diag. bottom right
            neighbours.append(id+row_length)  # down
            neighbours.append(id-1)  # right
            neighbours.append(id+1)  # left
        # map edges' cases
        else:
            if not self.in_top_row(id):
                neighbours.append(id-row_length)  # up
            if not self.in_bottom_row(id):
                neighbours.append(id+row_length)  # down
            if not self.in_left_column(id):
                neighbours.append(id+1)  # left
            if not self.in_right_column(id):
                neighbours.append(id-1)  # right
            # corners
            if not self.in_top_row(id) and not self.in_right_column(id):
                neighbours.append(id-row_length+1)  # diag. top right
            if not self.in_top_row(id) and not self.in_left_column(id):
                neighbours.append(id-row_length-1)  # diag. top left
            if not self.in_bottom_row(id) and not self.in_left_column(id):
                neighbours.append(id+row_length-1)  # diag. bottom left
            if not self.in_bottom_row(id) and not self.in_right_column(id):
                neighbours.append(id+row_length+1)  # diag. bottom right

        return neighbours

    def graph2map(self):
        '''
        Method that inserts array of nodes (object) one by one

        Return:
        Matrix of different values
        '''
        self.map_mat = None
        value = 1
        # percorre lista de nodos colocando cada um deles na matriz
        map = np.empty((self.map_height, self.map_width), np.int8)
        for nodo in self.g_nodes.values():
            type = nodo.getType()
            l, c = nodo.getPosY(), nodo.getPosX()
            if type == "PLAYER":
                value = 6
            elif type == "FINISH":
                value = 8
            elif type == "PATH":
                value = 2
            elif type == "WALL":
                value = 1
            map[l, c] = value
        self.map_mat = map
        return map

    def clear_path(self):
        self.complete_paths = []
        self.paths = []
        self.players = []
        self.players_cars = []
    
    def clear_map(self):
        self.g_graph = {}
        self.g_nodes = {}
        self.g_h = {}
        self.finish = []
        self.map = []
        self.map_mat = None
        self.players = []
        self.players_cars = []

    def add_jumps(self, map):
        '''
        Method that adds path to map

        Parameters:
        map (matrix): Map before path

        Return:
        Map after inserting path
        '''
        for path in self.paths:
            for node in path:
                l, c = node.getPosY(), node.getPosX()
                if node != self.get_node_by_id(self.players):
                    map[l, c] = 5
        return map

    def get_inbetweeners(self):
        for path in self.paths:
            complete_path = []
            positions = [(x.getPosY(), x.getPosX()) for x in path]
            positions_pairs = zip(positions, positions[1:])
            lines = [plotLine(x, y) for (x, y) in positions_pairs]
            complete_path_positions = [position for line in lines for position in line][1:]
            for c, l in complete_path_positions:
                complete_path.append(self.get_node_by_id(self.get_id_from_position((l,c))))
            self.complete_paths.append(complete_path)
    
    def add_path(self, map):
        for path in self.paths:
            positions = [(x.getPosY(), x.getPosX()) for x in path]
            positions_pairs = zip(positions, positions[1:])
            lines = [plotLine(x, y) for (x, y) in positions_pairs]
            complete_path_positions = [position for line in lines for position in line][1:]

            for l, c in complete_path_positions:
                map[l, c] = 3

        return map


def plotLineLow(x0, y0, x1, y1):
    dx = x1 - x0
    dy = y1 - y0
    yi = 1
    if dy < 0:
        yi = -1
        dy = -dy
    D = (2 * dy) - dx
    y = y0

    r = []

    for x in range(x0, x1 + 1):
        r.append((x, y))
        if D > 0:
            y = y + yi
            D = D + (2 * (dy - dx))
        else:
            D = D + 2*dy

    return r


def plotLineHigh(x0, y0, x1, y1):
    dx = x1 - x0
    dy = y1 - y0
    xi = 1
    if dx < 0:
        xi = -1
        dx = -dx
    D = (2 * dx) - dy
    x = x0

    r = []

    for y in range(y0, y1 + 1):
        r.append((x, y))
        if D > 0:
            x = x + xi
            D = D + (2 * (dx - dy))
        else:
            D = D + 2*dx

    return r


def plotLine(a, b):
    x0, y0 = a
    x1, y1 = b
    if abs(y1 - y0) < abs(x1 - x0):
        if x0 > x1:
            return plotLineLow(x1, y1, x0, y0)
        else:
            return plotLineLow(x0, y0, x1, y1)
    else:
        if y0 > y1:
            return plotLineHigh(x1, y1, x0, y0)
        else:
            return plotLineHigh(x0, y0, x1, y1)
