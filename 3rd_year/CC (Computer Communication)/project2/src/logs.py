import logging
import copy
import os.path

class Logs:
    '''
    Module that is responsible to create individual logger classes to each log file that exists in the system
    '''
    def __init__(self, filepaths=None, debug="shy", client=False): 
        '''
        Constructor of class responsible of writing logs in all log files
        Parameters:
        filepath (list): List of strings that identify different paths to different log files
        debug (String): String that defines debug mode
                        # if "shy" only insert into file
                        # if "debug" insert into file and print into terminal
        client (Boolean): If its a client or not
        '''
        self.loggers = {}        
        self.path_exists = {}
        self.client = client

        if filepaths != None:
            for filepath in filepaths:
                #no core não é possível ter o absolute path por isso fiz uma função auxiliar core_abspath que mete o path "/home/core/CC32" antes de cada um dos paths
                if self.core_abspath(filepath[1]):
                    self.path_exists[filepath[1]] = True
                else:
                    self.path_exists[filepath[1]] = False

                if filepath[0] in self.loggers:
                    self.loggers[filepath[0]].append(Logger(filepath[1]))
                else:                    
                    self.loggers[filepath[0]] = [Logger(filepath[1])]
        
        if debug != "shy":
            self.loggers["debug"] = [Logger(level="debug")]
        
        if not "all" in self.loggers and filepaths != None and not client:
            if self.core_abspath("logs/all.log"):
                self.path_exists["logs/all.log"] = True
            else:
                self.path_exists["logs/all.log"] = False

            self.loggers["all"] = [Logger(self.core_abspath("logs/all.log"))]
         

        elif self.client:
            if self.core_abspath("logs/all.log"):
                self.path_exists["logs/client.log"] = True
            else:
                self.path_exists["logs/client.log"] = False
            
            self.loggers["all"] = [Logger(self.core_abspath("logs/client.log"))]

    def core_abspath(self, path):
        '''
        Sets the path on the Core, making testing easier
        '''
        return "/home/core/CC32/" + str(path)

    def get_path_exists(self):
        '''
        Returns dictionary of log name to a boolean (String -> Boolean)
        '''
        return copy.deepcopy(self.path_exists)

    def get_logs(self):
        '''
        Returns dictionary of logger's
        '''
        return copy.deepcopy(self.loggers)

    def set_logs(self, lgrs: dict):
        '''
        Sets logs to a list of logs or just append it to the actual one
        Parameters:
        logs (dict): Dictionary that contains list of object logs
        '''
        self.loggers = lgrs

    def write(self, message, logger=None):
        '''
        Method that writes in specific logger obj file

        Parameters:
        msg (String): Message to write in log file
        log (String): Key of logger in self.logs dictionary
        '''
        try:
            for l in self.loggers["all"]:
                l.logger.info(message)

            if "debug" in self.loggers:
                for l in self.loggers["debug"]:
                    l.logger.debug(message)

            if logger != None:
                for l in self.loggers[logger]:
                    l.logger.info(message)
        except Exception as err:
            print(f"ERROR while logging: Logger {err} doesn't exist .")


class Logger:
    '''
    Method that do the function of write the logs in certain file
    '''
    
    def __init__(self, filepath=None, level="shy"):
        '''
        Constructor of class Logger
        Parameters:
        path (String): Path to log file
        debug_mode (String): Debug or Shy mode are the two possible types while writing in log files
        '''
        formatter = logging.Formatter('%(asctime)s:%(msecs)03d: %(message)s', datefmt='%d:%m:%y.%H:%M:%S')

        if level == "shy" and filepath != None:
            # Caminho para o ficheiro de log
            handler = logging.FileHandler(filepath)

            handler.setFormatter(formatter)
            self.logger = logging.getLogger(filepath.replace('.log',''))
            self.logger.addHandler(handler)
            self.logger.setLevel(logging.INFO)

        elif level == "debug" and filepath == None:
            # escrever para o STDOUT
            self.logger = logging.getLogger('Debug')
            handler = logging.StreamHandler()
            handler.setFormatter(formatter)
            self.logger.addHandler(handler)
            self.logger.setLevel(logging.DEBUG)
        else:
            raise Exception('Only one parameter is available: filepath or level.')

        

