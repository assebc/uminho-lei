class jarros:
    def __init__(self):
        self.quantidade=(0,0)
    
    def __str__(self):
        return "jarros " + str(self.capacidade)

    def __repr__(self):
        return "jarros " + str(self.capacidade)

    def getQuantidade(self):
        return self.quantidade
    
    def setQuantidade(self,capac):
        self.capacidade = capac