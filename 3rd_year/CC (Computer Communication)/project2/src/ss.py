from parser import Parser
from logs import Logs
from dns_controller import Query
from database import Database
import socket, os.path, sys, threading
import random

class Application:
    '''
    Class that saves the servers or client, individually
    '''
    def __init__(self,argv):
        '''
        Constructor for the SS server

        Parameters:
        argv (list): List that contains all string values given as argument 
        '''

        self.properties = {
            "domain": "", # default domain
            "address": "0.0.0.0", # default address is localhost
            "port": 5353, # normalized port
            "timeout": 255, # default timeout
            "debug_mode": "shy", # shy or debug in debug_mode
            "file_config": "", # path for config file
            "object_config": None,
            "file_log": [], #path for log file
            "logger": Logs(), # object log
            "file_db": "", #path for data base file
            "database": Database(), # object of data base file
            "list_st": [], # list of ST servers
            "list_sp": {}, # dictionary of domains and address that are primary to this server (Domain:Adress)
            "size": 1024, # header 1 KB
            "encoder": "utf-8" # encoder format
        }

        try:
            keys = ["file_config","port","timeout","debug_mode"]
            self.properties = Parser().get_args(self.properties,keys,argv)

            if not os.path.exists(argv[0]):
                raise Exception("Inserted config file path is not valid!")

            self.properties["object_config"] = Parser(self.properties["file_config"],config=True,dict=self.properties)

            #get host's ip address
            self.properties["address"] = str(self.get_ip())
            db = Parser(self.properties["file_db"],db=True,dict=self.properties)
            self.properties["database"] = db.get_db()
            self.properties["logger"] = Logs(self.properties["file_log"],self.properties["debug_mode"],False)
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

    def start_server(self):
        '''
        Method with the responsability of starting a TCP server to interact
        in the transfer zone with main servers in or out of the same domain
        '''
        #print(f"Starting secondary server at " + self.properties["address"]+":"+str(self.properties["port"]))
        self.properties["logger"] = Logs(self.properties["file_log"],self.properties["debug_mode"],False)
        try:
            
            for domain in self.properties["list_sp"].keys():
                if not self.check_db_updated(domain):
                    self.zone_transfer(domain)
                
            #self.properties["logger"].write(f'EV @ connected-at {self.properties["address"]}:{self.properties["port"]}')
        except Exception as error:
            self.properties["logger"].write(f'FL @ {error}')
            exit(0)

        self.start_serverUDP()

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

                # string para ser devolvida ao cliente
                response = str(queryResp)
                
                #query_name = queryResp.getQuery_name()
                dns_msg = response.encode(self.properties["encoder"])
                
                socket.sendto(dns_msg, address)
                
                self.properties["logger"].write(f'RP {address[0]}:{address[1]} {str(dns_msg.decode())}')

            except Exception as error:
                self.properties["logger"].write(f'ER {address[0]}:{address[1]} {error}')


    def check_db_updated(self,domain):
        '''
        Using an DNS message through UDP, verifies if it is necessary to update Database
        '''
        # create query msg
        msg = str(random.randint(1,65535)) + "," + "Q" + "+" + "I" + "," + "0,0,0,0;" + self.properties["domain"] + "," + "ZT" + ";"

        try:
            server = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
            server.settimeout(float(self.properties["timeout"]))
            address = self.properties["list_sp"].get(domain).split(":")
            server.sendto(msg.encode(str(self.properties["encoder"])),(address[0], self.properties["port"]))
        except Exception as error:
            self.properties["logger"].write(f'FL @ {error}')
            exit(0)

        try:
            msg, add = server.recvfrom(int(self.properties["size"]))
            msg2 = msg.decode().replace("\n","").split(";")
            serial = msg2[-2]

            self.properties["logger"].write(f'RR {address[0]}:{self.properties["port"]} database serial {serial}')

        except socket.timeout:
            self.properties["logger"].write(f'TO @ timed-out {address[0]}:{self.properties["port"]}')

        linha = self.properties["database"].get_serial()
        server.close()

        return serial == str(linha)

    def zone_transfer(self,domain):
        '''
        Zone transfer method - makes a request for a copy of it's primary server database
        '''
        address = self.properties["list_sp"].get(domain).split(":")
        server = socket.socket(socket.AF_INET,socket.SOCK_STREAM)
        server.connect((address[0], self.properties["port"]))

        #send domain
        data = domain.encode(self.properties["encoder"])
        server.send(data)

        #recieve lines
        no_lines = int(server.recv(1024).decode(self.properties["encoder"]))

        #send line number check
        no_lines_check = str(no_lines).encode(self.properties["encoder"])
        server.send(no_lines_check)

        #receive db entries
        db_entries = []
        x = 0
        valid = True
        for i in range(no_lines):
            try:
                db_entry = server.recv(4096).decode(self.properties["encoder"])

                splited_entry = db_entry.split(":")
                if int(splited_entry[0]) > x:
                    x = int(splited_entry[0]) #verifica se recebe ordenado
                    db_entries.append(splited_entry[1]) #coloca no registo de entradas
                    try:
                        data = "OK!".encode('utf-8')
                        server.send(data)
                    except Exception as error:
                        self.properties["logger"].write(f'RR @ não consegi enviar confirmação {error}')

                else:
                    self.properties["logger"].write(f'RR @ lost database entry')
                    valid = False
                    break
            except Exception as error:
                self.properties["logger"].write(f'RR @ não recebi entry {error}')
            
            
            

        if valid:
            for entry in db_entries:
                self.properties["database"].insertParsed(entry)
            
            self.properties["logger"].write(f'ZT @ successful')
        server.close()

def main():
    args = []
    i = 1
    while i<5:
        args.append(sys.argv[i])
        i+=1
        
    ss = Application(args)
    ss.start_server()

if __name__ == "__main__":
    main() 