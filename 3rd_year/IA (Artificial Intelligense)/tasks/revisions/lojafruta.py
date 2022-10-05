class LojaFrutas:

	def __init__(self,nome, precosFruta)
		#nome: Nome da loka de fruta
		#precosFruta: Dicionário com a fruta
		#valor: {'maçãs':2.00,'laranjas':1.50,'pêras':1.75}

		self.precosFruta = precosFruta
		self.nome = nome
		print("Bem vindo à loja de fruta %s"%(nome))


	def getCustoPorKg(self,fruta):
		if fruta not in self.precosFruta:
			return None
		return self.precosFruta(fruta)

	def getPrecoCompras(self,listaCompras):
		custoTolas = 0.0
		for fruta, numKgs in listaCompras:
			custoPorKg = self.getCustoPorKg(fruta)
			if custoPorKg!=None:
				custoTotal+=numKgs*custoPorKg
			return custoTotal

	def getNome(self):
		return self.nome