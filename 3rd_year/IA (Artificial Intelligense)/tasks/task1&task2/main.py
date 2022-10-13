#LICENCIATURA EM ENGENHARIA INFORMÁTICA
#MESTRADO integrado EM ENGENHARIA INFORMÁTICA

#Inteligência Artificial
#2022/23

#Draft Ficha 1


#Importar classes nodo e grafo
from grafo import Graph
from nodo import Node


def main():

    #Criar instância de grafo
    g = Graph()

    #Adicionar vertices ao grafo g
    g.add_edge("s","e",2)
    g.add_edge("s","a",2)
    g.add_edge("e","f",5)
    g.add_edge("a","b",2)
    g.add_edge("b","c",2)
    g.add_edge("c","d",3)
    g.add_edge("d","t",3)
    g.add_edge("g","t",2)
    g.add_edge("f","g",2)


    #cosntrução de menu
    saida = -1
    while saida != 0:
        print("1-Imprimir Grafo")
        print("2-Desenhar Grafo")
        print("3-Imprimir  nodos de Grafo")
        print("4-Imprimir arestas de Grafo")
        print("5-BFS")
        print("6-DFS")
        print("0-Saír")

        saida = int(input("introduza a sua opcao-> "))
        if saida == 0:
            print("saindo.......")
        elif saida == 1:
            #Escrever o grafo como string
            print(g)
            l=input("prima enter para continuar")
        elif saida == 2:
            #Desenhar o grafo de forma gráfica
            g.desenha()
        elif saida == 3:
            #Imprimir as chaves do dicionario que representa o grafo
            print(g.m_graph.keys())
            l = input("prima enter para continuar")
        elif saida == 4:
            #imprimir todas as arestas do grafo
            print(g.imprime_aresta())
            l = input("prima enter para continuar")
        elif saida == 5:
            inicio=input("Nodo inicial->")
            fim=input("Nodo final->")
            print(g.procura_BFS(inicio,fim,path=[]))
            l = input("prima enter para continuar")
        elif saida == 6:
            #Efetuar  pesquisa de caminho entre nodo inicial e final com DFS
            inicio=input("Nodo inicial->")
            fim = input("Nodo final->")
            print(g.procura_DFS(inicio, fim, path=[], visited=set()))
            l = input("prima enter para continuar")
        else:
            print("Opção inválida...")
            l = input("prima enter para continuar")

if __name__ == "__main__":
    main()
