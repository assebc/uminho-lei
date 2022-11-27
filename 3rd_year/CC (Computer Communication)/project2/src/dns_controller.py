import database


class Query:
    '''
    Class that encompasses a query request or response
    '''

    def __init__(self):
        '''
        Constructor of class Query
        '''
        self.message_id = 0             # random ente 1 e 65535
        self.flags = ""                 # Q -> indica que é query, senão e resposta a esta
                                        # R -> indica que o processo é recursivo, por defeito é iterativo
                                        # A -> indica que é autoritativa
        self.response_code = 0          # codigo de erro
        self.n_values = 0               # numero de entradas relevantes (max 255)
        self.n_authorities = 0          # número de entradas de servidores autoritativos
        self.n_extra = 0                # numero de entradas com info adicional
        self.query_name = ""            # nome da query (dominio) && deve ser incluido na resposta
        self.query_type = ""            # tipo da query (mesmos da bd da sp) && deve ser incluido na resposta
        self.values_response = []       # lista das entradas que fizeram match ao name e type na bd
        self.values_authorities = []    # lista das entradas que fizeram match ao name e com type == NS na bd
        self.values_extra = []          # lista das entradas de tipo A e que fizeram match no parametro com todos os valores do response e authotities

    def clone(self):
        query = Query()
        query.message_id = self.message_id
        query.flags = self.flags
        query.n_values = self.n_values
        query.n_authorities = self.n_authorities
        query.n_extra = self.n_extra
        query.query_name = self.query_name
        query.query_type = self.query_type
        query.values_response = self.values_response
        query.values_authorities = self.values_authorities
        query.values_extra = self.values_extra
        return query

    def getQuery_name(self):
        '''
        Getter for the parameter query_name
        '''
        return self.query_name

    # Cria a reposta que o SP envia de volta ao CL

    #TODO: Otimizar esta funcao
    def __str__(self):
        '''
        Creates string to represent a query request or response

        Return: 
        String
        '''
        res = str(self.message_id) + "," + self.flags + "," + str(self.response_code) + "," + str(self.n_values) + "," + \
            str(self.n_authorities) + "," + str(self.n_extra) + ";" + self.query_name + "," + self.query_type + ";"

        # ir buscar os response, autho e extra values

        res = res + "\n"       # debug

        if self.values_response is not None:
            i = 0
            for resp in self.values_response:
                res = res + resp
                if (i < len(self.values_response)-1):
                    res = res + ","
                    i = i + 1
                else:
                    res = res + ";"

        res = res + "\n"       # debug

        if self.values_authorities is not None:
            i = 0
            for auth in self.values_authorities:
                res = res + auth
                if (i < len(self.values_authorities)-1):
                    res = res + ","
                    i = i + 1
                else:
                    res = res + ";"

        res = res + "\n"       # debug

        if self.values_extra is not None:
            i = 0
            for extra in self.values_extra:
                res = res + extra
                if (i < len(self.values_extra)-1):
                    res = res + ","
                    i = i + 1
                else:
                    res = res + ";"

        return res

    def verifyDomainExistance(self,db):
        '''
        Verefies if the domain requested in a query request exists in a relevant record in the Database
        '''
        match self.query_type:
            case "MX":
                if self.query_name not in db.typeMX.keys():
                    return False

            case "A":
                if db.typeMX:
                    if self.query_name not in db.typeNS.keys() or self.query_name not in db.typeMX.keys():
                        return False
                else:
                    if self.query_name not in db.typeNS.keys():
                        return False
            case "NS":
                if self.query_name not in db.typeNS.keys():
                    return False

        return True

    """
        # LEGACY CODE
        def verifyServerExistence(self,db):
        match self.query_type:
            case "MX":
                for vs in db.typeMX.values():
                    for v in vs:
                        if self.query_name == v[0]:
                            return True

            case "NS":
                for vs in db.typeNS.values():
                    for v in vs:
                        if self.query_name == v[0]:
                            return True
            case "A":
                if self.query_name in db.typeA.keys():
                    return True
            case "CNAME":
                if self.query_name in db.typeCN.keys():
                    return True
                else:
                    for vs in db.typeCN.values():
                        for v in vs:
                            if v[0] == self.query_name:
                                return True
        return False
    """

    def readQueryRequest(self,request):
        '''
        Creates a query request from a string from a header
        
        Parameters:
        request: header

        Return: 
        query request
        '''
        split1 = str(request).split(",",7)
        split2 = str(split1[5]).split(";",2)

        self.message_id = int(split1[0])
        self.flags = str(split1[1])
        self.response_code = int(split1[2])
        self.n_values = int(split1[3])
        self.n_authorities = int(split1[4])
        self.n_extra = int(split2[0])
        self.query_name = str(split2[1])

        temp = str(split1[6])
        self.query_type = temp[0 : (len(temp)-1)]

        res = self.clone()

        return res

    def getResponseVal(self, db):
        '''
        Fetches the response values of a query from a database

        Parameters:
        db (String): database

        Return:
        List with all relevant response values
        '''
        resV = []  # lista de tuplos

        # caso de nome dominio
        # if flag == 0:     # LEGACY
        match self.query_type:
            case "MX":
                if self.query_name in db.typeMX.keys():
                    for q in db.typeMX[self.query_name]:
                        resV.append(q)

            case "A":
                if self.query_name in db.typeA.keys():
                    resV.append(db.typeA[self.query_name])
                """
                # Caso de pedir TODOS os valores de A
                for v in db.typeA.values():
                    resV.append(v)
                """

            case "NS":
                if self.query_name in db.typeNS.keys():
                    for q in db.typeNS[self.query_name]:
                        resV.append(q)

            case "CNAME":
                for k, v in db.typeNS.items():
                    if self.query_name == k or self.query_name == v[0]:
                        resV.append(v)
                """
                # Caso de pedir TODOS os valores de CNAME
                for v in db.typeCN.values():
                    resV.append(v)
                """

            # case _:

            #case "PTR":

        # caso de ser nome servidor
        '''
        elif flag == 1:
            match self.query_type:
                case "MX":
                    for vs in db.typeMX.values():
                        for v in vs:
                            if v[0] == self.query_name:
                                resV.append(v[1])

                case "A":
                    if self.query_name in db.typeA.keys():
                        resV.append(db.typeA[self.query_name])

                case "NS":
                    for vs in db.typeNS.values():
                        for v in vs:
                            if v[0] == self.query_name:
                                resV.append(v[1])

                case "CNAME":
                    if self.query_name in db.typeCN.keys():
                        for v in db.typeCN[self.query_name]:
                            resV.append(v[1])
                    else:
                        for vs in db.typeCN.values():
                            for v in vs:
                                if v[0] == self.query_name:
                                    resV.append(v[1])
        '''
        return resV

    def getAuthorVal(self,db):
        '''
            Fetches the authorative values of a query from a database

            Parameters:
            db (String): database path

            Return:
            List with all relevant authorative values
        '''
        # Match nome e tipo NS
        resA = [] # lista de tuplos

        if self.query_type != "NS":
            # nome e dominio
            #if flag == 0:
            if self.query_name in db.typeNS.keys():
                for q in db.typeNS[self.query_name]:
                    resA.append(q)
            # nome e servidor
            #elif flag == 1:
            '''
                for vs in db.typeNS.values():
                    for v in vs:
                        if v[0] == self.query_name:
                            resA.append(v[1])
            '''
        return resA

    def getExtraVal(self,db,chosen):
        '''
            Fetches the extra values of a query from a database

            Parameters:
            db (String): database path

            Return:
            List with all relevant extra values
        '''
        # Match valores escolhidos nos outros values e que sao do tipo A
        resE = [] #lista de tuplos
        for c in chosen:
            if c[0] in db.typeA.keys():
                s = (c[1].split(" "))[2] # pega dominio para substituir
                if s[len(s) - 1] != ".":
                    s = s + "."
                aux = db.typeA[c[0]].replace(c[0],s) # substitui chosen por o seu dominio
                resE.append(aux)
        return resE

    def createQueryResponse(self,db):
        '''
        Creates the response to a query request, using said request as its basis
        '''
        # clona original e altera flag
        res = Query.clone(self)
        res.flags = "A"

        if self.query_type == "ZT":
            serial = str(db.get_serial())
            res.values_response.append(serial)
            res.n_values = len(res.values_response)
            return res


        # nome é dominio
        # LEGACY: if '.' in self.query_name:

        isA = False

        # Safeguard (variavel orignal e so usado para restaurar nome original)
        original = self.query_name

        # response code 2
        if not self.verifyDomainExistance(db):
            res.response_code = 2
            self.query_name = original
            return res

        # para fazer do tipo A e necessario fazer MX e NS
        if self.query_type == "A":
            isA = True
            self.query_type = "MX"

        # pega nos response e author values
        valR = self.getResponseVal(db)
        valA = self.getAuthorVal(db)
        chosen = []

        #print(str(valR) + "\n")        # DEBUG

        #print(str(valA) + "\n")        # DEBUG

        # response code 1 (para tipos diferentes de A)
        if not isA:
            if self.verifyDomainExistance(db) and len(valR)==0:
                res.response_code = 1
                res.values_response = valR
                self.query_name = original
                return res

        # busca valores necessarios para as extra
        for r in valR:
            chosen.append(r)
            res.values_response.append(r[1])

        if valA:
            for a in valA:
                chosen.append(a)
                res.values_authorities.append(a[1])

        # pega nos valores extra
        res.values_extra = self.getExtraVal(db,chosen)

        # reformar resposta a tipo A
        if isA:
            res.query_type = self.query_type = "A"
            res.values_response = self.values_response = res.values_extra
            res.values_extra = self.values_extra = []

            # response code 1 (para tipo A)
            if self.verifyDomainExistance(db) and len(res.values_response) == 0:
                res.n_values = len(res.values_response)
                res.n_authorities = len(res.values_authorities)
                res.n_extra = len(res.values_extra)
                res.response_code = 1
                self.query_name = original
                return res

        # define numero de valores encontrados
        res.n_values = len(res.values_response)
        res.n_authorities = len(res.values_authorities)
        res.n_extra = len(res.values_extra)

        # Safeguard (restauro do nome original)
        self.query_name = original


        """
        # LEGACY CODE
        # nome é servidor
        else:
            # response code 2
            if not self.verifyServerExistence(db):
                res.response_code = 2
                return res

            # pega nos response e author values
            res.values_response = self.getResponseVal(db, 1)
            res.values_authorities = self.getAuthorVal(db, 1)


            # response code 1
            if self.verifyDomainExistance(db) and res.values_response is None:
                res.response_code = 1
                return res

            # pega nos valores extra
            self.values_extra = []
            if (self.query_type != "A"):
                if self.query_name in db.typeA.keys():
                    res.values_extra.append(db.typeA[self.query_name])

            res.n_extra = len(res.values_extra)
            res.n_values = len(res.values_response)
            res.n_authorities = len(res.values_authorities)
        """

        return res

