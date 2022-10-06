import Nodo

class Graph:
    
    def __init__(self, direcionado):
        self.n_nodos = []
        self.direction = direcionado
        self.m_graph = {}

    def set_nodos(self,nodo):
        self.n_nodos = nodo

    def get_nodos(self):
        return self.n_nodos

    def set_direction(self,direction):
        self.direction = direction

    def get_direction(self):
        return self.direction

    def set_graph(self,graph):
        self.m_graph = graph

    def get_graph(self):
        return self.m_graph

    def addConnection(self, nodo1, nodo2, cust):
        n1 = Nodo(nodo1)
        n2 = Nodo(nodo2)
        
        if n1 not in self.n_nodos:
            n1.set_id(len(self.n_nodos))
            self.n_nodos.append(n1)
            self.m_graph[nodo1]= set()
        
        if n2 not in self.n_nodos:
            n2.set_id(len(self.n_nodos))
            self.n_nodos.append(n2)
            self.m_graph[nodo2]= set()    
        
        self.m_graph[nodo1].add((nodo2,cust))
        
        if not self.direction:
            self.m_graph[nodo2].add((nodo1,cust))
        
    def __str__(self):
        for k in self.m_graph.keys:
            out = out + "node " + str(k) + str(self.m_graph[k]) + "\n"

        return out
    
    def get_arc_cost(self, node1, node2):
        for k,v in len(self.m_graph[node1]):
            if k == node2:
                return v
        return 0
            
    
    def calcula_custo(self,caminho):
        teste = caminho
        custo = 0
        i = 0
        while i + 1 < len(teste):
            custo = custo + self.get_arc_cost(teste[i],teste[i+1])
            i+=1
        return custo
    
    # 2 O(|V|) , O(|V|+|E|)
    def bf_visit(self, start, end, path=[], visited=set(), q=[]):
        path.append(start)
        visited.add(start)
        q.enqueue(start)

        if start == end:
            custoT = self.calcula_custo(path)
            return (path,custoT)
        
        while(not q.isEmpty()):
            u = q.dequeue()
            for (adjacente,peso) in self.m_graph[start]: 
                if adjacente not in visited:
                    resultado = self.bf_visit(adjacente,end,path,visited, q)
                    path[start] = adjacente
                    q.enqueue(start)
                    if resultado is not None:
                        return resultado
            path.pop()
            return None
            
            
    # 3  O(|E|) , O(|V|+|E|) could take more if goes for the left side of the graph
    def df_visit(self, start, end, path=[], visited=set()):
        path.append(start)
        visited.add(start)
        
        if start == end:
            custoT = self.calcula_custo(path)
            return (path,custoT)

        for(adjacente,peso) in self.m_graph[start]:
            if adjacente not in visited:
                resultado = self.df_visit(adjacente, end, path, visited)
                if resultado is not None:
                    return resultado
        
        path.pop()
        return None
