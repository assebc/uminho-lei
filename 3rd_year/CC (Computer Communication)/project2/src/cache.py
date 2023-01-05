import time
import database
import dns_controller

class Entry:
    def __init__(self):
        self.name = ""
        self.type = ""
        self.value = ""
        self.ttl = 0
        self.order = 0
        self.origin = ""            # ignorar origin FILE (ja esta na db)
        self.timestamp = 0.0
        self.status = "FREE"

    def clone(self):
        entry = Entry()
        entry.name = self.name
        entry.type = self.type
        entry.value = self.value
        entry.ttl = self.ttl
        entry.order = self.order
        entry.origin = self.origin
        entry.timestamp = self.timestamp
        entry.status = self.status
        return entry

    def __str__(self):
        return str(self.name) + " | " +\
                str(self.type) + " | " +\
                str(self.value) + " | " +\
                str(self.ttl) + " | " +\
                str(self.order) + " | " +\
                str(self.origin) + " | "+\
                str(self.timestamp) + " | " +\
                str(self.status)
class Cache:

    def __init__(self):
        self.storage = [Entry()] * 20

    def __str__(self):
        res = ""
        i = 0
        while i < len(self.storage):
            res = res + str(i+1) + ": " + str(self.storage[i]) + "\n"
            i += 1
        return res

    # create cache entry from db entry to insert
    def createEntry(self,key,type,value,priority,origin,starttime):
        res = Entry()
        res.name = key
        res.type = type
        res.value = value
        res.ttl = int(value.split(" ")[3])
        res.order = priority
        res.origin = origin
        res.timestamp = time.time() - starttime
        res.status = "VALID"

        return res

    # searches for a certain entry in cache
    def searchEntry(self, index, name, type, starttime):

        i = index
        flagR1 = 0
        flagR2 = 0
        while i < len(self.storage):
            if self.storage[i].origin == "OTHERS" and time.time() - starttime - self.storage[i].timestamp > self.storage[i].ttl:
                self.storage[i].status = "FREE"

            if self.storage[i].name == name and self.storage[i].type == type:
                return i
            elif self.storage[i].name == name and self.storage[i].type != type:
                flagR1 += 1
            else:
                flagR2 += 1

            i += 1

        # resCode 1 query
        if flagR1 > 0:
            return -1
        # resCode 2 query
        elif flagR2 == len(self.storage):
            return -2

        return -3

    # checks if entries are equal
    def twinEntry(self,e1,e2):
        return e1.name == e2.name and e1.type == e2.type and e1.value == e2.value and e1.ttl == e2.ttl and e1.order == e2.order and True

    # insert entry in cache
    # NOTA: antes de inserir, atualizar timestamps fazendo: c.searchEntry(0, "DUMMY", "DUMMY",starttime)
    def insertEntry(self,e,db,starttime):

        i = 0

        # caso i) (FILE)
        if db is not None and db.checkDB(e.name,e.value,e.type) and True:
            return True

        # caso SP
        elif e.origin == "SP":
            while i < len(self.storage):
                if self.storage[i].status == "FREE":
                    self.storage[i] = e
                    return True
                # caso a entry ja existe e ainda esteja válida
                elif e == self.storage[i]:
                    return True
                i += 1

        else:
            reg = -1
            while i < len(self.storage):
                # caso a entry ja existe e ainda esteja válida
                if e == self.storage[i]:
                    return True
                # caso i) (SP) e ii)
                if self.storage[i].status == "FREE":
                    # caso ii)
                    if self.twinEntry(self.storage[i], e):
                        if self.storage[i].origin == "OTHERS":
                            self.storage[i].timestamp = time.time() - starttime
                            self.storage[i].status = "VALID"
                            return True
                        # caso i) (SP)
                        else:
                            return True
                    # caso iii)
                    else:
                        reg = i
                i += 1

            # caso iii)
            if reg != -1:
                e.timestamp = time.time() - starttime
                e.status = "VALID"
                self.storage[reg] = e
                return True

        return False

    # frees entries of name (SS ONLY, when SOAEXPIRE activates)
    def freeNameEntry(self,name):
        i = 0
        while i < len(self.storage):
            if self.storage[i].name == name:
                self.storage[i].status == "FREE"
            i += 1

    # tries to create a query reponse by checking its cache
    def queryFromCache(self,q,starttime):
        res = q.clone()
        # TODO: VERIFICAR AS FLAGS DE UMA QUERY
        i = 0

        while i >= 0:
            i = self.searchEntry(i,q.query_name,q.query_type,starttime)

            if i >= 0:
                res.values_response.append(self.storage[i].value)
                i += 1

        # res codes
        if i == -1:
            res.response_code = 1

        if i == -2:
            res.response_code = 2

        # no server, se esta resposta tiver vazia, ir ver a DB. Se a DB tambem nao tiver
        # mandar para o outro servidor para procurar
        return res

    def queryToCache(self,q,priority,origin,starttime,db):
        array = [q.values_response, q.values_authorities, q.values_extra]
        for val in array:
            if val is not None:
                for e in val:
                    aux = self.createEntry(q.query_name,q.query_type,e,priority,origin,starttime)
                    self.insertEntry(aux,db,starttime)



    #TODO: Criar funcao para criar cache entry a paritr de query request recebida (not sure if needed)

    # LEGACY CODE
    """

            else:
                reg = -1
                while i < len(self.storage):
                    # caso i) (SP) e ii)
                    if self.storage[i].status == "FREE":
                        # caso ii)
                        if self.twinEntry(self.storage[i],e):
                            if self.storage[i].origin == "OTHERS":
                                self.storage[i].timestamp = time.time() - starttime
                                self.storage[i].status = "VALID"
                                return True
                            # caso i) (SP)
                            else:
                                return True
                        # caso iii)
                        else:
                            reg = i
                    i += 1

                # caso iii)
                if reg != -1:
                    e.timestamp = time.time() - starttime
                    e.status = "VALID"
                    self.storage[reg] = e
                    return True


            return False
    """

    """
            else:
                print("else")
                while i >= 0:
                    i = self.searchEntry(i, e.name, e.type)
                    print(str(i))
                    if i >= 0:
                        # caso i) (SP) e ii)
                        if self.storage[i].status == "FREE":
                            # caso ii)
                            print("CASO II")
                            if self.twinEntry(self.storage[i],e):
                                if self.storage[i].origin == "OTHERS":
                                    self.storage[i].timestamp = time.time() - starttime
                                    self.storage[i].status = "VALID"
                                    return True
                                # caso i) (SP)
                                else:
                                    print("true")
                                    return True

                # caso iii)
                print("CASO III")
                reg = -1
                i = 0
                while i < len(self.storage):
                    if self.storage[i].status == "FREE":
                        reg = i
                    i += 1

                # caso iii)
                    print("reg: " + str(reg))
                if reg != -1:
                    e.timestamp = time.time() - starttime
                    e.status = "VALID"
                    self.storage[reg] = e
                    return True

            return False
    """