import random

from logs import Logs
from parser import Parser
from dns_controller import Query

import os, socket, sys, time

class Application:
    '''
    Class that saves the servers or client, individually
    '''
    def __init__(self,argv,id):
        '''
        Constructor for the client

        Parameters:
        argv (list): List that contains all string values given as argument 
        id (int): Define if is creating alias or not
        '''

        if int(id) == 0:  
            os.system("alias " + str(argv[0]) + "=\"python3.10 src/client.py\"")
        else:
            self.properties = {
                "domain": "", # default domain
                "address": "0.0.0.0", # default address is localhost
                "address_server" : "0.0.0.0", # default address is localhost~
                "server_domain" : "", # default server domain
                "query_name" : "", # default query name
                "query_type" : "", # type of query
                "query_flag": "I", # default query flag(s)
                "logger": Logs(),
                "port": 5353, # normalized port
                "timeout": 255, # default timeout
                "debug_mode": "debug", # default debug mode
                "size": 1024, # header 1 KB
                "encoder": "utf-8" # encoder format
            }

            try:
                keys = ["address_server","server_domain","query_name","query_type","query_flag"]
                self.properties = Parser().get_args(self.properties,keys,argv)
            except:
                raise Exception("Error while initializing")
            
    def run_connection(self):
        '''
        Method with the responsability to make connection with server 
        '''

        # msg provavelmetne não vai ser do tipo string mas foi só para não dar erro

        # REVIEW: mensagem a mandar para o dns_controller/servidor (a usar para a query)
        msg = str(random.randint(1,65535)) + "," + "Q"
        
        if (self.properties["query_flag"] != "I"):
            msg = msg + "+" + self.properties["query_flag"]
        msg = msg + "," + "0,0,0,0;" + self.properties["server_domain"] + "," + self.properties["query_name"] + ";" #"," + self.properties["query_type"] + ";"
        #print(msg)        # DEBUG

        # Create message
        try:
            client = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
            client.settimeout(float(self.properties["timeout"]))
 
            connection_start = time.time()
            client.sendto(msg.encode(str(self.properties["encoder"])),(self.properties["address_server"],self.properties["port"]))
            self.properties["logger"] = Logs([], self.properties["debug_mode"], True)
            self.properties["logger"].write(f'QE {self.properties["address_server"]}:{self.properties["port"]} {str(msg)}')

        except Exception as error:
            self.properties["logger"].write(f'FL @ {error}')
            exit(0)

        try:
            msg, add = client.recvfrom(int(self.properties["size"]))
            connection_end = time.time()
            msg2 = msg.decode()  # Resposta ja vem construida    (ºuº)
            self.properties["logger"].write(f'RR {self.properties["address_server"]}:{self.properties["port"]} {str(msg2)}')

        except socket.timeout:
            self.properties["logger"].write(f'TO @ timed-out {self.properties["address_server"]}:{self.properties["port"]}')

def main():
    args = []

    if len(sys.argv)==2 :
        args.append(sys.argv[1])
        client = Application(args,0)
    else:
        args.append(sys.argv[1])
        args.append(sys.argv[2])
        args.append(sys.argv[3])
        args.append(sys.argv[4])
        client = Application(args,1)
        client.run_connection()

if __name__ == "__main__":
    main()