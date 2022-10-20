#LICENCIATURA EM ENGENHARIA INFORMÁTICA
#MESTRADO integrado EM ENGENHARIA INFORMÁTICA

#Inteligência Artificial
#2022/23

#Draft Ficha 2

#Importar classes nodo e grafo
from grafo import Graph
from nodo import Node

def main():

    #Criar instância de grafo
    g1 = Graph()

    #Adicionar vertices ao grafo g
    g1.add_edge("s","e",2)
    g1.add_edge("s","a",2)
    g1.add_edge("e","f",5)
    g1.add_edge("a","b",2)
    g1.add_edge("b","c",2)
    g1.add_edge("c","d",3)
    g1.add_edge("d","t",3)
    g1.add_edge("g","t",2)
    g1.add_edge("f","g",2)

    #Criar instância de grafo
    g2 = Graph()

    #Adicionar vertices ao grafo g

    g2.add_edge("elvas", "borba", 15)
    g2.add_edge("borba", "estremoz", 15)
    g2.add_edge("estremoz", "evora", 40)
    g2.add_edge("evora", "montemor", 20)
    g2.add_edge("montemor", "vendasnovas", 15)
    g2.add_edge("vendasnovas", "lisboa", 50)
    g2.add_edge("elvas", "arraiolos", 50)
    g2.add_edge("arraiolos", "alcacer", 90)
    g2.add_edge("alcacer", "palmela", 35)
    g2.add_edge("palmela", "almada", 25)
    g2.add_edge("palmela", "barreiro", 25)
    g2.add_edge("barreiro", "palmela", 30)
    g2.add_edge("almada", "lisboa", 15)
    g2.add_edge("elvas", "alandroal", 40)
    g2.add_edge("alandroal", "redondo", 25)
    g2.add_edge("redondo", "monsaraz", 30)
    g2.add_edge("monsaraz", "barreiro", 120)
    g2.add_edge("barreiro", "baixadabanheira", 5)
    g2.add_edge("baixadabanheira", "moita", 7)
    g2.add_edge("moita", "alcochete", 20)
    g2.add_edge("alcochete", "lisboa", 20)

    #Adicionar as heuristicas a cada nodo

    g2.add_heuristica("elvas", 270)
    g2.add_heuristica("borba", 250)
    g2.add_heuristica("estremoz", 145)
    g2.add_heuristica("evora", 95)
    g2.add_heuristica("montemor", 70)
    g2.add_heuristica("vendasnovas", 45)
    g2.add_heuristica("arraiolos", 220)
    g2.add_heuristica("alcacer", 140)
    g2.add_heuristica("palmela", 85)
    g2.add_heuristica("almada", 25)
    g2.add_heuristica("alandroal", 180)
    g2.add_heuristica("redondo", 170)
    g2.add_heuristica("monsaraz", 120)
    g2.add_heuristica("barreiro", 30)
    g2.add_heuristica("baixadabanheira", 33)
    g2.add_heuristica("moita", 35)
    g2.add_heuristica("alcochete", 26)
    g2.add_heuristica("lisboa", 0)


    #construção de menu
    saida = -1
    saida2 = -1
    while saida != 0:
        print("1-Imprimir Grafo")
        print("2-Desenhar Grafo")
        print("3-Imprimir  nodos de Grafo")
        print("4-Imprimir arestas de Grafo")
        print("5-BFS")
        print("6-DFS")
        print("7-Pesquisa Gulosa")
        print("8-Pesquisa A*")
        print("0-Saír")

        saida = int(input("introduza a sua opcao-> "))
        if saida == 0:
            print("saindo.......")
        elif saida == 1:
            #Escrever o grafo como string
            print("1-Grafo 1")
            print("2-Grafo 2")
            saida2 = int(input("introduza a sua opcao-> "))
            if saida2 == 1:
                print(g1)
            elif saida2 == 2:
                print(g2)
            else:
                print("Opção inválida...")
            l=input("prima enter para continuar")
        elif saida == 2:
            #Desenhar o grafo de forma gráfica
            print("1-Grafo 1")
            print("2-Grafo 2")
            saida2 = int(input("introduza a sua opcao-> "))
            if saida2 == 1:
                desenha(g1)
            elif saida2 == 2:
                desenha(g2)
            else:
                print("Opção inválida...")
        elif saida == 3:
            #Imprimir as chaves do dicionario que representa o grafo
            print(g1.m_graph.keys())
            l = input("prima enter para continuar")
        elif saida == 4:
            #imprimir todas as arestas do grafo
            print("1-Grafo 1")
            print("2-Grafo 2")
            saida2 = int(input("introduza a sua opcao-> "))
            if saida2 == 1:
                print(g1.imprime_aresta())
            elif saida2 == 2:
                print(g2.imprime_aresta())
            else:
                print("Opção inválida...")       
            l = input("prima enter para continuar")
        elif saida == 5:
            inicio=input("Nodo inicial->")
            fim=input("Nodo final->")
            print(g1.procura_BFS(inicio,fim,path=[]))
            l = input("prima enter para continuar")
        elif saida == 6:
            #Efetuar  pesquisa de caminho entre nodo inicial e final com DFS
            print("1-Grafo 1")
            print("2-Grafo 2")
            saida2 = int(input("introduza a sua opcao-> "))
            if saida2 == 1:
                inicio=input("Nodo inicial->")
                fim = input("Nodo final->")
                print(g1.procura_DFS(inicio, fim, path=[], visited=set()))
            elif saida2 == 2:
                inicio=input("Nodo inicial->")
                fim = input("Nodo final->")
                print(g2.procura_DFS(inicio, fim, path=[], visited=set()))
            else:
                print("Opção inválida...")
            l = input("prima enter para continuar")
        elif saida == 7:
            # Efetuar  pesquisa de caminho entre nodo inicial e final com Gulosa
            inicio = input("Nodo inicial->")
            fim = input("Nodo final->")
            print(g2.greedy(inicio,fim))
            l = input("prima enter para continuar")
        elif saida == 8:
            # Efetuar  pesquisa de caminho entre nodo inicial e final com Gulosa
            inicio = input("Nodo inicial->")
            fim = input("Nodo final->")
            print(g2.Aestrela(inicio,fim))
            l = input("prima enter para continuar")
        else:
            print("Opção inválida...")
            l = input("prima enter para continuar")



if __name__ == "__main__":
    main()