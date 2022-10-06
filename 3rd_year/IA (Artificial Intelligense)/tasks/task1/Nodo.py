class Nodo:

    def __init__(self,name,id=-1):
        self.name = str(name)
        self.id = id

    def set_id(self, id):
        self.id = id

    def get_id(self):
        return self.id

    def set_name(self,name):
        self.name = name 

    def get_name(self):
        return self.name

    def __str__(self):
        return "node " + self.name 