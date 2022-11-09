import numpy as np
import numpy.random as npr

def objectivo(x):
    return x[0] ** 2.0


def simulated_annealing(objectivo, limites, numero_iteracoes, tamanho_passo, temperatura_inicial):
    melhor = limites[:, 0] + npr.rand(len(limites)) * (limites[:, 1] - limites[:, 0])
    melhor_avaliacao = objectivo(melhor)
    atual, atua_avaliacao = melhor_avaliacao, melhor_avaliacao
    resultados = list()
    for i in range(numero_iteracoes):
        candidato = atual + npr.randn(len(limites)) * tamanho_passo
        candidato_avaliacao = objectivo(candidato)
        if candidato_avaliacao < melhor_avaliacao:
            melhor, melhor_avaliacao = candidato, candidato_avaliacao
            resultados.append(melhor_avaliacao)
            print('> Iteracao: %d, f(%s) = %.5f' % (i, melhor, melhor_avaliacao))
        diferenca = candidato_avaliacao - atua_avaliacao
        t = temperatura_inicial / float(i + 1)
        probabilidade_aceitacao = np.exp(-diferenca / t)
        if diferenca < 0 or npr.rand() < probabilidade_aceitacao:
            atual, atua_avaliacao = candidato, candidato_avaliacao
    return [melhor, melhor_avaliacao, resultados]


npr.seed(1)
limites = np.asarray([[-5.0, 5.0]])
numero_iteracoes = 500
tamanho_passo = 0.1
temperatura_inicial = 10
melhor, resultado, resultados = simulated_annealing(objectivo, limites, numero_iteracoes, tamanho_passo, temperatura_inicial)
print('Fim!')
print('f(%s) = %f' % (melhor, resultado))
