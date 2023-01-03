import os.path, sys 
from logs import Logs
from interpreter import Parser
from dns_controller import Query
from cache import Cache

import socket
import time
import threading # needs to support concurrency

class Application:
    '''
    Class that saves the servers or client, individually
    '''
    def __init__(self,argv):
        '''
        Constructor for the SR server

        Parameters:
        argv (list): List that contains all string values given as argument 
        '''

        self.properties = {
            "domain": "", # default domain
            "address": "0.0.0.0", # default address is localhost
            "port": 5353, # normalized port
            "timeout": 255, # default timeout
            "debug_mode": "debug", # debug in debug_mode
            "file_config": "", # path for config file
            "obj_file_config": None, # object for file config
            "file_log": [], # path for list log file
            "logger": Logs(), # object logs
            "file_st": "", # path for file that define ST servers
            "obj_file_st": None, # object for st file
            "list_st": [], # list of ST servers
            "size": 1024, # header 1 KB
            "encoder": "utf-8", # encoder format
            "cache": Cache(), # cache object (BEING IMPLEMENTED)
            "starttime": time.time() # time the server started

        }

        try:
            keys = ["file_config","file_st","port"]
            self.properties = Parser().get_args(self.properties,keys,argv)
            
            if not os.path.exists(argv[0]):
                raise Exception("Inserted config file path is not valid!")
            
            if not os.path.exists(argv[1]):
                raise Exception("Inserted ST file path is not valid!")

            self.properties["obj_file_config"] = Parser(self.properties["file_config"],config=True,dict = self.properties)
            self.properties["obj_file_st"] = Parser(self.properties["file_st"],st=True,dict = self.properties)

            #get host's ip address
            self.properties["address"] = str(self.get_ip())
            
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

    def insertIntoCache(self,data):
        '''
        Method that insert data into cache using Cache entry function

        Parameters:
        data (String): message to be inserted
        '''
        try:
            '''
            # update entries
            self.properties["cache"].searchEntry(0,"DUMMY","DUMMY",self.properties["starttime"])
            '''

            # clean white space
            data.rstrip()
            # get all data
            info = data.split(";")
            # cache name
            name = info[1].split(",")[0]
            # holds all values, seperated in arrays
            vals = []
            i = 2
            while i < len(info) - 1:
                vals.append(info[i].split(","))
                i += 1

            # origin
            origin = info[i]

            # each array in vals
            for val in vals:
                if val is not None:
                    # each value entry
                    for v in val:
                        # TODO: Priority!!!!!!
                        priority = 0
                        # entry type
                        type = v.split(" ")[1]
                        # creates cache entry
                        entry = self.properties["cache"].createEntry(name, type, v, priority, origin,
                                                                     self.properties["starttime"])
                        # update entries
                        self.properties["cache"].searchEntry(0, "DUMMY", "DUMMY", self.properties["starttime"])
                        # inserts entry
                        self.properties["cache"].insertEntry(entry, None, self.properties["starttime"])

            return origin

        except Exception:
            raise Exception

    def getProperties(self):
        '''
        Getter of the dictionary properties

        Returns:
        properties (dict): Dictionary that contains all information about main server
        '''
        return self.properties
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
                # cria query request
                
                queryReq = Query().readQueryRequest(msg.decode())
                
                #query_name = queryReq.getQuery_name()
                self.properties["logger"].write(f'QR {address[0]}:{address[1]} {str(queryReq)}')
                

                # create query response
                q_res = self.properties["cache"].queryFromCache(queryReq, self.properties["starttime"])

                #origin = "OTHERS"
                # if not in cache
                if q_res.response_code == 2:
                    
                    for st in self.properties["list_st"]:
                        
                        
                        #dns_msg = str(msg).encode(self.properties["encoder"])
                        socket.sendto(msg, (str(st),self.properties["port"]))
                        print(st)
                        res, _ = socket.recvfrom(self.properties["size"])
                        
                        recv_res = res.decode()
                        
                        res_flag = int(recv_res.split(";")[0].split(",")[2])
                         
                        while res_flag != 0:
                            
                            # response code 1 (has to be sent back to client)
                            if res_flag == 1:
                                q_res = recv_res
                            
                            elif res_flag == 3:
                                q_res = recv_res
                                print("AAA")
                                lista = self.parse_addresses(q_res.split(";"))
                                print("BBB")
                                print(lista)
                                for endereco in lista:
                                    print(endereco)
                                    socket.sendto(msg, (str(endereco),self.properties["port"]))
                                    res, _ = socket.recvfrom(self.properties["size"])
                                    recv_res = res.decode()
                                    res_flag = int(recv_res.split(";")[0].split(",")[2])

                        # check response code if it is possible to insert (0 = success!)
                        if res_flag == 0:
                            # origin = self.insertIntoCache(recv_res)
                            self.insertIntoCache(recv_res)
                            q_res = recv_res
                            break

                # send response back to client
                response = str(q_res).replace("OTHERS", "").replace("SP","")
                socket.sendto(response, (str(address[0]),self.properties["port"]))
                self.properties["logger"].write(f'RP {address[0]}:{address[1]} {str(response.decode())}')

            except Exception as error:
                self.properties["logger"].write(f'ER {address[0]}:{address[1]} {error}')
                
            socket.close()

    def parse_addresses(self, lista):
        print(lista)
        lista_servidores = lista[-1].split(",")
        print(lista_servidores)
        enderecos = []
        for servidor in lista_servidores:
            enderecos.append(servidor.split(" ")[-1])
        return enderecos


    def iterative_search(self, socket, address_list):
        #origin = "OTHERS"
            # if not in cache
            if q_res.response_code == 2:
                for st in self.properties["list_st"]:
                    socket.sendto(msg.decode(), self.properties[st])
                    recv_res = socket.recv(self.properties["size"]).decode(self.properties["encoder"])
                    res_flag = int(recv_res.split(";")[0].split(",")[2])

                    # check response code if it is possible to insert (0 = success!)
                    if res_flag == 0:
                        # origin = self.insertIntoCache(recv_res)
                        self.insertIntoCache(recv_res)
                        q_res = recv_res
                        break

                    # response code 1 (has to be sent back to client)
                    elif res_flag == 1:
                        q_res = recv_res

def main():
    args = []
    i = 1
    while i<3:
        args.append(sys.argv[i])
        i+=1
        
    sr = Application(args)
    sr.start_serverUDP()

if __name__ == "__main__":
    main()
    
