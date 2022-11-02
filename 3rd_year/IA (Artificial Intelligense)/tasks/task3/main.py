#LICENCIATURA EM ENGENHARIA INFORMÁTICA
#MESTRADO integrado EM ENGENHARIA INFORMÁTICA

#Inteligência Artificial
#2022/23

#Draft Ficha 3

from Graph import Grafo
from nodo import Node
from Baldes import Balde

def main():

    problema=Balde()
    problema.cria_grafo()
    saida = -1

    while saida != 0:
        print("1-Imprimir grafo ")
        print("2-Desenhar Grafo")
        print("3-Imprimir  nodos de Grafo")
        print("4-Imprimir arestas de Grafo")
        print("5-DFS")
        print("6-BFS")
        print("7 -Outra solução ")
        print("0-Saír")

        saida = int(input("introduza a sua opcao-> "))
        if saida == 0:
            print("saindo.......")
        elif saida == 1:
            print(problema.g.m_graph)
            l=input("prima enter para continuar")
        elif saida == 2:
            problema.g.desenha()
        elif saida == 3:
            print(problema.g.m_graph.keys())
            l = input("prima enter para continuar")
        elif saida == 4:
            print(problema.g.imprime_aresta())
            l = input("prima enter para continuar")
        elif saida == 5:
            inicio=input("Nodo inicial->")
            fim = input("Nodo final->")
            caminho=problema.solucaoDFS(inicio, fim)
            print(caminho)
            if caminho != None:
               a = caminho[0]
               lista=problema.imprimeA(a)
               print(lista)
            l = input("prima enter para continuar")
        elif saida == 6:
            inicio = input("Nodo inicial->")
            fim = input("Nodo final->")
            caminho=problema.solucaoBFS(inicio,fim)
            print(caminho)
            if caminho != None:
                a = caminho[0]
                lista = problema.imprimeA(a)
                print(lista)
            l = input("prima enter para continuar")
        elif saida == 7:
            inicio = input("Nodo inicial->")
            fim = input("Nodo final->")
            caminho = problema.encontraDFS(inicio, fim)
            print(caminho)
            if caminho != None:
                a = caminho[0]
                lista = problema.imprimeA(a)
                print(lista)
            l = input("prima enter para continuar")
        else:
            print("you didn't add anything")
            l = input("prima enter para continuar")

if __name__ == "__main__":
    main()
