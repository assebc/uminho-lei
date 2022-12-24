class Node:

    def __init__(self, id, type, coordx, coordy):
        self.n_id = id
        self.n_type = str(type)  # PLAYER - WALL - PATH - FINISH
        self.n_pos = (coordx, coordy)

    def __str__(self):
        return "node " + str(self.n_id) + " at coords " + str(self.n_pos) + str(self.n_type)

    def __repr__(self):
        return "node :" + str(self.n_id) + str(self.n_pos) + str(self.n_type)

    # id
    def getId(self):
        return self.n_id

    def setId(self, id):
        self.n_id = id

    # type
    def getType(self):
        return self.n_type

    def setType(self, type):
        self.n_type = str(type)

    # position
    def getPos(self):
        return self.n_pos

    def getPosX(self):
        return self.n_pos[0]

    def getPosY(self):
        return self.n_pos[1]

    def setPos(self, pos):
        self.pos = pos

    def setPosX(self, X):
        self.pos = (X, self.n_pos[1])

    def setPosY(self, Y):
        self.pos = (self.n_pos[0], Y)

    def __eq__(self, other):
        # são iguais se o id for igual
        # poderia-se comparar as posições
        return self.n_id == other

    def __hash__(self):
        return hash(self.n_id)
