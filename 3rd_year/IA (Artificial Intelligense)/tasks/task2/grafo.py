#LICENCIATURA EM ENGENHARIA INFORMÁTICA
#MESTRADO integrado EM ENGENHARIA INFORMÁTICA

#Inteligência Artificial
#2022/23

#Draft Ficha 1


# Biblioteca de tratamento de grafos necessária para desenhar graficamente o grafo
#import networkx as nx
# Biblioteca de tratamento de grafos necessária para desenhar graficamente o grafo
#import matplotlib.pyplot as plt

#biblioteca necessária para se poder utilizar o valor math.inf  (infinito)
import math
from queue import Queue

# Importar a classe nodo
from nodo import Node

#Definição da classe grafo:
#Um grafo tem uma lista de nodos,
#um dicionário:  nome_nodo -> lista de tuplos (nome_nodo,peso)
#para representar as arestas 
#uma flag para indicar se é direcionado ou não
class Graph:
    # Construtor da classe
    def __init__(self, directed=False):
        self.m_nodes = []   # lista de nodos do grafo
        self.m_directed = directed   # se o grafo é direcionado ou nao
        self.m_graph = {}   #  dicionario para armazenar os nodos, arestas  e pesos
        self.m_h={}         # dicionário para armazenar heuristica para cada nodo



    ##############################
    # Escrever o grafo como string
    ##############################
    def __str__(self):
        out = ""
        for key in self.m_graph.keys():
            out = out + "node " + str(key) + ": " + str(self.m_graph[key]) + "\n"
        return out

    #####################################
    # Adicionar aresta no grafo, com peso
    ####################################
    def add_edge(self, node1, node2, weight):   #node1 e node2 são os 'nomes' de cada nodo
        n1 = Node(node1)     # cria um objeto node  com o nome passado como parametro
        n2 = Node(node2)     # cria um objeto node  com o nome passado como parametro
        if (n1 not in self.m_nodes):
            self.m_nodes.append(n1)
            self.m_graph[node1] = set()
        else:
            n1 = self.get_node_by_name(node1)

        if (n2 not in self.m_nodes):
            self.m_nodes.append(n2)
            self.m_graph[node2] = set()
        else:
            n2 = self.get_node_by_name(node2)

        self.m_graph[node1].add((node2, weight))

        # se o grafo for nao direcionado, colocar a aresta inversa
        if not self.m_directed:
            self.m_graph[node2].add((node1, weight))

    ################################
    # Encontrar nodo pelo nome
    ################################
    def get_node_by_name(self, name):
        search_node = Node(name)
        for node in self.m_nodes:
            if node == search_node:
                return node
            else:
                return None

    ###########################
    # Imprimir arestas
    ###########################
    def imprime_aresta(self):
        listaA = ""
        for nodo in self.m_graph.keys():
            for (nodo2, custo) in self.m_graph[nodo]:
                listaA = listaA + nodo + " ->" + nodo2 + " custo:" + str(custo) + "\n"
        return listaA

    ################################
    # Devolver o custo de uma aresta
    ################################
    def get_arc_cost(self, node1, node2):
        custoT=math.inf
        a=self.m_graph[node1]    # lista de arestas para aquele nodo
        for (nodo,custo) in a:
            if nodo==node2:
                custoT=custo

        return custoT



    ######################################
    # Dado um caminho calcula o seu custo
    #####################################
    def calcula_custo(self, caminho):
        #caminho é uma lista de nomes de nodos
        teste=caminho
        custo=0
        i=0
        while i+1 < len(teste):
             custo=custo + self.get_arc_cost(teste[i], teste[i+1])
             i=i+1
        return custo

    ################################################################################
    # Procura BFS
    ####################################################################################
    def procura_BFS(self,start,end,path=[]):
        visited = set()
        visited.add(start)
        q = Queue()
        q.put(start)

        parent = dict()
        parent[start] = None

        path_found = False
        while not q.empty():
            u = q.get()
            if u == end:
                path_found = True
                break

            for(adjacente,peso) in self.m_graph[u]:
                if adjacente not in visited:
                    visited.add(adjacente)
                    q.put(adjacente)
                    parent[adjacente] = u

        if path_found:
            u = end
            path.append(u)
            while u != start:
                path.append(parent[u])
                u = parent[u]

            path.reverse()

        return (path, self.calcula_custo(path))

    ################################################################################
    # Procura DFS
    ####################################################################################
    def procura_DFS(self,start, end, path=[], visited=set()):
        path.append(start)
        visited.add(start)

        if start == end:
            # calcular o custo do caminho funçao calcula custo.
            custoT= self.calcula_custo(path)
            return (path, custoT)
        for (adjacente, peso) in self.m_graph[start]:
            if adjacente not in visited:
                resultado = self.procura_DFS(adjacente, end, path, visited)
                if resultado is not None:
                    return resultado
        path.pop()  # se nao encontra remover o que está no caminho......
        return None

    ###########################
    # Desenha grafo  modo grafico
    #########################
    def desenha(self):
        ##criar lista de vertices
        lista_v = self.m_nodes
        lista_a = []
        g=nx.Graph()

        #Converter para o formato usado pela biblioteca networkx
        for nodo in lista_v:
            n = nodo.getName()
            g.add_node(n)
            for (adjacente, peso) in self.m_graph[n]:
                lista = (n, adjacente)
                #lista_a.append(lista)
                g.add_edge(n,adjacente,weight=peso)

        #desenhar o grafo
        pos = nx.spring_layout(g)
        nx.draw_networkx(g, pos, with_labels=True, font_weight='bold')
        labels = nx.get_edge_attributes(g, 'weight')
        nx.draw_networkx_edge_labels(g, pos, edge_labels=labels)

        plt.draw()
        plt.show()

    #############################################
    # Adiciona heuristica a nodo
    #############################################

    def add_heuristica(self, n, estima):
            n1 = Node(n)
            if n1 in self.m_nodes:
                self.m_h[n] = estima

    ###################################################
    # Devolve vizinhos de um nó
    ###################################################

    def getNeighbours(self, nodo):
        lista = []
        for (adjacente, peso) in self.m_graph[nodo]:
            lista.append((adjacente, peso))
        return lista

    #############################################
    # Pesquisa gulosa
    #############################################

    def greedy(self, start, end):
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

        while len(open_list) > 0:
            n = None

            # encontraf nodo com a menor heuristica
            for v in open_list:
                if n == None or self.m_h[v] < self.m_h[n]:
                    n = v

            if n == None:
                print('Path does not exist!')
                return None

            # se o nodo corrente é o destino
            # reconstruir o caminho a partir desse nodo até ao start
            # seguindo o antecessor
            if n == end:
                reconst_path = []

                while parents[n] != n:
                    reconst_path.append(n)
                    n = parents[n]

                reconst_path.append(start)

                reconst_path.reverse()

                return (reconst_path, self.calcula_custo(reconst_path))

            # para todos os vizinhos  do nodo corrente
            for (m, weight) in self.getNeighbours(n):
                # Se o nodo corrente nao esta na open nem na closed list
                # adiciona-lo à open_list e marcar o antecessor
                if m not in open_list and m not in closed_list:
                    open_list.add(m)
                    parents[m] = n


            # remover n da open_list e adiciona-lo à closed_list
            # porque todos os seus vizinhos foram inspecionados
            open_list.remove(n)
            closed_list.add(n)

        print('Path does not exist!')
        return None

    #############################################
    # Pesquisa A*
    #############################################

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
                if n == None or distances[v] + self.m_h[v] < distances[n] + self.m_h[n]:
                    n = v

            if n == None:
                print('Path does not exist!')
                return None

            # se o nodo corrente é o destino
            # reconstruir o caminho a partir desse nodo até ao start
            # seguindo o antecessor
            if n == end:
                reconst_path = []

                while parents[n] != n:
                    reconst_path.append(n)
                    n = parents[n]

                reconst_path.append(start)

                reconst_path.reverse()

                return (reconst_path, self.calcula_custo(reconst_path))

            # para todos os vizinhos  do nodo corrente
            for (m, weight) in self.getNeighbours(n):
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
