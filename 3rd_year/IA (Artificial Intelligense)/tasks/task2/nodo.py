#LICENCIATURA EM ENGENHARIA INFORMÁTICA
#MESTRADO integrado EM ENGENHARIA INFORMÁTICA

#Inteligência Artificial
#2022/23

#Draft Ficha 1

# Classe nodo para definiçao dos nodos
# Cada nodo tem um nome
# poderá posteriormente ter também informação sobre um objeto a armazenar...

class Node:
    #  construtor do nodo....."
    def __init__(self, name):
        self.m_name = str(name)
        #Posteriormente colocar o objeto que o nodo vai referenciar...

    #Devolve a representação na forma de string do nodo por forma a ser de leitura 'amigável'
    def __str__(self):
        return "node " + self.m_name

    #Devolve representação 'oficial' do objeto, neste caso particular pode ser igual a __str__
    def __repr__(self):
        return "node " + self.m_name

    #Obter o noem de um nodo
    def getName(self):
        return self.m_name

    #Atualizar o nome de um nodo
    def setName(self, name):
        self.m_name=name

    #Método utilizado para comparar dois nodos,
    #neste caso dois nodos são iguais se os nomes forem iguais
    def __eq__(self, other):
        # são iguais se nome igual, não usa o id
        return self.m_name == other.m_name

    #Devolve o hash de um nodo. Ao implementar o método __eq__
    #torna-se também necessário definir __hash__. Caso
    #contrário o objeto torna-se unhashable
    def __hash__(self):
        return hash(self.m_name)
