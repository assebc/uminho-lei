class Pessoa:
	populacao = 0
	def __init__(self,minhaIdade):
		self.idade = minhaIdade
		Pessoa.populacao+=1

	def get_populacao(self):
		return Pessoa.populacao

	def get_idade(self):
		return self.get_idade

	def __str__(self):
		return str(self.idade)

	def __eq__(self,other):
		return self.idade == other.get_idade

	def __hash__(self):
		return hash(self.idade)