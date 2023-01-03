class Database:
    '''
    Module database with the responsability of creating and reading database atributes at .txt file
    '''
    def __init__(self):
        '''
        Constructor of class Database
        '''
        self.defaults = {}  #key: macro               value: what to replace with
        self.soaSp = ""
        self.soaAdmin = ""
        self.soaSerial = ""
        self.soaRefresh = ""
        self.soaRetry = ""
        self.soaExpire = ""
        self.typeNS = {}    #key: name domain         value: tuple (word to match with extra,rest of line with substitutions)
        self.ipNS = {}      #key: ns name             value: IP of said ns
        self.ipWWW = {}     #key: www name            value: IP of said www
        self.typeA = {}     #key: first word          value: rest of line with substitutions
        self.typeMX = {}    #key: name domain         value: tuple (word to match with extra,rest of line with substitutions)
        self.typeCN = {}    #key: synonym             value: name to replace with
        self.typePTR = {}   #key: ip_adress           value: name server of certain ip address

    def __str__(self):
        return str(self.defaults) + "\n" +\
                str(self.soaSp) + "\n" +\
                str(self.soaAdmin) + "\n" +\
                str(self.soaSerial) + "\n" +\
                str(self.soaRefresh) + "\n" +\
                str(self.soaRetry) + "\n" +\
                str(self.soaExpire) + "\n" +\
                str(self.typeNS) + "\n" +\
                str(self.ipNS) + "\n" +\
                str(self.ipWWW) + "\n" +\
                str(self.typeA) + "\n" +\
                str(self.typeMX) + "\n" +\
                str(self.typeCN) + "\n" +\
                str(self.typePTR) + "\n"

    def get_serial(self):
        '''
        Feteches the SOASERIAL
        '''
        return self.soaSerial

    def get_NS_addresses(self):
        '''
        Fetches all the IP adresses of the Name Servers
        '''
        ret = []
        for ns in self.ipNS.items():
            ret.append(ns[1])
        return ret
    
    def get_WWW_addresses(self):
        '''
        Fetches all the IP addresses of the WWW Servers
        '''
        ret = []
        for www in self.ipWWW.items():
            ret.append(www[1])
        return ret

    def macroReplace(self,line):
        '''
        Replaces all the macros established in a database file in a line of said file, with their respective value
        
        Parameters:
        line: line with macros to replace

        Return: 
        line without macros
        '''
        res = line
        for macro in self.defaults:
            if macro in res:
                res = res.replace(macro,self.defaults.get(macro))
        return res

    def insertParsed(self,parsed):
        '''
        Given a line that has been parsed from a database file, it inserts its info into the database

        Parameters:
        parsed: line parsed from database file
        '''

        parsed = parsed.strip()
        splited = str.split(parsed," ")

        if len(splited) > 1:
            match splited[1]:
                case "DEFAULT":
                    self.defaults[splited[0]] = splited[2].replace("\n","")
                case "SOASP":
                    self.soaSp = self.macroReplace(parsed)
                case "SOAADMIN":
                    self.soaAdmin = self.macroReplace(parsed)
                case "SOASERIAL":
                    self.soaSerial = self.macroReplace(parsed)
                case "SOAREFRESH":
                    self.soaRefresh = self.macroReplace(parsed)
                case "SOARETRY":
                    self.soaRetry = self.macroReplace(parsed)
                case "SOAEXPIRE":
                    self.soaExpire = self.macroReplace(parsed)

                case "NS":
                    key = splited[2].split(".",1)[1]

                    val = (splited[2].split(".",1)[0],self.macroReplace(parsed))

                    if key not in self.typeNS.keys():
                        self.typeNS[key] = list()
                    list.append(self.typeNS[key],val)

                case "MX":
                    key = splited[2].split(".", 1)[1]

                    if key[len(key) - 1] != ".":
                        key = key + "."

                    val = (splited[2].split(".", 1)[0],self.macroReplace(parsed))

                    if key not in self.typeMX.keys():
                        self.typeMX[key] = list()
                    list.append(self.typeMX[key], val)

                case "A":
                    key = splited[0]

                    val = self.macroReplace(parsed)

                    ip = splited[2]

                    if key not in self.typeA.keys():
                        self.typeA[key] = list()
                    list.append(self.typeA[key], val)

                    # self.typeA[key] = val
                    if "ns" in key:
                        self.ipNS[key] = ip
                    elif "www" in key:
                        self.ipWWW[key] = ip

                case "CNAME":
                    key = splited[0]

                    val = splited[2]

                    if key not in self.typeA.keys():
                        self.typeCN[key] = val
                        self.defaults[key] = val

                case "PTR": # rDNS
                    key = splited[0]
                    val = splited[2]

                    if key not in self.typePTR.keys():
                        self.typePTR[key] = val

                case _:
                    pass        # this should be ok
                    #raise Exception("Not valid line type was parsed!")
        else:
            pass

    # checks if entry is in DB
    def checkDB(self,name,value,type):
        match type:
            case "A":
                if name in self.typeA.keys():
                    for val in self.typeA[name]:
                        if val[1] == value:
                            return True
            case "MX":
                if name in self.typeMX.keys():
                    for val in self.typeMX[name]:
                        if val[1] == value:
                            return True
            case "NS":
                if name in self.typeNS.keys():
                    for val in self.typeNS[name]:
                        if val[1] == value:
                            return True

        return False