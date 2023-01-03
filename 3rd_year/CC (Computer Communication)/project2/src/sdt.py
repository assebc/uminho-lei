import os.path, sys
import time
from logs import Logs
from interpreter import Parser
from dns_controller import Query
from database import Database
from cache import Cache

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
            "address": ".", # default address is localhost
            "port": 5353, # normalized port
            "timeout": 255, # default timeout
            "debug_mode": "shy", # shy or debug in debug_mode
            "file_config": "", # path for config file
            "obj_file_config": None, 
            "sp_address": "", # sp address #TODO: search in config files (dont know how it is suppose to be done)
            "size": 1024, # header 1 KB
            "encoder": "utf-8", # encoder format
            "cache": None, # cache object (BEING IMPLEMENTED)
            "starttime": time.time() # time the server started
        }

        try:
            keys = ["file_config","port","timeout","debug_mode"]
            self.properties = Parser().get_args(self.properties,keys,argv)
            
            if not os.path.exists(argv[0]):
                raise Exception("Inserted config file path is not valid!")


            self.properties["obj_file_config"] = Parser(self.properties["file_config"],config=True,dict = self.properties)

            #get host's ip address
            self.properties["address"] = str(self.get_ip())

            self.properties["cache"] = Cache()
        
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
    
    def start_serverTCP(self):
        '''
        Method that starts a server using TCP protocol
        '''
        try:
            server = socket.socket(socket.AF_INET,socket.SOCK_STREAM)
            server.bind((self.properties["address"],self.properties["port"]))
            server.listen()
        
        except:
            raise Exception

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

        #check if it's from an authority domain

        #receive domain
        request = socket.recv(self.properties["size"]).decode(self.properties["encoder"])

        # create query request
        q_req = Query.readQueryRequest(request)

        # create query response
        q_res = self.properties["cache"].queryFromCache(q_req, self.properties["starttime"])

        # create query response
        q_res = self.properties["cache"].queryFromCache(q_req, self.properties["starttime"])

        origin = "OTHERS"

        # if not in cache
        if q_res.response_code == 2:
            socket.sendto(request, self.properties["sp_address"])
            recv_res = socket.recv(self.properties["size"]).decode(self.properties["encoder"])
            res_flag = int(recv_res.split(";")[0].split(",")[2])

            # check response code if it is possible to insert (0 = success!)
            if res_flag == 0:
                origin = self.insertIntoCache(recv_res)
                q_res = recv_res

            # response code 1 (has to be sent back to client)
            elif res_flag == 1:
                q_res = recv_res

        # send response back
        response = str(q_res).replace("OTHERS", "").replace("SP", "")
        response = response + origin
        socket.send(response)
        socket.close()
        '''
        Pseudo-code of what is suppose

        Search dns query request in self.properties["cache"]
        for i in range(self.properties["cache"].size()):
            self.properties["cache"].searchEntry(i,request,type,starttime)

        if not in self.properties["cache"]:
            socket.sendto(request,self.properties[sp_address])
            request = socket.recv(self.properties["size"]).decode(self.properties["encoder"])
            self.insertIntoCache(request)
        '''

