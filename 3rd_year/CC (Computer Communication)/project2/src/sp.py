import os.path, sys, re
from logs import Logs
from interpreter import Parser
from dns_controller import Query
from database import Database
#import st
#import sdt

import socket 
import threading # needs to support concurrency

class Application:
    '''
    Class that saves the servers or client, individually
    '''
    def __init__(self,argv):
        '''
        Constructor for the SP server

        Parameters:
        argv (list): List that contains all string values given as argument 
        '''

        self.properties = {
            "address": "0.0.0.0", # default address is localhost
            "port": 5353, # normalized port
            "timeout": 25, # default timeout
            "debug_mode": "shy", # shy or debug in debug_mode
            "file_config": "", # path for config file
            "obj_file_config": None, 
            "file_log": [], #path for list log file
            "logger": Logs(), # object logs
            "file_db": "", # path for data base file
            "file_st": "", # path for st file
            "database": Database(), # object database
            "list_ss": {}, # list of address that are secondary to this server (Domain:[Addresses])
            "size": 1024, # header 1 KB
            "encoder": "utf-8", # encoder format
            #"object_st": None, # to implement in recursive query
            #"object_sdt": [None] # to implement in recursive query
        }

        try:
            keys = ["file_config","port","timeout","debug_mode"]
            self.properties = Parser().get_args(self.properties,keys,argv)
            
           

            if not os.path.exists(argv[0]):
                raise Exception("Inserted config file path is not valid!")


            self.properties["obj_file_config"] = Parser(self.properties["file_config"],config=True,dict = self.properties)

            #get host's ip address
            self.properties["address"] = str(self.get_ip())
            db_parser = Parser(self.properties["file_db"],db=True,dict=self.properties)
            self.properties["database"] = db_parser.get_db()
            
            self.properties["logger"] = Logs(self.properties["file_log"], self.properties["debug_mode"],False)
            self.properties["logger"].write(f'ST {self.properties["address"]} {self.properties["port"]} {self.properties["timeout"]} {self.properties["debug_mode"]}')
            self.properties["logger"].write("EV @ conf-file-read " + self.properties["file_config"])
            self.properties["logger"].write("EV @ initialized")
        except:
            raise Exception("Error while initializing")

    def get_ip(self):
        '''
        Feteches its own IP
        '''
        s = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
        s.settimeout(0)
        try:
            # doesn't even have to be reachable
            s.connect(('10.254.254.254', 1))
            IP = s.getsockname()[0]
        except Exception:
            IP = '127.0.0.1'
        finally:
            s.close()
        return IP

    def getDataBase(self):
        '''
        Returns database at the moment
        '''
        return self.properties["database"]

    def getProperties(self):
        '''
        Getter of the dictionary properties

        Returns:
        properties (dict): Dictionary that contains all information about main server
        '''
        return self.properties

    def start_serverTCP(self):
        '''
        Method that starts a server using TCP protocol
        '''
        try:
            server = socket.socket(socket.AF_INET,socket.SOCK_STREAM)
            server.bind((self.properties["address"],self.properties["port"]))
            server.listen()

            self.properties["logger"].write(f'EV @ tcp-listening-on {self.properties["address"]}:{self.properties["port"]}')
        
        except Exception as error:
            self.properties["logger"].write(f'FL @ {error}')
            exit(0)

        while True:
            msg, add = server.accept()
            threading.Thread(target=self.processTCP,args=(msg, add)).start()
            
        server.close()

    def processTCP(self,socket,address):
        '''
        Method that process each connection using TCP

        Parameters:
        connection (Socket): Socket given as message in TCP connection 
        address (String): String of address he is acceptin sockets from
        '''
        #receive domain
        request = socket.recv(self.properties["size"]).decode(self.properties["encoder"])
        
        #check if it's from an authority domain
        if self.valid_zt_request(address):
            
            #get db entries
            (no_lines,lines) = self.get_db_lines()
            data = str(no_lines).encode(self.properties["encoder"])
            socket.send(data)


            #receive confirmation for no. of entries
            response = socket.recv(self.properties["size"])
            check = int(response.decode(self.properties["encoder"]))


            if check == no_lines:
                n = 1
                data = bytes
                for line in lines:
                    try:
                        db_entry = str(n) + ":" + str(line)
                        data = db_entry.encode('utf-8')
                        socket.send(data)
                    except Exception as error:
                        self.properties["logger"].write(f'FL @ tried to send entry {error}')
                    try:
                        msg = socket.recv(self.properties["size"])
                        n += 1
                    except Exception as error:
                        self.properties["logger"].write(f'FL @ tried to read confirmation {error}')
                    
            else:
                self.properties["logger"].write(f'RR @ different number of lines')
            
            
            self.properties["logger"] = Logs(self.properties["file_log"], self.properties["debug_mode"],False)
            self.properties["logger"].write(f'EV @ new-connection-tcp {address[0]}:{address[1]}')

        else:
            self.properties["logger"].write(f'EV @ {address[0]}:{address[1]} not allowed to get database')
        
        socket.close()
        self.properties["logger"].write(f'EV @ close-connection-tcp {address[0]}:{address[1]}')

    def valid_zt_request(self,address):
        '''
        Verifies if the zone transfer request comes from an authorized server
        '''
        ss_list = []

        for list in self.properties["list_ss"].values():
            for ss in list:
                ss_list.append(ss)

        return address[0] in ss_list

    def get_db_lines(self):
        '''
        Feteches the lines from this server's database file, filtering the relevant information into a list, returning it and it's lenght
        '''
        lines = []
        with open(self.properties["file_db"], 'r') as f:
            lines = (line.rstrip() for line in f) 
            lines = list(line for line in lines if line)
            with_comment = [x for x in lines if x.startswith("#")]
            without_comment = [x for x in lines if x not in with_comment]
        
        count = 0
        for line in without_comment:
            count +=1
        return (count,without_comment)

    def start_serverUDP(self):
        '''
        Method that starts a server using UDP protocol
        '''
        serverUDP = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
        serverUDP.bind((self.properties["address"],self.properties["port"]))
        
        self.properties["logger"].write(f'EV @ udp-listening-at {self.properties["address"]}:{self.properties["port"]}')

        threading.Thread(target=self.udp_readSocket,args=(serverUDP,)).start()
    
    def udp_readSocket(self,socket=socket):
        '''
        Method that interact with the UDP message provenient from client

        Parameters:
        socket (socket): message in specific socket
        '''

        while True:
            msg, address = socket.recvfrom(self.properties["size"])

            try:

                #msg e a query do cliente
                # codigo abaixo assume a classe database ja inserida no servidor

                # cria query request

                queryReq = Query().readQueryRequest(msg.decode())
                
                #query_name = queryReq.getQuery_name()
                self.properties["logger"].write(f'QR {address[0]}:{address[1]} {str(queryReq)}')
                

                # executa o query request
                queryResp = queryReq.createQueryResponse(self.properties["database"])

                # string para ser devolvida ao cliente; SP e a origin para efeitos de cache
                response = str(queryResp)
                
                #query_name = queryResp.getQuery_name()
                dns_msg = response.encode(self.properties["encoder"])
                
                socket.sendto(dns_msg, address)
                
                self.properties["logger"].write(f'RP {address[0]}:{address[1]} {str(dns_msg.decode())}')

            except Exception as error:
                self.properties["logger"].write(f'ER {address[0]}:{address[1]} {error}')

def main():
    args = []
    i = 1
    while i<5:
        args.append(sys.argv[i])
        i+=1
        
    sp = Application(args)
    sp.start_serverUDP()
    sp.start_serverTCP()

if __name__ == "__main__":
    main()
    
