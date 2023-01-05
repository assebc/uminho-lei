import os.path, sys
import re
from ipaddress import ip_address, IPv4Address
from database import Database

class Parser:
    '''
    Class responsible for the most crucial part of this project

    Where we validate the data inside files and associate with servers properties
    and other parameters
    '''
    def __init__(self,filepath="",config=False,st=False,db=False,dict={}):
        '''
        Constructor of class parser, responsable of parse different files

        Parameters:
        filepath (string): Path to certain file that is going to be submitted
        config (boolean): If true, value in filepath is a config file
        st (boolean): If true, value in filepath is a st file
        db (boolean): If true, value in filepath is a db file
        '''
        self.filepath = filepath
        self.config = config
        self.st = st
        self.db = db
        self.db_obj = Database()
        self.lines=[[]]
        self.default = ""
        self.TTL = 0

        if self.filepath != "" and (config or st or db):
            self.check_file(dict)
    
    def setLines(self):
        '''
        Method that get lines from file and insert them in a matrix
        '''
        self.lines = [[]]
        if self.filepath != "":
            f = open(self.filepath, 'r')
            for line in f.readlines():
                if str(line)[0] != '#' and str(line)[0] != '\n' and str(line)[0] != '\r':
                    splited = []
                    for x in str(line).split(' '):
                        splited.append(x.replace('\n','')) 
                    self.lines.append(splited)
                    
            f.close()
    
    def get_db(self):
        '''
        Feteches the Database object
        '''
        return self.db_obj

    def get_args(self,dict,keys,args):
        '''
        Method that reads from terminal all the input values

        Parameters:
        dict (dict): dictionary that contains all properties from server/client
        keys (list): list that contains all keys that could possible change value
        args (string): string with arguments inserted in terminal
        '''
        # keys = ["file_config","port","timeout","debug_mode"]
        # file_config port timeout debug
        a = ""
        i = 0
        for a in args:
            # keys = ["file_config","file_st","port"]
            if "file_st" in keys or "file_sdt" in keys:
                match i:
                    case 0: # obrigatório
                        b = str(a).split('.')
                        if b[1] == "txt":
                            dict[keys[i]] = a
                            i+=1
                        else: 
                            raise Exception("Not a valid config file!")

                    case 1: #obrigatorio
                        b = str(a).split('.')
                        if b[1] == "txt":
                            dict[keys[i]] = a
                            i+=1
                        else: 
                            raise Exception("Not a valid ST file!")

                    case 2: # opcional, se < 1 não é considerado
                        if int(a) >= 1 and int(a) <= 65535:
                            dict[keys[i]] = int(a)
                            i+=1
                        elif int(a) < 1:
                            i+=1
                        else:
                            raise Exception("Not a valid port input!")

            elif "file_config" in keys:
                match i:
                    case 0: # obrigatório
                        b = str(a).split('.')
                        if b[1] == "txt":
                            dict[keys[i]] = a
                            i+=1
                        else: 
                            raise Exception("Not a valid config file!")
                    
                    case 1: # opcional, se < 1 não é considerado
                        if int(a) >= 1 and int(a) <= 65535:
                            dict[keys[i]] = int(a)
                            i+=1
                        elif int(a) < 1:
                            i+=1
                        else:
                            raise Exception("Not a valid port input!")
                    
                    case 2: # timeout under 0 not valid
                        if int(a) >= 0:
                            dict[keys[i]] = int(a)
                            i+=1
                        elif int(a) < 0:
                            i+=1
                        else:
                            raise Exception("Not a valid timeout input!")
                    
                    case 3:
                        if str(a) == "shy" or str(a) == "debug":
                            dict[keys[i]] = str(a)
                        else:
                            raise Exception("Not a valid debug mode input!") 


            else:
                # keys = ["address_server","server_domain","query_name","query_flag"]
                match i:
                    case 0: # obrigatório
                        if self.is_ipv4(str(a)):
                            dict[keys[i]] = str(a)
                            i+=1
                        else: 
                            raise Exception("Not a valid ip server file!")
                    
                    case 1: # obrigatório
                        if self.is_domain(str(a)): # verify for the cases has an '.' or not in the end
                            dict[keys[i]] = str(a)
                            i+=1
                        else:
                            raise Exception("Not a valid server domain input!")
                    
                    case 2: #obrigatório
                        if self.is_query(str(a)):
                            dict[keys[i]] = str(a)
                            i+=1
                        else:
                            raise Exception("Not a valid query input!")

                    case 3: #opcional, default é I
                        if str(a) == 'I' or str(a) == 'R' or str(a) == 'A':
                            dict[keys[i]] = str(a)
                        elif str(a) == '0':
                            return 
                        else:
                            raise Exception("Not a valid query flag input!") 
                               
        return dict

    def check_file(self,dict={}):
        '''
        Method that verifies file coherence

        Parameters:
        dict (dict): Dictionary to insert data into server
        '''
        if self.config or self.st or self.db:
            self.setLines()
            i = 0
            for line in self.lines:
                if line != []:
                    if not self.check_line(line):
                        print(str(line))
                    else:
                        if self.config:
                            self.insertintoServer(dict,line)
                        elif self.db:
                            self.insertintoDB(dict,line)
                        elif self.st:
                            self.insertintoST(dict,line)
                    i+=1
                     
        else:
            raise Exception("File type not defined")
    
    def check_line(self,line):
        '''
        Method that verifies line coherence

        Parameters:
        line(list): List of previous line splitted by white_spaces (' ')

        Returns:
        boolean: given line is coherent
        '''
        if self.config:
            return self.check_config(line)
        elif self.st:
            return self.check_st(line)
        elif self.db:
            match len(line):
                case 3:
                    return self.check_db_len_3(line)
                case 4: 
                    return self.check_db_len_4(line)
                case 5:
                    return self.check_db_len_5(line)
                case _:
                    raise Exception("Number of arguments its different then 4 or 5!")
        else: #Impossible to enter here but lets doble check
            raise Exception("File type not defined!")
    
    def check_config(self,line):
        '''
        Method that validates if given line is a valid config line

        Parameters:
        line (string): File string

        Returns:
        boolean
        '''
        if len(line) == 3:
            match line[1]:
                case "DB":
                    return self.is_domain(line[0]) and os.path.abspath(line[2])  
                case "SP":
                    return self.is_domain(line[0]) and self.is_ipv4(line[2]) 
                case "SS":
                    return self.is_domain(line[0]) and self.is_ipv4(line[2]) 
                case "DD":
                    return self.is_domain(line[0]) and self.is_ipv4(line[2]) 
                case "ST":
                    return line[0]=="root" and os.path.abspath(line[2])
                case "LG":
                    return line[0]=="all" or os.path.abspath(line[2])
                case _:
                    raise Exception("Value in type is invalid!")
        else:
            raise Exception("Number of arguments is different then 3!")

    def check_st(self,line):
        '''
        Method that validates if given line is a valid ST line

        Parameters:
        line (string): File string

        Returns:
        boolean
        '''
        if len(line)==3:
            if line[0] == "." and line[1] == "ST":
                return self.is_ipv4(line[2])
            else:
                raise Exception("Found some invalid values in ST file!")
        else:
            raise Exception("Invalid number of arguments in ST file!")

    def isSDT(self,address):
        '''
        Method that verifies is given address is from SDT

        Parameters:
        address (address): address of possible SDT

        Returns:
        boolean: Is address is SDT or not
        '''
        return re.fullmatch("([a-z0-9]+.[a-z0-9]+)",address) or re.fullmatch("([a-z0-9]+.[a-z0-9]+.)",address) or re.fullmatch("(.+[a-z0-9]+.)",address) or re.fullmatch("(.+[a-z0-9]+)",address)

    def check_db_len_3(self,line):
        '''
        Method that validates if given line with 3 given parameters is a valid DB line

        Parameters:
        line (string): File string

        Returns:
        boolean
        '''
        match line[1]:
            case "DEFAULT":
                if line[0] == "TTL":
                    self.TTL = int(line[2])
                    return True
                elif line[0] == "@":
                    if line[2] == ".":
                        self.default = str(line[2])
                        return True
                    elif not str(line[2]).endswith('.'):
                        if self.is_domain(line[2]):
                            self.default = str(line[2])
                            return True
                        else:
                            raise Exception("Invalid domain!")
                    else:
                        if self.is_domain(line[2]):
                            self.default = str(line[2])
                            return True
                        else:
                            raise Exception("Invalid domain!")
                else:
                    raise Exception("Invalid default value!")
            case _:
                raise Exception("Value in type is invalid!")

    def check_db_len_4(self,line):
        '''
        Method that validates if given line with 4 given parameters is a valid DB line

        Parameters:
        line (string): File string

        Returns:
        boolean
        '''
        match line[1]:
            case "SOASP":
                return self.is_domain(line[0]) and self.is_domain(line[2]) and self.is_TTL(line[3])
            case "SOAADMIN":
                return self.is_domain(line[0]) and self.is_domain(line[2]) and self.is_TTL(line[3])
            case "SOASERIAL":
                return self.is_domain(line[0]) and self.is_TTL(line[2]) and self.is_TTL(line[3])
            case "SOAREFRESH":
                return self.is_domain(line[0]) and self.is_TTL(line[2]) and self.is_TTL(line[3])
            case "SOARETRY":
                return self.is_domain(line[0]) and self.is_TTL(line[2]) and self.is_TTL(line[3])
            case "SOAEXPIRE":
                return self.is_domain(line[0]) and self.is_TTL(line[2]) and self.is_TTL(line[3])
            case "NS":
                return self.is_domain(line[0]) and self.is_domain(line[2]) and self.is_TTL(line[3])
            case "MX":
                return self.is_domain(line[0]) and self.is_domain(line[2]) and self.is_TTL(line[3])
            case "A": 
                return (self.is_chars(line[0]) or self.is_domain(line[0])) and self.is_ipv4(line[2]) and self.is_TTL(line[3])
            case "WWW":
                return self.is_domain(line[0]) and self.is_domain(line[2]) and self.is_TTL(line[3])
            case "CNAME": 
                return self.is_chars(line[0]) and self.is_chars(line[2]) and self.is_TTL(line[3])
            case "PTR":
                return self.is_ipv4(line[0]) and self.is_TTL(line[2]) and self.is_TTL(line[3])
            case _:
                print(line)
                raise Exception("Value in type is invalid!")

    def check_db_len_5(self,line):
        '''
        Method that validates if given line with 5 given parameters is a valid DB line

        Parameters:
        line (string): File string

        Returns:
        boolean
        '''
        match line[1]:
            case "NS":
                return self.is_domain(line[0]) and self.is_domain(line[2]) and self.is_TTL(line[3]) and (self.is_priority(line[4]) or self.is_priority(self.TTL)) # temporary fix
            case "MX":
                return self.is_domain(line[0]) and self.is_domain(line[2]) and self.is_TTL(line[3]) and (self.is_priority(line[4]) or self.is_priority(self.TTL)) # temporary fix
            case "A":
                return self.is_chars(line[0]) and self.is_ipv4(line[2]) and self.is_TTL(line[3]) and (self.is_priority(line[4]) or self.is_priority(self.TTL)) # temporary fix
            case _:
                raise Exception("Value in type is invalid!")

    def is_domain(self,line):
        '''
        Method that checks if given line is a valid domain

        Parameters:
        default (string): Checks if line its an '@' char and if the default value correspond to a specific format
        line (string): Value given in db file to check if is correr

        Returns:
        boolean: given line is a valid domain
        
        '''
        if line == "@":
            return True
        else:
            return re.fullmatch("(.+.)",line) or re.fullmatch("([a-z0-9.]+.)",line) or line == "."

    def is_plus_domain(self,id,line):
        '''
        Method that checks if given line is a valid domain

        Parameters:
        id (int): Defines if domain does not has an '.', in case of 0, has it in case of 1 or in case 2 has an '.' in left side of domain
        line (string): Value given in db file to check if is correr

        Returns:
        boolean: given line is a valid domain
        '''
        if int(id) == 0:
            return re.fullmatch("([a-z0-9]+.[a-z0-9]+.[a-z0-9]+)",line)
        elif int(id) == 1:
            return re.fullmatch("([a-z0-9]+.[a-z0-9]+.[a-z0-9]+.)",line)
        elif int(id) == 2:
            return re.fullmatch("([a-z0-9]+.[a-z0-9]+.[a-z0-9]+.[a-z0-9]+.)",line)

        return False
            
    def is_TTL(self,line):
        '''
        Method that verifies if given string is TTL or a number

        Parameters:
        line (string): String that was submitted to the test

        Returns:
        boolean: given line is TTL or a number
        '''
        if line != "TTL":
            return re.fullmatch("(\\d+)",line)

        return True

    def is_chars(self,line):
        '''
        Method that checks if given string is a random concatenation of chars

        Parameters:
        line (string): String that was submitted to the test

        Returns:
        boolean: given line is random word
        '''
        return re.fullmatch("(\\w+)",line)

    def is_ipv4(self,line):
        '''
        Method that checks if given string is a valid IPv4 

        Parameters:
        line (string): String that could possible be an IPv4

        Returns:
        boolean: given line is an IPv4 address
        '''
        # 0.0.0.0:3333
        splited = line.split('.')
        if int(splited[0]) > 255 or int(splited[1]) > 255 or int(splited[2]) >255:
            return False

        if ':' in splited[3]:
            splits = splited[3].split(':')

            if int(splits[0])> 255 or not(int(splits[1])):
                return False
        
        elif int(splited[3]) > 255:
            return False

        return True   

    def is_priority(self,line):
        '''
        Method that verifies if given string is between 0 and 255

        Parameters:
        line (string): String that was submitted to the test

        Returns:
        boolean: given line is a priority value
        '''
        if str(line) == "TTL": return False
        return int(line)<=255 and int(line)>=0
    
    def is_query(self,q):
        '''
        Method that verifies if query input is valid

        Parameters:
        q (string): String that contains query name

        Returns:
        boolean: given word is a query
        '''
        if str(q) not in ("SOASP","SOAADMIN", "SOASERIAL", "SOAREFRESH", "SOARETRY", "SOAEXPIRE" , "NS" , "A" , "CNAME" , "MX" ,"PTR"):
            return False 
        
        return True

    def insertintoServer(self,dict={},line=[]):
        '''
        Method that inserts into dictionary parameters from a valid line

        Parameters:
        dict (dict): Dictionary of server
        line (array): Array with line parameters
        '''
        match line[1]:
            case "DB":
                dict["domain"] = line[0]
                dict["file_db"] = line[2]
            case "SP":
                dict["list_sp"][str(line[0])] = line[2] #guarda no dicionário os endereços e domínios dos SPs para o qual é SS
            case "SS":
                if str(line[0]) in dict["list_ss"].keys():
                    dict["list_ss"][str(line[0])].append(str(line[2]))
                else:
                    list = [str(line[2])]
                    dict["list_ss"][str(line[0])] = list
            case "ST":
                dict["file_st"] = line[2]
            case "LG":
                dict["file_log"].append(line[2])
            case "DD":
                print("DD to be implemented")
            case _:
                raise Exception("Value in type is invalid!")

    def insertintoDB(self,dict={},line=[]):
        '''
        Method that inserts into dictionary db parameters form a valid line

        Parameters:
        dict (dict): Dictionary of server
        line (array): Array with line parameters
        '''
        full_line = ""
        for i in range(len(line)):
            full_line += str(line[i]) + " "

        self.db_obj.insertParsed(full_line)

    def insertintoST(self,dic={},line=[]):
        '''
        Method that inserts into dictionary parameters from a valid line

        Parameters:
        dict (dict): Dictionary of server
        line (array): Array with line parameters
        '''
        if "list_st" in dic.keys():
            dic["list_st"].append(line[2])
        else:
            dic["list_sdt"].append(line[2])
