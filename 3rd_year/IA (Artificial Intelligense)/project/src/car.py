from queue import Queue

class car:

    def __init__(self, id, coordx, coordy, acel, vel, start_node=None):
        self.id = id
        self.pos = (coordx, coordy)
        self.acel = acel
        self.vel = vel
        self.visited = set()
        self.queue = Queue()
        self.parent = dict()
        self.path = []
        self.path_found = False
        self.current_node = None
        self.start_node = start_node
        # greedy
        self.open_list = None
        self.closed_list = None
        self.cost = 0

    def __str__(self):
        return "car" + str(self.id) + " at coords " + str(self.pos)

    def __repr__(self):
        return "car : " + str(self.id) + str(self.pos) + str(self.acel) + str(self.vel)

    def __eq__(self, other):
        return self.id == other.id

    def get_current_node(self):
        return self.current_node

    # posição
    def getPos(self):
        return self.pos

    def getPosX(self):
        return self.pos[0]

    def getPosY(self):
        return self.pos[1]

    def setPos(self, pos):
        self.pos = pos

    def setPosX(self, X):
        self.pos = (X, self.pos[1])

    def setPosY(self, Y):
        self.pos = (self.pos[0], Y)

    # aceleracao
    def getAcel(self):
        return self.acel

    def getAcelL(self):
        return self.acel[0]

    def getAcelC(self):
        return self.acel[1]

    def setAcel(self, acel):
        self.acel = acel

    def setAcelL(self, X):
        self.acel = (X, self.acel[1])

    def setAcelC(self, Y):
        self.acel = (self.acel[0], Y)

    # velocidade
    def getVel(self):
        return self.vel

    def getVelL(self):
        return self.vel[0]

    def getVelC(self):
        return self.vel[1]

    def setVel(self, vel):
        self.vel = vel

    def setVelL(self, X):
        self.vel = (X, self.vel[1])

    def setVelC(self, Y):
        self.vel = (self.vel[0], Y)

    def returnPista(self):
        self.vel = (0, 0)

    def next_position(self):
        self.vel = (self.vel[0] + self.acel[0], self.vel[1] + self.acel[1])
        self.pos = (self.pos[0] + self.vel[0], self.pos[1] + self.vel[1])
