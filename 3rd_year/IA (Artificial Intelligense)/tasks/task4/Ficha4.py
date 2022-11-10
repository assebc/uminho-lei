import time
from math import inf as infinito
import random as rd

#Valor atribuido ao jogador Humano
HUMANO = -1
#valor atribuido ao bot/computador
BOT = +1
#definição inicial do tabuleiro 3x3
tabuleiro = [
    [0, 0, 0],
    [0, 0, 0],
    [0, 0, 0],
]

#Função que tem como objetivo avaliar o estado. Se o o bot vencer retorna +1
# Se o humano vencer retorna -1 e em caso de empat retorna 0
def avaliar(estado):
    if verifica_vitoria(estado, BOT):
        return +1
    elif verifica_vitoria(estado, HUMANO):
        return -1
    else:
        return 0


#Funcao que verifica se um determinado jogador ganhou
#Retorna um Booleano, se um dos jogadores (Bot ou humano) tiver ganho
def verifica_vitoria(estado, jogador):
    #representa todos os estados onde é possível ganhar com os valores do tabuleiro no momento atual
    estado_vitoria = [
        [estado[0][0], estado[0][1], estado[0][2]],
        [estado[1][0], estado[1][1], estado[1][2]],
        [estado[2][0], estado[2][1], estado[2][2]],
        [estado[0][0], estado[1][0], estado[2][0]],
        [estado[0][1], estado[1][1], estado[2][1]],
        [estado[0][2], estado[1][2], estado[2][2]],
        [estado[0][0], estado[1][1], estado[2][2]],
        [estado[2][0], estado[1][1], estado[0][2]],
    ]
    #verifica se:
    # se a lista [1, 1, 1] (computador), existe no estados onde é possível ganha, se sim retorna Verdadeiro
    # se a lista [-1, -1, -1] (humano), existe no estados onde é possível ganha, se sim retorna Verdadeiro
    if [jogador, jogador, jogador] in estado_vitoria:
        return True
    return False


#Função que retorna a lista de células vazias num determinado estado
def celulas_vazias(estado):
    #incialização da lista de células vazias , como uma list fazia
    lista_celula_vazias = []
    for x, linha in enumerate(estado):
        for y, celula in enumerate(linha):
            if celula == 0:
                lista_celula_vazias.append([x, y])
    return lista_celula_vazias



#Função responsavel por aplicar o movimento pretendido no tabuleiro
def aplica_movimento(x, y, jogador):
    movimento_valido = False
    #verifica se é uma jogada válida para aquelas coordenadas
    if [x,y] in celulas_vazias(tabuleiro):
        movimento_valido = True
    if movimento_valido:
        #caso seja atualiza o tabuleiro do jogo, com o número do jogador
        # -1 para o humano ou +1 para o computador, retornado Verdadeiro
        tabuleiro[x][y] = jogador
        return True
    return False



#Funçao responsável por imprimir o jogo para a consola
def render(estado, escolha_bot, escolha_humano):

    dict_jogadas = {
        -1: escolha_humano,
        +1: escolha_bot,
        0: ' '
    }
    str_line = '---------------'

    print('\n' + str_line)
    for linha in estado:
        for celula in linha:
            simbolo = dict_jogadas[celula]
            print(f'| {simbolo} |', end='')
        print('\n' + str_line)

#Função onde é invocada a função minimax
def turno_bot(escolha_bot, escolha_humana):

    profundidade = len(celulas_vazias(tabuleiro))


    render(tabuleiro, escolha_bot, escolha_humana)

    if profundidade == 9:
        x = rd.choice([0, 1, 2])
        y = rd.choice([0, 1, 2])
    else:
        movimento = minimax(tabuleiro, profundidade, BOT)
        x, y = movimento[0], movimento[1]

    aplica_movimento(x, y, BOT)
    #time.sleep(2)

#Função em aplicar a escolha do humano
def turno_humano(escolha_bot, escolha_humano):


    # Dicionario dos movimentos validos
    movimento = -1
    movimentos = {
        1: [0, 0], 2: [0, 1], 3: [0, 2],
        4: [1, 0], 5: [1, 1], 6: [1, 2],
        7: [2, 0], 8: [2, 1], 9: [2, 2],
    }

    render(tabuleiro, escolha_bot, escolha_humano)

    while movimento < 1 or movimento > 9:
        try:
            movimento = int(input('Use os números (1..9): '))
            coordenadas = movimentos[movimento]
            movimento_verifica = aplica_movimento(coordenadas[0], coordenadas[1], HUMANO)

            if not movimento_verifica:
                print('Mau movimento')
                movimento = -1
        except(KeyError, ValueError):
            print('Número inválido')

def minimax(tabuleiro,profundidade,jogador):

    if jogador == BOT:
        best = [-1,-1,-infinito]
    else:
        best = [-1,-1,+infinito]

    if profundidade == 0 or (verifica_vitoria(tabuleiro, HUMANO) or verifica_vitoria(tabuleiro, BOT)):
        score = avaliar(tabuleiro)
        return [-1,-1,score]

    for (x,y) in celulas_vazias(tabuleiro):
        tabuleiro[x][y] = jogador
        score = minimax(tabuleiro,profundidade-1,-jogador)
        tabuleiro[x][y] = 0
        score[0], score[1] =x, y
    
        if jogador == BOT:
            if score[2] > best[2]:
                best = score 
        else:
            if score[2] < best[2]:
                best = score
    
    return best

escolha_humano = ''  # X ou O
escolha_bot = ''  # X ou O
primeiro = ''  # se o humano for o primeiro

# O humano escolhe X ou O para jogar
while escolha_humano != 'O' and escolha_humano != 'X':
    try:
        print('')
        escolha_humano = input('Escolha X ou O\nEscolha: ').upper()
    except (KeyError, ValueError):
        print('Simbolo incorreto. Insira um dos simbolos possiveis')

# Define a escolha do computador
if escolha_humano == 'X':
    escolha_bot = 'O'
else:
    escolha_bot = 'X'

while primeiro != 'S' and primeiro != 'N':
    try:
        primeiro = input('Quer ser o primeiro a jogar?[s/n]: ').upper()
    except (KeyError, ValueError):
        print('Escolha invalida. Insira uma letra valida')

# Ciclo responsável pelo desenvolvimento do jogo
while len(celulas_vazias(tabuleiro)) > 0 and not (
    verifica_vitoria(tabuleiro, HUMANO) or verifica_vitoria(tabuleiro, BOT)):
    if primeiro == 'N':
        turno_bot(escolha_bot, escolha_humano) 
        primeiro = ''
    
    turno_humano(escolha_bot, escolha_humano)
    turno_bot(escolha_bot, escolha_humano)

# Messagem de jogo terminado (se o humano venceu , ganhou ou empatou)
if verifica_vitoria(tabuleiro, HUMANO):
    render(tabuleiro, escolha_bot, escolha_humano)
    print('VENCEU!')
elif verifica_vitoria(tabuleiro, BOT):
    render(tabuleiro, escolha_bot, escolha_humano)
    print('PERDEU!')
else:
    render(tabuleiro, escolha_bot, escolha_humano)
    print('EMPATE!')