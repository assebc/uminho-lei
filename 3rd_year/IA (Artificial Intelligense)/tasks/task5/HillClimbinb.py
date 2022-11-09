import numpy as np
import numpy.random as npr
from matplotlib import pyplot


def objectivo(x):
    return x[0] ** 2.0


def hillclimbing(objectivo, limites, numero_iteracoes, tamanho_passo):
    ponto_atual = limites[:, 0] + npr.rand(len(limites)) * (limites[:, 1] - limites[:, 0])
    ponto_atual_avalicao = objectivo(ponto_atual)
    resultados = list()
    resultados.append(ponto_atual)
    for i in range(numero_iteracoes):
        candidato = ponto_atual + npr.randn(len(limites)) * tamanho_passo
        candidato_avaliacao = objectivo(candidato)
        if candidato_avaliacao <= ponto_atual_avalicao:
            ponto_atual, ponto_atual_avalicao = candidato, candidato_avaliacao
            resultados.append(ponto_atual)
            print('Iteracacao: >%d,  f(%s) = %.5f' % (i, ponto_atual, ponto_atual_avalicao))
    return [ponto_atual, ponto_atual_avalicao, resultados]


npr.seed(1)
limites = np.asarray([[-5.0, 5.0]])
numero_iteracoes = 500
tamanho_passo = 0.1
melhor, avalicao, resultados = hillclimbing(objectivo, limites, numero_iteracoes, tamanho_passo)
print('Fim!')
print('f(%s) = %f' % (melhor, avalicao))
